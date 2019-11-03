#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <string.h>

// 초기값, 시작값, 최대값
const int INITIAL_VALUE = 0, START = 0, MAX_SIZE = 100;
// 주문 내역 , 판매현황 구분
const int DATE = 0, DAY_NIGHT = 1, AGE = 2, COUNT = 3, PRICE = 4, DISCOUNT = 5,
		  SALES = 1;
// 우대 사항 구분
const int NONE = 1, DISABLE = 2, MERIT = 3, MULTICHILD = 4, PREGNANT = 5;
// 권종 구분
const int DAY = 1, NIGHT = 2;
// 연령 구분
const int BABY = 1, CHILD = 2, TEEN = 3, ADULT = 4, OLD = 5, 
		  TOTAL_COUNT = 0, TOTAL_SALES = 6;
// 연령에 따른 범위값
const int MIN_BABY = 1, MIN_CHILD = 3, MIN_TEEN = 13, MIN_ADULT = 19,
		  MAX_CHILD = 12, MAX_TEEN = 18, MAX_ADULT = 64;
// 년, 월, 일 분리
const int CUT_YEAR = 10000, CUT_MONTH = 100;

// 파일 입력
int inputOrderListFile(int(*orderList)[6], int orderListIndex);

// 문자열 변환
int strTransIntDayAndNight(char *strDayAndNight);
int strTransIntAgeGroup(char *strAgeGroup);
int strTransIntDiscount(char *strDiscount);

// 판매 현황 계산
int calcDayAndNightSales(int(*orderList)[6], int(*dateSalesList)[2]);
void calcDateSales(int(*orderList)[6], int *daySalesList, int *nightSalesList);
void calcDiscountSales(int(*orderList)[6], int *discountSalesList);

// 화면 출력
void orderListPrint(int(*orderList)[6], int orderListIndex);
void dayAndNightSalesPrint(int *daySalesList, int *nightSalesList);
void dateSalesPrint(int(*dateSalesList)[2], int datePosition);
void discountSalesPrint(int *discountSalesList);

// 파일 출력
void dayAndNightSalesFilePrint(int *daySalesList, int *nightSalesList, struct tm t);
void dateSalesFilePrint(int(*dateSalesList)[2], int datePosition, struct tm t);
void discountSalesFilePrint(int *discountSalesList, struct tm t);
/************************************************************************************
				메인
*************************************************************************************/
int main()
{
	// 현재 날짜를 구함
	time_t timer;
	struct tm t;
	timer = time(NULL);
	t = *localtime(&timer);

	// report.csv 내용을 저장하는 배열
	int orderList[100][6] = { INITIAL_VALUE };
	// orderList 배열의 마지막 위치
	int orderListIndex = INITIAL_VALUE;
	// 주간권 판매 현황을 저장하는 배열
	int daySalesList[7] = { INITIAL_VALUE };
	// 야간권 판매 현황을 저장하는 배열
	int nightSalesList[7] = { INITIAL_VALUE };
	// 일자 별 매출 현황을 저장하는 배열
	int dateSalesList[100][2] = { INITIAL_VALUE };
	// dateSaleList 배열의 마지막 위치
	int datePosition = INITIAL_VALUE;
	// 우대권 판매 현황을 저장하는 배열
	int discountSalesList[6] = {INITIAL_VALUE};

	// 파일 입력
	orderListIndex = inputOrderListFile(orderList, orderListIndex);

	// 권종 별 판매 현황 계산
	datePosition = calcDayAndNightSales(orderList, dateSalesList);
	// 일자 별 매출 현황 계산
	calcDateSales(orderList, daySalesList, nightSalesList);
	// 우대권 판매 현황 계산
	calcDiscountSales(orderList, discountSalesList);

	// 입력한 파일 화면 출력 (규칙에 맞는 정수로 변환됨)
	orderListPrint(orderList, orderListIndex);
	// 권종 별 판매 현황 화면 출력
	dayAndNightSalesPrint(daySalesList, nightSalesList);
	// 일자 별 매출 현황 화면 출력
	dateSalesPrint(dateSalesList, datePosition);
	// 우대권 판매 현황 화면 출력
	discountSalesPrint(discountSalesList);

	// 권종 별 판매 현황 파일 출력
	dayAndNightSalesFilePrint(daySalesList, nightSalesList, t);
	// 일자 별 매출 현황 파일 출력
	dateSalesFilePrint(dateSalesList, datePosition, t);
	// 우대권 판매 현황 파일 출력
	discountSalesFilePrint(discountSalesList, t);
}
/************************************************************************************
			 입력부
*************************************************************************************/
// 파일 입력
int inputOrderListFile(int(*orderList)[6], int orderListIndex)
{
	FILE *fp = fopen("report.csv", "r+");
	// 문자열 동적 할당
	char *strDayAndNight = (char *)malloc(sizeof(char)* MAX_SIZE),
		 *strAgeGroup = (char *)malloc(sizeof(char)* MAX_SIZE),
		 *strDiscount = (char *)malloc(sizeof(char)* MAX_SIZE),
		 *strCategory = (char *)malloc(sizeof(char)* MAX_SIZE);

	for (int index = START; index < 6; index++)
	{
		fscanf(fp, "%s\t,", strCategory);
	}
	// 정수는 바로 배열에 입력하고 문자열은 정수로 바꿔서 입력
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
	// 메모리 해제
	free(strDayAndNight);
	free(strAgeGroup);
	free(strDiscount);
	free(strCategory);
	fclose(fp);

	return orderListIndex; // 마지막 줄의 위치를 저장
}
/************************************************************************************
				처리부
*************************************************************************************/
// 권종 문자열을 대응하는 정수값으로 변환
int strTransIntDayAndNight(char *strDayAndNight)
{
	char *day = "주간권", *night = "야간권";
	// strcmp : 두 문자열이 같으면 0을 반환
	if (!strcmp(strDayAndNight, day))
	{
		return DAY;
	}
	else if (!strcmp(strDayAndNight, night))
	{
		return NIGHT;
	}
}
// 연령구분 문자열을 대응하는 정수값으로 변환
int strTransIntAgeGroup(char *strAgeGroup)
{
	char *baby = "유아", *child = "어린이",
		 *teen = "청소년", *adult = "어른",
		 *old = "노인";

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
// 우대사항 문자열을 대응하는 정수값으로 변환
int strTransIntDiscount(char *strDiscount)
{
	char *none = "없음", *disable = "장애인",
		 *merit = "국가유공자", *multichild = "다자녀",
		 *pregnant = "임산부";
	
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

// 권종 별 판매 현황 계산
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
// 일자 별 매출 현황 계산
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
// 우대권 판매 현황 계산
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
				출력부
*************************************************************************************/
// 구매내역 출력
void orderListPrint(int(*orderList)[6], int orderListIndex)
{
	printf("================== report.csv ==================\n");
	printf("%6s %7s %6s %6s %7s %8s\n", 
		"날짜", "권종", "연령구분", "수량", "가격","우대사항");
	for (int index = START; index < orderListIndex; index++)
	{
		printf("%d %4d %6d %7d %9d %5d\n", orderList[index][DATE], 
			orderList[index][DAY_NIGHT], orderList[index][AGE], 
			orderList[index][COUNT], orderList[index][PRICE], 
			orderList[index][DISCOUNT]);
	}
	printf("------------------------------------------------\n\n");
}
// 권종 별 판매 현황 출력
void dayAndNightSalesPrint(int *daySalesList, int *nightSalesList)
{
	printf("================== 권종 별 판매현황 ==================\n");
	printf("주간권 총 %d매\n", daySalesList[TOTAL_COUNT]);
	printf("유아 %d매, 어린이 %d매, 청소년 %d매, 어른 %d매, 노인 %d매 \n",
		daySalesList[BABY], daySalesList[CHILD], daySalesList[TEEN], 
		daySalesList[ADULT], daySalesList[OLD]);
	printf("주간권 매출 : %d원\n", daySalesList[TOTAL_SALES]);
	printf("\n");
	printf("야간권 총 %d매\n", nightSalesList[TOTAL_COUNT]);
	printf("유아 %d매, 어린이 %d매, 청소년 %d매, 어른 %d매, 노인 %d매 \n",
		nightSalesList[BABY], nightSalesList[CHILD], nightSalesList[TEEN], 
		nightSalesList[ADULT], nightSalesList[OLD]);
	printf("야간권 매출 : %d원\n", nightSalesList[TOTAL_SALES]);
	printf("------------------------------------------------------\n\n");
}
// 일자 별 판매 현황 출력
void dateSalesPrint(int(*dateSalesList)[2], int datePosition)
{
	int date = INITIAL_VALUE, year = INITIAL_VALUE, month = INITIAL_VALUE;

	printf("========== 일자별 매출 현황 ==========\n");
	for (int index = START; index < datePosition; index++)
	{
		date = dateSalesList[index][DATE];
		year = date / CUT_YEAR;
		date %= CUT_YEAR;
		month = date / CUT_MONTH;
		date %= CUT_MONTH;
		printf("%d년 %02d월 %02d일 : 총 매출 %8d원\n", 
			year, month, date, dateSalesList[index][SALES]);
	}
	printf("--------------------------------------\n\n");
}
// 우대권 판매 현황 출력
void discountSalesPrint(int *discountSalesList)
{
	printf("===== 우대권 판매 현황 =====\n");
	printf("총 판매 티켓수 %5c %5d매\n",':', discountSalesList[TOTAL_COUNT]);
	printf("우대 없음 %10c %5d매\n", ':', discountSalesList[NONE]);
	printf("장애인 %13c %5d매\n", ':', discountSalesList[DISABLE]);
	printf("국가유공자 %9c %5d매\n", ':', discountSalesList[MERIT]);
	printf("다자녀 %13c %5d매\n", ':', discountSalesList[MULTICHILD]);
	printf("임산부 %13c %5d매\n", ':', discountSalesList[PREGNANT]);
	printf("----------------------------\n");
}

// 권종 별 판매 현황 파일출력
void dayAndNightSalesFilePrint(int *daySalesList, int *nightSalesList, struct tm t)
{
	char *path = (char *)malloc(sizeof(char)* MAX_SIZE); // 저장 경로
	// 저장 경로에 현재 날짜 추가
	strftime(path, MAX_SIZE, "ticket_Sales_Report_%Y-%m-%d.csv", &t); 
	FILE *fp = fopen(path, "w");
	
	fprintf(fp, "구분 ,주간권 ,야간권\n");
	fprintf(fp, "유아 ,%d,%d\n", daySalesList[BABY], nightSalesList[BABY]);
	fprintf(fp, "어린이 ,%d,%d\n", daySalesList[CHILD], nightSalesList[CHILD]);
	fprintf(fp, "청소년 ,%d,%d\n", daySalesList[TEEN], nightSalesList[TEEN]);
	fprintf(fp, "어른 ,%d,%d\n", daySalesList[ADULT], nightSalesList[ADULT]);
	fprintf(fp, "노인 ,%d,%d\n", daySalesList[OLD], nightSalesList[OLD]);
	fprintf(fp, "합계 ,%d,%d\n", daySalesList[TOTAL_COUNT], nightSalesList[TOTAL_COUNT]);
	fprintf(fp, "매출 ,%d,%d\n", daySalesList[TOTAL_SALES], nightSalesList[TOTAL_SALES]);

	free(path);
	fclose(fp);
}
// 일자 별 판매 현황 파일 출력
void dateSalesFilePrint(int(*dateSalesList)[2], int datePosition, struct tm t)
{
	char *path = (char *)malloc(sizeof(char)* MAX_SIZE); // 저장 경로
	// 저장 경로에 현재 날짜 추가
	strftime(path, MAX_SIZE, "date_Sales_Report_%Y-%m-%d.csv", &t);
	FILE *fp = fopen(path, "w");
	int date = INITIAL_VALUE, year = INITIAL_VALUE, month = INITIAL_VALUE;

	fprintf(fp, "일자 ,총 매출\n");
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
// 우대권 판매 현황 파일 출력
void discountSalesFilePrint(int *discountSalesList, struct tm t)
{
	char *path = (char *)malloc(sizeof(char)* MAX_SIZE); // 저장 경로
	// 저장 경로에 현재 날짜 추가
	strftime(path, MAX_SIZE, "discount_Sales_Report_%Y-%m-%d.csv", &t);
	FILE *fp = fopen(path, "w");

	fprintf(fp, "총 판매 티켓수, %d\n", discountSalesList[TOTAL_COUNT]);
	fprintf(fp, "우대 없음, %d\n", discountSalesList[NONE]);
	fprintf(fp, "장애인, %d\n", discountSalesList[DISABLE]);
	fprintf(fp, "국가유공자, %d\n", discountSalesList[MERIT]);
	fprintf(fp, "다자녀, %d\n", discountSalesList[MULTICHILD]);
	fprintf(fp, "임산부, %d\n", discountSalesList[PREGNANT]);

	free(path);
	fclose(fp);
}
