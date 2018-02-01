#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solveSK.h"

//board is n by n

char ** loadBoard(const char * filePath, int *n);
void printBoard(char ** board, int n);

char base_char;

void testSolveSK(){
    int n;
    char ** board = loadBoard("puzzle.txt", &n);
    printBoard(board, n);
    printf("-----------------------------------Solving sudoku-----------------------------\n");
    solveSK(board, n);
    printBoard(board, n);
    printf("------------------------------------------------------------------------------\n");
 }

int main()
{
    testSolveSK();
    return 0;
}

char ** loadBoard(const char * filePath, int *n){
    FILE *fp;
    char line[300];
    fp = fopen (filePath, "r");
    if (fp == NULL) {
        printf("file %s can not be found!!!\n Program exiting...\n", filePath);
        exit(EXIT_FAILURE);
    }
    if(fgets ( line, sizeof(line), fp ) != NULL ){
        *n = atoi(line);
    }
    printf("n= %d\n", *n);
    // if(*n <= 9){
    //     base_char = '1';
    // }else{
    //     base_char = 'a';
    // }
    base_char = 'a';

    int squareN = *n * *n;
    char ** board = (char**)malloc(sizeof(char*) * squareN );
    int i, j;
    for(i = 0; i < squareN; i++) board[i] = (char*)malloc(sizeof(char)* squareN);
    i = 0;
    while(fgets(line, sizeof(line),fp) != NULL ) /* read a line */
    {    j = 0;
         char *token = strtok (line," \n");
         if(token != NULL){
            if(strcmp(token,"-") == 0) board[i][j++] = '-';
            else board[i][j++] = token[0];
         }
         while (token != NULL){
            token = strtok (NULL, " \n");
            if(token != NULL){
                if(strcmp(token,"-") == 0) board[i][j++] = '-';
                else board[i][j++] = token[0];
            }
         }
         i++;
    }
    fclose(fp);
    return board;
}

void printBoard(char ** board, int n){
// It is required to add more code to make the board print out nicer than this
    int i, j;
    for(i = 0; i < n; i ++){
        for(j = 0; j < n ; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}
