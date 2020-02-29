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

int ca,cb;

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
	//cb=getc(fp);
	switch(c)
	{
		case '+':
				return 1;
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
	if((ca=='+')||(ca=='-')||(ca=='*')||(ca=='/'))
	{
		t1.lex[0]=ca;
		if(ca=='+')
		{
			strcpy(t1.type,"ADD");
		}
		else if(ca=='-')
		{
			strcpy(t1.type,"SUB");
		}
		else if(ca=='*')
		{
			strcpy(t1.type,"MUL");
		}
		else if(ca=='/')
		{
			strcpy(t1.type,"DIV");
		}
		ca=getc(fp);
		if(ca=='=')
		{
			t1.lex[1]=ca;
			t1.lex[2]='\0';
		}
		else
		{
			t1.lex[1]='\0';
			ungetc(ca,fp);
		}

	}

	/////////////////RELATIONAL OPERATOR//////////////////
	else if((ca=='<')||(ca=='>'))
	{
		t1.row=linec;
		t1.col=colc;
		strcpy(t1.type,"Relational");
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
			strcpy(t1.type,"Relational");
			t1.lex[1]=ca;
			t1.lex[2]='\0';
			colc+=2;
			return t1;
		}
		else if((ca==' ')||(ca=='\n')||(ca=='\t'))
		{
			t1.row=linec;
			t1.col=colc;
			strcpy(t1.type,"SS");
			t1.lex[1]='\0';
			colc+=1;
			return t1;
		}
		else
		{
			t1.row=linec;
			t1.col=colc;ind=1;
			strcpy(t1.type,"Invalid");
			while((ca!=' ')&&(ca!='\n')&&(ca!='\t'))
			{
				t1.lex[ind++]=ca;
				ca=getc(fp);
			}
			t1.lex[ind]='\0';
			if(ca==' ')
			{
				colc=colc+ind+1;
			}
			else if(ca=='\n')
			{
				colc=1;
				linec++;
			}
			else if(ca=='\t')
			{
				colc=colc+4+ind;
			}
			ungetc(ca,fp);
			return t1;
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
		//ca=getc(fp);
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
			/*if(ca=='\n')
			{
				linec++;
				colc=1;
			}*/
			//cb=ca;
			ca=getc(fp);
		}
		//t1.lexeme[ind++]=ca;
		t1.lex[ind]='\0';
		colc=colc+ind;
		//ungetc(ca,fp);
		//printf("\n%c\n",ca);

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
			colc=colc+ind+4;
		}
		else
		{
			colc=colc+ind;
		}
		ungetc(ca,fp);
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
				strcpy(t1.type,"Invalid");
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
			colc++;
		}
		ungetc(ca,fp);
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


typedef struct node *nodeptr;

typedef struct node
{
	token tok;
	nodeptr next;
}node;


nodeptr createnode(token ele)
{
	nodeptr temp=(nodeptr)malloc(sizeof(node));
	temp->tok=ele;
	temp->next=NULL;
	return temp;
}

nodeptr newnode(nodeptr head,token ele)
{
	if(head==NULL)
	{
		nodeptr temp=createnode(ele);
		return temp;
	}
	nodeptr temp=head;
	while(temp->next!=NULL)
	{
		temp=temp->next;
	}
	nodeptr temp1=createnode(ele);
	temp->next=temp1;
	return head;

}

void display(nodeptr head)
{
	nodeptr temp=head;
	while(temp!=NULL)
	{
		printf("<%s,%d,%d,%s>\n",temp->tok.lex,temp->tok.row,temp->tok.col,temp->tok.type);
		temp=temp->next;
	}
}