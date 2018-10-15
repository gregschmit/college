import constraint
import math
import random
from simanneal import Annealer
import cvxpy as cp
import numpy as np
import itertools as iter

######################### EXAMPLES OF HOW TO USE PACKAGES ####################

""" An example of how to set up and solve a CSP for the map of Australia """
def graphColoringExample():
    colorProblem = constraint.Problem()
    domains = ["red", "green", "blue"]
    colorProblem.addVariable("WA", domains)
    colorProblem.addVariable("NT", domains)
    colorProblem.addVariable("Q", domains)
    colorProblem.addVariable("NSW", domains)
    colorProblem.addVariable("V", domains)
    colorProblem.addVariable("SA", domains)
    colorProblem.addVariable("T", domains)
    colorProblem.addConstraint(lambda a, b: a !=b, ("WA","NT"))
    colorProblem.addConstraint(lambda a, b: a !=b, ("WA","SA"))
    colorProblem.addConstraint(lambda a, b: a !=b, ("SA","NT"))
    colorProblem.addConstraint(lambda a, b: a !=b, ("Q","NT"))
    colorProblem.addConstraint(lambda a, b: a !=b, ("SA","Q"))
    colorProblem.addConstraint(lambda a, b: a !=b, ("NSW","SA"))
    colorProblem.addConstraint(lambda a, b: a !=b, ("NSW","Q"))
    colorProblem.addConstraint(lambda a, b: a !=b, ("SA","V"))
    colorProblem.addConstraint(lambda a, b: a !=b, ("NSW","V"))
    print colorProblem.getSolution()

""" An example of the syntax to set up and solve a convex problem """
def convexProgrammingExample():
    n = 2
    m = 10
    A = np.random.randn(m,n )
    x = cp.Variable(n)
    f = sum([cp.norm(x -A[ i,:],2) for i in range(m)])
    constraints = [sum(x) == 0]
    result = cp.Problem(cp.Minimize(f), constraints).solve()
    print x.value

""" An example of how to set up and solve an integer problem """
def integerProgrammingExample():
    # Create two scalar optimization variables.
    x = cp.Variable(integer=True)
    y = cp.Variable(integer=True)

    # Create two constraints.
    constraints = [x + y == 10,
                   x - y >= 1]

    # Form objective.
    obj = cp.Minimize((x - y)**2)

    # Form and solve problem.
    prob = cp.Problem(obj, constraints)
    print prob.solve()

############################ HOMEWORK STARTS HERE #############################

############################## PROBLEM 1 ######################################

""" A helper function to visualize ouput.  You do not need to change this """
def sudokuCSPToGrid(output,psize):
    dim = psize**2
    return np.reshape([[output[str(dim*i+j+1)] for j in range(dim)] for i in range(dim)],(dim,dim))

""" helper function to add variables to the CSP """
""" you do not need to change this"""
def addVar(problem, grid, domains, init):
    numRow = grid.shape[0]
    numCol = grid.shape[1]
    for rowIdx in range(numRow):
        for colIdx in range(numCol):
            if grid[rowIdx, colIdx] in init:
                problem.addVariable(grid[rowIdx,colIdx], [init[grid[rowIdx, colIdx]]])
            else:
                problem.addVariable(grid[rowIdx,colIdx], domains)

def unique(*x):
    y = []
    return not any(e in y or y.append(e) for e in x)

def cstAdd(problem, grid, domains, psize):
    # --------------------
    # Your code
    n_rows = grid.shape[0]
    n_cols = grid.shape[1]
    g_r = []
    g_c = [[] for i in range(n_cols)]
    g_b = [[] for i in range(psize*psize)]
    # iter rows/boxes
    for r_i, r in enumerate(grid):
        g_r.append(r)
        for c_i, value in enumerate(r):
            g_c[c_i].append(value)
            g_b[c_i//2 + (r_i//2 * psize)].append(value)
    for g in g_r + g_c + g_b:
        problem.addConstraint(unique, tuple(g))

    # --------------------

""" Implementation for a CSP Sudoku Solver """
""" positions: list of (row,column,value) triples representing the already filled in cells"""
""" psize: the problem size (e.g. 3 for a 3x3 grid of 3x3 squares in a standard Sudoku) """
""" You do not need to change this """
def sudokuCSP(positions,psize):
    sudokuPro = constraint.Problem()
    dim = psize ** 2
    numCol = dim
    numRow = dim
    domains = range(1,dim+1)
    init = {str(dim*p[0]+p[1]+1):p[2] for p in positions}
    sudokuList = [str(i) for i in range(1,dim**2+1)]
    sudoKuGrid = np.reshape(sudokuList, [numRow, numCol])
    addVar(sudokuPro, sudoKuGrid, domains, init)
    cstAdd(sudokuPro, sudoKuGrid, domains,psize)
    return sudokuPro.getSolution()

############################## PROBLEM 2 ######################################

class TravellingSalesmanProblem(Annealer):

    """problem specific data"""
    # latitude and longitude for the twenty largest U.S. cities
    cities = {
        'New York City': (40.72, 74.00),
        'Los Angeles': (34.05, 118.25),
        'Chicago': (41.88, 87.63),
        'Houston': (29.77, 95.38),
        'Phoenix': (33.45, 112.07),
        'Philadelphia': (39.95, 75.17),
        'San Antonio': (29.53, 98.47),
        'Dallas': (32.78, 96.80),
        'San Diego': (32.78, 117.15),
        'San Jose': (37.30, 121.87),
        'Detroit': (42.33, 83.05),
        'San Francisco': (37.78, 122.42),
        'Jacksonville': (30.32, 81.70),
        'Indianapolis': (39.78, 86.15),
        'Austin': (30.27, 97.77),
        'Columbus': (39.98, 82.98),
        'Fort Worth': (32.75, 97.33),
        'Charlotte': (35.23, 80.85),
        'Memphis': (35.12, 89.97),
        'Baltimore': (39.28, 76.62)
    }

    """problem-specific helper function"""
    """you may wish to implement this """
    def distance(self, a, b):
        """Calculates distance between two latitude-longitude coordinates."""
        # -----------------------------
        # Your code
        # maybe this is bad? return math.sqrt(((a[0] - b[0]) ** 2) + ((a[1] - b[1]) ** 2))
        # so do haversine:
        lat1 = a[0]
        long1 = a[1]
        lat2 = b[0]
        long2 = b[1]
        dlong = long2 - long1
        dlat = lat2 - lat1
        x = np.sin(dlat/2.0)**2 + np.cos(lat1) * np.cos(lat2) * np.sin(dlong/2.0)**2
        return 2 * np.arcsin(np.sqrt(x))
        # -----------------------------



    """ make a local change to the solution"""
    """ a natural choice is to swap to cities at random"""
    """ current state is available as self.state """
    def move(self):

        # --------------------
        l = len(self.state)
        if l > 1:
            x = random.sample([i for i in range(l)], 2)
            tmp = self.state[x[0]]
            self.state[x[0]] = self.state[x[1]]
            self.state[x[1]] = tmp
        # -------------------------


    """ how good is this state? """
    """ lower is better """
    """ current state is available as self.state """
    """ to get credit your energy must be the total distance travelled in the current state """
    def energy(self):
        #-----------------------
        # Your code
        accum = 0
        o = self.state[0]
        for s in self.state[1:]:
            accum += self.distance(self.cities[o], self.cities[s])
            o = s
        return accum
        #-----------------------

# Execution part, please don't change it!!!
def annealTSP(initial_state):
        # initial_state is a list of starting cities
        tsp = TravellingSalesmanProblem(initial_state)
        return tsp.anneal()

############################## PROBLEM 3 ######################################

class SudokuProblem(Annealer):

    """ positions: list of (row,column,value) triples representing the already filled in cells"""
    """ psize: the problem size (e.g. 3 for a 3x3 grid of 3x3 squares in a standard Sudoku) """
    def __init__(self,initial_state,positions,psize):
        self.psize = psize
        self.positions = positions

        # calculate rows, cols, boxes now
        self.g_r = [[e for e in range(i, i+self.psize**2)] for i in [r*self.psize**2 for r in range(self.psize**2)]]
        self.g_c = [[i + e*self.psize**2 for e in range(self.psize**2)] for i in [r for r in range(self.psize**2)]]
        self.g_b = []
        for maj_r in range(self.psize):
            for maj_c in range(self.psize):
                pieces = []
                for min_r in range(self.psize):
                    pieces.extend([e + maj_c*(self.psize) + maj_r*(self.psize ** 3) + min_r*(self.psize ** 2) for e in range(self.psize)])
                self.g_b.append(pieces)

        self.empty = [i for i in range(self.psize**4)]
        for p in positions:
            self.empty.remove(p[0]*self.psize**2 + p[1])
            initial_state[p[0]*self.psize**2 + p[1]] = p[2]

        super(SudokuProblem, self).__init__(initial_state)

    """ make a local change to the solution"""
    """ current state is available as self.state """
    def move(self):

        # --------------------
        # Your code
        # change random spot that isn't taken
        spot = random.choice(self.empty)
        spot_value = self.state[spot]
        while self.state[spot] == spot_value:
            self.state[spot] = random.randint(1, self.psize ** self.psize)
        # -------------------------


    def num_not_unique(self, *x):
        y = []
        c = 0
        for e in x:
            if e in y: c += 1
            y.append(e)
        return c


    """ how good is this state? """
    """ lower is better """
    """ current state is available as self.state """
    def energy(self):
        #-----------------------
        # Your code
        # maybe return the number of non-unique instances... good measure for goodness of a sudoku state
        nonuniques = 0
        for s in self.g_r + self.g_c + self.g_b:
            x = self.num_not_unique(*tuple(self.state[x] for x in s))
            nonuniques += x
        return nonuniques
        #-----------------------

# Execution part, please don't change it!!!
def annealSudoku(positions, psize):
        # initial_state of starting values:
        initial_state = [random.randint(1,psize**2) for i in range(psize ** 4)]
        sudoku = SudokuProblem(initial_state,positions,psize)
        sudoku.steps = 100000
        sudoku.Tmax = 100.0
        sudoku.Tmin = 1.0
        return sudoku.anneal()

############################## PROBLEM 4 ######################################

def packingProblem(c):
    # --------------------
    # Your code
    x1 = cp.Variable()
    x2 = cp.Variable()
    x3 = cp.Variable()
    obj = cp.Maximize((2.0/5.0)*x1+x2+x3)
    constraints = [
        x1>=0, x2>=0, x3>=0, x1<=5, x2<=3, x3<=1, (x1 + x2 + x3)<=c
    ]
    # print constraints
    # exit(0)
    problem = cp.Problem(obj, constraints)
    s = problem.solve()
    return s

def coveringProblem(c):
    # --------------------
    # Your code
    y1 = cp.Variable()
    y2 = cp.Variable()
    y3 = cp.Variable()
    y4 = cp.Variable()
    obj = cp.Minimize(y1+y2+y3+(c*y4))
    constraints = [
        y1>=0, y2>=0, y3>=0, y4>=0, y1 + 5*y4 >= 2, y2 + 3*y4 >= 3, y3 + y4 >= 1
    ]
    problem = cp.Problem(obj, constraints)
    s = problem.solve()
    return s
    # --------------------

############################## PROBLEM 5 ######################################

""" A helper function to visualize ouput.  You do not need to change this """
""" binary: the output of your solver """
""" psize: the problem size (e.g. 3 for a 3x3 grid of 3x3 squares in a standard Sudoku) """
def sudokuIPToGrid(binary,psize):
    dim = psize**2
    x = np.zeros((dim,dim),dtype=int)
    for i in range(dim):
        for j in range(dim):
            for k in range(dim):
                if binary[dim*i+j][k] >= 0.99:
                    x[i][j] = k+1
    return x

""" Implementation for a IP Sudoku Solver """
""" positions: list of (row,column,value) triples representing the already filled in cells"""
""" psize: the problem size (e.g. 3 for a 3x3 grid of 3x3 squares in a standard Sudoku) """
def sudokuIP(positions,psize):
    # --------------------
    # Your code
    dim = psize**2
    M = cp.Variable((dim**2,dim),integer=True) #Sadly we cannot do 3D Variables

    # calculate groups
    g_r = [[e for e in range(i, i+psize**2)] for i in [r*psize**2 for r in range(psize**2)]]
    g_c = [[i + e*psize**2 for e in range(psize**2)] for i in [r for r in range(psize**2)]]
    g_b = []
    for maj_r in range(psize):
        for maj_c in range(psize):
            pieces = []
            for min_r in range(psize):
                pieces.extend([e + maj_c*(psize) + maj_r*(psize ** 3) + min_r*(psize ** 2) for e in range(psize)])
            g_b.append(pieces)

    constraints = []
    #ADD YOUR CONSTRAINTS HERE
    # constraints for init values:
    for p in positions:
        spot = p[0]*psize**2 + p[1]
        constraints.append(M[spot][p[2]-1] == 1)

    for i in range(psize**4):
        constraints.append(M[i] >= 0)
        constraints.append(M[i] <= dim-1)
        constraints.append(sum([M[i][x] for x in range(dim)]) == 1)

    for block in g_r + g_c + g_b:
        # b is the block that needs to be unique
        for layer in range(dim):
            c = sum([M[i][layer] for i in block]) == 1
            constraints.append(c)
    # print constraints
    # print psize
    # print positions
    # print M[0]

    # Form objective.
    obj = cp.Minimize(M[0][0])

    # Form and solve problem.
    prob = cp.Problem(obj, constraints)
    prob.solve()
    return M.value
    # --------------------

############################## PROBLEM 6 ######################################

""" Computes MMS allocation """
""" n: number of players """
""" m: number of items """
""" v: matrix of v[i][j] values """
""" MMS: list of MMS[i] for each player i """
def calculateMMSAllocation(n,m,v,MMS):
    # --------------------
    # Your code
    A = cp.Variable((n,m),integer=True)

    return A.value
    # --------------------

""" Computes MMS(i) """
""" n: number of players """
""" m: number of items """
""" v: matrix of v[i][j] values """
""" i: player to compute MMS of """
def calculateMMSValue(n,m,v,i):
    # --------------------
    # Your code
    A = cp.Variable((n,m),integer=True)
    d = cp.Variable()

    return d.value
    # --------------------

######################### TESTING CODE: DEMO THE EXAMPLES OR ADD YOUR OWN TESTS HERE ###############################
#graphColoringExample()
#convexProgrammingExample()
#integerProgrammingExample()
