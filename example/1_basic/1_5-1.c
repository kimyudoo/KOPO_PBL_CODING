#include <stdio.h>
//*�� ����ϴ� �Լ� ����
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

