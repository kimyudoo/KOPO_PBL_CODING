#include <stdio.h>

void main()
{
    int score;
    char grade;
    
    //�л� ���� �Է�
    printf("�л� ���� �Է� : ");
    scanf("%d", &score);
    
    //��� ó��
    if(score >= 90){
        grade = 'A';
    }
    else if(score >= 80){
        grade = 'B';
    }
    else if(score >= 70){
        grade = 'C';
    }
    else if(score >= 60){
        grade = 'D';
    }
    else{
        grade = 'F';
    }
    printf("�л� ���� : %d\t ��� : %c\n", score, grade);
}
