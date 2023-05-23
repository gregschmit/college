// https://docs.oracle.com/javase/8/docs/api/java/io/File.html
import java.io.File;
// https://docs.oracle.com/javase/8/docs/api/javax/imageio/ImageIO.html
import javax.imageio.ImageIO;
// https://docs.oracle.com/javase/8/docs/api/java/awt/image/BufferedImage.html
import java.awt.image.BufferedImage;
// https://docs.oracle.com/javase/8/docs/api/java/io/IOException.html
import java.io.IOException;

/**
 * Class for representing JPG files (mime type image/jpeg).
 */
public class MimedJpegFile extends MimedImageType {

  MimedJpegFile(File file) {
    super(file);
  }

  public String getMimeSubTypeName() {
    return "jpeg";
  }
}
