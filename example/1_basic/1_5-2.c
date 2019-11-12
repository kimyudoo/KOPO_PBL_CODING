#include <stdio.h>
//*를 출력하는 함수 선언
void star_print(int count);

void main()
{
    int i;
    for(i=1; i<10; i++)
    {
        star_print(i);
    }
    
}

void star_print(int count){
    for(int i=0; i<count; i++){
        printf("*");
    }
    printf("\n");
}

