package uic.redlightcams;

/**
 * Exception class that describes that something went wrong when trying to
 * process and filter JSON data.
 */
public class FilterException extends Exception {

  FilterException(String message) {
    super(message);
  }
}