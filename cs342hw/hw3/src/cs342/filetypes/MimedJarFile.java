// https://docs.oracle.com/javase/8/docs/api/java/io/File.html
import java.io.File;
// https://docs.oracle.com/javase/8/docs/api/java/io/IOException.html
import java.io.IOException;
// https://docs.oracle.com/javase/8/docs/api/java/util/zip/ZipFile.html
import java.util.zip.ZipFile;
// https://docs.oracle.com/javase/8/docs/api/java/util/zip/ZipException.html
import java.util.zip.ZipException;

/**
 * Class for representing Jar files (mime type application/x-java-archive).
 */
public class MimedJarFile extends MimedApplicationType implements Multipart {

  MimedJarFile(File file) {
    super(file);
  }

  public String getMimeSubTypeName() {
    return "x-java-archive";
  }

  public Integer getNumParts() {
    return this.getNumFilesArchived();
  }
}
