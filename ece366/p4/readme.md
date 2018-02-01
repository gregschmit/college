# Cache Simulator

## Meta

Author: Gregory N. Schmit

Date: 11 Dec 2017

## Introduction

I wrote a cache simulator in Python 3. It is very flexible in terms of how you can configure the parameters. Run it with a `-h` option to see the program parameters:

    $ python3 cachesim.py -h

## Usage

```
usage: cachesim.py [-h] [-w] [-pc]
                   [size_kb] [n_sets] [block_size] [miss_penalty]
                   [cpu_frequency] filename

positional arguments:
  size_kb
  n_sets
  block_size
  miss_penalty
  cpu_frequency
  filename

optional arguments:
  -h, --help            show this help message and exit
  -w, --write-no-allocate
  -pc, --print-cache

```

## Test Cases

I tested a lot of cases, but I included a full set of testing from Directly Mapped (sets == blocks) to fully associative (1 set):

```
gns-mac1:p4 gns$ python3 cachesim.py 64 1 64 gcc.trace
blocks per set: 1024
cycles: 3548064
cycle_time: 1.15e-09
total time: 4.0802736ms
gns-mac1:p4 gns$ python3 cachesim.py 64 2 64 gcc.trace
blocks per set: 512
cycles: 3040362
cycle_time: 1.15e-09
total time: 3.4964162999999995ms
gns-mac1:p4 gns$ python3 cachesim.py 64 4 64 gcc.trace
blocks per set: 256
cycles: 2302108
cycle_time: 1.15e-09
total time: 2.6474241999999997ms
gns-mac1:p4 gns$ python3 cachesim.py 64 8 64 gcc.trace
blocks per set: 128
cycles: 2044692
cycle_time: 1.15e-09
total time: 2.3513957999999997ms
gns-mac1:p4 gns$ python3 cachesim.py 64 16 64 gcc.trace
blocks per set: 64
cycles: 1924264
cycle_time: 1.15e-09
total time: 2.2129035999999997ms
gns-mac1:p4 gns$ python3 cachesim.py 64 32 64 gcc.trace
blocks per set: 32
cycles: 1772418
cycle_time: 1.15e-09
total time: 2.0382806999999996ms
gns-mac1:p4 gns$ python3 cachesim.py 64 64 64 gcc.trace
blocks per set: 16
cycles: 1750844
cycle_time: 1.15e-09
total time: 2.0134706ms
gns-mac1:p4 gns$ python3 cachesim.py 64 128 64 gcc.trace
blocks per set: 8
cycles: 1737182
cycle_time: 1.265e-09
total time: 2.19753523ms
gns-mac1:p4 gns$ python3 cachesim.py 64 256 64 gcc.trace
blocks per set: 4
cycles: 1735940
cycle_time: 1.15e-09
total time: 1.996331ms
gns-mac1:p4 gns$ python3 cachesim.py 64 512 64 gcc.trace
blocks per set: 2
cycles: 1725406
cycle_time: 1.2075e-09
total time: 2.0834277450000003ms
gns-mac1:p4 gns$ python3 cachesim.py 64 1024 64 gcc.trace
blocks per set: 1
cycles: 1772832
cycle_time: 1.15e-09
total time: 2.0387568ms
```
