# Cost-Constrained Shortest Path (Two-Dimensional Dijkstra)

## Usage

This implementation was written in Python 3 and then ported to make it compatible with Python 2. It has been tested with Python 2.7 and 3.6. To use:

    python cpath.py <datafile> <source> <destination> <budget> [<DEBUG>]

Example:

    python cpath.py testdata.txt 0 6 17

Alternatively, if your system has a specific version of Python installed, then you may need to use that. E.g.:

    python2.7 cpath.py testdata.txt 0 6 17
    python3.5 cpath.py testdata.txt 0 6 17

## Authors (+ work breakdown)

 - Gregory N. Schmit (50%)
   - focused on writing the implementation (assisted with the algorithm)
 - Rahel Okbit (50%)
   - focused on developing the algorithm (assisted with testing)
