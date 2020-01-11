#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fa, *fb;
	int ca, cb;
	fa = fopen("input2.c","r");
	if(fa == NULL)
	{
		printf("Cant open file\n");
		exit(0);
	}
	fb = fopen("output2.c", "w");
	ca = getc(fa);
	while(ca != EOF)
	{
		if(ca == '#')
		{
			cb = getc(fa);
			while(cb != '\n')
				cb = getc(fa);
			ca = cb;
			cb = ' ';
			putc(cb, fb);
			//putc(ca, fb);
		}
		else
		{
			putc(ca, fb);
		}
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}