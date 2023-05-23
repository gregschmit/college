// https://docs.oracle.com/javase/8/docs/api/java/io/File.html
import java.io.File;
// https://docs.oracle.com/javase/8/docs/api/java/io/IOException.html
import java.io.IOException;
// https://docs.oracle.com/javase/8/docs/api/javax/imageio/ImageIO.html
import javax.imageio.ImageIO;
// https://docs.oracle.com/javase/8/docs/api/java/awt/image/BufferedImage.html
import java.awt.image.BufferedImage;

/**
 * Class for representing PNG files (mime type image/png).
 */
public class MimedPngFile extends MimedImageType {

  MimedPngFile(File file) {
    super(file);
  }

  public String getMimeSubTypeName() {
    return "png";
  }
}
