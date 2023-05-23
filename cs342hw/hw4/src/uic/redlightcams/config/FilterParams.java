package uic.redlightcams.config;

import uic.redlightcams.enums.Column;
import uic.redlightcams.enums.SortDirection;

/**
 * Class that represents a set of filter instructions that should, elsewhere,
 * be applied to a set of DataPoints.
 */
public class FilterParams {
  
  private Column filterColumn;
  private String filterValue;
  private Column sortColumn;
  private SortDirection sortDirection;
  private Integer milesFromUic;
  private Boolean shouldMerge = false;

  /**
   * Set which column the dataset should be filtered by.
   *
   * @param filterCol Column The column to filter the data set by.
   *
   * @return FilterParams The current object, for the builder pattern.
   */
  public FilterParams setFilterColumn(Column filterCol) {
    this.filterColumn = filterCol;
    return this;
  }

  /**
   * Returns the filter column that the data set should be fitlered by.
   *
   * @return Column The column to filter by, or null if no filtering by column
   *                should be performed.
   */
  public Column getFilterColumn() {
    return this.filterColumn;
  }

  /**
   * Set the value to filter the "fitler column" by.
   *
   * @param filterVal String The value to filter the filter column by.
   *
   * @return FilterParams The current object, for the builder pattern.
   */
  public FilterParams setFilterValue(String filterVal) {
    this.filterValue = filterVal;
    return this;
  }

  /**
   * Returns the value that the filter column should be limited to.
   *
   * @return String The value to filter by, or null if no filtering should be
   *                performed.
   */
  public String getFilterValue() {
    return this.filterValue;
  }

  /**
   * Sets the column that the data set should be sorted by.
   *
   * @param sortCol Column
   *
   * @return FilterParams The current object, for the builder pattern.
   */
  public FilterParams setSortColumn(Column sortCol) {
    this.sortColumn = sortCol;
    return this;
  }

  /**
   * Returns the column that a dataset should be sorted by.
   *
   * @return Column The column that the data set should be sorted by, or
   *                null if no sorting is required.
   */
  public Column getSortColumn() {
    return this.sortColumn;
  }

  /**
   * Sets the direction that the sorting should occur in.
   *
   * @param sortDir SortDirection Whether to sort the dataset, by the sort
   *                              column, in ascending or descending order.
   *
   * @return FilterParams The current object, for the builder pattern.
   */
  public FilterParams setSortDirection(SortDirection sortDir) {
    this.sortDirection = sortDir;
    return this;
  }

  /**
   * Returns the direction that the sort column should be sorted in.
   *
   * @return SortDirection The direction the sort column should be sorted in,
   *                       or null if no sorting option is specified.
   */
  public SortDirection getSortDirection() {
    return this.sortDirection;
  }

  /**
   * Sets the maximum number of miles from UIC a datapoint can be.
   *
   * <p>All data points have a lattitude and longitude.  If this option is
   * set, it indicates that no data point located more the *miles* away
   * from UIC, shoudl be included in the dataset.
   *
   * @param miles Integer A positive number of miles
   *
   * @return FilterParams The current object, for the builder pattern.
   */
  public FilterParams setMilesFromUic(Integer miles) {
    this.milesFromUic = miles;
    return this;
  }

  /**
   * Returns the max number of miles from UIC a camera can be to be included.
   *
   * @return Integer Either a positive number of miles, or null if you should
   *                 not filter by distance.
   */
  public Integer getMilesFromUic() {
    return this.milesFromUic;
  }

  /**
   * Sets whether the data set should merge locations across dates.
   *
   * @param shouldMerge Boolean
   *
   * @return FilterParams The current object, for the builder pattern.
   */
  public FilterParams setShouldMerge(Boolean shouldMerge) {
    this.shouldMerge = shouldMerge;
    return this;
  }

  /**
   * Returns whether the data set should merge records by location, across date.
   *
   * @return Boolean
   */
  public Boolean getShouldMerge() {
    return this.shouldMerge;
  }
}