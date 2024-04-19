import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item> {
    private class Node {
        Item item;
        Node next;
        Node prev;
    }

    private Node first;
    private Node last;
    private int size;

    // Construct an empty deque.
    public Deque() {
        this.first = null;
        this.last = null;
        this.size = 0;
    }

    // Is the deque empty?
    public boolean isEmpty() {
        return this.first == null;
    }

    // Return the number of items on the deque.
    public int size() {
        return this.size;
    }

    // Add the item to the front.
    public void addFirst(Item item) {
        if (item == null) {
            throw new IllegalArgumentException("Item cannot be null.");
        }

        Node oldFirst = this.first;
        this.first = new Node();
        this.first.item = item;
        this.first.next = oldFirst;

        if (oldFirst == null) {
            this.last = this.first;
        } else {
            oldFirst.prev = this.first;
        }

        this.size++;
    }

    // Add the item to the back.
    public void addLast(Item item) {
        if (item == null) {
            throw new IllegalArgumentException("Item cannot be null.");
        }

        Node oldLast = this.last;
        this.last = new Node();
        this.last.item = item;
        this.last.prev = oldLast;

        if (oldLast == null) {
            this.first = this.last;
        } else {
            oldLast.next = this.last;
        }

        this.size++;
    }

    // Remove and return the item from the front.
    public Item removeFirst() {
        if (isEmpty()) {
            throw new NoSuchElementException("Deque is empty.");
        }

        Item item = this.first.item;
        this.first = this.first.next;

        if (this.first == null) {
            this.last = null;
        } else {
            this.first.prev = null;
        }

        this.size--;

        return item;
    }

    // Remove and return the item from the back.
    public Item removeLast() {
        if (isEmpty()) {
            throw new NoSuchElementException("Deque is empty.");
        }

        Item item = this.last.item;
        this.last = this.last.prev;

        if (this.last == null) {
            this.first = null;
        } else {
            this.last.next = null;
        }

        this.size--;

        return item;
    }

    // Return an iterator over items in order from front to back.
    public Iterator<Item> iterator() {
        return new DequeIterator();
    }

    private class DequeIterator implements Iterator<Item> {
        private Node current = first;

        public boolean hasNext() {
            return current != null;
        }

        public void remove() {
            throw new UnsupportedOperationException("Remove is not supported.");
        }

        public Item next() {
            if (!hasNext()) {
                throw new NoSuchElementException("No more items to return.");
            }

            Item item = this.current.item;
            this.current = this.current.next;

            return item;
        }
    }

    // Unit testing (required).
    public static void main(String[] args) {
        Deque<Integer> deque = new Deque<Integer>();
        System.out.println("Is empty: " + deque.isEmpty());
        deque.addFirst(1);
        System.out.println("Is empty: " + deque.isEmpty());
        System.out.println("Size: " + deque.size());
        deque.addFirst(2);
        System.out.println("Size: " + deque.size());
        deque.addLast(3);
        System.out.println("Size: " + deque.size());
        deque.addLast(4);
        System.out.println("Size: " + deque.size());

        // Print all by iterator.
        System.out.println("All:");
        for (Integer i : deque) {
            System.out.println("Value: " + i);
        }

        System.out.println("Remove first: " + deque.removeFirst());
        System.out.println("Remove last: " + deque.removeLast());
    }
}