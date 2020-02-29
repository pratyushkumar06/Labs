#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define error printf("invalid\n");
#define success printf("valid\n");
#define prev fseek(fin,-1,SEEK_CUR);
int global;
void get_next_char();

char ch;
FILE *fin; 

void init()
{
    fin = fopen("input.txt","r");
    get_next_char();
}


void get_next_char()
{
    
    ch = getc(fin);
    while(ch == '\n' || ch == '\r' || ch == ' ' || ch == '\t')
        ch = getc(fin);
}

void match(char t)
{

    if(ch == t)
    {
        get_next_char();
    }
    else if(ch == '$')
    {
        
        error;
        exit(0);
    }
    else
    {
        global = 0;
        // error;
    }
        
}

