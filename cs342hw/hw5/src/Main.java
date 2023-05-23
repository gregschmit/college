import edu.uic.cs342.SentenceParser;
import edu.uic.cs342.SentenceParserException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.stream.Collectors;
import net.sourceforge.argparse4j.ArgumentParsers;
import net.sourceforge.argparse4j.impl.Arguments;
import net.sourceforge.argparse4j.inf.ArgumentParser;
import net.sourceforge.argparse4j.inf.ArgumentParserException;
import net.sourceforge.argparse4j.inf.Namespace;


/**
 * Main entry class for HW5.
 */
public class Main {

  /**
   * Entry point for the sentparse application.
   *
   * @param args String[] The commandline provided argments.
   */
  public static void main(String[] args) {

    ArgumentParser argParser = ArgumentParsers
        .newArgumentParser("sentparse")
        .defaultHelp(true);

    argParser.addArgument("--path")
        .help("A file path to read a text from.  If not provided, text is read"
              + " from STDIN.");

    Namespace res;
    try {
      res = argParser.parseArgs(args);
    } catch (ArgumentParserException e) {
      argParser.handleError(e);
      System.exit(1);
      return;
    }

    String inputPath = res.get("path");
    Charset utf8 = StandardCharsets.UTF_8;
    String inputText = null;

    if (inputPath != null) {

      try {
        Path path = FileSystems.getDefault().getPath(inputPath);
        inputText = Files.readAllLines(path, utf8).stream()
            .collect(Collectors.joining("\n"));
      } catch (java.io.IOException error) {
        System.err.print(error.toString());
        System.exit(1);
      }

    } else {

      inputText = new BufferedReader(new InputStreamReader(System.in))
          .lines()
          .collect(Collectors.joining("\n"));

    }

    SentenceParser parser = new SentenceParser();
    try {
      String parserOutput = parser.asList(inputText).stream()
          .collect(Collectors.joining("\n"));
      System.out.print(parserOutput);
    } catch (SentenceParserException error) {
      System.err.print(error.toString());
      System.exit(1);
    }
  }
}
