import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;

public class PercolationStats {
    private int n;
    private int trials;
    private int[] percolatedAt;
    private Double mean;
    private Double stddev;

    // Perform independent trials on an n-by-n grid.
    public PercolationStats(int n, int trials) {
        if (n <= 0 || trials <= 0) {
            throw new IllegalArgumentException("Both `n` and `trials` must be greater than 0.");
        }

        this.n = n;
        this.trials = trials;
        this.percolatedAt = new int[trials];
        for (int i = 0; i < trials; i++) {
            Percolation percolation = new Percolation(n);
            while (!percolation.percolates()) {
                int row = StdRandom.uniformInt(1, n + 1);
                int col = StdRandom.uniformInt(1, n + 1);
                percolation.open(row, col);
            }
            this.percolatedAt[i] = percolation.numberOfOpenSites();
        }
    }

    // Sample mean of percolation threshold.
    public double mean() {
        if (this.mean == null) {
            this.mean = StdStats.mean(this.percolatedAt) / (this.n * this.n);
        }
        return this.mean;
    }

    // Sample standard deviation of percolation threshold.
    public double stddev() {
        if (this.stddev == null) {
            this.stddev = StdStats.stddev(this.percolatedAt) / (this.n * this.n);
        }
        return this.stddev;
    }

    // Low endpoint of 95% confidence interval.
    public double confidenceLo() {
        return this.mean() - (1.96 * this.stddev() / Math.sqrt(this.trials));

    }

    // High endpoint of 95% confidence interval.
    public double confidenceHi() {
        return this.mean() + (1.96 * this.stddev() / Math.sqrt(this.trials));
    }

    // Test client (see below).
    public static void main(String[] args) {
        PercolationStats ps = new PercolationStats(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
        System.out.println("mean                    = " + ps.mean());
        System.out.println("stddev                  = " + ps.stddev());
        System.out.println("95% confidence interval = [" + ps.confidenceLo() + ", " + ps.confidenceHi() + "]");
    }
}