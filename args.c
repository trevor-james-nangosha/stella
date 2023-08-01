// code generation using subroutine arguments

#include "stdio.h"
#include "lex.h"

void factor(char* tempvar);
void term(char* tempvar);
void expression(char* tempvar);

extern char* newname();
extern void freename(char* s);

void statements(){
    // statements -> expression ;
    //             | expression ; statements
    char* tempvar;
    while (!match(EOI)){
        expression(tempvar = newname());

        if(match(SEMI)){
            advance();
        } else {
            fprintf(stderr, "%d: Inserting missing semicolon.", yylineno);
        }
    }
}

void expression(char* tempvar){
    char *tempvar2;
    term( tempvar );

    while(match(PLUS)){
        advance();
        term( tempvar2 = newname() );
        printf(" %s += %s\n", tempvar, tempvar2 );
        freename( tempvar2 );
    }
}

void term(char* tempvar){
    char *tempvar2;
    factor( tempvar );
    while (match(TIMES)){
        advance();

        factor(tempvar2 = newname());
        printf(" %s *= %s\n", tempvar, tempvar2 );
        freename( tempvar2 );
    }

}

void factor(char* tempvar){
    if(match(NUM_OR_ID)){
        printf(" %s = %.*s\n", tempvar, yyleng, yytext );
        advance();
    } else if (match(LP)){
        advance();
        expression( tempvar );
        if (match(RP)){
            advance();
        } else {
            fprintf( stderr, "%d: Mismatched parenthesis\n", yylineno ) ;
        }
    } else {
        fprintf( stderr, "%d: Number or identifier expected\n", yylineno ) ;
    }
}

