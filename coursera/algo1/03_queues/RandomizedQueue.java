import java.util.Iterator;
import java.util.NoSuchElementException;

import edu.princeton.cs.algs4.StdRandom;

public class RandomizedQueue<Item> implements Iterable<Item> {
    private static final int INITIAL_CAPACITY = 2;

    private Item[] items;
    private int capacity;
    private int size;

    // Construct an empty randomized queue.
    public RandomizedQueue() {
        this.items = (Item[]) new Object[INITIAL_CAPACITY];
        this.capacity = INITIAL_CAPACITY;
        this.size = 0;
    }

    // Is the randomized queue empty?
    public boolean isEmpty() {
        return this.size == 0;
    }

    // Return the number of items on the randomized queue.
    public int size() {
        return this.size;
    }

    private void resize(int newCapacity) {
        Item[] newItems = (Item[]) new Object[newCapacity];

        if (newCapacity < this.size) {
            this.size = newCapacity;
        }

        for (int i = 0; i < this.size; i++) {
            newItems[i] = this.items[i];
        }

        this.items = newItems;
        this.capacity = newCapacity;
    }

    // Add the item.
    public void enqueue(Item item) {
        if (item == null) {
            throw new IllegalArgumentException("Item cannot be null.");
        }

        if (this.size == this.capacity) {
            this.resize(2 * this.capacity);
        }

        this.items[this.size++] = item;
    }

    // Remove and return a random item.
    public Item dequeue() {
        if (this.isEmpty()) {
            throw new NoSuchElementException("Randomized queue is empty.");
        }

        int randomIndex = StdRandom.uniformInt(this.size);
        Item item = this.items[randomIndex];

        this.items[randomIndex] = this.items[--this.size];
        this.items[this.size] = null;

        if (this.size > 0 && this.size <= this.capacity / 4) {
            this.resize(this.capacity / 2);
        }

        return item;
    }

    // Return a random item (but do not remove it).
    public Item sample() {
        if (this.isEmpty()) {
            throw new NoSuchElementException("Randomized queue is empty.");
        }

        return this.items[StdRandom.uniformInt(this.size)];
    }

    // Return an independent iterator over items in random order.
    public Iterator<Item> iterator() {
        return new RandomizedQueueIterator();
    }

    private class RandomizedQueueIterator implements Iterator<Item> {
        private int current;
        private final int[] indices;

        public RandomizedQueueIterator() {
            this.current = 0;
            this.indices = new int[size];

            for (int i = 0; i < size; i++) {
                this.indices[i] = i;
            }

            StdRandom.shuffle(this.indices);
        }

        public boolean hasNext() {
            return this.current < size;
        }

        public Item next() {
            if (!hasNext()) {
                throw new NoSuchElementException("No more items to return.");
            }

            return items[indices[current++]];
        }

        public void remove() {
            throw new UnsupportedOperationException("Remove operation is not supported.");
        }
    }

    // Unit testing (required).
    public static void main(String[] args) {
        RandomizedQueue<Integer> rq = new RandomizedQueue<>();

        rq.enqueue(1);
        rq.enqueue(2);
        rq.enqueue(3);
        rq.enqueue(4);
        rq.enqueue(5);

        for (int i : rq) {
            System.out.println(i);
        }

        System.out.println("Sample: " + rq.sample());
    }
}