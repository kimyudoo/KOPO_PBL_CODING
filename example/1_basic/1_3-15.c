#include <stdio.h>

void main()
{
   int kor[5]; //5명의 학생선언
   int rank[5];
   
   int i, j, sum=0;
   float avg;
   
   for(i=0; i<5; i++){
       printf("[%d] 학생의 국어점수: ", i+1);
       scanf("%d", &kor[i]);
       
       rank[i]=1;
       
       sum = sum + kor[i];
   }
   avg = (float)sum / 5;
   
//   석차 계산
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if(rank[i]<rank[j]){
                rank[i]++ //rank[i] = rank[i] + 1;
            }
        }
    }
   
   printf("번호\t 국어점수\t 등수\n");
   for(i=0; i<5; i++){
       printf("%d\t %d\t %d\n", i+1, kor[i], rank[i]);
   }
   printf("합계 : %d\n", sum);
   printf("평균 : %.2f", avg);
}
