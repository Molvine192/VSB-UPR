#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void modify(char* str, int start_from) {
    int k = 0, v = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (i % 2) {
            if (i >= start_from + 1 && k > 0)
            {
                printf("%c",str[strlen(str)-k-2]);
            }
            k++;
        }
        else {
            if (i >= start_from)
            {
                printf("%c",str[v-1]);
            }
            v++;
        }
    }
    printf("\n");
}

int main() {
    char buf[20];
    fgets(buf, sizeof(buf), stdin);
    char b[2];
    strncpy(b,buf,sizeof(b));
    int start_from = atoi(b);

    char* strings = NULL;

    strings = (char*) malloc(sizeof(char *) * 50 * 100);

    char str[50];
    int i = 0;
    fgets(str, sizeof(str), stdin);
    while (str[1] != 0) {
        strcpy(strings + i*50,str);
        fgets(str, sizeof(str), stdin);
        i++;
    }

    

    i = 0;
    while (strings[i*50] != 0) {
        modify(strings + i*50, start_from);
        // printf("%s", strings + i*50);
        i++;
    }

    free(strings);

    return 0;
}