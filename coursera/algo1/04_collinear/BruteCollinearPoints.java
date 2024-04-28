import java.util.Arrays;

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

public class BruteCollinearPoints {
    private int numberOfSegments;
    private LineSegment[] segments;

    // Finds all line segments containing 4 points.
    public BruteCollinearPoints(Point[] points) {
        if (points == null) {
            throw new IllegalArgumentException("The points array is null.");
        }

        int n = points.length;
        for (int i = 0; i < n; i++) {
            if (points[i] == null) {
                throw new IllegalArgumentException("The points array contains null elements.");
            }
        }

        Point[] pointsSorted = points.clone();
        Arrays.sort(pointsSorted);
        for (int i = 0; i < n - 1; i++) {
            if (pointsSorted[i].compareTo(pointsSorted[i + 1]) == 0) {
                throw new IllegalArgumentException("The points array contains duplicate elements.");
            }
        }

        this.numberOfSegments = 0;
        this.segments = new LineSegment[n * n];

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    for (int el = k + 1; el < n; el++) {
                        Point pi = points[i];
                        Point pj = points[j];
                        Point pk = points[k];
                        Point pl = points[el];

                        double s1 = pi.slopeTo(pj);
                        double s2 = pi.slopeTo(pk);
                        double s3 = pi.slopeTo(pl);

                        if (s1 == s2 && s2 == s3) {
                            // Sort the points and add segment of first and last points.
                            Point[] collinearPoints = { pi, pj, pk, pl };
                            Arrays.sort(collinearPoints);
                            this.segments[this.numberOfSegments++] = new LineSegment(
                                    collinearPoints[0], collinearPoints[3]);
                        }
                    }
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
        BruteCollinearPoints collinear = new BruteCollinearPoints(points);
        for (LineSegment segment : collinear.segments()) {
            StdOut.println(segment);
            segment.draw();
        }
        StdDraw.show();
    }
}
