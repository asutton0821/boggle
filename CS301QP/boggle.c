
#include "boggle.h"
/*
Copyright Colson Sutton 2017

Boggle is a wordsearch game in which you can form words of any letters from any direction on the board. 

*/


/*

This function allows the board to be initialized to 0 so that the board can have a place in RAM. It's just to be safe, to make sure that memory is allocated for it. 

*/
void
init (char board[rows][cols])
{

  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
	board[i][j] = 0;
    }
}

/*

This is the write to file method. After the game is over, the user can pull up the Boggle.txt file and see the words they found, their board, and the points that they scored. 

*/

void
writeToFile (char *fileName, char board[rows][cols], char *word[SIZE])
{
  FILE *fp = fopen (fileName, "w");
  fprintf (fp, "Boggle.c\n");
  fprintf (fp, "Board is %dx%d\n", rows, cols);
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
	{
	  fprintf (fp, " %c ", board[i][j]);
	}
      fprintf (fp, "\n");
    }
  fprintf (fp, "You found %d words and obtained %d points\n", wordLength,
	   points);
  fprintf (fp, "\n\nWords found: \n");
  for (int k = 0; k < wordLength; k++)
    {
      fprintf (fp, "%s\n", words[k]);
    }
  fclose (fp);
//      free(fp); //free the file
}

/*

This function allows us to generate the letters based on the frequency of words used in the board. This allows us to 
maintain a constant ratio of consonants to vowels. 

*/

char
generateRandom ()
{
  double i = rand () % 1000000;
  i = i / 1000000;
  if (i < .08167)
    {
      return 'a';
    }
  if (i < .09659)
    {
      return 'b';
    }
  if (i < .12441)
    {
      return 'c';
    }
  if (i < .16694)
    {
      return 'd';
    }
  if (i < .29396)
    {
      return 'e';
    }
  if (i < .31624)
    {
      return 'f';
    }
  if (i < .33639)
    {
      return 'g';
    }
  if (i < .39733)
    {
      return 'h';
    }
  if (i < .46699)
    {
      return 'i';
    }
  if (i < .46852)
    {
      return 'j';
    }
  if (i < .47624)
    {
      return 'k';
    }
  if (i < .51649)
    {
      return 'l';
    }
  if (i < .54055)
    {
      return 'm';
    }
  if (i < .60804)
    {
      return 'n';
    }
  if (i < .68311)
    {
      return 'o';
    }
  if (i < .70240)
    {
      return 'p';
    }
  if (i < .70335)
    {
      return 'q';
    }
  if (i < .76322)
    {
      return 'r';
    }
  if (i < .82649)
    {
      return 's';
    }
  if (i < .91705)
    {
      return 't';
    }
  if (i < .94463)
    {
      return 'u';
    }
  if (i < .95441)
    {
      return 'v';
    }
  if (i < .97801)
    {
      return 'w';
    }
  if (i < .97951)
    {
      return 'x';
    }
  if (i < .99925)
    {
      return 'y';
    }
  if (i < 1)
    {
      return 'z';
    }
  else
    {
      return 'e';
    }
}

/*

This function allows us to read the dictionary file, initiate space in memory for the words, and throw them into a dictionary. This allows 
for much easier searching of the board and array.

*/

void
readFile (char *fileName)
{
  int i = 0;
  char line[50];
  FILE *file;
  file = fopen (fileName, "r");
  while (fgets (line, sizeof line, file) != NULL)
    {
      //printf ("%s", line);
      array[i] = malloc (sizeof (line));
      strcpy (array[i], line);
      array[i][strlen (array[i]) - 1] = '\0';
      i++;
      wordCount++;
    }
  fclose (file);
  // free(file);
}

/*

This fills the board with random letters by calling generateRandom(), replacing the 0's that the board is currently initialized to. 

*/

void
fillBoard (char board[rows][cols])
{

  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
	{
	  board[i][j] = generateRandom ();
	}
    }
}

/*

This prints the board in a nice, organized fashion with enough space for the user to see.

*/

void
printBoard (char board[rows][cols])
{
  printf ("\n\n");
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
	{
	  printf ("%c ", board[i][j]);
	}
      printf ("\n");
    }
  printf ("\n\n");
}

/*

This method is mainly for debugging purposes but allows any array to be printed. This was used to debug the word array.

*/

void
printArray (char *array[SIZE])
{
  printf ("printing now: ");
  for (int i = 0; i < SIZE; i++)
    {
      printf ("%s\n", array[i]);
    }
}

/*

This is a modified version of binary search. Instead of using bsearch that is built into C, 
I built my own. This allows us to quickly find a word and make sure that it does exist within the
dictionary array. 

*/


int
binsearch (char *str[], int max, char *value)
{
  int position, begin = 0, end = max - 1, cond = 0;
  while (begin <= end)
    {
      position = (begin + end) / 2;
      if ((cond = strcmp (str[position], value)) == 0)
	{
	  return position;
	}
      else if (cond < 0)
	{
	  begin = position + 1;
	}
      else
	{
	  end = position - 1;
	}
    }
  return -1;

}

/*

This function is a little tricky. It is the recursive function that allows us 
make words using adjacency. It first makes sure that the current character in the word
matches the next character in the word. If the index is equal, then it will start by
making sure the word is a valid word in the dictionary file, make sure that it has 
also not been used/found already. If it is, then it won't return anything. 
Now in all 8 directions of every letter, we can use isValid to make sure that 
the letter we currently have is adjacent to the other letters. And if so, search 
for that letter. If all the indices match, then we can return true for that word. 

*/

void
searchBoggle (char board[rows][cols], int row, int col,
	      int prevRow, int prevCol, char *word,
	      char *path, int index, int n)
{
  // return if current character doesn't match with
  // the next character in the word
  if (index > n || board[row][col] != word[index])
    return;

  if (index == n)
    {
      if (binsearch (array, SIZE, word) != -1)
	{
	  if (findInArray (words, wordLength, word) == 0)
	    {
	      //printf("found word: %s @ %d %d\n", word, row, col);
	      printf ("found word not in found list: %s\n", word);
	      words[wordLength] = malloc (sizeof (char *));
	      strcpy (words[wordLength], word);
	      wordLength++;
	      // printf("word length is %d\n",wordLength);
	    }
	  else if (findInArray (words, wordLength, word) == 1)
	    {
	      //printf("word %s exists already! try again \n",word);
	      return;
	    }
	}
    }

  // Recur for all connected neighbours
  for (int k = 0; k < 8; ++k)
    if (isvalid (row + rowNum[k], col + colNum[k], prevRow, prevCol))

      searchBoggle (board, row + rowNum[k], col + colNum[k],
		    row, col, word, path, index + 1, n);
}


/*

This will allow us to call searchBoggle, by iterating through the entire board. 

*/

void
findWords (char board[rows][cols], char *word, int n)
{
  // traverse through the all cells of given matrix
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)

      // occurrence of first character in matrix
      if (board[i][j] == word[0])

	// check and print if path exists
	searchBoggle (board, i, j, -1, -1, word, "", 0, n);
}

/*

This function makes sure that the next element is adjacent by using the rowNum and colNum table provided. 

*/

bool
isvalid (int row, int col, int prevRow, int prevCol)
{
  // return true if row number and column number
  // is in range
  return (row >= 0) && (row < rows) &&
    (col >= 0) && (col < cols) && !(row == prevRow && col == prevCol);
}

/*

This function deals with the autosearching of the array, and allows the game to automatically find words for you. 

*/

void
autoSearch (char board[rows][cols])
{
  for (int i = 0; i < wordCount; i++)
    {
      findWords (board, array[i], strlen (array[i]) - 1);
} }

/*

This function specifically pertains to the printWordsArray, which will display any words that are found. 

*/

void
printWordsArray (char *words[SIZE], int length)
{
  for (int i = 0; i < length; i++)
    {
      printf ("%s\n", words[i]);
} }

/*

This function handles the findInArray, which will allow us to search the words array to see if the word has already been used.
If so, we return 1, otherwise we return 0. 

*/

int
findInArray (char *words[SIZE], int length, char *word)
{
  for (int i = 0; i < length; i++)
    {
      if (strcmp (words[i], word) == 0)
	{
	  // printf("%s matches %s", words[i], word);
	  // printf("word exists");
	  return 1;
	}
    }
  return 0;
}

/*

This scoreTotal function allows us to create the points system that will keep track of the user's points throughout the game. 


The scoring algorithm follows boggle's scoring guidelines. 
*/

int
scoreTotal (char *words[SIZE], int length)
{
  for (int i = 0; i < length; i++)
    {
      if (strlen (words[i]) < 4)
	{
	  points += 1;
	}
      if (strlen (words[i]) == 5)
	{
	  points += 2;
	}
  if (strlen (words[i]) == 6)
	{
	  points += 3;
	}
  if (strlen (words[i]) == 7)
	{
	  points += 5;
	}
  if (strlen (words[i]) > 7)
	{
	  points += 11;
	}
  
  
  
    }
  return points;
}

/*

This allows us to free the array that is used for storing the words. 

*/

void
freeArray (char *array[SIZE])
{
  for (int i = 0; i < wordCount; i++)
    {
      free (array[i]);
    }

}

void
freeWords (char *array[SIZE])
{
  for (int i = 0; i < wordLength; i++)
    {
      free (array[i]);
    }

}

/*

The main function handles all the details of the game, along with some of the basic logic and calling the functions together. 
You can use "auto" to have boggle automatically find words, use "print" to be able to see the words you've found, use "quit" to quit the game, or use "board" to print the 
board again. 

The program can take two command-line arguments to change the dimension of the board, otherwise it defaults to the boggle standard of 4 x 4. 


*/

int
main (int argc, char **argv)
{

  printf ("loaded\n\n\n");
  printf
    ("\n\nWelcome to Boggle!\n\nIn this game, you will type words that you see until you can't find anymore!\nYou will be rewarded points based upon the amount of words you find!\nType 'auto' to let the computer find the words for you,\nType 'print' to print the words you've found,\nType 'board' to reprint the board,\nor Type 'quit' to quit the game!\n\n");
  
    if(argc > 1){
       rows = atoi (argv[1]);
        cols = atoi (argv[2]);
    }
    else{
      rows = 4;
      cols = 4;
      
    }
  if (rows < 4 || cols < 4)
    {
      while(rows < 4 && cols < 4){
      printf ("enter row number 4 or above: ");
      scanf ("%d", &rows);
      printf ("enter col number 4 or above: ");
      scanf ("%d", &cols);
      }
    }
  if (argc != 3)
    {
      rows = 4;
      cols = 4;
    }

  char board[rows][cols];
  init (board);
  readFile ("words2.txt");
  srand (time (NULL));
  fillBoard (board);
  printBoard (board);
  char *word = malloc (sizeof (char *));



  while (using)
    {
      printf ("Enter a word you see or a command: ");
      scanf ("%s", word);
      if (strcmp (word, "quit") == 0)
	{
	  printf ("quitting program\n");
	  printf ("You found %d words. You have %d points! ", wordLength,
		  scoreTotal (words, wordLength));
	  writeToFile ("Boggle.txt", board, words);
	  printf ("See Boggle.txt to view your game!");
	  free (word);
	  freeArray (array);
	  freeWords (words);
	  return 0;

	}
      if (strcmp (word, "auto") == 0)
	{
	  autoSearch (board);

	}
      if (strcmp (word, "print") == 0)
	{
	  printWordsArray (words, wordLength);
	}
      if (strcmp (word, "board") == 0)
	{
	  printBoard (board);
	}
      findWords (board, word, strlen (word) - 1);
    }

  free (word);
  freeArray (array);
  freeWords (words);

  return 0;

}


/*

My Lookback:

Overall, this was a really fun and interesting project. It was definitely a challenge trying to get the searchBoggle to work perfectly, but I got it. 
I had to learn a lot about what memory management really was and how to allocate memory properly. I think now I understand it! One of the biggest problems I 
ran into on this project, though, was the fact that I couldn't create a single C file to store the main in. I couldn't get it to link. No matter what I tried,
it would complain about multiple definitions and I could not get it to stop this. However, the program works just fine, is fast and fluid, and is very fun to play. 
I love the auto feature! After finding all the words you can, auto will go through and help find words for you, adding to your points!
It's definitely a fun game! 

*/
