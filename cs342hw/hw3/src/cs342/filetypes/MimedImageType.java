// https://docs.oracle.com/javase/8/docs/api/java/io/File.html
import java.io.File;
// https://docs.oracle.com/javase/8/docs/api/java/util/ArrayList.html
import java.util.ArrayList;
// https://docs.oracle.com/javase/8/docs/api/javax/imageio/ImageReader.html
import javax.imageio.ImageIO;
import javax.imageio.ImageReader;
import javax.imageio.stream.ImageInputStream;
import java.io.IOException;
import java.util.Iterator;

/**
 * Class for representing Image files (mime type image).
 */
public abstract class MimedImageType extends MimedFile implements Graphical {

  MimedImageType(File file) {
    super(file);
  }

  public String getMimeTopLevelTypeName() {
    return "image";
  }

  private class ImageDims {
    int i_height;
    int i_width;
    boolean err;
    ImageDims(File file) {
      ImageInputStream stream = null;
      Iterator<ImageReader> readers = null;
      try {
        stream = ImageIO.createImageInputStream(file);
        readers = ImageIO.getImageReaders(stream);
      } catch (IOException | IllegalArgumentException e1) {
        System.err.println("fileinfo: exception while getting image dims");
        this.err = true;
      }
      if (!this.err && readers.hasNext()) {
        ImageReader reader = readers.next();
        try {
          reader.setInput(stream, true);
        } catch (IllegalArgumentException e) {
          System.err.println("fileinfo: exception while getting image dims");
          this.err = true;
        }
        if (!this.err) {
          try {
            this.i_width = reader.getWidth(0);
            this.i_height = reader.getHeight(0);
          } catch (IllegalStateException | IndexOutOfBoundsException | IOException e) {
            System.err.println("fileinfo: exception while getting image dims");
            this.err = true;
          }
        }
        reader.dispose();
      } else {
        this.err = true;
      }
      if (this.err) {
        this.i_height = 0;
        this.i_width = 0;
      }
    }
  }

  public Integer getHeight() {
    ImageDims dims = new ImageDims(this.file);
    return dims.i_height;
  }

  public Integer getWidth() {
    ImageDims dims = new ImageDims(this.file);
    return dims.i_width;
  }
}
