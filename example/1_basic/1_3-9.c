#include <stdio.h>

void main()
{
    int i=1;
    int end;
    int sum=0;
    
    printf("2개의 정수 입력 : ");
    scanf("%d %d", &i, &end);
    
    while(i<=end){
        if(i != end){
            printf("%d + ",i);
        }
        else{
            printf("%d = ",i);
        }
        sum = sum + i;
        i++;
    }
    printf("%d\n", sum);
}
