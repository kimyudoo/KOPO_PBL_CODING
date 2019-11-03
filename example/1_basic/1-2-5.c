#include <stdio.h>
int main()
{
    FILE *fp;
    fp = fopen("output.txt", "a");
    fprintf(fp, "제 이름은 홍길동 이고, 나이는 20살 입니다.\n");
    fclose(fp);
    return 0;
}
