#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int str_get_lowercase_count(char* str);
int str_get_uppercase_count(char* str);
int str_get_space_count(char* str);
void str_normalize(char* str);

int main() {
    char buf[10];
    fgets(buf, sizeof(buf), stdin);
    int str_count = atoi(buf);

    char* strings = NULL;
    strings = (char*) malloc(sizeof(char) * 51 * str_count);

    for (int i = 0; i < str_count; i++) {
        char str[51] = "";
        fgets(str, sizeof(str), stdin);
        strncpy(strings + i*51, str, 50);
        strings[i*51 + 50] = '\0';
    }
    
    for (int i = 0; i < str_count; i++) {
        char str_copy[51] = "";
        strcpy(str_copy,strings+i*51);
        char str_result[51] = "";

        char* token;
        token = strtok(strings+i*51, " ");
        while( token != NULL ) {
            char normalized_token[51] = "";
            strcpy(normalized_token,token);
            str_normalize(normalized_token);
            strcat(str_result,normalized_token);

            token = strtok(NULL, " ");
            if (token != NULL && token[0] != '\n') {
                strcat(str_result," \0");
            }
        }

        if (i > 0) printf("\n");
        printf("%s",str_result);
        if (str_result[strlen(str_result)-1] != '\n') printf("\n");
        printf("lowercase: %d -> %d\n", str_get_lowercase_count(str_copy), str_get_lowercase_count(str_result));
        printf("uppercase: %d -> %d\n", str_get_uppercase_count(str_copy), str_get_uppercase_count(str_result));
        printf("spaces: %d -> %d\n", str_get_space_count(str_copy), str_get_space_count(str_result));
    }

    free(strings);

    return 0;
}

int str_get_lowercase_count(char* str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (islower(str[i])) result++;
    }
    return result;
}

int str_get_uppercase_count(char* str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper(str[i])) result++;
    }
    return result;
}

int str_get_space_count(char* str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') result++;
    }
    return result;
}

void str_normalize(char* str) {
    int i = 0;
    char ch = ' ';
    int type = 0;
    while (ch != 0) {
        ch = str[i];
        if (ch >= 65 && ch <= 90) type = 1;
        i++;
    }

    if (type == 0) {
        for (int i = 0; str[i] != '\0'; i++) {
            if (islower(str[i])) {
                str[i] = toupper(str[i]);
            }
        }
    }
    else {
        for (int i = 0; str[i] != '\0'; i++) {
            if (i == 0) {
                str[i] = toupper(str[i]);
            }
            else if (isupper(str[i])) {
                str[i] = tolower(str[i]);
            }
        }
    }
    
    int index = 1;
    int curr = 0;
    while (str[index] != '\0') {
        if ((str[curr] != str[index])) {
            curr++;
            str[curr] = str[index];
        }
        index++;
    }
    str[curr + 1] = '\0';
}