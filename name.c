// temporary variable allocation routines

#include "stdio.h"
#include "stdlib.h"
#include "lex.h"

char *Names [] = { "tO", "tl", "t2", "t3", "t4", "t5", "t6", "t7" };
char **Namep = Names;

char* newname(){
    if(Namep >= &Names[sizeof(Names)/sizeof(*Names)]){
        fprintf(stderr, "%d: Expression too complex\n", yylineno);
        exit(1);
    }

    return (*Namep++);
}

void freename(char* s){
    if(Namep > Names){
        *--Namep = s;
    } else {
        fprintf(stderr, "%d: Name stack underflow\n", yylineno);
    }
}