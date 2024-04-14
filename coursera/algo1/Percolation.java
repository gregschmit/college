import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
    private int n;
    private int top;
    private int bottom;
    private int openCount;
    private boolean[] grid;
    private WeightedQuickUnionUF ufGrid;
    private WeightedQuickUnionUF noBackwashUfGrid;

    // Creates n-by-n grid, with all sites initially blocked.
    public Percolation(int n) {
        if (n <= 0) {
            throw new IllegalArgumentException("`n` must be greater than 0.");
        }

        this.n = n;
        this.top = 0;
        this.bottom = n * n + 1;

        // Create a grid of size n*n + 2, where the first and last are the virtual top
        // and bottom sites, respectively. Also use a WeightedQuickUnionUF object to
        // keep track of the connections between sites.
        this.grid = new boolean[n * n + 2];
        this.ufGrid = new WeightedQuickUnionUF(n * n + 2);

        // The `noBackwashUfGrid` is used to prevent backwash. It is the same as
        // `ufGrid`
        // but without the bottom virtual site.
        this.noBackwashUfGrid = new WeightedQuickUnionUF(n * n + 1);

        // Set the virtual top and bottom sites to open.
        this.grid[this.top] = true;
        this.grid[this.bottom] = true;
    }

    // Opens the site (row, col) if it is not open already.
    public void open(int row, int col) {
        this.checkRowAndCol(row, col);
        int index = this.getIndex(row, col);

        if (this.grid[index]) {
            return;
        }

        this.grid[index] = true;
        this.openCount++;

        // Connect the site to its open neighbors.
        int[] neighbors = this.getNeighbors(row, col);
        // Not a performance bug.
        // CHECKSTYLE:OFF
        for (int neighbor : neighbors) {
            if (neighbor != 0 && this.grid[neighbor]) {
                this.ufGrid.union(index, neighbor);
                this.noBackwashUfGrid.union(index, neighbor);
            }
        }
        // CHECKSTYLE:ON

        // If the site is in the top row, connect it to the virtual top site.
        if (row == 1) {
            this.ufGrid.union(index, this.top);
            this.noBackwashUfGrid.union(index, this.top);
        }

        // If the site is in the bottom row, connect it to the virtual bottom site.
        if (row == this.n) {
            this.ufGrid.union(index, this.bottom);
        }
    }

    // Is the site (row, col) open?
    public boolean isOpen(int row, int col) {
        this.checkRowAndCol(row, col);
        return this.grid[this.getIndex(row, col)];
    }

    // Is the site (row, col) full?
    public boolean isFull(int row, int col) {
        this.checkRowAndCol(row, col);
        return this.isConnected(this.getIndex(row, col), this.top);
    }

    // Returns the number of open sites.
    public int numberOfOpenSites() {
        return this.openCount;
    }

    // Does the system percolate?
    public boolean percolates() {
        return this.isConnected(this.top, this.bottom);
    }

    public static void main(String[] args) {
        Percolation p = new Percolation(1);
        p.printGrid();
        System.out.println("Percolates: " + p.percolates());
        p.open(1, 1);
        p.printGrid();
        System.out.println("Percolates: " + p.percolates());
    }

    private boolean isConnected(int p, int q) {
        if (!this.grid[p] || !this.grid[q]) {
            return false;
        }

        // Must use normal `ufGrid` for the bottom virtual site.
        if (p == this.bottom || q == this.bottom) {
            return this.ufGrid.find(p) == this.ufGrid.find(q);
        }

        // Otherwise, use `noBackwashUfGrid` to prevent backwash.
        return this.noBackwashUfGrid.find(p) == this.noBackwashUfGrid.find(q);
    }

    private int getIndex(int row, int col) {
        return (row - 1) * this.n + col;
    }

    // Return an array of 4 possible neighbors. If the provided row/col doesn't have
    // a neighbor then the value will be 0.
    private int[] getNeighbors(int row, int col) {
        // Numeric literal is fine.
        // CHECKSTYLE:OFF
        int[] neighbors = new int[4];
        // CHECKSTYLE:ON
        int index = this.getIndex(row, col);

        // Above
        if (row == 1) {
            neighbors[0] = 0;
        } else {
            neighbors[0] = index - this.n;
        }

        // Below
        if (row == this.n) {
            neighbors[1] = 0;
        } else {
            neighbors[1] = index + this.n;
        }

        // Left
        if (col == 1) {
            neighbors[2] = 0;
        } else {
            neighbors[2] = index - 1;
        }

        // Right
        if (col == this.n) {
            neighbors[3] = 0;
        } else {
            neighbors[3] = index + 1;
        }

        return neighbors;
    }

    private void checkRowAndCol(int row, int col) {
        if (row < 1 || row > this.n || col < 1 || col > this.n) {
            throw new IllegalArgumentException("Both `row` and `col` must be between 1 and n (inclusive).");
        }
    }

    private String getSiteIndicator(boolean status) {
        return status ? "O " : "X ";
    }

    private void printGrid() {
        // First, print the top virtual site.
        System.out.println("Top: " + this.getSiteIndicator(this.grid[this.top]));

        // Then, print the grid.
        for (int i = 0; i < this.n; i++) {
            for (int j = 0; j < this.n; j++) {
                int index = i * this.n + j + 1;
                System.out.print(this.getSiteIndicator(this.grid[index]));
            }
            System.out.println();
        }

        // Finally, print the bottom virtual site.
        System.out.println("Bottom: " + this.getSiteIndicator(this.grid[this.bottom]));
    }
}