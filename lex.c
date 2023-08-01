#include "lex.h"
#include "stdio.h"
#include "ctype.h"

char *yytext = "";
int yyleng = 0; // lexeme length
int yylineno = 0; // input line number

int lex(){
    static char input_buffer[128];
    char* current;

    current = yytext + yyleng; // skip the current lexeme
    while (1){
        while (!*current){
            // get new lines, skipping any leading whitespace on the line
            // until a non-blank line is found.
            current = input_buffer;
            if(!gets(input_buffer)){
                *current = '\0';
                return EOI;
            }

            ++yylineno;

            while (isspace(*current)){
                ++current;
            }
        }

        for (; *current; ++current) {
            // get the next token
            yytext = current;
            yyleng = 1;

            switch (*current) {
                case EOF: return EOI;
                case ';': return SEMI;
                case '+': return PLUS;
                case '*': return TIMES;
                case '(': return LP;
                case ')': return RP;

                case '\n':
                case '\t':
                case ' ':
                    break;

                default:
                    if(!isalnum(*current)){
                        fprintf(stderr, "Ignoring illegal input <%c>\n", *current);
                    } else {
                        while (isalnum(*current)){
                            ++current;
                            yyleng = current - yytext;
                            return NUM_OR_ID;
                        }
                    }
                    break;
            }
        }
    }
}

static int Lookahead = -1;

int match(int token){
    // return "true" if token matches the current lookahead symbol
    if(Lookahead == -1){
        Lookahead = lex();
    }

    return token == Lookahead;
}

void advance(){
    // advance the lookahead to the next input symbol
    Lookahead = lex();
}