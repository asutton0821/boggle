//boggle.h
//Copyright colson Sutton 2017

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

//Board Definitions
#define SIZE 178691 //size of the file
// 

char * array[SIZE];
char * words[SIZE];

int wordCount=0;
int rows=0,cols=0,wordLength = 0,points = 0,using = 1;

int rowNum[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int colNum[] = {-1, 0, 1, -1, 1, -1, 0, 1};


//method declarations
void init(char board[rows][cols]);
char generateRandom(void);
void readFile (char *);
void fillBoard (char board[rows][cols]);
void printBoard (char board[rows][cols]);
void printArray (char *array[]) ;
int binsearch (char *[], int , char *);
void searchBoggle(char [rows][cols], int , int ,int , int , char* ,char * , int , int );
void findWords(char [rows][cols], char* , int );
bool isvalid(int , int , int, int);
int findInArray(char * [], int , char * );
void autoSearch(char board[rows][cols]);
void printWordsArray(char * [], int );
int scoreTotal(char * [], int );
void writeToFile(char *, char[rows][cols], char *[]);
void freeArray(char * []);
void freeWords(char * []);

         
