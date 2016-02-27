#include "ext2.h"

int getInodeNumberFromFile(char *filename)
{
  char path[10][32];
  int numberOfFiles = 0;
  int i = 0;

  printf("GetInodeNumberFromFile() \n");
  printf("filename = %s\n", filename);

  //parse filename into a char *path[MAX]
  numberOfFiles = parseInput(filename, path, "/");
  while(i < numberOfFiles)
  {
    printf("path[%d] = %s\n", i, path[i]);
    i++;
  }

  //search through path for dir entry that matches basename.

  //return inode number;
}

int parseInput(char *input, char parsedinput[10][32], char *delimiter)
{
	int i = 0;
	char *token = "0";
	char line[MAX];
	strcpy(line, input);

  //get first token from strtok
  token = strtok(line, delimiter);
  strcpy(parsedinput[i],token);

  //get the rest of the tokens and put into input
  i = 1;
  while((token = strtok(NULL, delimiter))!= NULL )
  {
	   //parsedinput[i] = (char*)calloc(MAX, sizeof(char));
	   strcpy(parsedinput[i],token);
     i++;
  }

  //number of seperate filenames returned
  return i;
}
