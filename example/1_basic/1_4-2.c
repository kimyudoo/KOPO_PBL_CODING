#include <stdio.h>

void main()
{
   int kor[5]; //5���� �л�����
   int rank[5];
   
   int i, j, sum=0;
   float avg;
   
   for(i=0; i<5; i++){
       printf("[%d] �л��� ��������: ", i+1);
       scanf("%d", &kor[i]);
       
       rank[i]=1;
       
       sum = sum + kor[i];
   }
   avg = (float)sum / 5;
   
//   ���� ���
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if(kor[i]<kor[j]){
                rank[i]++; //rank[i] = rank[i] + 1;
            }
        }
    }
   
   printf("\n��ȣ\t ����\t ���\n");
   printf("---------------------\n");
   for(i=0; i<5; i++){
       printf("%d\t %d\t %d\n", i+1, kor[i], rank[i]);
   }
   printf("�հ� : %d\n", sum);
   printf("��� : %.2f", avg);
}
