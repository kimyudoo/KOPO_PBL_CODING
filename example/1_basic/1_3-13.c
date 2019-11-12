#include <stdio.h>
void main()
{  
    int sum = 0;
    int i;
   for(i=1; i<=100; i++){
       if((i % 3) == 0){
           sum = sum + i;
           printf("%d ", i);
       }
   }
   printf("\n1 ~ 100의 정수 중 3의 배수의 합 : %d\n", sum);
}
