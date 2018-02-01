/*

	routines for printing bits
	
*/

#include <stdio.h>
#include <string.h>

void charToBitString(char number, char bitStr[9]);

int main()
{
	int i;
	char bitString[12];
	char outString[80];
	
	do{
		printf("enter a 8 bit integer\n");
		scanf("%d", &i);
	//	sprintf(outString, "you entered %7d", i);
	//	puts(outString);
	//	putchar('\n');
		charToBitString(i, bitString);
		puts(bitString);
		putchar('\n');
		
		
	}while(1);
	
	return 0;
}


void charToBitString(char number, char bitStr[9])
{
	int mask = 0x80;
	int i;
	
	bitStr[8] = '\0'; //set the length of the string
	
	for(i = 0; i < 8; ++i){
	
		if (mask & number){
			bitStr[i] = '1';
		}else{
			bitStr[i] = '0';
		}
		mask = mask >> 1;
    }
}


