#include "header.h"

void lexp();
void aterm();
void list();
void lexp_seq();
void lexp_seq1();
int global = 0;


void lexp()
{
    aterm();
    list();
}

void aterm()
{
    if(isdigit(ch))
    {
        while(isdigit(ch))
        {
            match(ch);
        }
    }
    else if(isalpha(ch))
    {
        while (isalpha(ch))
        {
            match(ch)
        }
        
    }lexp();
    lexp_seq1();
{
    if(ch == '(')
    {
        match('(');
        lexp_seq();
        match(')');
    }
    else
    {
        error;
        exit(0);
    }
}

void lexp_seq()
{
    lexp();
    lexp_seq1();
}

void lexp_seq1()
{
    lexp();
    lexp_seq1();
}



int main()
{
    init();
    lexp();

    // printf("back");
    if(ch =='$')
    {
        success;
    }
    else
        error;
    
    return 0;
}