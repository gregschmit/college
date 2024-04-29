import java.util.Arrays;

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

public class FastCollinearPoints {
    private int numberOfSegments;
    private LineSegment[] segments;

    // Helper tuple to store a slope and a point.
    private class SlopePoint implements Comparable<SlopePoint> {
        public final double slope;
        public final Point point;

        public SlopePoint(double slope, Point point) {
            this.slope = slope;
            this.point = point;
        }

        public int compareTo(SlopePoint that) {
            return Double.compare(this.slope, that.slope);
        }
    }

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
        this.segments = new LineSegment[n * n];

        // Think of p as the origin.
        // For each other point q > p, determine the slope it makes with p.
        // Sort the points according to the slopes they makes with p.
        // Check if any 3 (or more) adjacent points in the sorted order have equal
        // slopes with respect to p. If so, these points, together with p, are
        // collinear.
        for (int i = 0; i < n - 3; i++) {
            Point p = points[i];
            SlopePoint[] slopePoints = new SlopePoint[n - i - 1];
            for (int j = i + 1; j < n; j++) {
                slopePoints[j - i - 1] = new SlopePoint(p.slopeTo(points[j]), points[j]);
            }
            Arrays.sort(slopePoints);

            int count = 1;
            for (int j = 1; j < slopePoints.length; j++) {
                double previousSlope = slopePoints[j - 1].slope;
                double slope = slopePoints[j].slope;

                if (slope == previousSlope) {
                    // If this point has the same slope as the previous, just increment the count.
                    count++;
                } else {
                    // If the count is greater than or equal to 3, we have found the end of a line
                    // segment of length 3 or more.
                    if (count >= 3) {
                        Point[] collinearPoints = new Point[count + 1];
                        collinearPoints[0] = p;
                        for (int k = 1; k <= count; k++) {
                            collinearPoints[k] = slopePoints[j - k].point;
                        }

                        Arrays.sort(collinearPoints);
                        if (p.compareTo(collinearPoints[0]) == 0) {
                            this.segments[this.numberOfSegments++] = new LineSegment(collinearPoints[0],
                                    collinearPoints[count]);
                        }
                    }

                    count = 1;
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
