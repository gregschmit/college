package edu.uic.cs342;

import edu.uic.cs342.SentenceParserException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.stream.Collectors;

public class SentenceParser {

  /**
   * Represents a start and end marker of a complete sentence
   */
  private class SentenceMarker {

    /**
     * Represents the start position of the sentence
     */
    public Integer start;

    /**
     * Represents the end position of the sentence
     */
    public Integer end;

    /**
     * Constructor for the SentenceMarker Class
     *
     * <p>This constructor will set the start and end points, unless the start
     *    is after the end, in which case both will be set to null.
     *
     * @param start int Represents the start position of the sentence
     *
     * @param end int Represents the end position of the sentence
     */
    SentenceMarker(int start, int end) {
      if (start < end) {
        this.start = new Integer(start);
        this.end = new Integer(end);
      } else {
        this.start = null;
        this.end = null;
      }
    }

    /**
     * Method that checks to see if this sentence is contained by another
     *
     * @param other SentenceMarker The other sentence to check against
     */
    public boolean contained_by(SentenceMarker other) {
      return (this.start > other.start && this.end < other.end);
    }

    /**
     * Method that checks to see if this sentence contains another
     *
     * @param other SentenceMarker The other sentence to check against
     */
    public boolean contains(SentenceMarker other) {
      return (this.start < other.start && this.end > other.end);
    }

    /**
     * Method that checks to see if this sentence overlaps another
     *
     * @param other SentenceMarker The other sentence to check against
     */
    public boolean dependant_on(SentenceMarker other) {
      return (this.contained_by(other) || this.contains(other));
    }

    /**
     * Method that checks to see if this sentence is before another
     *
     * @param other SentenceMarker The other sentence to check against
     */
    public boolean is_before(SentenceMarker other) {
      return (this.end < other.start);
    }
  }

  /**
   * Parses a given text and splits it into sentences.
   *
   * @param text A text to split into sentences.
   *
   * @return A list of Strings, each being a full English sentence.
   *
   * @throws SentenceParserException Generic exception class to indicate
   *                                 something went wrong during parsing
   *                                 the text into sentences.
   */
  public List<String> asList(String text) throws SentenceParserException {

    Character[] sentenceEnders = { '.', '!', '?' };
    String[] sentenceEnderExceptions = { "...", "mr.", "mrs.", "ms.", "ph.d.", "m.s." };
    ArrayList<SentenceMarker> sentenceFlags = new ArrayList<SentenceMarker>();
    HashSet<Integer> sentenceFlagExceptions = new HashSet<Integer>();

    // PREPROCESS: exclude titles and stuff
    for (String exception : sentenceEnderExceptions) {
      int last = 0;
      while (last >= 0 && last < text.length()-1) {
        last = text.toLowerCase().indexOf(exception, last);
        if (last >= 0) {
          for (int i = last; i < last + exception.length(); i++) {
            sentenceFlagExceptions.add(i);
          }
          last += exception.length();
        }
      }
    }

    boolean done = false;
    SentenceMarker last = null;
    int start = 0;
    int end = 0;
    // while we're not done...
    while (end < text.length()) {
      if (Arrays.asList(sentenceEnders).contains(text.charAt(end))) {
        // found a delimiting character, possible sentence ender
        // check if it is excluded, and if not, add that bitch
        if (!sentenceFlagExceptions.contains(end)) {
          last = new SentenceMarker(start, end);
          sentenceFlags.add(last);
          start = end + 1;
        }
      }
      end++;
    }

    // build array of strings with sentenceFlags and return them
    ArrayList<String> sentences = new ArrayList<String>();
    for (SentenceMarker mark : sentenceFlags) {
      sentences.add(text.substring(mark.start, mark.end+1).trim());
    }
    return sentences;
  }
}
