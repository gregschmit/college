import sys
import argparse
import math

class BinaryNumber:

    def __init__(self, value=0, length=32):
        self.value = int(format(value, 'b')[-1*length:], 2)
        self.length = length

    def pull_chunk(self, start, end):
        if start > end: return 0
        if end >= self.length: return 0
        return int(format(self.value, '0' + str(self.length) + 'b')[-1*(end+1):self.length-start], 2)

class Block:

    def __init__(self, set, id=0, tag=0, valid=False):
        self.set = set
        self.id = id
        self.tag = tag
        self.valid = valid
        self.refs = 0

    def set_tag(self, tag, valid=True):
        self.tag = tag
        self.valid = valid
        self.refs = 0

    def __str__(self):
        fmt = '{:#0' + str(len('{:#x}'.format(len(self.set.blocks)-1))) + 'x}'
        return 'block<' + fmt.format(self.id) + '>[' + str(self.set) + ',tag=' + str(self.tag) + ',valid=' + str(self.valid) + ',refs=' + str(self.refs) + ']'


class Access:

    def __init__(self, addr=0, is_hit=False, is_load=False):
        self.addr = addr
        self.is_hit = is_hit    # vs miss
        self.is_load = is_load  # vs store


class Set:

    def __init__(self, cache, id=0, n_blocks=None):
        self.cache = cache
        self.id = id
        if n_blocks:
            self.blocks = []
            for i in range(n_blocks):
                self.blocks.append(Block(self, i))

    def __str__(self):
        fmt = '{:#0' + str(len('{:#b}'.format(len(self.cache.sets)-1))) + 'b}'
        return 'set<' + fmt.format(self.id) + '>'

    def block_lookup(self, tag):
        for block in self.blocks:
            if block.tag == tag:
                # found it
                return block
        return None

    def load_mem(self, tag):
        # assume tag not loaded; LRU policy
        b = self.blocks[0]
        b_first_invalid = None
        for block in self.blocks:
            if block.refs < b.refs:
                b = block
            if not block.valid:
                b = block
                break
        # evict code would be here, but this is a sim
        b.set_tag(tag)
        return b

    def load(self, tag):
        acc = Access(0, True, True)
        b = self.block_lookup(tag)
        acc.is_hit = True if b else False
        if not b: b = self.load_mem(tag)
        b.refs+=1
        return acc

    def store(self, tag, load=False):
        acc = Access(0, True, False)
        b = self.block_lookup(tag)
        acc.is_hit = True if b else False
        if not b and load:
            b = self.load_mem(tag)
            b.refs+=1
        return acc


class VirtualCache:

    def __init__(self, size_kb=16, n_sets=2, block_size=16,
            miss_penalty=40, cpu_frequency=0, write_allocate=False):
        self.size = size_kb * 2**10
        if self.size % block_size:
            sys.stderr.write('Cannot partition cache into blocks.\n')
            sys.exit(1)
        self.n_blocks = self.size // block_size
        if self.n_blocks % n_sets:
            sys.stderr.write('Cannot partition blocks into sets.\n')
            sys.exit(2)
        self.blocks_per_set = self.n_blocks // n_sets
        self.n_sets = n_sets
        self.block_size = block_size
        self.miss_penalty = miss_penalty
        self.cpu_frequency = cpu_frequency
        self.write_allocate = write_allocate
        self.accesses = []
        self.sets = []
        for i in range(self.n_sets):
            self.sets.append(Set(self, i, self.blocks_per_set))

    def is_associative(self):
        return self.blocks_per_set > 1

    def parse_addr(self, addr):
        # addr is memory address
        a = BinaryNumber(addr)
        # get pieces of addr (tag | set/block index | offset)
        offset_size = int(math.log(self.block_size, 2))
        index_size = int(math.log(self.n_sets, 2))
        offset = a.pull_chunk(0, offset_size-1)
        index = a.pull_chunk(offset_size, offset_size+index_size-1)
        tag = a.pull_chunk(offset_size+index_size, 31) # TODO: assumes 32 bits
        return tag, index, offset

    def load(self, addr):
        tag, index, offset = self.parse_addr(addr)
        acc = self.sets[index].load(tag)
        acc.addr = addr
        self.accesses.append(acc)
        return acc

    def store(self, addr):
        tag, index, offset = self.parse_addr(addr)
        acc = self.sets[index].store(tag, self.write_allocate)
        acc.addr = addr
        self.accesses.append(acc)
        return acc

    def print_cache(self):
        for s in self.sets:
            for b in s.blocks:
                print(b)


class CacheSim:

    def __init__(self, filename, cache):
        # extract file and run
        self.filename = filename
        self.cache = cache

    def run(self, print_cache=False):
        f = open(self.filename, 'r')
        hit_cycle = 0
        miss_cycle = vc.miss_penalty
        if vc.block_size == 32:
            miss_cycle += 2
        if vc.block_size == 64:
            miss_cycle += 6
        cycle_counter = 0
        for line in f:
            tokens = line.split()
            if len(tokens) == 3:
                cycle_counter+=int(tokens[2])+1
                if tokens[0] == 's':
                    acc = self.cache.store(int(tokens[1], 16))
                elif tokens[0] == 'l':
                    acc = self.cache.load(int(tokens[1], 16))
                else:
                    pass
                if not acc.is_hit:
                    cycle_counter += miss_cycle
        if print_cache: vc.print_cache()
        size_delay = 1
        if vc.size == 32 * 2**10:
            size_delay = 1.05
        if vc.size == 64 * 2**10:
            size_delay = 1.15
        associative_delay = 1
        if vc.blocks_per_set == 2:
            associative_delay = 1.05
        if vc.blocks_per_set == 8:
            associative_delay = 1.10
        cycle_time = 1/vc.cpu_frequency * size_delay * associative_delay
        print('blocks per set: ' + str(vc.blocks_per_set))
        print('cycles: ' + str(cycle_counter))
        print('cycle_time: ' + str(cycle_time))
        print('total time: ' + str(cycle_time * cycle_counter * 1000) + 'ms')


# main

parser = argparse.ArgumentParser()
parser.add_argument('size_kb', type=int, nargs='?', default=16)
parser.add_argument('n_sets', type=int, nargs='?', default=2)
parser.add_argument('block_size', type=int, nargs='?', default=16)
parser.add_argument('miss_penalty', type=int, nargs='?', default=40)
parser.add_argument('cpu_frequency', type=int, nargs='?', default=1000000000)
parser.add_argument('-w', '--write-no-allocate', action='store_true', default=False)
parser.add_argument('-pc', '--print-cache', action='store_true', default=False)
parser.add_argument('filename')
args = parser.parse_args()

vc = VirtualCache(args.size_kb, args.n_sets, args.block_size, args.miss_penalty, args.cpu_frequency, not args.write_no_allocate)
sim = CacheSim(args.filename, vc)
sim.run(args.print_cache)
