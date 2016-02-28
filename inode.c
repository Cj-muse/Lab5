#include "ext2.h"

int getInodeNumberFromFile(char *filename)
{
  char path[10][32];
  int numberOfFiles = 0;
  int i = 0;
  u16 blk, iblk;


  printf("GetInodeNumberFromFile() \n");
  printf("filename = %s\n", filename);

  //parse filename into a char *path[MAX]
  numberOfFiles = parseInput(filename, path, "/");
  while(i < numberOfFiles)
  {
    printf("path[%d] = %s\n", i, path[i]);
    i++;
  }

  getblk(2, buffer); // get the group descriptor
  gp = (GD *)buffer;
  iblk = (u16)gp->bg_inode_table; //get the inode begin block
  printf("iblk=%d\n", iblk);
  getblk(iblk, buffer);  /* read first inode block */
  ip = (INODE *)buffer +1;

  //search directory for current file in path.
  // inode = searchDirectory(dirptr, filename);

  //search through path for dir entry that matches basename.


  //return inode number;
}

/*int clear_bss(segment, tsize, dsize, bsize)
u16 segment, tsize, dsize, bsize;
{
   u16 i,j, seg, tdsize, rem;

   tdsize = tsize + dsize;
   seg = segment + (tdsize)/16;

   rem = tdsize % 16;

   for (i=0; i<rem; i++)
     put_byte(0, seg, i);

   for (j=0; j<bsize; j++)
    put_byte(0, seg, j + i);
}
*/

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
