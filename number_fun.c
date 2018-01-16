/*
   CSCI 2021
   Multiplication table generator
   for any base

   finish the function
   printMultTable
*/

#include <stdio.h>
#include <stdlib.h>

char convertToChar(int i, int base);
void printNumber(int i, int base, int field_width, int char_count);
void printMultTable(int base);
void printAddTable(int base);


int main()
{
    int i = 59;
    int base, fieldWidth;

    /*
    do{
    	printf("enter an integer, a base, and the field width\n");
		scanf("%d%d%d",&i, &base, &fieldWidth);
    	printf("...");
    	printNumber(i, base, fieldWidth, 0);
    	printf("...");
    	putchar('\n');
	}while(1);
  */

    printf("This program will print a multiplication base for any base 2 to 36\n");
    printf("What base would you like to use?\n");
    scanf("%d", &base);
    if (base >= 2 && base <= 36){
    	printf("Mult table\n");
       printMultTable(base);
       printf("\nAdd table\n");
       printAddTable(base);
    }else{
       printf("invalid base\n");
    }
    system("pause");
    return 0;
}
/*
  i < base
*/
char convertToChar(int i, int base)
{
    char answer;

    //real programs do error checking
    if ( i < 10){
      answer = i + '0';
     }else{
        answer = i + 'A' - 10;
     }
     return answer;
}

void printNumber(int i, int base, int field_width, int char_count)
{
    char ch;
    char_count++;
    if (i < base){
          int k;
         ch = convertToChar(i, base);
         //see if we need to pad it with spaces
         for(k = char_count; k < field_width; ++k)
         {
              putchar(' ');
         }

    }else{
        int r = i % base;
        ch = convertToChar(r, base);
        i = i /base;
        printNumber(i, base, field_width, char_count);
    }

    printf("%c", ch);
}


void printMultTable(int base)
{
	int i, j;
  // run through the rows
  for(i = 1; i <= 10; ++i){
    for (j = 1; j <= 10; ++j){
      printf("%4d ", j * i);
    } // for j
    printf("\n");
  } // for i

    printf("finish Mult \n");
}

void printAddTable(int base)
{
    printf("finish Add\n");
}
