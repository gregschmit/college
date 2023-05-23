// https://docs.oracle.com/javase/8/docs/api/java/io/File.html
import java.io.File;
// https://docs.oracle.com/javase/8/docs/api/java/io/IOException.html
import java.io.IOException;
// https://pdfbox.apache.org/docs/2.0.5/javadocs/org/apache/pdfbox/pdmodel/PDDocument.html
import org.apache.pdfbox.pdmodel.PDDocument;
// https://pdfbox.apache.org/docs/2.0.5/javadocs/org/apache/pdfbox/pdmodel/PDPage.html
import org.apache.pdfbox.pdmodel.PDPage;
// https://pdfbox.apache.org/docs/2.0.5/javadocs/org/apache/pdfbox/pdmodel/common/PDRectangle.html
import org.apache.pdfbox.pdmodel.common.PDRectangle;
// https://pdfbox.apache.org/docs/2.0.5/javadocs/org/apache/pdfbox/pdmodel/encryption/InvalidPasswordException.html
import org.apache.pdfbox.pdmodel.encryption.InvalidPasswordException;
// https://docs.oracle.com/javase/8/docs/api/java/lang/Math.html
// (not needed by the compiler, but provided as a nudge to the programmer :)
import java.lang.Math;

/**
 * Class for representing PDF files (mime type application/pdf).
 */
public class MimedPdfFile extends MimedApplicationType implements Graphical, Multipart {

  MimedPdfFile(File file) {
    super(file);
  }

  public String getMimeSubTypeName() {
    return "pdf";
  }

  private PDRectangle getBox() {
    PDDocument doc = null;
    try {
      doc = PDDocument.load(this.file);
    } catch (IOException e) {
      System.err.println("fileinfo: couldn't open pdf");
      return null;
    }
    PDPage firstpage;
    if (doc.getNumberOfPages() > 0) {
      firstpage = doc.getPage(0);
    } else {
      System.err.println("fileinfo: pdf seems to have no pages");
      return null;
    }
    return firstpage.getArtBox();
  }

  public Integer getHeight() {
    PDRectangle box = this.getBox();
    return Math.round(box.getHeight());
  }

  public Integer getWidth() {
    PDRectangle box = this.getBox();
    return Math.round(box.getWidth());
  }

  public Integer getNumParts() {
    PDDocument doc = null;
    try {
      doc = PDDocument.load(this.file);
    } catch (IOException e) {
      System.err.println("fileinfo: couldn't open pdf");
      return null;
    }
    return doc.getNumberOfPages();
  }
}
