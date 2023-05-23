package edu.uic.cs342;

/**
 * Exception class for when something went wrong during sentence parsing.
 */
public class SentenceParserException extends Exception {

  SentenceParserException(String message) {
    super(message);
  }
}
