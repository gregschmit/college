/**
 * This is code for HW3 in CS342.  You should not make any changes to this file.
 *
 * This interface is used for describing objects that represent multiple sub
 * parts.  Implementing classes should be able to describe the data they're
 * representing as meaningful sub-units (contained files, sub pages, etc).
 */
interface Multipart {
  /**
   * Implementing classes should implement this method to return the number of
   * elements represented by this object.  In the case of an archive, this
   * should be the number of files in the archive.  In the case of a multi-page
   * document, this should be the number of pages.
   */
  public Integer getNumParts();
}
