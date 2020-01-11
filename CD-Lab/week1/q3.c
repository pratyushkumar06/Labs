#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keywords_list[32][10] = {
	"auto","break","case","char",
	"const","continue","default","do",
	"double","else","enum","extern",
	"float","for","goto","if",
	"int","long","register","return",
	"short","signed","sizeof","static",
	"struct","switch","typedef","union",
	"unsigned","void","volatile","while"
};

void strUpper(char word[]){
	for(int i=0;i<strlen(word);i++){
		word[i] = toupper(word[i]);
	}
}

int isKeyword(char word[]){
	for(int i=0;i<32;i++){
		if(strcmp(word,keywords_list[i]) == 0)
			return 1;
	}

	return 0;
}

int main(){
	FILE *fa,*fb;
	char str[256];
	int wordlen = 0;
	int lineno = 1;
	int colno = 0;

	fa = fopen("q1.c","r");
	// fb = fopen("result3.c","w");
	printf("Word\t LineNo\t ColNo\n");
	printf("--------------------------\n");

	// read word by word
	while(1){
		int ca = getc(fa);

		if(ca == '\n'){
			lineno++;
			colno = 0;
		}

		if(ca == EOF)
			break;

		else if(isalnum(ca) || ca=='_'){
			str[wordlen++] = ca;
		}

		else if(wordlen != 0){
			str[wordlen] = '\0';

			if(isKeyword(str)){
				strUpper(str);
				printf("%s\t %d\t %d\n",str,lineno,colno-wordlen);
			}
			wordlen = 0;
		}

		if(ca == '\t')
			colno += 4;
		else
			colno++;
	}

	fclose(fa);
	// fclose(fb);

	return 0;
}