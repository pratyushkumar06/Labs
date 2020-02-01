%{
	int no_pint=0;
	int no_nint=0;
	int no_pfloat=0;
	int no_nfloat=0;
%}
DIGIT [0-9]
%%
\+?{DIGIT}+	 no_pint++;
-{DIGIT}+	no_nint++;

\+?{DIGIT}*\.{DIGIT}+	no_pfloat++;
-{DIGIT}*\.{DIGIT}+		no_nfloat++;
. ;

%%
int yywrap() {
	return 1;
}

int main(int argc, char *argv[]) {
	printf("Enter the string:\n");
	yylex();
	printf("+ve int: %d -ve int: %d \n",no_pint,no_nint);
	printf("+ve float: %d -ve float: %d \n",no_pfloat,no_nfloat);
}
