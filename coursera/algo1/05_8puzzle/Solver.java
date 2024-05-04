import java.util.Arrays;
import java.util.ArrayList;

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.StdOut;

public class Solver {
    private enum PriorityFunction {
        HAMMING, MANHATTAN
    }

    private final PriorityFunction priorityFunction = PriorityFunction.MANHATTAN;

    private boolean isSolvable = false;
    private int moves = -1;
    private ArrayList<Board> solution = null;

    private class Node implements Comparable<Node> {
        private final Board board;
        private final int moves;
        private final Node previous;
        private final int priority;

        public Node(Board board, int moves, Node previous) {
            this.board = board;
            this.moves = moves;
            this.previous = previous;

            switch (priorityFunction) {
                case HAMMING:
                    this.priority = this.board.hamming() + this.moves;
                    break;
                case MANHATTAN:
                    this.priority = this.board.manhattan() + this.moves;
                    break;
                default:
                    throw new IllegalArgumentException("Invalid priority function.");
            }
        }

        public int compareTo(Node that) {
            return this.priority - that.priority;
        }
    }

    // Find a solution to the initial board (using the A* algorithm).
    public Solver(Board initial) {
        if (initial == null) {
            throw new IllegalArgumentException("Initial board cannot be null.");
        }

        // Initialize the priority queue and insert the initial node.
        MinPQ<Node> pq = new MinPQ<Node>();
        pq.insert(new Node(initial, 0, null));

        // Initialize twin board and priority queue to detect unsolvable puzzles.
        Board twin = initial.twin();
        MinPQ<Node> pqTwin = new MinPQ<Node>();
        pqTwin.insert(new Node(twin, 0, null));

        // Pop from the priority queue the node with the minimum priority, and insert
        // its neighbors.
        while (true) {
            Node node = pq.delMin();
            Node nodeTwin = pqTwin.delMin();

            if (node.board.isGoal()) {
                this.isSolvable = true;
                this.moves = node.moves;
                this.solution = new ArrayList<>(Arrays.asList(node.board));
                while (node.previous != null) {
                    this.solution.add(0, node.previous.board);
                    node = node.previous;
                }
                break;
            }

            if (nodeTwin.board.isGoal()) {
                break;
            }

            // Insert the neighbors of the current node.
            for (Board neighbor : node.board.neighbors()) {
                if (node.previous == null || !neighbor.equals(node.previous.board)) {
                    pq.insert(new Node(neighbor, node.moves + 1, node));
                }
            }

            // Insert the neighbors of the current twin node.
            for (Board neighbor : nodeTwin.board.neighbors()) {
                if (nodeTwin.previous == null || !neighbor.equals(nodeTwin.previous.board)) {
                    pqTwin.insert(new Node(neighbor, nodeTwin.moves + 1, nodeTwin));
                }
            }
        }
    }

    // Is the initial board solvable?
    public boolean isSolvable() {
        return this.isSolvable;
    }

    // Min number of moves to solve initial board; -1 if unsolvable.
    public int moves() {
        return this.moves;
    }

    // Sequence of boards in a shortest solution; null if unsolvable.
    public Iterable<Board> solution() {
        return this.solution;
    }

    // Test client.
    public static void main(String[] args) {
        // Create initial board from file.
        In in = new In(args[0]);
        int n = in.readInt();
        int[][] tiles = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                tiles[i][j] = in.readInt();
        Board initial = new Board(tiles);

        // Solve the puzzle.
        Solver solver = new Solver(initial);

        // Print solution to standard output.
        if (!solver.isSolvable())
            StdOut.println("No solution possible");
        else {
            StdOut.println("Minimum number of moves = " + solver.moves());
            for (Board board : solver.solution())
                StdOut.println(board);
        }
    }
}