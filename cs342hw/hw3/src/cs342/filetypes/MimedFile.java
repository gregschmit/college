// https://docs.oracle.com/javase/8/docs/api/java/io/File.html
import java.io.File;

import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;

public abstract class MimedFile {

  protected File file;

  MimedFile(File file) {
    this.file = file;
  }

  /**
   * Returns the full mime type for the file type being represented.
   * For example, if a zip file is being represented, which has mime type
   * "application/zip", this method should return "application".
   *
   * You should not make any changes to this method definition.
   */
  final public String getFullMimeType() {
    return this.getMimeTopLevelTypeName() + "/" + this.getMimeSubTypeName();
  }

  /**
   * Returns the top level mime type.  For example, zip files have the mimetype
   * "application/zip".  In this case, this method should return the string
   * "application".
   */
  public abstract String getMimeTopLevelTypeName();

  /**
   * Returns the sub-type portion of this files mimetype.  For example,
   * given a zip file with the mimetype "application/zip", this method
   * should return "zip".
   */
  public abstract String getMimeSubTypeName();

  /**
   * This method should return the name of the file loaded.  This *should
   * not* include any path information.  For example, if this file was
   * loaded from "/home/user/file.txt", this method should return "file.txt".
   */
  public String getFileName() {
    return file.getName();
  }

  /**
   * Returns the size of the file being represented, as a number of bytes.
   */
  public Long getFileSize() {
    long size;
    try {
      size = file.length();
    } catch(SecurityException e) {
      System.err.println("fileinfo: Could not determine file size! (exists?"
        + "permissions?)");
      size = 0L;
    }
    return size;
  }

  protected Integer getLineCount() {
    BufferedReader br = null;
    int numlines = 0;
    try {
      br = new BufferedReader(new FileReader(this.file));
    } catch (FileNotFoundException e) {
      System.err.println("fileinfo: file or directory not found");
      try {
        br.close();
      } catch (IOException ed) {
        System.err.println("fileinfo: couldn't close, but it might be ok...");
      }
      return 0;
    }
    try {
      while (br.readLine() != null) {
        numlines++;
      }
    } catch (IOException e) {
      System.err.println("fileinfo: error while reading file");
      return 0;
    }
    try {
      br.close();
    } catch (IOException e) {
      System.err.println("fileinfo: couldn't close, but it might be ok...");
    }
    return numlines;
  }

  protected ArrayList<String> getLines() {
    ArrayList<String> result = new ArrayList<String>();
    BufferedReader br = null;
    try {
      br = new BufferedReader(new FileReader(this.file));
    } catch (FileNotFoundException e) {
      System.err.println("fileinfo: file or directory not found");
      try {
        br.close();
      } catch (IOException ed) {
        System.err.println("fileinfo: couldn't close, but it might be ok...");
      }
      return null;
    }
    try {
      String line = null;
      while ((line = br.readLine()) != null) {
        result.add(line);
      }
    } catch (IOException e) {
      System.err.println("fileinfo: error while reading file");
      return null;
    }
    try {
      br.close();
    } catch (IOException e) {
      System.err.println("fileinfo: couldn't close, but it might be ok...");
    }
    return result;
  }
}
