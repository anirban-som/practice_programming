#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE -1

void search_pattern(char *str, char *pat)
{
    int i=0, j=0, str_len=0, pat_len=0;
    str_len = strlen(str);
    pat_len = strlen(pat);

    printf("str=[%s]\n", str);
    printf("pat=[%s]\n", pat);

    for (i=0; i<=(str_len - pat_len); i++) {
        for (j=0; j<pat_len; j++) {
            if (str[i+j] != pat[j]) {
                break;
            }
        }
        if (j == (pat_len)) {
            printf("pattern found\n");
            return;
        }
    }
    printf("pattern not found\n");
}

int main()
{
    char *str = "My name is Anirban. I live in Burdwan";
    char *pat = "Anirban";
    /*passed with below cases also*/
    //char *pat = "Anirb";
    //char *pat = "AnirbanS";
    //char *pat = "Rathin";
    
    search_pattern(str, pat);

    return SUCCESS;
}
