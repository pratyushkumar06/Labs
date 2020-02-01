%{
	int words=0;
	int chars=0;
	int lines=0;
%}
%%
[\n] {lines++;}
[a-zA-Z]+ { words++;chars+=strlen(yytext);}
%%
int yywrap() {
	return 1;
}

int main(int argc, char *argv[]) {
	printf("Enter the string:\n");
	yylex();
	printf("Words: %d Lines: %d Charecters: %d",words,lines,chars);
}
