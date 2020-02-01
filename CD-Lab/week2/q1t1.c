

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
 
int isKeyword(char buffer[]){
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
	int i, flag = 0;
	
	for(i = 0; i < 32; ++i){
		if(strcmp(keywords[i], buffer) == 0){
			flag = 1;
			break;
		}
	}
	
	return flag;
}

char ch, buffer[15], operators[] = "+-*/%=<>";
	FILE *fp;
	int i,j=0;

	int linec=0,colc=0;


void getNextToken()
{
	while((ch = fgetc(fp)) != EOF){
   		for(i = 0; i < 8; ++i){
   			if(ch == operators[i])
   				printf("<%c operator  %d  %d>\n", ch,linec,colc);
   		}
   		
   		if(ch=='#')
   		{
   			while(ch!='\n')
   			{
   				ch=getc(fp);
   			}
   		}

   		if(ch=='\n')
   		{
   			linec++;
   			colc=0;
   		}
   		if(ch==' ')
   		{
   			colc++;
   		}
   		if(ch==';')
   		{
   			printf("<%c Special  %d  %d>\n",ch,linec,colc);
   		}
   		if(ch=='{')
   		{
   			printf("<%c LC  %d  %d>\n",ch,linec,colc);
   		}
   		if(ch=='}')
   		{
   			printf("<%c RC  %d  %d>\n",ch,linec,colc);
   		}

   		if(ch=='(')
   		{
   			printf("<%c LB  %d  %d>\n",ch,linec,colc);
   		}
   		if(ch==')')
   		{
   			printf("<%c RB  %d  %d>\n",ch,linec,colc);
   		}

   		if(ch=='"')
   		{
   			
   			while(ch!='"')
   			{
   				ch=getc(fp);
   				buffer[j++]=ch;

   			}
   			buffer[j]='\0';;
   			colc+=j;
   			printf("<%s string  %d  %d>\n",buffer,linec,colc);
   		}
   		
   		if(isalnum(ch)){
   			buffer[j++] = ch;
   		}
   		else if((ch == ' ' || ch == '\n') && (j != 0)){
   				buffer[j] = '\0';
   				j = 0;
   				   				
   				if(isKeyword(buffer) == 1)
   					printf("<%s keyword  %d  %d>\n", buffer,linec,colc);
   				else
   					printf("<%s identifier  %d  %d>\n", buffer,linec,colc);
   		}
   		
	}
	
}
 
int main(){
	
	fp = fopen("input.c","r");
	
	if(fp == NULL){
		printf("error while opening the file\n");
		exit(0);
	}
	getNextToken();
	
	fclose(fp);
	
	return 0;
}
