#include <stdio.h>
int main()
{    
	FILE *fp;
    fp = fopen("output.csv", "w");
    fprintf(fp, "Name,Math,English,Programming\n");
    fprintf(fp, "%s,%d,%d,%d\n", "Hong", 90, 100, 70);
    fprintf(fp, "%s,%d,%d,%d\n", "Kim", 50, 90, 50);
    fprintf(fp, "%s,%d,%d,%d\n", "Poly", 60, 100, 90);
    fprintf(fp, "%s,%d,%d,%d\n", "Park", 100, 80, 70);
    fclose(fp);
    return 0;
}
