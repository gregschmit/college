import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.SET;

public class PointSET {
    private SET<Point2D> set;

    // Construct an empty set of points.
    public PointSET() {
        this.set = new SET<>();
    }

    // Is the set empty?
    public boolean isEmpty() {
        return this.set.isEmpty();
    }

    // Number of points in the set.
    public int size() {
        return this.set.size();
    }

    // Add the point to the set (if it is not already in the set).
    public void insert(Point2D p) {
        if (p == null) {
            throw new IllegalArgumentException("Cannot insert null point.");
        }
        this.set.add(p);
    }

    // Does the set contain point p?
    public boolean contains(Point2D p) {
        if (p == null) {
            throw new IllegalArgumentException("Cannot check null point.");
        }
        return this.set.contains(p);
    }

    // Draw all points to standard draw.
    public void draw() {
        for (Point2D p : this.set) {
            p.draw();
        }
    }

    // All points that are inside the rectangle (or on the boundary).
    public Iterable<Point2D> range(RectHV rect) {
        if (rect == null) {
            throw new IllegalArgumentException("Cannot check null rectangle.");
        }

        SET<Point2D> rangeSet = new SET<>();

        for (Point2D p : this.set) {
            if (rect.contains(p)) {
                rangeSet.add(p);
            }
        }

        return rangeSet;
    }

    // A nearest neighbor in the set to point p; null if the set is empty.
    public Point2D nearest(Point2D p) {
        if (p == null) {
            throw new IllegalArgumentException("Cannot check null point.");
        }

        if (this.isEmpty()) {
            return null;
        }

        Point2D nearest = null;
        double minDistance = Double.POSITIVE_INFINITY;
        for (Point2D point : this.set) {
            double distance = p.distanceSquaredTo(point);
            if (distance < minDistance) {
                minDistance = distance;
                nearest = point;
            }
        }

        return nearest;
    }

    // Unit testing of the methods (optional).
    public static void main(String[] args) {
        // Create a set.
        PointSET set = new PointSET();

        // Check if the set is empty.
        System.out.println("Is the set empty? " + set.isEmpty());

        // Insert some points.
        set.insert(new Point2D(0.5, 0.5));
        set.insert(new Point2D(0.4, 0.4));
        set.insert(new Point2D(0.3, 0.3));
        set.insert(new Point2D(0.2, 0.2));
        set.insert(new Point2D(0.1, 0.1));

        // Check if the set is empty.
        System.out.println("Is the set empty? " + set.isEmpty());

        // Check the number of points in the set.
        System.out.println("Number of points in the set: " + set.size());

        // Check if the set contains a point (0.5, 0.5).
        System.out.println("Does the set contain (0.5, 0.5)? " + set.contains(new Point2D(0.5, 0.5)));

        // Check if the set contains a point (0.5, 0.6).
        System.out.println("Does the set contain (0.5, 0.6)? " + set.contains(new Point2D(0.5, 0.6)));

        // Check if the set contains a point (0.4, 0.4).
        System.out.println("Does the set contain (0.4, 0.4)? " + set.contains(new Point2D(0.4, 0.4)));

        // Draw all points in the set.
        set.draw();
    }
}