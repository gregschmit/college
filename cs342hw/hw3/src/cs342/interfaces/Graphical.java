/**
 * This is code for HW3 in CS342.  You should not make any changes to this file.
 *
 * This interface describes methods that can be applied to types of data
 * that have a visual, or display, aspect to them.  Examples of such documents
 * include image files, video files, and formatted, printable documents.
 */
interface Graphical {

  /**
   * Implementing classes must implement this method to return the height of
   * the file being represented.  For example, if this is an image, this
   * should return the height of the image, in pixels.  If the thing being
   * represented is a document, it should be the height of the document in
   * whatever expression makes sense (inches, cm, etc.).
   */
  public Integer getHeight();

  /**
   * Implementing classes must implement this method to return the width of
   * the file being represented.  For example, if this is an image, this
   * should return the height of the image, in pixels.  If the thing being
   * represented is a document, it should be the height of the document in
   * whatever expression makes sense (inches, cm, etc.).
   */
  public Integer getWidth();
}
