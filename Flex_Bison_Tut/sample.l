/* a sample UNIX word Count stuff */
/* just like Unix wc */
%{

//This section is to initialize a few varaibles so that we can use them in the following sections
int chars = 0;
int words = 0;
int lines = 0;
%}

/* This section is a list of our regular expressions and for each of them the corresponding actions written as C code would be given */
/* Doing so, we can, for any given input do the corresponding actions */
%%

[a-zA-Z]+  { words++; chars += strlen(yytext); }
\n         { chars++; lines++; }
.          { chars++; }

%%

int main(int argc, char **argv)
{
  /*If i write yylex() here it starts scannign the input given to us */
  yylex(); 
  printf("%8d%8d%8d\n", lines, words, chars);
}