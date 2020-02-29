#include<stdio.h>

//A comment line
#include<stdlib.h>


/* This is a program to 
check whether a number is Armstrong number or not*/

#include<math.h>

int arm(int n)
{
	int sum=0;
	int temp=n;
	// This uses math function
	while(temp) {
		//sum+=pow(temp%10,3);
		//temp=temp/10;
	}
	if(sum==n)
		return 1;
	else
		return 0;
}

int main()
{
	int n,i;
	int x[]={1,2,13,7};
	printf("Enter a number");
	scanf("%d",&n);
	
	
}
