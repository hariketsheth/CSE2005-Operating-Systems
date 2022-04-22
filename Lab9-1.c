#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 5, x = 0;
 
void Company(){
    --mutex;
    ++full;
    --empty;
    x++;
    printf("\nCompany produces item %d",
           x);
 
    ++mutex;
}
 
void Distribution(){
    
    --mutex;
    --full;
 
    ++empty;
    printf("\nItem is distributed %d",x);
    x--;

    ++mutex;
}
 
int main(){
    int n, i;
    printf("\n1. Company Production"
           "\n2. Distribution Item"
           "\n3. Exit");
 

#pragma omp critical
 
    for (i = 1; i > 0; i++) {
 
        printf("\nEnter your choice: ");
        scanf("%d", &n);
 

        switch (n) {
        case 1:
 
      
            if ((mutex == 1)
                && (empty != 0)) {
                Company();
            }
 
            else {
                printf("Warehouse is full!");
            }
            break;
 
        case 2:
            if ((mutex == 1)
                && (full != 0)) {
                Distribution();
            }
 
            else {
                printf("Warehouse is empty!");
            }
            break;
        case 3:
            exit(0);
            break;
        }
    }
}