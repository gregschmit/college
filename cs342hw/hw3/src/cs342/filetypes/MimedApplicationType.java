// https://docs.oracle.com/javase/8/docs/api/java/io/File.html
import java.io.File;
// https://docs.oracle.com/javase/8/docs/api/java/util/ArrayList.html
import java.util.ArrayList;

import java.util.zip.ZipFile;
import java.util.zip.ZipEntry;
import java.util.zip.ZipException;
import java.util.Collections;
import java.util.Enumeration;
import java.io.IOException;

/**
 * Class for representing Application files (mime type application).
 */
public abstract class MimedApplicationType extends MimedFile {

  MimedApplicationType(File file) {
    super(file);
  }

  public String getMimeTopLevelTypeName() {
    return "application";
  }

  protected Integer getNumFilesArchived() {
    ZipFile zip = null;
    try {
      zip = new ZipFile(this.file);
    } catch (IOException e) {
      System.err.println("fileinfo: error inspecting ZIP/JAR archive");
      return 0;
    }
    Enumeration<? extends ZipEntry> entries = zip.entries();
    int n = 0;
    while (entries.hasMoreElements()) {
      if (!entries.nextElement().isDirectory()) {
        n++;
      }
    }
    return n;
  }
}
