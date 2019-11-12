#include <stdio.h>
//*를 출력하는 함수 선언
void star_print();

void main()
{
    star_print();
    printf("Kim Jong Min\n");
    star_print();
}

void star_print(){
    for(int i=0; i<10; i++){
        printf("*");
    }
    printf("\n");
}

