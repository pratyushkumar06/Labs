%{ 
#include<stdio.h> 
#include<string.h> 
int flag = 0; 
%} 
  
/* Rules Section*/
%% 
[if,and,then,or] {flag=1;}
\n {}
. {} 
%% 
  
int yywrap(void){} 
  
int main() 
{    
    // The function that starts the analysis 
    yylex(); 
    if(flag==1)
      printf("Compound.\n");
    else  
      printf("Simple.\n");  
    return 0; 
}          