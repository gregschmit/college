/**
 * @file
 * Skeleton code for the homework three assignment for CS 342.
 *
 * You should not make any changes to this file.
 */

import java.lang.StringBuilder;

public class Main {

  public static String fileDescription(MimedFile aFile) {

    StringBuilder descBuilder = new StringBuilder();
    descBuilder.append("File name: " + aFile.getFileName() + "\n");
    descBuilder.append("File size: " + Long.toString(aFile.getFileSize()) + "\n");
    descBuilder.append("Mime type: " + aFile.getFullMimeType() + "\n");

    if (aFile instanceof Graphical) {
      Graphical graphicalFile = (Graphical) aFile;
      descBuilder.append("Height: " + graphicalFile.getHeight() + "\n");
      descBuilder.append("Width: " + graphicalFile.getWidth() + "\n");
    }

    if (aFile instanceof Multipart) {
      Multipart multipartFile = (Multipart) aFile;
      descBuilder.append("Num sub parts: " + multipartFile.getNumParts() + "\n");
    }

    if (aFile instanceof Textual) {
      Textual textualFile = (Textual) aFile;
      Integer numLines = textualFile.getNumberOfLines();

      descBuilder.append("Number of lines of text: " + Integer.toString(numLines) + "\n");

      if (numLines.intValue() > 0) {
        String firstLine = textualFile.getLinesOfText().get(0);
        descBuilder.append("First line: \n\t");
        descBuilder.append(firstLine);
        descBuilder.append("\n");
      }
    }

    return descBuilder.toString();
  }

  public static void main(String[] args) {

    for (String aFilePath : args) {
      MimedFile mimedFile = Registery.loadMimedFile(aFilePath);

      if (mimedFile == null) {
        System.err.println("Unable to load and determine the type of the file: " + aFilePath);
        System.exit(1);
      }

      String fileDescription = Main.fileDescription(mimedFile);
      System.out.println(fileDescription);
    }
  }
}