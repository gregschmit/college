/*
 * Programmer:  Gregory N. Schmit
 * Date:        20160601
 * Program:     Permute
 * Description: Given a C-style character array, provides a list of
 *              character permutations as an array of character arrays.
 *
 *              This requires the entire result to be stored in memory, which is
 *              terrible for scaling.
 *
 *              The algorithm used is simple; the fuction creates the memory 
 *              needed and then recursively calls itself to fill in the rest.
 */

int permute_qty(int len);

char **permute(char *pstring);
