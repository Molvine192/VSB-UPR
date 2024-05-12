#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char** argv) {
    char* file_path = "";
    char* pattern = "";
    int ignore_case = 0;
    char* output_file_path = "";

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-i")) {
            if (ignore_case == 1) {
                printf("Parameter -i provided multiple times\n");
                return 1;
            }
            ignore_case = 1;
        }
        else if (!strcmp(argv[i], "-o")) {
            if (strcmp(output_file_path, "")) {
                printf("Parameter -o provided multiple times\n");
                return 1;
            }
            i++;
            if (argv[i] == NULL)
            {
                printf("Missing output path\n");
                return 1;
            }
            output_file_path = argv[i];
        }
        else {
            if (!strcmp(file_path, "")) {
                file_path = argv[i];
            }
            else if (!strcmp(pattern, "")) {
                pattern = argv[i];
            }
            else {
                printf("Too many parameters provided\n");
                return 1;
            }
        }
    }

    if (!strcmp(file_path, "")) {
        printf("Input path not provided\n");
        return 1;
    }
    else if (!strcmp(pattern, "")) {
        printf("Needle not provided\n");
        return 1;
    }

    if (ignore_case == 1) {
        for (int i = 0; pattern[i] != '\0'; ++i) {
            pattern[i] = tolower(pattern[i]);
        }
    }

    FILE* file = fopen(file_path, "r");
    FILE* output_file = fopen(output_file_path, "w");

    char str[101];
    char str_cpy[101];
    while (fgets(str, sizeof(str), file) != NULL) {
        strcpy(str_cpy,str);
        if (ignore_case == 1) {
            for (int i = 0; str_cpy[i] != '\0'; ++i) {
                str_cpy[i] = tolower(str_cpy[i]);
            }
        }
        if (strstr(str_cpy, pattern) != NULL) {
            if (output_file != NULL) {
                fprintf(output_file, "%s", str);
            }
            else {
                printf("%s", str);
            }
        }
    }

    fclose(file);
    if (output_file != NULL) {
        fclose(output_file);
    }

    return 0;
}