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

void allocate(int numBytes);
void freeBlock(int blockNum);
void addblock(char * p, int len);

void blocklist(void);
void writeHeap(int writeBlock, char writeChar, int numCopies);

void printHeap(int blockNum, int numBytes);
void printHeader(int blockNum);

void setBlockSize(int n, char * p);
int getBlockSize(char * p);

void setBlockNum(char * p);
int getBlockNum(char * p);

int isAllocated(char * p);
void setAllocated(char * p);
void unallocate(char * p);

char * findAvailableBlock(int numBytes);
char * findBlockNum(int blockNum);

static int blockCounter = 1;
static char * heap;

int main(int argc, const char * argv[])
{
	int i=0;
	heap = (char *) malloc(HEAP_SIZE);
	char * p = heap;
	//Clear heap to all 0
	for(i=0;i<HEAP_SIZE;i++)
	{
		*(p+i)=0;
	}
	setBlockSize(HEAP_SIZE-2, heap+1);
	getInput();
	free(heap);
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
	char charInput = ' ';
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
					if(!strcmp(cmd, "writeheap"))
					{
						charInput = *token;
					}
					else
					{
						num2 = atoi(token);
					}
				}
				else //if (i==2)
				{
					num2 = atoi(token);
				}
				i++;
				token = strtok(NULL, " \n");
			}
		}

		//printf("Command: %s\n Num1: %d\n CharInput: %c\n Num2: %d\n", cmd, num1, charInput,num2);

		//GOTO CMD FUNCTIONS
		if(!strcmp(cmd, "allocate"))
		{
			allocate(num1);
		}
		else if(!strcmp(cmd, "free"))
		{
			freeBlock(num1);
		}
		else if(!strcmp(cmd, "blocklist"))
		{
			blocklist();
		}
		else if(!strcmp(cmd, "writeheap"))
		{
			writeHeap(num1,charInput,num2);
		}
		else if(!strcmp(cmd, "printheap"))
		{
			printHeap(num1,num2);
		}
		else if(!strcmp(cmd, "printheader"))
		{
			printHeader(num1);
		}
	}
}

void allocate(int numBytes)
{
	char * p = findAvailableBlock(numBytes);
	addblock(p,numBytes);
}

char * findAvailableBlock(int numBytes)
{
	char* iterator = heap;
	//changed numBytes+2 to just numBytes
	while( (iterator < heap + 125) && ((isAllocated(iterator+1)  || (getBlockSize(iterator+1) < numBytes)) ) )	//check 125 num during testing
	{
		iterator = iterator + 2 + getBlockSize(iterator+1);
	}
	//printf("Found available block: %p\n", iterator);
	if((iterator-(heap+126)>0))
	{
		iterator = NULL;
	}
	return iterator;
}

void addblock(char* p, int numBytes) {
	if(p!=NULL)
	{
		int newsize = numBytes; // the size of the allocated block
		int oldsize = getBlockSize(p+1); // block size stored in p
		*p = newsize; // set new length
		if(oldsize - newsize > 2)
		{
			//printf("Old size: %d, New Size: %d\n",oldsize,oldsize-newsize);
			setBlockSize((oldsize-newsize - 2),(p+newsize+3)); // writes in the size information for the next block
			setBlockSize(numBytes, p+1);
		}
		else
		{
			setBlockSize(oldsize,(p+1)); // writes in the size information for the next block
		}
		setBlockNum(p);
		setAllocated(p+1);
	}
}

//Block helper functions
int getBlockSize(char * p)
{
	return (int) ((unsigned char)*p >> 1);
}

void setBlockNum(char * p)
{
	*p = (char)(blockCounter);
	printf("%d\n",blockCounter);
	blockCounter++;
}

void setBlockSize(int numBytes, char * p)
{
	*p = (numBytes << 1);
}

int getBlockNum(char * p)
{
	return (int) *p;
}

//Allocation functions
int isAllocated(char * p)
{
	return (int) (*p & 0x1);
}

void setAllocated(char * p)
{
	*p = (*p | 0x1);
}
void unallocate(char * p)
{
	*p = (*p & 0xFE);
}

void freeBlock(int blockNum)
{
	char * p = heap;
	p=findBlockNum(blockNum);
	unallocate(p+1);
}
void blocklist()
{
	char* iterator = heap;
	printf("Size\t\tAllocated\tStart\t\tEnd\n");
	while(iterator < heap + 125)	//check 125 num during testing
	{
		//if((isAllocated(iterator+1)))
		//{
		printf("%d\t\t%s\t\t%ld\t\t%ld\n",getBlockSize(iterator+1)+2,(isAllocated(iterator+1)?"yes":"no") ,labs(heap-iterator), labs(heap-iterator)+getBlockSize(iterator+1)+1);
		//}
		iterator = iterator + 2 + getBlockSize(iterator+1);
	}
}
void writeHeap(int blockNum, char writeChar, int numCopies)
{
	int i = 0;
	char * p = findBlockNum(blockNum);
	if(p==NULL)
	{
		printf("Can't find blockNum\n");
	}
	else
	{
		if(numCopies>getBlockSize(p+1))
		{
			printf("Write too big\n");
		}
		else
		{
			p=p+2;		//first payload byte;
			for(i=0;i<numCopies;i++)
			{
				*p=writeChar;
				p++;
			}
		}
	}
}

void printHeap(int blockNum, int numBytes)
{
	//printf("Address\t\tBlockSize\t\tAllocated\t\t");
	char *p;
	int i;
	if(debug_printInput)
	{
		p = heap;
		i = 0;
		printf("Address\t\t\tValue\n");

		for(i=0; i < HEAP_SIZE;i++ )
		{
			printf("%p\t\t%d\n", p+i,(int)((unsigned char)*(p+i)));
		}
	}
	else
	{
		i = 0;
		p = findBlockNum(blockNum);
		if(p==NULL)
		{
			printf("Can't find blockNum\n");
		}
		else
		{
			if(numBytes>getBlockSize(p+1))
			{
				numBytes=getBlockSize(p+1);
			}
            p=p+2;		//first payload byte;
            for(i=0;i<numBytes;i++)
            {
                printf("%c",*(p+i));
            }
            printf("\n");
		}
	}
}
void printHeader(int blockNum)
{
	char * p = findBlockNum(blockNum);
	if(p!=NULL)
	{
		if(!isAllocated(p+1) )
		{
			printf("Block not allocated\n");
		}
		else
		{
			printf("%02X%02X\n",*p,(*(p+1)+4 & 0xFF));
		}
	}
	else
	{
		printf("Block does not exist\n");
	}

}

char * findBlockNum(int blockNum)
{
	char * iterator=heap;
	while((iterator < heap + 125))	//check 125 num during testing
	{
		if(getBlockNum(iterator)==blockNum)
		{
			return iterator;
		}
		iterator = iterator + 2 + getBlockSize(iterator+1);
	}
	return NULL;
}






