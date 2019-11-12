#include <stdio.h>

void main()
{
   int kor[5]; //5명의 학생선언
   int i, j, sum=0;
   float avg;
   
   for(i=0; i<5; i++){
       printf("[%d] 학생의 국어점수: ", i+1);
       scanf("%d", &kor[i]);
       
       sum = sum + kor[i];
   }
   avg = (float)sum / 5;
   
   printf("합계 : %d\n", sum);
   printf("평균 : %.2f", avg);
}
