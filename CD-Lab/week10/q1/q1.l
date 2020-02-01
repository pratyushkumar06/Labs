%{
	int vowels=0;
	int cons=0;
%}
%%
[aeiouAEIOU] {vowels++;}
[a-zA-Z] { cons++;}
%%
int yywrap() {
	return 1;
}

int main(int argc, char *argv[]) {
	printf("Enter the string:\n");
	yylex();
	printf("Vowels: %d Consonants: %d",vowels,cons);
}
