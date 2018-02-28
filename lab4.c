//Samuel Goldstein 55978173
//Taiki Tanaka 89214738
//Lab 4
//ICS 53 Winter 2018

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//FOR DEBUG
#define debug_printInput 0
#define HEAP_SIZE 127

#define maxLineLength 40
void getInput(void);
int allocate(int numBytes);
int freeBlock(int block);
void blocklist(void);
void writeHeap(int writeBlock, char writeChar, int numCopies);
void printHeap(int blockNum, int numBytes);
void printHeader(int headerNum);
void set_block_size(int n, char * p);
int get_block_size(char * p);
void addblock(char * p, int len);
int getBlockSize(char * p);
void setBlockSize(int n, char * p);
void setBlockNum(char * p);
int getBlockNum(char * p);
int check_allocated(char * p);
void setAllocated(char * p);
void resetAllocated(char * p);
char * findAvailableBlock(int numBytes);

static int blockCounter = 0;
static char * heap;

int main(int argc, const char * argv[])
{
    heap = (char *) malloc(HEAP_SIZE);
    setBlockNum(heap+1);
    setBlockSize(HEAP_SIZE, heap);
	getInput();
	return 0;
}

void getInput(void)
{
    if(heap == NULL)
    {
        perror("malloc error");
        exit(0);
    }
	char input[maxLineLength]="";
	char cmd[20] = "";
	int num1=-1;
	int num2=-1;
	char charInput;
	int i=0;
	char *token;


	while( (strcmp(cmd, "quit")) )
	{
	    printf("> ");
		i=0;
		if( fgets (input, maxLineLength, stdin)!=NULL )
		{
			token=strtok(input, " \n");
			strcpy(cmd, token);

			token = strtok(NULL, " \n");
			while(token!=NULL)
			{

				if(i==0)
				{
					num1 = atoi(token);
				}
				else if(i==1)
				{
					num2 = atoi(token);
				}
				else //if (i==2)
                {
                    charInput = *token;
                }
				i++;
				token = strtok(NULL, " \n");
			}
		}

		printf("Command: %s\n Arg1: %d\n Arg2: %d\n Arg3: %c\n", cmd, num1, num2,charInput);

		//GOTO CMD FUNCTIONS
		if(!strcmp(cmd, "allocate"))
		{
            allocate(0);
		}
		else if(!strcmp(cmd, "free"))
		{
		    freeBlock(0);
		}
		else if(!strcmp(cmd, "blocklist"))
		{
		    blocklist();
		}
		else if(!strcmp(cmd, "writeheap"))
		{
		    writeHeap(0,'a',0);
		}
		else if(!strcmp(cmd, "printheap"))
		{
		    printHeap(0,0);
		}
		else if(!strcmp(cmd, "printheader"))
		{
		    printHeader(0);
		}
	}
	free(heap);
}

int allocate(int numBytes)
{
    //First look for the first available block with enough space
    char * p = findAvailableBlock(numBytes);
    //p now points to the first block of
    //Now allocate the memory
    addblock(p,numBytes);
    return 0;
}

char * findAvailableBlock(int numBytes)
{
    char* iterator = heap;
    while(((iterator < heap + 127) && check_allocated(iterator + 1)) || getBlockSize(iterator) < numBytes + 2)
    {
        iterator = iterator + *iterator;
    }
    return iterator;
}

void addblock(char* p, int numBytes) {
    //Need to implement the splitting logic+++
    int newsize = numBytes; // the size of the allocated block
    int oldsize = *p; // block size stored in p
    *p = newsize; // set new length
    if(oldsize - newsize > 2)
        *(p+newsize+2) = oldsize - newsize; // writes in the size information for the next block
    setBlockNum(p+1);
}

//Block helper functions
int getBlockSize(char * p){
    return (int) ((unsigned char)*p >> 1);
}
void setBlockSize(int n, char * p){
    *p = n;
}

void setBlockNum(char * p){
    *p = (((char) blockCounter << 1) || (*p & 0x1));;
}

int getBlockNum(char * p){
    return (int) *p;
}

//Allocation functions
int check_allocated(char * p){
    return (int) (*p & 0x1);
}

void setAllocated(char * p){
    *p = (*p | 0x1);
}
void resetAllocated(char * p){
    *p = (*p & 0xFE);
}

int freeBlock(int block){return 0;}
void blocklist(){}
void writeHeap(int writeBlock, char writeChar, int numCopies){}
void printHeap(int blockNum, int numBytes)
{
    int i = 0;
    printf("Address\t\tBlockSize\t\tAllocated\t\t", )

    for(i=0; i < HEAP_SIZE;i++ )
    {
        printf("Address: %c\n", )
    }
}
void printHeader(int headerNum)
{}
































