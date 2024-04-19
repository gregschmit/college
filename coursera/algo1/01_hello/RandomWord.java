import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

public class RandomWord {
    public static void main(String[] args) {
        // StdOut.println("Type a list of strings delimited by whitespace and press
        // Enter and then Ctrl-D to finish:");

        String champion = "";
        int i = 1;
        while (!StdIn.isEmpty()) {
            String contender = StdIn.readString();
            // StdOut.println("Contender: " + contender);
            if (StdRandom.bernoulli(1.0 / i)) {
                champion = contender;
            }
            // StdOut.println("Champion: " + champion);
            i++;
        }
        StdOut.println(champion);
    }
}