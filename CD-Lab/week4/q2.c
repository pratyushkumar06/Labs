#include "header.h"

void E();
void T();
void E1();
void T1();
void F();

void F()
{
    if(ch =='(')
    {
        match('(');
        E();
        match(')');
    }
    else if(isalpha(ch) || isdigit(ch))
    {
        while(isalpha(ch) || isdigit(ch))
        {
            match(ch);
        }
    }
    else
    {
        error;
        exit(0);
    }
    
}

void T1()
{
    if(ch == '*')
    {
        match('*');
        F();
        T1();
    }
}

void T()
{
    F();
    T1();
}

void E1()
{
    if(ch == '+')
    {
        match('+');
        T();
        E1();
    }
}

void E()
{
    T();
    E1();
}

int main()
{
    init();
    E();

    if(ch =='$')
    {
        success;
    }
    else
        error;
    
    return 0;
}