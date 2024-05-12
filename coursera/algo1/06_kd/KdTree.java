import java.util.ArrayList;
import java.util.List;

import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;

public class KdTree {
    private class Node {
        private Point2D point;
        private Node left; // Left or below.
        private Node right; // Right or above.
        private boolean vertical;

        public Node(Point2D point, boolean vertical) {
            this.point = point;
            this.left = null;
            this.right = null;
            this.vertical = vertical;
        }
    }

    private Node root = null;
    private int size = 0;

    // Construct an empty set of points.
    public KdTree() {
    }

    // Is the set empty?
    public boolean isEmpty() {
        return this.root == null;
    }

    // Number of points in the set.
    public int size() {
        return this.size;
    }

    // Add the point to the set (if it is not already in the set).
    public void insert(Point2D p) {
        if (p == null) {
            throw new IllegalArgumentException("Cannot insert null point.");
        }

        if (this.isEmpty()) {
            this.root = new Node(p, true);
            this.size++;
            return;
        }

        Node current = this.root;
        while (true) {
            if (current.point.equals(p)) {
                return;
            }

            if (current.vertical) {
                if (p.x() < current.point.x()) {
                    // Point is to the left.
                    if (current.left == null) {
                        current.left = new Node(p, false);
                        this.size++;
                        return;
                    } else {
                        current = current.left;
                    }
                } else {
                    // Point is to the right.
                    if (current.right == null) {
                        current.right = new Node(p, false);
                        this.size++;
                        return;
                    } else {
                        current = current.right;
                    }
                }
            } else {
                if (p.y() < current.point.y()) {
                    // Point is below.
                    if (current.left == null) {
                        current.left = new Node(p, true);
                        this.size++;
                        return;
                    } else {
                        current = current.left;
                    }
                } else {
                    // Point is above.
                    if (current.right == null) {
                        current.right = new Node(p, true);
                        this.size++;
                        return;
                    } else {
                        current = current.right;
                    }
                }
            }
        }
    }

    // Does the set contain point p?
    public boolean contains(Point2D p) {
        if (p == null) {
            throw new IllegalArgumentException("Cannot check null point.");
        }

        if (this.isEmpty()) {
            return false;
        }

        Node current = this.root;
        while (true) {
            if (current.point.equals(p)) {
                return true;
            }

            if (current.vertical) {
                if (p.x() < current.point.x()) {
                    // Point is to the left.
                    if (current.left == null) {
                        return false;
                    } else {
                        current = current.left;
                    }
                } else {
                    // Point is to the right.
                    if (current.right == null) {
                        return false;
                    } else {
                        current = current.right;
                    }
                }
            } else {
                if (p.y() < current.point.y()) {
                    // Point is below.
                    if (current.left == null) {
                        return false;
                    } else {
                        current = current.left;
                    }
                } else {
                    // Point is above.
                    if (current.right == null) {
                        return false;
                    } else {
                        current = current.right;
                    }
                }
            }
        }
    }

    // Draw all points to standard draw.
    public void draw() {
        // TODO
    }

    private List<Point2D> range(RectHV rect, Node node) {
        if (node == null) {
            return new ArrayList<>();
        }

        List<Point2D> points = new ArrayList<>();
        if (rect.contains(node.point)) {
            points.add(node.point);
        }

        if (node.vertical) {
            double x = node.point.x();
            if (rect.xmin() < x) {
                points.addAll(this.range(rect, node.left));
            }
            if (rect.xmax() > x) {
                points.addAll(this.range(rect, node.right));
            }
        } else {
            double y = node.point.y();
            if (rect.ymin() < y) {
                points.addAll(this.range(rect, node.left));
            }
            if (rect.ymax() > y) {
                points.addAll(this.range(rect, node.right));
            }
        }

        return points;
    }

    // All points that are inside the rectangle (or on the boundary).
    public Iterable<Point2D> range(RectHV rect) {
        if (rect == null) {
            throw new IllegalArgumentException("Cannot check null rectangle.");
        }

        if (this.isEmpty()) {
            return new ArrayList<>();
        }

        List<Point2D> points = new ArrayList<>();
        double x = this.root.point.x();

        // Insert root point if it is in the rectangle.
        if (rect.contains(this.root.point)) {
            points.add(this.root.point);
        }

        // If the rectangle exists to the left of the root, then check the left subtree.
        if (rect.xmin() < x) {
            points.addAll(this.range(rect, this.root.left));
        }

        // If the rectangle exists to the right of the root, then check the right
        // subtree.
        if (rect.xmax() > x) {
            points.addAll(this.range(rect, this.root.right));
        }

        return points;
    }

    private Node nearest(Point2D p, Node champion) {
        double d = p.distanceTo(champion.point);

        if (champion.vertical) {
            if (p.x() < champion.point.x()) {
                // Check left first.
                boolean prune = false;
                if (champion.left != null) {
                    Node newChampion = this.nearest(p, champion.left);

                    if (p.distanceTo(newChampion.point) < d) {
                        champion = newChampion;
                        prune = true;
                    }
                }

                // Check right if necessary.
                if (!prune && champion.right != null) {
                    Node newChampion = this.nearest(p, champion.right);

                    if (p.distanceTo(newChampion.point) < d) {
                        champion = newChampion;
                    }
                }
            } else {
                // Check right first.
                boolean prune = false;
                if (champion.right != null) {
                    Node newChampion = this.nearest(p, champion.right);

                    if (p.distanceTo(newChampion.point) < d) {
                        champion = newChampion;
                        prune = true;
                    }
                }

                // Check left if necessary.
                if (!prune && champion.left != null) {
                    Node newChampion = this.nearest(p, champion.left);

                    if (p.distanceTo(newChampion.point) < d) {
                        champion = newChampion;
                    }
                }
            }
        } else {
            if (p.y() < champion.point.y()) {
                // Check below first.
                boolean prune = false;
                if (champion.left != null) {
                    Node newChampion = this.nearest(p, champion.left);

                    if (p.distanceTo(newChampion.point) < d) {
                        champion = newChampion;
                        prune = true;
                    }
                }

                // Check above if necessary.
                if (!prune && champion.right != null) {
                    Node newChampion = this.nearest(p, champion.right);

                    if (p.distanceTo(newChampion.point) < d) {
                        champion = newChampion;
                    }
                }
            } else {
                // Check above first.
                boolean prune = false;
                if (champion.right != null) {
                    Node newChampion = this.nearest(p, champion.right);

                    if (p.distanceTo(newChampion.point) < d) {
                        champion = newChampion;
                        prune = true;
                    }
                }

                // Check below if necessary.
                if (!prune && champion.left != null) {
                    Node newChampion = this.nearest(p, champion.left);

                    if (p.distanceTo(newChampion.point) < d) {
                        champion = newChampion;
                    }
                }
            }
        }

        return champion;
    }

    // A nearest neighbor in the set to point p; null if the set is empty.
    public Point2D nearest(Point2D p) {
        if (p == null) {
            throw new IllegalArgumentException("Cannot check null point.");
        }

        if (this.isEmpty()) {
            return null;
        }

        return this.nearest(p, this.root).point;
    }

    // Unit testing of the methods (optional).
    public static void main(String[] args) {
        // Create a set.
        KdTree set = new KdTree();

        // Insert points:
        // A 0.7 0.2
        // B 0.5 0.4
        // C 0.2 0.3
        // D 0.4 0.7
        // E 0.9 0.6
        set.insert(new Point2D(0.7, 0.2));
        set.insert(new Point2D(0.5, 0.4));
        set.insert(new Point2D(0.2, 0.3));
        set.insert(new Point2D(0.4, 0.7));
        set.insert(new Point2D(0.9, 0.6));

        // Check range of rectangle.
        RectHV rect = new RectHV(0, 0, 1, 1);
        System.out.println("Points in range: " + set.range(rect));
    }
}