#include <stdio.h>
void main()
{   int num[5];
   int i, j;
   int temp;
   
   for(i=0; i<5; i++){
       printf("[%d] 정수 입력: ", i);
       scanf("%d", &num[i]);
   }
     for(i=0; i<5; i++){
        for(j=i+1; j<5; j++){
            if(num[i]>num[j]){
                temp = num[i];
                num[i] = num[j];
                num[j] = temp;
            }
        }
    }
   printf("\t \t \t 정렬 후 \n");
   printf("-----------------------------------------------------\n");
   for(i=0; i<5; i++){
       printf("[%d] : %d \t", i, num[i]);
   }
   printf("\n"); }
