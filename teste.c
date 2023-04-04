#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* leNome()
{
    char* s = (char*) malloc(sizeof(char));
    int i = 0, c;
    s[0] = getchar();
    if (s[0] != '"')
    {
        i = 1;
        while ((c = getchar()) != ' ' && c != '\t' && c != '\n'){
            s = realloc(s, i + 1);
            s[i++] = c;
        }
        ungetc(c, stdin);
    }
    else
    {
        while ((c = getchar()) != '"'){
            s = realloc(s, i + 1);
            s[i++] = c;
        }
    }
    s[i++] = '\0';
    return s;
}

int main(){
    char* s;
    s = leNome();
    
    free(s);
    return 0;
}