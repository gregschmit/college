package uic.redlightcams;

import java.io.File;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.StringJoiner;
import java.util.stream.Stream;
import org.json.JSONArray;
import uic.redlightcams.DataPoint;
import uic.redlightcams.FilterException;
import uic.redlightcams.config.FilterParams;
import uic.redlightcams.enums.Column;
import uic.redlightcams.enums.OutputOptions;
import uic.redlightcams.enums.SortDirection;


/**
 * Class that handles the hard work of reading DataPoint records out of
 * a JSON file, and then filtering them accoring to some given configuraiton
 * parameters.
 */
public class Filter {

  protected List<DataPoint> data;

  /**
   * Constructor for object for filtering DataPoint results.
   *
   * @param jsonRecords Stream  A stream of JSONArray items, each describing a
   *                            single redlight camera datapoint.
   *
   * @throws FilterException If there was an error processing, or otherwise
   *                         processing the data set.
   */
  public Filter(Stream<JSONArray> jsonRecords) throws FilterException {
    // Your code should do something here to parse the inputFile into a series
    // uic.redlightcams.DataPoint objects.
    data = new ArrayList<DataPoint>();
    jsonRecords.forEach(entry -> data.add(new DataPoint(entry)));
  }

  /**
   * Helper method to calculate distance from UIC given lat/long.
   *
   * @param lat1 Double A number representing the latitude of the target
   *
   * @param long1 Double A number representing the longitude of the target
   *
   * @return Double The distance in miles
   */
  private Double distfromuic(Double lat1, Double long1) {
    double lat2 = 41.8720;
    double long2 = -87.6490;
    double earthRadius = 3958.756;
    double deltaLong = (lat2 - lat1) * Math.PI / 180.0;
    double deltaLat = (long2 - long1) * Math.PI / 180.0;
    double a = (Math.sin(deltaLat / 2.0) * Math.sin(deltaLat / 2.0))
            + (Math.cos(lat1 * Math.PI / 180.0)
            * Math.cos(lat2 * Math.PI / 180.0)
            * Math.sin(deltaLong / 2.0)
            * Math.sin(deltaLong / 2.0));
    return new Double(earthRadius * (2.0 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a))));
  }

  /**
   * Generates textual description of the data set.
   *
   * <p>The returned textual description should reflect the inital data set,
   * with the filtering, sorting and aggregating parameters described by
   * the provided filtering paramters applied.
   *
   * <p>In the general case, this will be a rows of columns:
   *   - Intersection
   *   - Camera ID
   *   - Address
   *   - Date
   *   - Num Violations
   *   - Latitude
   *   - Longitude
   *
   * <p>If, though, were aggregating / merging all dates for each camera, then
   * the generated rows should have the columns:
   *   - Intersection
   *   - Camera ID
   *   - Address
   *   - Sum of Num Violations, across all dates
   *   - Latitude
   *   - Longitude
   *
   * @param params FilterParams Settings describing how to modify or restrict
   *                            the data set.
   * @param outputType OutputOptions The type of output to generate (JSON or
   *                                 or CSV).
   *
   * @return String A textual description of the sorted, filtered and aggregated
   *                data set.
   *
   * @throws FilterException If there was an error processing, or otherwise
   *                         processing the data set.
   */
  public String generateReport(FilterParams params, OutputOptions outputType)
      throws FilterException {
    // filter column
    if (params.getFilterColumn() != null && params.getFilterValue() != null) {
      switch (params.getFilterColumn()) {
        case INTERSECTION:
          this.data.removeIf(entry ->
              entry.intersection != params.getFilterValue()
          );
          break;
        case CAMERA_ID:
          this.data.removeIf(entry ->
              !entry.id.equals(Integer.parseInt(params.getFilterValue())));
          break;
        case ADDRESS:
          this.data.removeIf(entry -> {
            return !entry.address.equals(params.getFilterValue());
          });
          break;
        case DATE:
          //DateTimeFormatter formatter = DateTimeFormatter
          //  .ofPattern("yyyy-MM-dd'T'HH:mm:ss");
          LocalDateTime mydate = LocalDateTime.parse(params.getFilterValue());
          this.data.removeIf(entry -> entry.date.equals(mydate));
          break;
        case VIOLATIONS:
          this.data.removeIf(entry ->
              !entry.violationCount.equals(Integer.parseInt(params.getFilterValue())));
          break;
        case LATITUDE:
          this.data.removeIf(entry ->
              Math.abs(entry.latitude
              - Double.parseDouble(params.getFilterValue())) >= 0.1);
          break;
        case LONGITUDE:
          this.data.removeIf(entry ->
              Math.abs(entry.longitude
              - Double.parseDouble(params.getFilterValue())) >= 0.1);
          break;
        default:
          break;
      }
    }
    // sort
    if (params.getSortColumn() != null && params.getSortDirection() != null) {
      switch (params.getSortColumn()) {
        case INTERSECTION:
          if (params.getSortDirection() == SortDirection.ASC) {
            this.data.sort((e1, e2) ->
                e1.intersection.compareTo(e2.intersection));
          } else {
            this.data.sort((e1, e2) ->
                e2.intersection.compareTo(e1.intersection));
          }
          break;
        case CAMERA_ID:
          if (params.getSortDirection() == SortDirection.ASC) {
            this.data.sort((e1, e2) -> e1.id.compareTo(e2.id));
          } else {
            this.data.sort((e1, e2) -> e2.id.compareTo(e1.id));
          }
          break;
        case ADDRESS:
          if (params.getSortDirection() == SortDirection.ASC) {
            this.data.sort((e1, e2) -> e1.address.compareTo(e2.address));
          } else {
            this.data.sort((e1, e2) -> e2.address.compareTo(e1.address));
          }
          break;
        case DATE:
          if (params.getSortDirection() == SortDirection.ASC) {
            this.data.sort((e1, e2) -> e1.date.compareTo(e2.date));
          } else {
            this.data.sort((e1, e2) -> e2.date.compareTo(e1.date));
          }
          break;
        case VIOLATIONS:
          if (params.getSortDirection() == SortDirection.ASC) {
            this.data.sort((e1, e2) ->
                e1.violationCount.compareTo(e2.violationCount));
          } else {
            this.data.sort((e1, e2) ->
                e2.violationCount.compareTo(e1.violationCount));
          }
          break;
        case LATITUDE:
          if (params.getSortDirection() == SortDirection.ASC) {
            this.data.sort((e1, e2) -> e1.latitude.compareTo(e2.latitude));
          } else {
            this.data.sort((e1, e2) -> e2.latitude.compareTo(e1.latitude));
          }
          break;
        case LONGITUDE:
          if (params.getSortDirection() == SortDirection.ASC) {
            this.data.sort((e1, e2) -> e1.longitude.compareTo(e2.longitude));
          } else {
            this.data.sort((e1, e2) -> e2.longitude.compareTo(e1.longitude));
          }
          break;
        default:
          break;
      }
    }
    // filter miles from uic
    if (params.getMilesFromUic() != null) {
      this.data.removeIf(entry ->
          distfromuic(entry.latitude, entry.longitude) > params.getMilesFromUic()
      );
    }
    // merge data
    if (params.getShouldMerge()) {
      ArrayList<DataPoint> newdata = new ArrayList<DataPoint>();
      while (data.size() > 0) {
        DataPoint current = data.get(0);
        DataPoint mergeEntry = new DataPoint(current);
        mergeEntry.violationCount = new Integer(0);
        mergeEntry.isMerged = true;
        ArrayList<DataPoint> found = new ArrayList<DataPoint>();
        for (DataPoint entry : data) {
          if (entry.id.equals(current.id)) {
            found.add(entry);
            mergeEntry.violationCount += entry.violationCount;
          }
        }
        data.removeAll(found);
        newdata.add(mergeEntry);
      }
      this.data = newdata;
    }
    // output as csv or json
    String out;
    switch (outputType) {
      case CSV:
        StringJoiner preCsv = new StringJoiner("\n", "", "\n");
        for (DataPoint element : this.data) {
          StringJoiner line = new StringJoiner(",");
          line.add(element.intersection)
            .add(element.id.toString())
            .add(element.address);
          if (element.isMerged) {
            line.add(element.violationCount.toString());
          } else {
            line.add(element.date.format(DateTimeFormatter.ISO_LOCAL_DATE_TIME))
              .add(element.violationCount.toString());
          }
          line.add(element.latitude.toString())
            .add(element.longitude.toString());
          preCsv.add(line.toString());
        }
        out = preCsv.toString();
        break;
      case JSON:
        StringJoiner preJson = new StringJoiner(",\n  ", "[\n  ", "\n]\n");
        for (DataPoint element : this.data) {
          StringJoiner line = new StringJoiner("\",\n    \"", "[\n    \"", "\"\n  ]");
          line.add(element.intersection)
            .add(element.id.toString())
            .add(element.address);
          if (element.isMerged) {
            line.add(element.violationCount.toString());
          } else {
            line.add(element.date.format(DateTimeFormatter.ISO_LOCAL_DATE_TIME))
              .add(element.violationCount.toString());
          }
          line.add(element.latitude.toString())
            .add(element.longitude.toString());
          preJson.add(line.toString());
        }
        out = preJson.toString();
        break;
      default:
        out = new String("\n");
        break;
    }
    return out;
  }
}
