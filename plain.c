// a basic parser that shows the structure but there is no code generation

#include "lex.h"
#include "stdio.h"

void expression();
void term();
void expr_prime();
void term_prime();
void factor();

void statements(){
    // statements -> expression ;
    //             | expression ; statements
    expression();

    if(match(SEMI)){
        advance();
    } else {
        fprintf(stderr, "%d: Inserting missing semicolon.", yylineno);
    }

    if(!match(EOI)){
        statements(); // do another statement
    }
}

void expression() {
    // expression -> term expression'
    term ();
    expr_prime();
}

void expr_prime(){
    // expression' -> PLUS term expression'
    //             | epsilon
    if(match(PLUS)){
        advance();
        term();
        expr_prime();
    }
}

void term(){
    // term -> factor term'
    factor();
    term_prime();
}

void term_prime(){
    // term' -> TIMES factor term'
    //          | epsilon
    if(match(TIMES)){
        advance();
        factor();
        term_prime();
    }
}

void factor(){
    // factor -> NUM_OR_ID
    //           | LP expression RP
    if(match(NUM_OR_ID)){
        advance();
    } else if (match(LP)){
        advance();
        expression();
        if (match(RP)){
            advance();
        } else {
            fprintf( stderr, "%d: Mismatched parenthesis\n", yylineno);
        }
    } else {
        fprintf ( stderr, "%d Number or identifier expected\n", yylineno ) ;
    }
}


