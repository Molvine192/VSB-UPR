#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Record
{
    int index;
    char* action_name;
    float start;
    float end;
    int trades;
};

void formatNumber(int number, char *formatted);

int main(int argc, char** argv) {
    if ((argc-1) < 2) { //Pokud na vstupu programu nebudou dva tyto parametry
        printf("Wrong parameters\n");
        return 1;
    }
    
    int row_count = atoi(argv[2]);

    int index_most_trades = -1;
    int most_trades = 0;

    struct Record* records = (struct Record*) malloc(row_count * sizeof(struct Record));
    for (int i = 0; i < row_count; i++) {
        char str[101];
        fgets(str, 101, stdin);
        str[100] = '\0';
        char* token = strtok(str,",");
        records[i].index = atoi(token);
        token = strtok(NULL,",\n");
        records[i].action_name = malloc(strlen(token) + 1);
        strcpy(records[i].action_name, token);
        token = strtok(NULL,",\n");
        records[i].start = atof(token);
        token = strtok(NULL,",\n");
        records[i].end = atof(token);
        token = strtok(NULL,",\n");
        records[i].trades = atoi(token);

        if (!strcmp(records[i].action_name, argv[1])) {
            if (most_trades < records[i].trades) {
                index_most_trades = i;
                most_trades = records[i].trades;
            }
        }
    }

    printf("<html>\n<body>\n<div>\n");
    if (index_most_trades >= 0) {
        char f_number[20];
        formatNumber(records[index_most_trades].trades, f_number);
        printf("<h1>%s: highest volume</h1>\n", argv[1]);
        printf("<div>Day: %d</div>\n", records[index_most_trades].index);
        printf("<div>Start price: %.2f</div>\n", records[index_most_trades].start);
        printf("<div>End price: %.2f</div>\n", records[index_most_trades].end);
        printf("<div>Volume: %s</div>\n", f_number);
    }
    else {
        printf("Ticker %s was not found\n", argv[1]);
    }
    printf("</div>\n<table>\n<thead>\n<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n</thead>\n<tbody>\n");

    for (int i = row_count-1; i >= 0; i--) {
        char f_number[20];
        formatNumber(records[i].trades, f_number);
        if (!strcmp(records[i].action_name, argv[1])) {
            printf("<tr>\n");
            printf("\t<td><b>%d</b></td>\n", records[i].index);
            printf("\t<td><b>%s</b></td>\n", records[i].action_name);
            printf("\t<td><b>%.2f</b></td>\n", records[i].start);
            printf("\t<td><b>%.2f</b></td>\n", records[i].end);
            printf("\t<td><b>%.2f</b></td>\n", records[i].end - records[i].start);
            printf("\t<td><b>%s</b></td>\n", f_number);
            printf("</tr>\n");
        }
        else {
            printf("<tr>\n");
            printf("\t<td>%d</td>\n", records[i].index);
            printf("\t<td>%s</td>\n", records[i].action_name);
            printf("\t<td>%.2f</td>\n", records[i].start);
            printf("\t<td>%.2f</td>\n", records[i].end);
            printf("\t<td>%.2f</td>\n", records[i].end - records[i].start);
            printf("\t<td>%s</td>\n", f_number);
            printf("</tr>\n");
        }
    }

    printf("</tbody>\n</table>\n</body>\n</html>\n");

    for (int i = 0; i < row_count; i++) {
        free(records[i].action_name);
    }
    free(records);

    return 0;
}

void formatNumber(int number, char *formatted) {
    char buf[20];
    sprintf(buf, "%d", number);

    int length = strlen(buf);
    int count = (length - 1) / 3;
    int f_length = length + count;

    int j = 0;
    for (int i = 0; i < f_length; i++) {
        if (i > 0 && (f_length - i) % 4 == 0) {
            formatted[i] = '_';
        }
        else {
            formatted[i] = buf[j];
            j++;
        }
    }
    formatted[f_length] = '\0';
}