#include <stdio.h>
#define MAX 5

void main()
{
   int std[MAX][3]; //5���� �л��� ����, ����, ����
   int sum[MAX];
   float avg[MAX];
   int i, j;
   //�л� ����,����,���� �Է� 
   for(i=0; i<MAX; i++){
       printf("[%d] �л��� ����,����,���� �Է�: ", i+1);
       scanf("%d %d %d", &std[i][0], &std[i][1], &std[i][2]);
       
       sum[i] = std[i][0] + std[i][1] + std[i][2];
       avg[i] = (float)sum[i]/3;
   }
   //���
   printf("================== �� �� ǥ ==================\n");
   printf("----------------------------------------------\n");
   printf("��ȣ\t ����\t ����\t ����\t �հ�\t ���\n");
   for(i=0; i<MAX; i++){
       printf("%d\t %d\t %d\t %d\t %d\t %.2f\n", i+1, std[i][0], std[i][1], std[i][2], sum[i], avg[i]);
   }     
}
