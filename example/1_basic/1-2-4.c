#include <stdio.h>
int main()
{
    FILE *fp;
    fp = fopen("output.txt", "w");
    fprintf(fp, "�� �̸��� ȫ�浿 �̰�, ���̴� 20�� �Դϴ�.\n");
    fclose(fp);
    return 0;
}