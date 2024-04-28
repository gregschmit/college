import java.util.Arrays;

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

public class FastCollinearPoints {
    private int numberOfSegments;
    private LineSegment[] segments;

    // Finds all line segments containing 4 or more points.
    public FastCollinearPoints(Point[] points) {
        if (points == null) {
            throw new IllegalArgumentException("The points array is null.");
        }

        int n = points.length;
        for (int i = 0; i < points.length; i++) {
            if (points[i] == null) {
                throw new IllegalArgumentException("The points array contains null elements.");
            }
        }

        Arrays.sort(points);
        for (int i = 0; i < n - 1; i++) {
            if (points[i].compareTo(points[i + 1]) == 0) {
                throw new IllegalArgumentException("The points array contains duplicate elements.");
            }
        }

        this.numberOfSegments = 0;
        this.segments = new LineSegment[n];

        // Think of p as the origin.
        // For each other point q > p, determine the slope it makes with p.
        // Sort the points according to the slopes they makes with p.
        // Check if any 3 (or more) adjacent points in the sorted order have equal
        // slopes with respect to p. If so, these points, together with p, are
        // collinear.
        for (int i = 0; i < n - 3; i++) {
            Point p = points[i];
            Point[] pointsSorted = Arrays.copyOfRange(points, i + 1, n);
            Arrays.sort(pointsSorted, p.slopeOrder());

            int count = 1;
            for (int j = 1; j < pointsSorted.length; j++) {
                if (j == pointsSorted.length - 1 || p.slopeTo(pointsSorted[j]) != p.slopeTo(pointsSorted[j + 1])) {
                    if (count >= 3) {
                        Point[] collinearPoints = new Point[count + 1];
                        collinearPoints[0] = p;
                        for (int k = 1; k <= count; k++) {
                            collinearPoints[k] = pointsSorted[j - k + 1];
                        }

                        Arrays.sort(collinearPoints);
                        if (p.compareTo(collinearPoints[0]) == 0) {
                            this.segments[this.numberOfSegments++] = new LineSegment(collinearPoints[0],
                                    collinearPoints[count]);
                        }
                    }
                    count = 1;
                } else {
                    count++;
                }
            }
        }

        LineSegment[] segmentsSized = new LineSegment[this.numberOfSegments];
        for (int i = 0; i < this.numberOfSegments; i++) {
            segmentsSized[i] = this.segments[i];
        }
        this.segments = segmentsSized;
    }

    // The number of line segments.
    public int numberOfSegments() {
        return this.numberOfSegments;
    }

    // The line segments.
    public LineSegment[] segments() {
        return this.segments.clone();
    }

    public static void main(String[] args) {
        // read the n points from a file
        In in = new In(args[0]);
        int n = in.readInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            int x = in.readInt();
            int y = in.readInt();
            points[i] = new Point(x, y);
        }

        // draw the points
        StdDraw.enableDoubleBuffering();
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        for (Point p : points) {
            p.draw();
        }
        StdDraw.show();

        // print and draw the line segments
        FastCollinearPoints collinear = new FastCollinearPoints(points);
        for (LineSegment segment : collinear.segments()) {
            StdOut.println(segment);
            segment.draw();
        }
        StdDraw.show();
    }
}
