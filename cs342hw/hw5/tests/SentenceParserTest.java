import edu.uic.cs342.SentenceParser;
import edu.uic.cs342.SentenceParserException;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.stream.Collectors;
import org.junit.Assert;
import org.junit.Test;

public class SentenceParserTest {

  static Charset TEST_CHARSET = StandardCharsets.UTF_8;

  /**
   * Reads a file into a String, normalizing the line endings to unix endings.
   *
   * @param pathName The path to file on disk, in the tests/data subdirectory.
   *
   * @return The contents of file at the given path, as a String.
   *
   * @throws IOException If there is an error reading the file from disk.
   */
  static String fileToString(String pathName) throws IOException {
    Path filePath = FileSystems.getDefault().getPath("tests", "data", pathName);
    return Files.readAllLines(filePath, SentenceParserTest.TEST_CHARSET)
        .stream()
        .map(x -> x.trim())
        .collect(Collectors.joining("\n"));
  }

  /**
   * Turns a list of strings into a single string, by joining with "\n".
   *
   * @param inputList A list of strings.
   *
   * @return The strings in the provided list, joined with unix new line
   *         characters.
   */
  static String listToString(List<String> inputList) {
    return inputList.stream().collect(Collectors.joining("\n"));
  }

  /**
   * Runs a test text through the SentenceParser class, joined as a String.
   *
   * @param pathName The path to file on disk, in the tests/data subdirectory.
   *
   * @return The result of parsing the test text through the SentenceParser,
   *         returned as a single string, with each given sentence on
   *         a new line.
   *
   * @throws IOException If there is an error reading the file from disk.
   *
   * @throws SentenceParserException Thrown when some error occured during
   *                                 parsing a text into sentences.
   */
  static String fileToTestResult(String pathName) throws IOException, SentenceParserException {

    String fileContents = SentenceParserTest.fileToString(pathName);

    SentenceParser parser = new SentenceParser();
    List<String> testResult = parser.asList(fileContents);
    return SentenceParserTest.listToString(testResult);
  }

  /**
   * Simplest test case, with sentences ending with "."s.
   */
  @Test
  public void toSentencesExample1Test() throws IOException, SentenceParserException {

    String correctResult = SentenceParserTest.fileToString("1-correct.txt");
    String testResult = SentenceParserTest.fileToTestResult("1-test.txt");

    Assert.assertEquals(correctResult, testResult);
  }

  /**
   * Testing sentences with ellipses
   *
   * <p>Ellipses can appear to be the end of a sentence when they are not.
   */
  @Test
  public void toSentencesExample2Test() throws IOException, SentenceParserException {

    String correctResult = SentenceParserTest.fileToString("2-correct.txt");
    String testResult = SentenceParserTest.fileToTestResult("2-test.txt");

    Assert.assertEquals(correctResult, testResult);
  }

  /**
   * Testing sentences with abbreviations (such as Mr., Mrs.)
   *
   * <p>We need to distinguish between abbreviations and sentence ending periods.
   */
  @Test
  public void toSentencesExample3Test() throws IOException, SentenceParserException {

    String correctResult = SentenceParserTest.fileToString("3-correct.txt");
    String testResult = SentenceParserTest.fileToTestResult("3-test.txt");

    Assert.assertEquals(correctResult, testResult);
  }

  /**
   * Testing sentences with other sentence-ending punctuation like '!' and '?'
   */
  @Test
  public void toSentencesExample4Test() throws IOException, SentenceParserException {

    String correctResult = SentenceParserTest.fileToString("4-correct.txt");
    String testResult = SentenceParserTest.fileToTestResult("4-test.txt");

    Assert.assertEquals(correctResult, testResult);
  }

  /**
   * 5: Testing sentences with quotation marks outside of the punctuation
   *
   * <p>Proper American English places the quotation mark outside of
   *    punctuation, which means that a quote can end a sentence.
   */
  @Test
  public void toSentencesExample5Test() throws IOException, SentenceParserException {

    String correctResult = SentenceParserTest.fileToString("5-correct.txt");
    String testResult = SentenceParserTest.fileToTestResult("5-test.txt");

    Assert.assertEquals(correctResult, testResult);
  }

  /**
   * 6: Testing sentences with sentence in quotes of a parent sentence
   *
   * <p>A quoted sentence can appear to be a sentence on its own.
   */
  @Test
  public void toSentencesExample6Test() throws IOException, SentenceParserException {

    String correctResult = SentenceParserTest.fileToString("6-correct.txt");
    String testResult = SentenceParserTest.fileToTestResult("6-test.txt");

    Assert.assertEquals(correctResult, testResult);
  }

  /**
   * 7: Testing sentences where an abbreviation ends a sentence
   *
   * <p>An abbreviation can end a sentence, which means that the period used
   *    is in fact a sentence ending period.
   */
  @Test
  public void toSentencesExample7Test() throws IOException, SentenceParserException {

    String correctResult = SentenceParserTest.fileToString("7-correct.txt");
    String testResult = SentenceParserTest.fileToTestResult("7-test.txt");

    Assert.assertEquals(correctResult, testResult);
  }

  /**
   * 8: Testing sentences with double sentences in quotes of parent sentence
   *
   * <p>Multiple quoted sentences can be hard to distinguish as all part of one
   *    sentence.
   */
  @Test
  public void toSentencesExample8Test() throws IOException, SentenceParserException {

    String correctResult = SentenceParserTest.fileToString("8-correct.txt");
    String testResult = SentenceParserTest.fileToTestResult("8-test.txt");

    Assert.assertEquals(correctResult, testResult);
  }

  /**
   * 9: Testing sentences with a quoted exclamation and another *phrase*
   *
   * <p>A phrase that belongs with a quote can appear to be two sentences.
   */
  @Test
  public void toSentencesExample9Test() throws IOException, SentenceParserException {

    String correctResult = SentenceParserTest.fileToString("9-correct.txt");
    String testResult = SentenceParserTest.fileToTestResult("9-test.txt");

    Assert.assertEquals(correctResult, testResult);
  }

  /**
   * 10: Testing sentences with a quoted exclamation and another *sentence*
   *
   * <p>A separate sentence next to a quote can appear to be one sentence.
   */
  @Test
  public void toSentencesExample10Test() throws IOException, SentenceParserException {

    String correctResult = SentenceParserTest.fileToString("10-correct.txt");
    String testResult = SentenceParserTest.fileToTestResult("10-test.txt");

    Assert.assertEquals(correctResult, testResult);
  }

  /**
   * 11: Testing sentences with quantities that have a period in them
   */
  @Test
  public void toSentencesExample11Test() throws IOException, SentenceParserException {

    String correctResult = SentenceParserTest.fileToString("11-correct.txt");
    String testResult = SentenceParserTest.fileToTestResult("11-test.txt");

    Assert.assertEquals(correctResult, testResult);
  }

  /**
   * 12: Testing nested quoted sentences
   */
  @Test
  public void toSentencesExample12Test() throws IOException, SentenceParserException {

    String correctResult = SentenceParserTest.fileToString("12-correct.txt");
    String testResult = SentenceParserTest.fileToTestResult("12-test.txt");

    Assert.assertEquals(correctResult, testResult);
  }
}
