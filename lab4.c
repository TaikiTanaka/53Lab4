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

#define maxLineLength 40
void getInput(void);
int allocate(int numBytes);
int freeBlock(int block);
void blocklist();
void writeHeap(int writeBlock, char writeChar, int numCopies);
void printHeap(int blockNum, int numBytes);
void printHeader(int headerNum);

int main(int argc, const char * argv[])
{
	getInput();
	return 0;
}

void getInput(void)
{
	char input[maxLineLength]="";
	char cmd[20] = "";
	int num1=-1;
	int num2=-1;
	char charInput;
	int i=0;
	char *token;


	while( (strcmp(cmd, "quit")) )
	{
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
}

int allocate(int numBytes){return 0;}
int freeBlock(int block){return 0;}
void blocklist(){}
void writeHeap(int writeBlock, char writeChar, int numCopies){}
void printHeap(int blockNum, int numBytes){}
void printHeader(int headerNum){}
































