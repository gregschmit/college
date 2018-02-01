# Cost-Contrained Shortest Path City Demo
# Authors:
#  Gregory N. Schmit
#  Rahel Okbit


from sys import argv, exit, stdout
from fileinput import input

# get args
debug = None
if len(argv) == 5:
    script, file, arg_s, arg_d, arg_budget = argv
elif len(argv) == 6:
    script, file, arg_s, arg_d, arg_budget, debug = argv
else:
    print('Improper arguments -- Usage:\n  python cpath.py <datafile> <source> <destination> <budget> [<DEBUG>]')
    exit()

if debug and debug == '1':
    DEBUG = True
else:
    DEBUG = False

class CCSPBinaryMinHeap:

    def __init__(self):
        self.paths = []

    def get_parent(self, index):
        parent = int((index-1)//2)
        if parent < 0:
            parent = None
        return parent

    def get_children(self, index):
        child1 = 2*index + 1
        child2 = child1 + 1
        if child1 >= self.size:
            child1 = None
        if child2 >= self.size:
            child2 = None
        return [child1, child2]

    @property
    def size(self):
        return len(self.paths)

    def swap(self, index1, index2):
        tmp = self.paths[index1]
        self.paths[index1] = self.paths[index2]
        self.paths[index2] = tmp

    def bubble_up(self, index):
        parent = self.get_parent(index)
        if (parent is not None) and (self.paths[index] < self.paths[parent]):
            self.swap(index, parent)
            self.bubble_up(parent)

    def bubble_down(self, index):
        child1, child2 = self.get_children(index)
        indexPath = self.paths[index]
        child1small = False
        child2small = False
        if child1:
            child1Path = self.paths[child1]
            if child1Path < indexPath:
                child1small = True
        if child2:
            child2Path = self.paths[child2]
            if child2Path < indexPath:
                child2small = True
        if child1small and child2small:
            if child1Path < child2Path:
                self.swap(index, child1)
                self.bubble_down(child1)
            else:
                self.swap(index, child2)
                self.bubble_down(child2)
        else:
            if child1small:
                self.swap(index, child1)
                self.bubble_down(child1)
            elif child2small:
                self.swap(index, child2)
                self.bubble_down(child2)
            else:
                pass


    def push(self, path):
        index = self.size
        self.paths.append(path)
        self.bubble_up(index)

    def pop(self):
        self.swap(0, self.size - 1)
        retval = self.paths.pop()
        if self.size:
            self.bubble_down(0)
        return retval

    def print_heap(self):
        # prints heap
        if not self.paths:
            print('[]')
        for path in self.paths:
            print(path)

class Vertex:

    def __init__(self, id):
        self.id = id
        self.CCSPaths = []

    def __eq__(self, other):
        if self is None or other is None:
            if self is None and other is None:
                return True
            else:
                return False
        if self.id == other.id:
            return True
        return False

    def __repr__(self):
        return str(self.id)

    def connected_edges(self, graph, excluded_vertices=[]):
        edges = []
        for edge in graph.edges:
            if edge.end1 == self or edge.end2 == self:
                if (edge.end1 not in excluded_vertices) and (edge.end2 not in excluded_vertices):
                    edges.append(edge)
        return edges

class Edge:

    def __init__(self, u, v, cost=0, time=0):
        self.end1 = u
        self.end2 = v
        self.cost = cost
        self.time = time

    def __eq__(self, other):
        if self.end1 == self.end2:
            return True
        return False

    def __repr__(self):
        return '[' + str(self.end1) + '->' + str(self.end2) + ',c=' + str(self.cost) + ',t=' + str(self.time) + ']'


class Path:

    def __init__(self, edges=[], end=None):
        self.edges = edges
        self.end = end

    def __lt__(self, other):
        if self.cost < other.cost:
            return True
        elif self.cost > other.cost:
            return False
        else:
            if self.time < other.time:
                return True
            else:
                return False

    @property
    def tail_vertices(self):
        vertices = []
        for edge in self.edges:
            if (edge.end1 not in vertices) and (edge.end1 is not self.end):
                vertices += [edge.end1]
            if (edge.end2 not in vertices) and (edge.end2 is not self.end):
                vertices += [edge.end2]
        return vertices

    def dominated_by(self, other):
        if self.cost == other.cost and self.time == other.time:
            return False
        if self.cost >= other.cost and self.time >= other.time:
            return True
        return False

    def __repr__(self):
        spath = ''
        for edge in self.edges:
            spath += '(' + str(edge.end1) + ',' + str(edge.end2) + ')->'
        spath = spath.rstrip('->')
        return '[' + spath + ',c=' + str(self.cost) + ',t=' + str(self.time) + ',end=' + str(self.end) + ']'

    @property
    def cost(self):
        return sum(e.cost for e in self.edges)

    @property
    def time(self):
        return sum(e.time for e in self.edges)

    def add_edge(self, edge):
        self.edges.append(edge)

    def set_path(self, edgelist):
        self.edges = edgelist


class Graph:

    def __init__(self, V):
        self.vertices = []
        self.edges = []
        self.V = V

    def add_edge(self, u, v, c, t):
        U = [x for x in self.vertices if (x.id == u)]
        V = [x for x in self.vertices if (x.id == v)]
        if U:
            U = U[0]
        else:
            U = Vertex(u)
            self.add_vertex(U)
        if V:
            V = V[0]
        else:
            V = Vertex(v)
            self.add_vertex(V)
        edge = Edge(U, V, c, t)
        self.edges.append(edge)

    def add_vertex(self, u):
        self.vertices.append(u)

    def get_vertex(self, v):
        for vertex in self.vertices:
            if vertex.id == v:
                return vertex
        return None

    def print_graph(self):
        print("Vertices: " + str(self.vertices))
        print("Edges: " + str(self.edges))

    def CCSPExecute(self, source, destination):
        # basically, BFS/Dijkstra but with both weights, storing the non
        #  dominated paths
        heap = CCSPBinaryMinHeap()
        # push init edges to heap
        for edge in source.connected_edges(self):
            end = edge.end2
            if end == source:
                end = edge.end1
            heap.push(Path([edge], end))
        if DEBUG:
            heap.print_heap()
        # guts
        i = 1
        while heap.size:
            if DEBUG:
                print('DEBUG :: round ' + str(i))
                heap.print_heap();
                print('...')
            path = heap.pop()
            # if dominated discard, otherwise, insert
            signatures = path.end.CCSPaths
            if not signatures or (signatures and (not path.dominated_by(signatures[-1]))):
                path.end.CCSPaths.append(path)
                # only add edges of this end node if it is not dominated, and of course, stop at destination
                if path.end != destination:
                    exclude = path.edges[-1].end1
                    if exclude == path.end:
                        exclude = path.edges[-1].end2
                    for edge in path.end.connected_edges(self, [exclude]):
                        end = edge.end2
                        if end == path.end:
                            end = edge.end1
                        heap.push(Path(path.edges + [edge], end))
            if DEBUG:
                heap.print_heap();
                print('DEBUG :: endround ' + str(i) + '\n\n')
            i += 1

f = open(file, 'r')
V = int(f.readline())
g = Graph(V)
for line in f:
     u, v, c, t = map(int, line.strip().split(' '))
     g.add_edge(u, v, c, t)

S = g.get_vertex(int(arg_s))
D = g.get_vertex(int(arg_d))
budget = int(arg_budget)
if S not in g.vertices or D not in g.vertices:
    print('Your source and desination vertex must both exist in the graph.')
    exit()
g.CCSPExecute(S, D)

# show output:
print('Signature Paths for Destination Vertex (' + str(D) + '):\n' + str(D.CCSPaths))

# curve:
if len(D.CCSPaths) > 0:
    xmax = D.CCSPaths[-1].cost + 4
    ymax = D.CCSPaths[0].time + 4
    print('\n time\n  |')
    for y in reversed(range(ymax)):
        if (y > 0):
            stdout.write(str(y).ljust(2) + '-')
            for x in range(1, xmax+1):
                mark = ' '
                for sig in D.CCSPaths:
                    if sig.cost == x and sig.time == y:
                        mark = 'X'
                    elif sig.cost == x and sig.time > y:
                        mark = '|'
                    elif sig.cost > x and sig.time == y:
                        mark = '-'
                stdout.write('   ' + mark)
            print('\n  | ')
        else:
            stdout.write('0 -')
            for x in range(xmax):
                stdout.write('---|')
            stdout.write('--- cost\n  0 ')
            for x in range(1, xmax+1):
                stdout.write('  ' + str(x).ljust(2))
            print('\n')

best = None
for path in D.CCSPaths:
    if path.cost <= budget:
        if (not best) or path.time < best.time:
            best = path
if best:
    print('The fastest path within your budget is: ' + str(best))
else:
    print('There is no path that fits within your budget.')
