#include <stdio.h>

int main ()
{
    int cash = 250;
    int remainder = cash;
    printf("Bankovka 5000: %dx\n", remainder / 5000);
    remainder = remainder % 5000;
    printf("Bankovka 2000: %dx\n", remainder / 2000);
    remainder = remainder % 2000;
    printf("Bankovka 1000: %dx\n", remainder / 1000);
    remainder = remainder % 1000;
    printf("Bankovka 500: %dx\n", remainder / 500);
    remainder = remainder % 500;
    printf("Bankovka 200: %dx\n", remainder / 200);
    remainder = remainder % 200;
    printf("Bankovka 100: %dx\n", remainder / 100);
    remainder = remainder % 100;
    return 0;
}