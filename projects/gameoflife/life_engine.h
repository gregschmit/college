/*
 * Programmer:  Gregory N. Schmit
 * Date:        20160604
 * Program:     Game of Life Engine
 * Description: Backend engine for the game of life. nextstate is a helper
 *              function for nextgen, but nextgen is the main function that
 *              takes a C-style 2D array and returns the next generation.
 *
 *              Note: Using this methodology requires us to store the entire
 *              gamespace in memory twice (input and return), so it will not
 *              scale in a sensible way. This engine is not designed to.
 */

/*
 * nextstate is a helper for nextgen that takes the entire field and a position
 * and returns whether that cell ought to be dead (0) or alive (1) in the next
 * generation. -gns
 */
int nextstate(int **g0, int x, int y);

/*
 * nextgen is the main function that takes in a C-style array and the length in
 * the style g0[x][y]. Note that many C arrays-of-arrays are indexed like
 * array[y][x]; not this one. -gns
 */
int **nextgen(int **g0, int lenx, int leny);
