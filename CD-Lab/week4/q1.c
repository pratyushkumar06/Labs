#include "header.h"

void Proc_T1();
void Proc_T();
void Proc_S();

void Proc_T1()
{
    
    if(ch == ',')
    {  
        match(',');
        Proc_S();
        Proc_T1();
    }
    
    return;
}


void Proc_T()
{
    Proc_S();
    Proc_T1();
    return;
}

void Proc_S()
{
    if(ch == 'a')
    {
        match('a');
        return;
    }
    else if(ch == '>')
    {
        match('>');
        return;
    }
    else if(ch == '(')
    {
        match('(');
        Proc_T();
        match(')');
        return;
    }
    
    error;
    
    return;
}

int main()
{
    init();
    Proc_S();

    if(ch =='$')
    {
        success;
    }
    else
        error;
    
    return 0;
}