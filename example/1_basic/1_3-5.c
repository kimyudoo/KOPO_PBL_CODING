#include <stdio.h>

void main()
{
   int excel, powpoint, word;
    int sum;
    float avg;
    
    printf("����, �Ŀ�����Ʈ, ���� : ");
    scanf("%d %d %d", &excel, &powpoint, &word);
    
    //�հ� ��� ���
    sum = excel + powpoint + word;
    avg = (float)sum / 3;
    
    printf("�հ� : %d\n", sum);
    printf("��� : %.2f\n", avg);
    
    if((avg >= 60) && (excel > 40) && (powpoint > 40) && (word > 40)){
        printf("�հ�\n");
    }
    else{
        printf("���հ�\n");
    }
}
