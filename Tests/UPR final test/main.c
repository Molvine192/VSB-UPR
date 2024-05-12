#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char name[100];
    int count;
} Ingredient;

typedef struct {
    int size;
    Ingredient* ingredients;
} Recept;

int main(int argc, char** argv) {
    if (argc < 3) {return 1;}
    int ing = atoi(argv[1]);
    int recepty = atoi(argv[2]);

    Ingredient* ingredients = NULL;
    ingredients = (Ingredient*) malloc(sizeof(Ingredient) * ing);

    for (int i = 0; i < ing; i++) {
        ingredients[i] = (Ingredient) {"",0};
        char str[200] = "";
        fgets(str, sizeof(str), stdin);
        char str_copy[200] = "";
        strcpy(str_copy,str);
        char* token;
        token = strtok(str_copy, ",");
        strcpy(ingredients[i].name, token);
        token = strtok(NULL, ",");
        int count = atoi(token);
        ingredients[i].count = count;
    }

    Recept* recepts = (Recept*) malloc(sizeof(Recept) * recepty);

    int current_recept = 0;
    int max_porc = 0;
    for (int i = 0; i < recepty; i++) {
        char str[200] = "";
        fgets(str, sizeof(str), stdin);
        char* token;
        token = strtok(str, ";");
        int ing_count = atoi(token);
        recepts[i].ingredients = (Ingredient*) malloc(sizeof(Ingredient) * ing_count);

        for (int k = 0; k < ing_count; k++) {
            Ingredient ingredient = {"",0};
            token = strtok(NULL, ",");
            strcpy(ingredient.name, token);
            token = strtok(NULL, ";");
            int count = atoi(token);
            ingredient.count = count;
            recepts[i].size = ing_count;
            recepts[i].ingredients[k] = ingredient;
        }

        if (ing == 0 || recepty == 0) continue;

        for (int i = 0; i < recepty; i++) {
            int current_max_porc = 0;
            for (int k = 0; k < recepts[i].size; k++) {
                for (int t = 0; t < ing; t++) {
                    if (current_max_porc == -1) {
                        continue;
                    }
                    int tmp_current_max_porc = 0;
                    if (!strcmp(ingredients[t].name, recepts[i].ingredients[k].name)) {
                        tmp_current_max_porc = ingredients[t].count / recepts[i].ingredients[k].count;
                        if (tmp_current_max_porc < current_max_porc) {
                            current_max_porc = tmp_current_max_porc;
                            printf("1\n");
                        }
                    }
                    else {
                        current_max_porc = -1;
                    }
                }
            }
            if ((current_max_porc != -1 && current_max_porc < max_porc) || max_porc == -1) {
                current_recept = i+1;
                max_porc = current_max_porc;
            }
        }
    }

    if (current_recept < 1 || max_porc < 1 || ing == 0 || recepty == 0) {
        printf("Zadny recept nelze uvarit :(\n");
    }
    else {
        printf("Recept %d lze uvarit %dx\n", current_recept, max_porc);
    }
    
    free(recepts);
    free(ingredients);

    return 0;
}