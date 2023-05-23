/**
 * File type registery for mapping file type extensions to their implementing
 * class.
 *
 * You should not make any changes to this file.
 */

import java.io.File;

public class Registery {

  public static MimedFile loadMimedFile(String filePath) {

    String[] filePathParts = filePath.split("\\.");

    if (filePathParts.length == 0) {
      return null;
    }

    File providedFile = new File(filePath);

    String extension = filePathParts[filePathParts.length - 1];
    switch (extension) {
      case "txt":
        return new MimedTextFile(providedFile);

      case "html":
        return new MimedHtmlFile(providedFile);

      case "jpg":
      case "jpeg":
        return new MimedJpegFile(providedFile);

      case "jar":
        return new MimedJarFile(providedFile);

      case "js":
        return new MimedJavascriptFile(providedFile);

      case "pdf":
        return new MimedPdfFile(providedFile);

      case "png":
        return new MimedPngFile(providedFile);

      case "zip":
        return new MimedZipFile(providedFile);

      default:
        return null;
    }
  }
}