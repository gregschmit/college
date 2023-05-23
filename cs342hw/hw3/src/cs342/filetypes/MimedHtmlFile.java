// https://docs.oracle.com/javase/8/docs/api/java/io/File.html
import java.io.File;
// https://docs.oracle.com/javase/8/docs/api/java/util/ArrayList.html
import java.util.ArrayList;

/**
 * Class for representing HTML files (mime type text/html).
 */
public class MimedHtmlFile extends MimedTextType implements Textual {

  MimedHtmlFile(File file) {
    super(file);
  }

  public String getMimeSubTypeName() {
    return "html";
  }

  public ArrayList<String> getLinesOfText() {
    return this.getLines();
  }
}
