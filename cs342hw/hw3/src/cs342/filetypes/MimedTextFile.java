// https://docs.oracle.com/javase/8/docs/api/java/io/File.html
import java.io.File;
// https://docs.oracle.com/javase/8/docs/api/java/util/ArrayList.html
import java.util.ArrayList;

/**
 * Class for representing Plain (text) files (mime type text/plain).
 */
public class MimedTextFile extends MimedTextType {

  MimedTextFile(File file) {
    super(file);
  }

  public String getMimeSubTypeName() {
    return "plain";
  }
}
