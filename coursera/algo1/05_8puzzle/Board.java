import java.util.Arrays;

public class Board {
    private final int[][] board;
    private final int n;
    private int zeroRow;
    private int zeroCol;

    // Create a board from an n-by-n array of tiles, where tiles[row][col] = tile at
    // (row, col).
    public Board(int[][] tiles) {
        this.n = tiles.length;
        this.board = new int[this.n][this.n];

        for (int row = 0; row < this.n; row++) {
            for (int col = 0; col < this.n; col++) {
                this.board[row][col] = tiles[row][col];

                if (tiles[row][col] == 0) {
                    this.zeroRow = row;
                    this.zeroCol = col;
                }
            }
        }
    }

    // String representation of this board.
    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append(this.board.length + "\n");

        for (int row = 0; row < this.board.length; row++) {
            for (int col = 0; col < this.board[row].length; col++) {
                result.append(this.board[row][col] + " ");
            }
            result.append("\n");
        }

        return result.toString();
    }

    // Board dimension n.
    public int dimension() {
        return this.n;
    }

    private boolean hasCorrectValueAt(int row, int col) {
        if (row == this.n - 1 && col == this.n - 1) {
            return this.board[row][col] == 0;
        }

        return this.board[row][col] == row * this.n + col + 1;
    }

    // Number of tiles out of place.
    public int hamming() {
        int hamming = 0;

        for (int row = 0; row < this.n; row++) {
            for (int col = 0; col < this.n; col++) {
                if (this.board[row][col] != 0 && !this.hasCorrectValueAt(row, col)) {
                    hamming++;
                }
            }
        }

        return hamming;
    }

    // Sum of Manhattan distances between tiles and goal.
    public int manhattan() {
        int manhattan = 0;

        for (int row = 0; row < this.n; row++) {
            for (int col = 0; col < this.n; col++) {
                int value = this.board[row][col];

                if (value == 0) {
                    continue;
                }

                int goalRow = (value - 1) / this.n;
                int goalCol = (value - 1) % this.n;

                manhattan += Math.abs(row - goalRow) + Math.abs(col - goalCol);
            }
        }

        return manhattan;
    }

    // Is this board the goal board?
    public boolean isGoal() {
        for (int row = 0; row < this.n; row++) {
            for (int col = 0; col < this.n; col++) {
                if (!this.hasCorrectValueAt(row, col)) {
                    return false;
                }
            }
        }

        return true;
    }

    // Does this board equal y?
    public boolean equals(Object y) {
        if (!(y instanceof Board)) {
            return false;
        }

        Board other = (Board) y;

        if (this.n != other.n) {
            return false;
        }

        for (int row = 0; row < this.n; row++) {
            for (int col = 0; col < this.n; col++) {
                if (this.board[row][col] != other.board[row][col]) {
                    return false;
                }
            }
        }

        return true;
    }

    // Return a copy of the board with the two tiles in the given positions swapped.
    private Board swap(int row1, int col1, int row2, int col2) {
        int[][] copy = new int[this.n][this.n];

        for (int row = 0; row < this.n; row++) {
            for (int col = 0; col < this.n; col++) {
                copy[row][col] = this.board[row][col];
            }
        }

        int temp = copy[row1][col1];
        copy[row1][col1] = copy[row2][col2];
        copy[row2][col2] = temp;

        return new Board(copy);
    }

    // All neighboring boards.
    public Iterable<Board> neighbors() {
        // First, handle corners with 2 neighbors.
        if (zeroRow == 0 && zeroCol == 0) {
            // Top-left corner.
            return Arrays.asList(this.swap(0, 0, 0, 1),
                    this.swap(0, 0, 1, 0));
        } else if (zeroRow == 0 && zeroCol == n - 1) {
            // Top-right corner.
            return Arrays.asList(this.swap(0, n - 1, 0, n - 2),
                    this.swap(0, n - 1, 1, n - 1));
        } else if (zeroRow == n - 1 && zeroCol == 0) {
            // Bottom-left corner.
            return Arrays.asList(this.swap(n - 1, 0, n - 2, 0),
                    this.swap(n - 1, 0, n - 1, 1));
        } else if (zeroRow == n - 1 && zeroCol == n - 1) {
            // Bottom-right corner.
            return Arrays.asList(this.swap(n - 1, n - 1, n - 2, n - 1),
                    this.swap(n - 1, n - 1, n - 1, n - 2));
        }

        // Then, handle edges with 3 neighbors.
        if (zeroRow == 0) {
            // Top edge.
            return Arrays.asList(this.swap(0, zeroCol, 0, zeroCol - 1),
                    this.swap(0, zeroCol, 0, zeroCol + 1),
                    this.swap(0, zeroCol, 1, zeroCol));
        } else if (zeroRow == n - 1) {
            // Bottom edge.
            return Arrays.asList(this.swap(n - 1, zeroCol, n - 1, zeroCol - 1),
                    this.swap(n - 1, zeroCol, n - 1, zeroCol + 1),
                    this.swap(n - 1, zeroCol, n - 2, zeroCol));
        } else if (zeroCol == 0) {
            // Left edge.
            return Arrays.asList(this.swap(zeroRow, 0, zeroRow - 1, 0),
                    this.swap(zeroRow, 0, zeroRow + 1, 0),
                    this.swap(zeroRow, 0, zeroRow, 1));
        } else if (zeroCol == n - 1) {
            // Right edge.
            return Arrays.asList(this.swap(zeroRow, n - 1, zeroRow - 1, n - 1),
                    this.swap(zeroRow, n - 1, zeroRow + 1, n - 1),
                    this.swap(zeroRow, n - 1, zeroRow, n - 2));
        }

        // Finally, handle the rest with 4 neighbors.
        return Arrays.asList(this.swap(zeroRow, zeroCol, zeroRow - 1, zeroCol),
                this.swap(zeroRow, zeroCol, zeroRow + 1, zeroCol),
                this.swap(zeroRow, zeroCol, zeroRow, zeroCol - 1),
                this.swap(zeroRow, zeroCol, zeroRow, zeroCol + 1));
    }

    // A board that is obtained by exchanging any pair of tiles.
    public Board twin() {
        int[][] twinTiles = new int[this.n][this.n];

        for (int row = 0; row < this.n; row++) {
            for (int col = 0; col < this.n; col++) {
                twinTiles[row][col] = this.board[row][col];
            }
        }

        // Either flip the first two tiles in the first row or the first two tiles in
        // the second row.
        if (twinTiles[0][0] != 0 && twinTiles[0][1] != 0) {
            int temp = twinTiles[0][0];
            twinTiles[0][0] = twinTiles[0][1];
            twinTiles[0][1] = temp;
        } else {
            int temp = twinTiles[1][0];
            twinTiles[1][0] = twinTiles[1][1];
            twinTiles[1][1] = temp;
        }

        return new Board(twinTiles);
    }

    // Unit testing (not graded).
    public static void main(String[] args) {
        // Initialize a Board.
        int[][] tiles = { { 8, 1, 3 }, { 4, 0, 2 }, { 7, 6, 5 } };
        Board board = new Board(tiles);

        // Print out the board.
        System.out.println(board.toString());

        // Use all public methods to test the Board class.
        System.out.println("Dimension: " + board.dimension());
        System.out.println("Hamming: " + board.hamming());
        System.out.println("Manhattan: " + board.manhattan());
        System.out.println("Is goal: " + board.isGoal());

        // Create a board which is in the goal state.
        int[][] goalTiles = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 0 } };
        Board goalBoard = new Board(goalTiles);
        System.out.println("Is goal: " + goalBoard.isGoal());

        System.out.println("Equals: " + board.equals(board));
        System.out.println("Neighbors: ");
        for (Board neighbor : board.neighbors()) {
            System.out.println(neighbor);
        }
        System.out.println("Twin: " + board.twin());
        Board hammingBoard = new Board(new int[][] { { 0, 1, 3 }, { 4, 2, 5 }, { 7, 8, 6 } });
        System.out.println("Hamming: " + hammingBoard.hamming());
    }
}