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
   printf("\n1 ~ 100�� ���� �� 3�� ����� �� : %d\n", sum);
}
