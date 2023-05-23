// https://docs.oracle.com/javase/8/docs/api/java/util/ArrayList.html
import java.util.ArrayList;

/**
 * This is code for HW3 in CS342.  You should not make any changes to this file.
 *
 * This interface is for describing objects that represent textual data, in
 * some format (e.g. data that is intended to be editable and viewable using
 * standard command line, text editing tools).
 */
interface Textual {
  /**
   * Implementing classes should implement this method to return the number
   * of lines of text in the text file / data they're representing.
   */
  public Integer getNumberOfLines();

  /**
   * Implementing classes should implement this method to return an ArrayList
   * containing each of the lines of text in the text file being represented.
   */
  public ArrayList<String> getLinesOfText();
}
