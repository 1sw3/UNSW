#include <stdio.h>

int main(){
    int number = 0;
    printf("Enter size: ");
    scanf("%d", &number);

    for(int x = 0; x < number; x ++){
        for(int y = 0; y < number; y ++){
            if(y==number/2 || x==number/2){
                printf("*");
            }else{
                printf("-");
            }
        }
        printf("\n");
    }
}
