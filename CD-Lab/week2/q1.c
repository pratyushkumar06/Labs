#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

char keys[32][15]={
	"auto","break","case","char",
	"const","continue","default","do",
	"double","else","enum","extern",
	"float","for","goto","if",
	"int","long","register","return",
	"short","signed","sizeof","static",
	"struct","switch","typedef","union",
	"unsigned","void","volatile","while"
};

int isKey(char buf[40])
{
	for(int i=0;i<32;i++)
	{
		if(!strcmp(buf,keys[i]))
			return 1;
	}
	return 0;
}

int isAOperator(int c)
{
	switch(c)
	{
		case '+':return 1;
				break;
		case '-':return 1;
				break;
		case '/':return 1;
				break;
		case '*':return 1;
				break;
		case '%':return 1;
				break;
		default:return 0;
				break;
	}
}


int ca,cb;

typedef struct token
{
	int row;
	int col;
	char lex[60];
	char type[30];
}token;

int linec=1,colc=1;

token getNextToken(FILE *fp)
{
	char buf[50];int ind=0;
	token t1;

	///////////////ARITHMETIC OPERATOR////////////
	if(isAOperator(ca))
	{
		t1.row=linec;
		t1.col=colc;
		t1.lex[0]=ca;t1.lex[1]='\0';
		colc++;
		strcpy(t1.type,"Operator");
		//ca=getc(fp);
		

	}

	/////////////////RELATIONAL OPERATOR//////////////////
	else if((ca=='<')||(ca=='>'))
	{
		t1.row=linec;
		t1.col=colc;
		strcpy(t1.type,"Operator");
		t1.lex[0]=ca;
		ca=getc(fp);
		if(ca=='=')
		{	
			t1.lex[1]=ca;
			t1.lex[2]='\0';
			colc=colc+2;
		}
		else
		{
			t1.lex[1]='\0';
			colc=colc+1;
			ungetc(ca,fp);
		}
		//ca=getc(fp);

	}
	else if(ca=='!')
	{
		t1.lex[0]=ca;
		ca=getc(fp);
		if(ca=='=')
		{
			t1.row=linec;
			t1.col=colc;
			strcpy(t1.type,"Operator");
			t1.lex[1]=ca;
			t1.lex[2]='\0';
			return t1;
			colc=colc+2;
		}
		else if((ca==' ')||(ca=='\n')||(ca=='\t'))
		{
			t1.row=linec;
			t1.col=colc;
			strcpy(t1.type,"SS");
			t1.lex[1]='\0';
			return t1;
			colc++;
		}
		else
		{
			t1.row=linec;
			t1.col=colc;ind=1;
			strcpy(t1.type,"Identifier");
			while((ca!=' ')&&(ca!='\n')&&(ca!='\t'))
			{
				t1.lex[ind++]=ca;
				ca=getc(fp);
			}
			t1.lex[ind]='\0';
			ungetc(ca,fp);
			return t1;
			colc=colc+ind;
		}
	}
	////////////////////ASSIGNMENT OPERATOR////////////////
	else if((ca=='='))
	{
		t1.row=linec;
		t1.col=colc;
		strcpy(t1.type,"Assignment Operator");
		t1.lex[0]=ca;
		t1.lex[1]='\0';
		colc++;
		//ca=getc(fp);
	}

	///////////////BRACES////////////
	else if((ca=='('))
	{
		t1.row=linec;
		t1.col=colc;
		t1.lex[0]='(';t1.lex[1]='\0';
		strcpy(t1.type,"LB");
		colc++;
		//ca=getc(fp);
	}
	else if(ca==')')
	{
		t1.row=linec;
		t1.col=colc;
		t1.lex[0]=')';t1.lex[1]='\0';
		strcpy(t1.type,"RB");
		colc++;
		//ca=getc(fp);
	}
	else if(ca=='{')
	{
		t1.row=linec;
		t1.col=colc;
		t1.lex[0]='{';t1.lex[1]='\0';
		strcpy(t1.type,"LC");
		colc++;
	}
	else if(ca=='}')
	{
		t1.row=linec;
		t1.col=colc;
		t1.lex[0]='}';t1.lex[1]='\0';
		strcpy(t1.type,"RC");
		colc++;
		//ca=getc(fp);
	}
	
	else if(ca=='[')
	{
		t1.row=linec;
		t1.col=colc;
		t1.lex[0]='[';t1.lex[1]='\0';
		strcpy(t1.type,"LS");
		colc++;
	}
	else if(ca==']')
	{
		t1.row=linec;
		t1.col=colc;
		t1.lex[0]=']';t1.lex[1]='\0';
		strcpy(t1.type,"RS");
		colc++;
	}

	////////////////////////////STRING////////////////
	else if(ca=='\"')
	{
		t1.row=linec;
		t1.col=colc;
		strcpy(t1.type,"String");
		ca=getc(fp);
		while(ca!='\"')
		{
			t1.lex[ind++]=ca;
			colc++;
			ca=getc(fp);
		}
		t1.lex[ind]='\0';

	}
	//////////////////////////////////KEYWORD AND IDENTIFIER///////////////////	
	else if(isalpha(ca))
	{
		ind=0;
		while((isalnum(ca))||(ca=='_'))
		{
			buf[ind++]=ca;
				//colc++;
			//cb=ca;
			ca=getc(fp);
		}
		//ca=cb;
		buf[ind]='\0';
		if(isKey(buf))
		{
			//printf("%s    %d    %d\n",buf,lc,colc);
			t1.row=linec;
			t1.col=colc;
			strcpy(t1.type,"Keyword");
			strcpy(t1.lex,buf);
		}
		else
		{
			t1.row=linec;
			t1.col=colc;
			strcpy(t1.type,"Identifier");
			strcpy(t1.lex,buf);
		}
		if(ca=='\n')
		{
			linec++;
			colc=1;
		}	
		else if((ca==' '))
		{
			colc=colc+ind+1;
		}
		else if(ca=='\t')
		{
			colc=colc+4;
		}
		else
		{
			colc=colc+ind;
			ungetc(ca,fp);
		}
		//ungetc(ca,fp);
		//printf("\n%c\n",ca);
	}

	///////////////////////NUMBER///////////////

	else if(isdigit(ca))
	{
		t1.row=linec;
		t1.col=colc;
		ind=0;
		strcpy(t1.type,"Number");
		while(isalnum(ca))
		{
			buf[ind++]=ca;
			//cb=ca;
			ca=getc(fp);
		}
		//ca=cb;
		buf[ind]='\0';
		for(int j=0;j<ind;j++)
		{
			if(isalpha(buf[j]))
			{
				strcpy(t1.type,"Identifier");
				break;
			}
		}
		strcpy(t1.lex,buf);
		if(ca=='\n')
		{
			linec++;
			colc=1;
		}
		else if(ca=='\t')
		{
			colc=colc+ind+4;
		}
		else if(ca==' ')
		{
			colc=colc+ind+1;
		}
		else
		{
			colc=colc+ind;
			ungetc(ca,fp);
		}
		//ungetc(ca,fp);
		//printf("\n%c\n",ca);
	}
	/////////////////////////////SPECIAL///////////////////////////
	else
	{
		t1.row=linec;
		t1.col=colc;
		t1.lex[0]=ca;
		t1.lex[1]='\0';
		strcpy(t1.type,"SS");
		//ca=getc(fp);
	}
	return t1;
}

int main()
{
	FILE *fp=fopen("input.c","r");
	token t1;
	ca=getc(fp);
	while(1)
	{
		if(ca==EOF)
		{
			return 0;
		}
		else if(ca=='\n')
		{
			linec++;
			colc=1;
		}
		else if(ca==' ')
		{
			colc++;
		}
		else if(ca=='#')
		{
			while(ca!='\n')
			{
				ca=getc(fp);
			}

			linec++;
			colc=1;
		}
		else if(ca=='/')
		{
			cb=getc(fp);
			if(cb=='/')
			{
				ca=getc(fp);
				while(ca!='\n')
				{
					ca=getc(fp);
				}
				linec++;
				colc=1;
			}
			else if(cb=='*')
			{
				ca=getc(fp);
				cb=getc(fp);
				while((ca!='*')&&(cb!='/'))
				{
					if(cb=='\n')
					{
						linec++;
						colc=1;
					}
					ca=cb;
					cb=getc(fp);
					colc++;
				}
				//ca=getc(fp);
			}
			else
			{
				//ca=getc(fp);
				;
			}
		}
		else if(ca=='\t')
		{
			colc=colc+4;
		}
		else
		{
			//printf("\n%c\n",ca);
			t1=getNextToken(fp);
			printf("<%s,%d,%d,%s>\n",t1.lex,t1.row,t1.col,t1.type);	
		}
		
		ca=getc(fp);
		
		
	}
	fclose(fp);
	return 0;
}