#include <stdio.h>

void main()
{
     int num1, num2;
    char oper;
    
    //2���� ������ 1���� ������ �Է�
    printf("���� ������ ���� �Է��ϼ���\n");
    printf("(��: 5 (+,-,*,/) 7) :");
    scanf("%d %c %d", &num1, &oper, &num2);
    
    //������� ó��
    switch(oper)
    {
        case '+' :
        printf("%d %c %d = %d\n", num1, oper, num2, num1+num2);
        break;
        
        case '-' :
        printf("%d %c %d = %d\n", num1, oper, num2, num1-num2);
        break;
        
        case '*' :
        printf("%d %c %d = %d\n", num1, oper, num2, num1*num2);
        break;
        
        case '/' :
        printf("%d %c %d = %d\n", num1, oper, num2, num1/num2);
        break;
        
        default :
        printf("�����ڸ� �߸� �Է��Ͽ����ϴ�.\n");
        break;
    }
}
