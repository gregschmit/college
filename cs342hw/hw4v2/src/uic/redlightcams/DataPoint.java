package uic.redlightcams;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import org.json.JSONArray;

/**
 * This class represents a single day's datapoint for information about
 * how many violations were recorded at a given location, on a give date.
 */
public class DataPoint {

  // 1.  Intersection of recording
  // 2.  ID of the camera doing the recording
  // 3.  The address of the camera
  // 4.  The date of the recording
  // 5.  Number of redlight violations that the camera recorded, on this date
  // 6.  The latitude where the camera is located
  // 7.  The longitude where the camera is located
  public String intersection;
  public Integer id;
  public String address;
  public LocalDateTime date;
  public Integer violationCount;
  public Double latitude;
  public Double longitude;
  public boolean isMerged;

  DataPoint(DataPoint entry) {
    this.intersection = new String(entry.intersection);
    this.id = new Integer(entry.id);
    this.address = new String(entry.address);
    this.date = LocalDateTime.parse(entry.date.format(DateTimeFormatter.ISO_LOCAL_DATE_TIME));
    this.violationCount = new Integer(entry.violationCount);
    this.latitude = new Double(entry.latitude);
    this.longitude = new Double(entry.longitude);
    this.isMerged = entry.isMerged;
  }

  DataPoint(JSONArray entry) {
    this.intersection = new String(entry.getString(0));
    if (!entry.isNull(1)) {
      this.id = new Integer(entry.getInt(1));
    } else {
      this.id = -1;
    }
    this.address = entry.getString(2);
    if (this.id == -1) {
      this.intersection = "UNKNOWN";
      this.address = "UNKNOWN";
    }
    this.date = LocalDateTime.parse(entry.getString(3));
    this.violationCount = new Integer(entry.getInt(4));
    this.latitude = new Double(Double.parseDouble(entry.getString(5)));
    this.longitude = new Double(Double.parseDouble(entry.getString(6)));
  }
}
