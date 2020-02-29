#include "header.h"

void S();
void A();
void A1();
void B();

void A1()
{
    if(ch =='b')
    {
        match('b');
        A1();
    }
}

void A()
{
    if(ch == 'b')
    {
        match('b');
        A1();
        return;
    }

    error;
    exit(0);

}

void B()
{
    if(ch == 'd')
    {
        match('d');
    }
    else
    {
        error;
        exit(0);
    }
}
void S()
{
    if(ch == 'a')
    {
        match('a');
        A();
        match('c');
        B();
        // printf("%c",ch);
        match('e');
        // printf("%c",ch);
        return;
    }
    exit(0);
    error;
    
}

int main()
{
    init();
    S();

    // printf("back");
    if(ch =='$')
    {
        success;
    }
    else
        error;
    
    return 0;
}