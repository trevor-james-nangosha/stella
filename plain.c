// a basic parser that shows the structure but there is no code generation

#include "lex.h"
#include "stdio.h"
#include "stdarg.h"

#define MAXFIRST 16
#define SYNCH SEMI

void expression();
void term();
//void expr_prime();
//void term_prime();
void factor();
int legal_lookahead(int first_arg, ...);

void statements(){
    // statements -> expression ;
    //             | expression ; statements
    while (!match(EOI)){
        expression();

        if(match(SEMI)){
            advance();
        } else {
            fprintf(stderr, "%d: Inserting missing semicolon.", yylineno);
        }
    }
}

void expression() {
    // expression -> term expression'
    // expression' -> PLUS term expression' | epsilon
    if(!legal_lookahead(NUM_OR_ID, LP, 0)){
        return;
    }

    term();
    while (match(PLUS)){
        advance();
        term();
    }
}

//void expr_prime(){
//    // expression' -> PLUS term expression'
//    //             | epsilon
//    if(match(PLUS)){
//        advance();
//        term();
//        expr_prime();
//    }
//}

//void term(){
//    // term -> factor term'
//    if(!legal_lookahead(NUM_OR_ID, LP, 0)){
//        return;
//    }
//
//    factor();
//    while (match(TIMES)){
//        advance();
//        factor();
//    }
//}

//void term_prime(){
//    // term' -> TIMES factor term'
//    //          | epsilon
//    if(match(TIMES)){
//        advance();
//        factor();
//        term_prime();
//    }
//}

void factor(){
    // factor -> NUM_OR_ID
    //           | LP expression RP
    if(!legal_lookahead(NUM_OR_ID, LP, 0)){
        return;
    }

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

int legal_lookahead(int first_arg, ...){
    /* Simple error detection and recovery. Arguments are a 0-terminated list of
    * those tokens that can legitimately come next in the input. If the list is
    * empty, the end of file must come next. Print an error message if
    * necessary. Error recovery is performed by discarding all input symbols
    * until one that's in the input list is found
    * * Return true if there's no error or if we recovered from the error,
    * false if we can't recover.
    */
    va_list args;
    int tok;
    int lookaheads[MAXFIRST], *p = lookaheads, *current;
    int error_printed = 0;
    int rval = 0;

    va_start(args, first_arg);

    if(!first_arg){
        if(match(EOI)){
            rval = 1;
        }
    } else {
        *p++ = first_arg;
        while( (tok = va_arg(args, int)) && p < &lookaheads[MAXFIRST] ){
            *p++ = tok;
        }

        while (!match(SYNCH)){
            for (current = lookaheads; current < p ; ++current) {
                if(match(*current)){
                    rval = 1;
                    goto exit;
                }
            }

            if(!error_printed){
                fprintf( stderr, "Line %d: Syntax error\n", yylineno );
                error_printed = 1;
            }

            advance();
        }
    }

    exit:
        va_end(args);
        return rval;
}


