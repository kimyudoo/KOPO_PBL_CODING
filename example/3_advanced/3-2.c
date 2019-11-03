#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <string.h>

// �ʱⰪ, ���۰�, �ִ밪
const int INITIAL_VALUE = 0, START = 0, MAX_SIZE = 100;
// �ֹ� ���� , �Ǹ���Ȳ ����
const int DATE = 0, DAY_NIGHT = 1, AGE = 2, COUNT = 3, PRICE = 4, DISCOUNT = 5,
		  SALES = 1;
// ��� ���� ����
const int NONE = 1, DISABLE = 2, MERIT = 3, MULTICHILD = 4, PREGNANT = 5;
// ���� ����
const int DAY = 1, NIGHT = 2;
// ���� ����
const int BABY = 1, CHILD = 2, TEEN = 3, ADULT = 4, OLD = 5, 
		  TOTAL_COUNT = 0, TOTAL_SALES = 6;
// ���ɿ� ���� ������
const int MIN_BABY = 1, MIN_CHILD = 3, MIN_TEEN = 13, MIN_ADULT = 19,
		  MAX_CHILD = 12, MAX_TEEN = 18, MAX_ADULT = 64;
// ��, ��, �� �и�
const int CUT_YEAR = 10000, CUT_MONTH = 100;

// ���� �Է�
int inputOrderListFile(int(*orderList)[6], int orderListIndex);

// ���ڿ� ��ȯ
int strTransIntDayAndNight(char *strDayAndNight);
int strTransIntAgeGroup(char *strAgeGroup);
int strTransIntDiscount(char *strDiscount);

// �Ǹ� ��Ȳ ���
int calcDayAndNightSales(int(*orderList)[6], int(*dateSalesList)[2]);
void calcDateSales(int(*orderList)[6], int *daySalesList, int *nightSalesList);
void calcDiscountSales(int(*orderList)[6], int *discountSalesList);

// ȭ�� ���
void orderListPrint(int(*orderList)[6], int orderListIndex);
void dayAndNightSalesPrint(int *daySalesList, int *nightSalesList);
void dateSalesPrint(int(*dateSalesList)[2], int datePosition);
void discountSalesPrint(int *discountSalesList);

// ���� ���
void dayAndNightSalesFilePrint(int *daySalesList, int *nightSalesList, struct tm t);
void dateSalesFilePrint(int(*dateSalesList)[2], int datePosition, struct tm t);
void discountSalesFilePrint(int *discountSalesList, struct tm t);
/************************************************************************************
				����
*************************************************************************************/
int main()
{
	// ���� ��¥�� ����
	time_t timer;
	struct tm t;
	timer = time(NULL);
	t = *localtime(&timer);

	// report.csv ������ �����ϴ� �迭
	int orderList[100][6] = { INITIAL_VALUE };
	// orderList �迭�� ������ ��ġ
	int orderListIndex = INITIAL_VALUE;
	// �ְ��� �Ǹ� ��Ȳ�� �����ϴ� �迭
	int daySalesList[7] = { INITIAL_VALUE };
	// �߰��� �Ǹ� ��Ȳ�� �����ϴ� �迭
	int nightSalesList[7] = { INITIAL_VALUE };
	// ���� �� ���� ��Ȳ�� �����ϴ� �迭
	int dateSalesList[100][2] = { INITIAL_VALUE };
	// dateSaleList �迭�� ������ ��ġ
	int datePosition = INITIAL_VALUE;
	// ���� �Ǹ� ��Ȳ�� �����ϴ� �迭
	int discountSalesList[6] = {INITIAL_VALUE};

	// ���� �Է�
	orderListIndex = inputOrderListFile(orderList, orderListIndex);

	// ���� �� �Ǹ� ��Ȳ ���
	datePosition = calcDayAndNightSales(orderList, dateSalesList);
	// ���� �� ���� ��Ȳ ���
	calcDateSales(orderList, daySalesList, nightSalesList);
	// ���� �Ǹ� ��Ȳ ���
	calcDiscountSales(orderList, discountSalesList);

	// �Է��� ���� ȭ�� ��� (��Ģ�� �´� ������ ��ȯ��)
	orderListPrint(orderList, orderListIndex);
	// ���� �� �Ǹ� ��Ȳ ȭ�� ���
	dayAndNightSalesPrint(daySalesList, nightSalesList);
	// ���� �� ���� ��Ȳ ȭ�� ���
	dateSalesPrint(dateSalesList, datePosition);
	// ���� �Ǹ� ��Ȳ ȭ�� ���
	discountSalesPrint(discountSalesList);

	// ���� �� �Ǹ� ��Ȳ ���� ���
	dayAndNightSalesFilePrint(daySalesList, nightSalesList, t);
	// ���� �� ���� ��Ȳ ���� ���
	dateSalesFilePrint(dateSalesList, datePosition, t);
	// ���� �Ǹ� ��Ȳ ���� ���
	discountSalesFilePrint(discountSalesList, t);
}
/************************************************************************************
			 �Էº�
*************************************************************************************/
// ���� �Է�
int inputOrderListFile(int(*orderList)[6], int orderListIndex)
{
	FILE *fp = fopen("report.csv", "r+");
	// ���ڿ� ���� �Ҵ�
	char *strDayAndNight = (char *)malloc(sizeof(char)* MAX_SIZE),
		 *strAgeGroup = (char *)malloc(sizeof(char)* MAX_SIZE),
		 *strDiscount = (char *)malloc(sizeof(char)* MAX_SIZE),
		 *strCategory = (char *)malloc(sizeof(char)* MAX_SIZE);

	for (int index = START; index < 6; index++)
	{
		fscanf(fp, "%s\t,", strCategory);
	}
	// ������ �ٷ� �迭�� �Է��ϰ� ���ڿ��� ������ �ٲ㼭 �Է�
	while (fscanf(fp, "%d, %s\t, %s\t, %d, %d, %s",
		&orderList[orderListIndex][DATE], strDayAndNight,
		strAgeGroup, &orderList[orderListIndex][COUNT],
		&orderList[orderListIndex][PRICE], strDiscount) != EOF)
	{
		orderList[orderListIndex][DAY_NIGHT] = strTransIntDayAndNight(strDayAndNight);
		orderList[orderListIndex][AGE] = strTransIntAgeGroup(strAgeGroup);
		orderList[orderListIndex][DISCOUNT] = strTransIntDiscount(strDiscount);
		orderListIndex++;
	}
	// �޸� ����
	free(strDayAndNight);
	free(strAgeGroup);
	free(strDiscount);
	free(strCategory);
	fclose(fp);

	return orderListIndex; // ������ ���� ��ġ�� ����
}
/************************************************************************************
				ó����
*************************************************************************************/
// ���� ���ڿ��� �����ϴ� ���������� ��ȯ
int strTransIntDayAndNight(char *strDayAndNight)
{
	char *day = "�ְ���", *night = "�߰���";
	// strcmp : �� ���ڿ��� ������ 0�� ��ȯ
	if (!strcmp(strDayAndNight, day))
	{
		return DAY;
	}
	else if (!strcmp(strDayAndNight, night))
	{
		return NIGHT;
	}
}
// ���ɱ��� ���ڿ��� �����ϴ� ���������� ��ȯ
int strTransIntAgeGroup(char *strAgeGroup)
{
	char *baby = "����", *child = "���",
		 *teen = "û�ҳ�", *adult = "�",
		 *old = "����";

	if (!strcmp(strAgeGroup, baby))
	{
		return BABY;
	}
	else if (!strcmp(strAgeGroup, child))
	{
		return CHILD;
	}
	else if (!strcmp(strAgeGroup, teen))
	{
		return TEEN;
	}
	else if (!strcmp(strAgeGroup, adult))
	{
		return ADULT;
	}
	else if (!strcmp(strAgeGroup, old))
	{
		return OLD;
	}
}
// ������ ���ڿ��� �����ϴ� ���������� ��ȯ
int strTransIntDiscount(char *strDiscount)
{
	char *none = "����", *disable = "�����",
		 *merit = "����������", *multichild = "���ڳ�",
		 *pregnant = "�ӻ��";
	
	if (!strcmp(strDiscount, none))
	{
		return NONE;
	}
	else if (!strcmp(strDiscount, disable))
	{
		return DISABLE;
	}
	else if (!strcmp(strDiscount, merit))
	{
		return MERIT;
	}
	else if (!strcmp(strDiscount, multichild))
	{
		return MULTICHILD;
	}
	else if (!strcmp(strDiscount, pregnant))
	{
		return PREGNANT;
	}
}

// ���� �� �Ǹ� ��Ȳ ���
int calcDayAndNightSales(int(*orderList)[6], int(*dateSalesList)[2])
{
	int date = INITIAL_VALUE, year = INITIAL_VALUE, month = INITIAL_VALUE;
	int datePosition = INITIAL_VALUE;
	for (int index = START; index < MAX_SIZE; index++)
	{
		date = orderList[index][DATE];

		if (index == START)
		{
			dateSalesList[datePosition][DATE] = date;
			dateSalesList[datePosition][SALES] += orderList[index][PRICE];
		}
		else if (orderList[index][DATE] == orderList[index - 1][DATE])
		{
			dateSalesList[datePosition][SALES] += orderList[index][PRICE];
		}
		else
		{
			datePosition++;
			dateSalesList[datePosition][DATE] = date;
			dateSalesList[datePosition][SALES] += orderList[index][PRICE];
		}
	}
	return datePosition;
}
// ���� �� ���� ��Ȳ ���
void calcDateSales(int(*orderList)[6], int *daySalesList, int *nightSalesList)
{
	int ageGroup = INITIAL_VALUE;

	for (int index = START; index < MAX_SIZE; index++)
	{
		ageGroup = orderList[index][AGE];

		if (orderList[index][DAY_NIGHT] == DAY)
		{
			daySalesList[TOTAL_COUNT] += orderList[index][COUNT];
			daySalesList[TOTAL_SALES] += orderList[index][PRICE];
			if (ageGroup == BABY)
			{
				daySalesList[BABY] += orderList[index][COUNT];
			}
			else if (ageGroup == CHILD)
			{
				daySalesList[CHILD] += orderList[index][COUNT];
			}
			else if (ageGroup == TEEN)
			{
				daySalesList[TEEN] += orderList[index][COUNT];
			}
			else if (ageGroup == ADULT)
			{
				daySalesList[ADULT] += orderList[index][COUNT];
			}
			else if (ageGroup == OLD)
			{
				daySalesList[OLD] += orderList[index][COUNT];
			}	
		}
		else if (orderList[index][DAY_NIGHT] == NIGHT)
		{
			nightSalesList[TOTAL_COUNT] += orderList[index][COUNT];
			nightSalesList[TOTAL_SALES] += orderList[index][PRICE];
			if (ageGroup == BABY)
			{
				nightSalesList[BABY] += orderList[index][COUNT];
			}
			else if (ageGroup == CHILD)
			{
				nightSalesList[CHILD] += orderList[index][COUNT];
			}
			else if (ageGroup == TEEN)
			{
				nightSalesList[TEEN] += orderList[index][COUNT];
			}
			else if (ageGroup == ADULT)
			{
				nightSalesList[ADULT] += orderList[index][COUNT];
			}
			else if (ageGroup == OLD)
			{
				nightSalesList[OLD] += orderList[index][COUNT];
			}		
		}
	}
}
// ���� �Ǹ� ��Ȳ ���
void calcDiscountSales(int(*orderList)[6], int *discountSalesList)
{
	int discount = INITIAL_VALUE;

	for (int index = START; index < MAX_SIZE; index++)
	{	
		discountSalesList[TOTAL_COUNT] += orderList[index][COUNT];
		if (orderList[index][DISCOUNT] == NONE)
		{
			discountSalesList[NONE] += orderList[index][COUNT];
		}
		else if (orderList[index][DISCOUNT] == DISABLE)
		{
			discountSalesList[DISABLE] += orderList[index][COUNT];
		}
		else if (orderList[index][DISCOUNT] == MERIT)
		{
			discountSalesList[MERIT] += orderList[index][COUNT];
		}
		else if (orderList[index][DISCOUNT] == MULTICHILD)
		{
			discountSalesList[MULTICHILD] += orderList[index][COUNT];
		}
		else if (orderList[index][DISCOUNT] == PREGNANT)
		{
			discountSalesList[PREGNANT] += orderList[index][COUNT];
		}
	}
}
/************************************************************************************
				��º�
*************************************************************************************/
// ���ų��� ���
void orderListPrint(int(*orderList)[6], int orderListIndex)
{
	printf("================== report.csv ==================\n");
	printf("%6s %7s %6s %6s %7s %8s\n", 
		"��¥", "����", "���ɱ���", "����", "����","������");
	for (int index = START; index < orderListIndex; index++)
	{
		printf("%d %4d %6d %7d %9d %5d\n", orderList[index][DATE], 
			orderList[index][DAY_NIGHT], orderList[index][AGE], 
			orderList[index][COUNT], orderList[index][PRICE], 
			orderList[index][DISCOUNT]);
	}
	printf("------------------------------------------------\n\n");
}
// ���� �� �Ǹ� ��Ȳ ���
void dayAndNightSalesPrint(int *daySalesList, int *nightSalesList)
{
	printf("================== ���� �� �Ǹ���Ȳ ==================\n");
	printf("�ְ��� �� %d��\n", daySalesList[TOTAL_COUNT]);
	printf("���� %d��, ��� %d��, û�ҳ� %d��, � %d��, ���� %d�� \n",
		daySalesList[BABY], daySalesList[CHILD], daySalesList[TEEN], 
		daySalesList[ADULT], daySalesList[OLD]);
	printf("�ְ��� ���� : %d��\n", daySalesList[TOTAL_SALES]);
	printf("\n");
	printf("�߰��� �� %d��\n", nightSalesList[TOTAL_COUNT]);
	printf("���� %d��, ��� %d��, û�ҳ� %d��, � %d��, ���� %d�� \n",
		nightSalesList[BABY], nightSalesList[CHILD], nightSalesList[TEEN], 
		nightSalesList[ADULT], nightSalesList[OLD]);
	printf("�߰��� ���� : %d��\n", nightSalesList[TOTAL_SALES]);
	printf("------------------------------------------------------\n\n");
}
// ���� �� �Ǹ� ��Ȳ ���
void dateSalesPrint(int(*dateSalesList)[2], int datePosition)
{
	int date = INITIAL_VALUE, year = INITIAL_VALUE, month = INITIAL_VALUE;

	printf("========== ���ں� ���� ��Ȳ ==========\n");
	for (int index = START; index < datePosition; index++)
	{
		date = dateSalesList[index][DATE];
		year = date / CUT_YEAR;
		date %= CUT_YEAR;
		month = date / CUT_MONTH;
		date %= CUT_MONTH;
		printf("%d�� %02d�� %02d�� : �� ���� %8d��\n", 
			year, month, date, dateSalesList[index][SALES]);
	}
	printf("--------------------------------------\n\n");
}
// ���� �Ǹ� ��Ȳ ���
void discountSalesPrint(int *discountSalesList)
{
	printf("===== ���� �Ǹ� ��Ȳ =====\n");
	printf("�� �Ǹ� Ƽ�ϼ� %5c %5d��\n",':', discountSalesList[TOTAL_COUNT]);
	printf("��� ���� %10c %5d��\n", ':', discountSalesList[NONE]);
	printf("����� %13c %5d��\n", ':', discountSalesList[DISABLE]);
	printf("���������� %9c %5d��\n", ':', discountSalesList[MERIT]);
	printf("���ڳ� %13c %5d��\n", ':', discountSalesList[MULTICHILD]);
	printf("�ӻ�� %13c %5d��\n", ':', discountSalesList[PREGNANT]);
	printf("----------------------------\n");
}

// ���� �� �Ǹ� ��Ȳ �������
void dayAndNightSalesFilePrint(int *daySalesList, int *nightSalesList, struct tm t)
{
	char *path = (char *)malloc(sizeof(char)* MAX_SIZE); // ���� ���
	// ���� ��ο� ���� ��¥ �߰�
	strftime(path, MAX_SIZE, "ticket_Sales_Report_%Y-%m-%d.csv", &t); 
	FILE *fp = fopen(path, "w");
	
	fprintf(fp, "���� ,�ְ��� ,�߰���\n");
	fprintf(fp, "���� ,%d,%d\n", daySalesList[BABY], nightSalesList[BABY]);
	fprintf(fp, "��� ,%d,%d\n", daySalesList[CHILD], nightSalesList[CHILD]);
	fprintf(fp, "û�ҳ� ,%d,%d\n", daySalesList[TEEN], nightSalesList[TEEN]);
	fprintf(fp, "� ,%d,%d\n", daySalesList[ADULT], nightSalesList[ADULT]);
	fprintf(fp, "���� ,%d,%d\n", daySalesList[OLD], nightSalesList[OLD]);
	fprintf(fp, "�հ� ,%d,%d\n", daySalesList[TOTAL_COUNT], nightSalesList[TOTAL_COUNT]);
	fprintf(fp, "���� ,%d,%d\n", daySalesList[TOTAL_SALES], nightSalesList[TOTAL_SALES]);

	free(path);
	fclose(fp);
}
// ���� �� �Ǹ� ��Ȳ ���� ���
void dateSalesFilePrint(int(*dateSalesList)[2], int datePosition, struct tm t)
{
	char *path = (char *)malloc(sizeof(char)* MAX_SIZE); // ���� ���
	// ���� ��ο� ���� ��¥ �߰�
	strftime(path, MAX_SIZE, "date_Sales_Report_%Y-%m-%d.csv", &t);
	FILE *fp = fopen(path, "w");
	int date = INITIAL_VALUE, year = INITIAL_VALUE, month = INITIAL_VALUE;

	fprintf(fp, "���� ,�� ����\n");
	for (int index = START; index < datePosition; index++)
	{
		date = dateSalesList[index][DATE];
		year = date / CUT_YEAR;
		date %= CUT_YEAR;
		month = date / CUT_MONTH;
		date %= CUT_MONTH;
		fprintf(fp, "%d-%02d-%02d ,%d\n",
			year, month, date, dateSalesList[index][SALES]);
	}
	free(path);
	fclose(fp);
}
// ���� �Ǹ� ��Ȳ ���� ���
void discountSalesFilePrint(int *discountSalesList, struct tm t)
{
	char *path = (char *)malloc(sizeof(char)* MAX_SIZE); // ���� ���
	// ���� ��ο� ���� ��¥ �߰�
	strftime(path, MAX_SIZE, "discount_Sales_Report_%Y-%m-%d.csv", &t);
	FILE *fp = fopen(path, "w");

	fprintf(fp, "�� �Ǹ� Ƽ�ϼ�, %d\n", discountSalesList[TOTAL_COUNT]);
	fprintf(fp, "��� ����, %d\n", discountSalesList[NONE]);
	fprintf(fp, "�����, %d\n", discountSalesList[DISABLE]);
	fprintf(fp, "����������, %d\n", discountSalesList[MERIT]);
	fprintf(fp, "���ڳ�, %d\n", discountSalesList[MULTICHILD]);
	fprintf(fp, "�ӻ��, %d\n", discountSalesList[PREGNANT]);

	free(path);
	fclose(fp);
}
