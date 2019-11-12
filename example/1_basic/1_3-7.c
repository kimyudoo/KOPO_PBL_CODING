#include <stdio.h>

void main()
{
     int num1, num2;
    char oper;
    
    //2개의 정수와 1개의 연산자 입력
    printf("정수 연산자 정수 입력하세요\n");
    printf("(예: 5 (+,-,*,/) 7) :");
    scanf("%d %c %d", &num1, &oper, &num2);
    
    //산술연산 처리
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
        printf("연산자를 잘못 입력하였습니다.\n");
        break;
    }
}
