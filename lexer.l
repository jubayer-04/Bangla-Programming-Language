%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>

int yylineno = 1;
%}

%x CCOMMENT

digit   [0-9]
id      [a-zA-Z_][a-zA-Z0-9_]*
flt     {digit}+"."{digit}*|"."{digit}+

%%
"#".*                 { }
"//".*                { }

"/*"                  { BEGIN(CCOMMENT); }
<CCOMMENT>"*/"        { BEGIN(INITIAL); }
<CCOMMENT>\n          { ++yylineno; }
<CCOMMENT>.           { }

"dekhao"              { return PRINT; }
"jodi"                { return IF; }
"tahole"              { return THEN; }
"nahole"              { return ELSE; }
"na hole"             { return ELSE; }
"cholo"               { return CHOLO; }
"jonno"               { return FOR; }
"shes"                { return END; }
"ferot"               { return RETURN; }
"deo"                 { return SCAN; }
"dhoro"               { return LET; }

"int"                 { return INT_T; }
"float"               { return FLOAT_T; }
"string"              { return STRING_T; }

"=="                  { return EQ; }
">"                   { return GT; }
"<"                   { return LT; }
"="                   { return ASSIGN; }
"++"                  { return INC; }
"--"                  { return DEC; }

{flt}                 { yylval.num = atof(yytext); return NUMBER; }
{digit}+              { yylval.num = atof(yytext); return NUMBER; }

{id}                  { yylval.str = strdup(yytext); return ID; }

\"([^\\\"]|\\.)*\"    {
                        int len = strlen(yytext) - 2;
                        char *s = (char*)malloc(len + 1);
                        strncpy(s, yytext + 1, len);
                        s[len] = '\0';
                        yylval.str = s;
                        return STRING;
                      }

[ \t]+                { }
\n                    { ++yylineno; }

.                     { return *yytext; }
%%
int yywrap(void) { return 1; }
