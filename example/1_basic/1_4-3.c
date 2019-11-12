#include <stdio.h>
#define MAX 5

void main()
{
   int std[MAX][3]; //5명의 학생의 국어, 영어, 수학
   int sum[MAX];
   float avg[MAX];
   int i, j;
   //학생 국어,영어,수학 입력 
   for(i=0; i<MAX; i++){
       printf("[%d] 학생의 국어,영어,수학 입력: ", i+1);
       scanf("%d %d %d", &std[i][0], &std[i][1], &std[i][2]);
       
       sum[i] = std[i][0] + std[i][1] + std[i][2];
       avg[i] = (float)sum[i]/3;
   }
   //출력
   printf("================== 성 적 표 ==================\n");
   printf("----------------------------------------------\n");
   printf("번호\t 국어\t 영어\t 수학\t 합계\t 평균\n");
   for(i=0; i<MAX; i++){
       printf("%d\t %d\t %d\t %d\t %d\t %.2f\n", i+1, std[i][0], std[i][1], std[i][2], sum[i], avg[i]);
   }     
}
