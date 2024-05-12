#include <stdio.h>

int main() {
    int obrazec, a, b;
    
    scanf("%d%d%d", &obrazec, &a, &b);
    
    //
    if (a <= 0 || (b <= 0 && obrazec != 3)) {return 0;}

    int i,k,j = 0;

    if (obrazec == 0) {
        for (i = 0; i < b; i += 1) {
            for (k = 0; k < a; k += 1) {
                printf("x");
            }
            printf("\n");
        }
    }

    else if (obrazec == 1) {
        for (i = 0; i < b; i += 1) {
            if (i == 0 || i == b-1) {
                for (k = 0; k < a; k += 1) {
                    printf("x");
                }
            }
            else {
                for (k = 0; k < a; k += 1) {
                    if (k == 0 || k == a-1) {printf("x");}
                    else {printf(" ");}
                }
            }
            printf("\n");
        }
    }

    else if (obrazec == 2) {
        for (i = 0; i < b; i += 1) {
            if (i == 0 || i == b-1) {
                for (k = 0; k < a; k += 1) {
                    printf("x");
                }
            }
            else {
                for (k = 0; k < a; k += 1) {
                    if (k == 0 || k == a-1) {printf("x");}
                    else {
                        printf("%d",j%10);
                        j += 1;
                    }
                }
            }
            printf("\n");
        }
    }

    else if (obrazec == 3) {
        for (i = 0; i < a; i += 1) {
            for (k = 0; k < i; k += 1) {
                printf(" ");
            }
            printf("x\n");
        }
    }

    else if (obrazec == 6) {
        if (a % 2 != 1) {return 0;}
        for (i = 0; i < b; i += 1) {
            for (k = 0; k < a; k += 1) {
                if (i == 0) {
                    printf("x");
                }
                else {
                    if (k == a/2) {
                        printf("x");
                    }
                    else {
                        printf(" ");
                    }
                }

            }
            printf("\n");
        }
    }

    else if (obrazec == 9) {
        for (i = 0; i < b; i += 1) {
            if (i == 0 || i == b-1) {
                for (k = 0; k < a; k += 1) {
                    printf("x");
                }
            }
            else {
                for (k = 0; k < a; k += 1) {
                    if (k == 0 || k == a-1) {printf("x");}
                    else {
                        printf("%d", (j+(k-1)*(b-2))%10 );
                        
                    }
                }
                j += 1;
            }
            printf("\n");
        }
    }

    else {printf("Neznamy obrazec");}
    //

    return 0;
}