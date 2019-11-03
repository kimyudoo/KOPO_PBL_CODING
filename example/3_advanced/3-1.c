#include <stdio.h>
#include <time.h>
#include <stdbool.h>

// 권종별 가격
const int BABY_PRICE = 0,
		  ADULT_DAY_PRICE = 56000, ADULT_NIGHT_PRICE = 46000,
		  TEEN_DAY_PRICE = 47000, TEEN_NIGHT_PRICE = 40000,
		  CHILD_DAY_PRICE = 44000, CHILD_NIGHT_PRICE = 37000,
		  OLD_DAY_PRICE = 44000, OLD_NIGHT_PRICE = 37000;

// 주민등록번호 분석
const long long int FULL_DIGIT = 10000000000000,
					FULL_DIGIT_MIN = 10000000000, 
					SEVEN_DIGIT = 1000000;

const int TWO_DIGIT = 100, ONE_DIGIT = 10,
		  OLD_GENERATION = 1900, NEW_GENERATION = 2000,
		  MALE_OLD = 1, FEMALE_OLD = 2, MALE_NEW = 3, FEMALE_NEW = 4,
		  BEFORE_BIRTH = 2, AFTER_BIRTH = 1;

// 나이에 따른 범위
const int 	MIN_BABY = 1, MIN_CHILD = 3, MIN_TEEN = 13, MIN_ADULT = 19,
		    MAX_CHILD = 12, MAX_TEEN = 18, MAX_ADULT = 64;

// 나이에 따른 그룹
const int BABY = 1, CHILD = 2, TEEN = 3, ADULT = 4, OLD = 5;

// 할인율
const float DISABLE_DISCOUNT_RATE = 0.6, MERIT_DISCOUNT_RATE = 0.5,
			MULTICHILD_DISCOUNT_RATE = 0.8,
                         PREGNANT_DISCOUNT_RATE = 0.85;

// 최대 주문량
const int MAX_COUNT = 10, MIN_COUNT = 1;

void errorMessagePrint();

int inputTicketSelect();
long long int inputCustomerIDNumber();
int inputOrderCount();
int inputDiscountSelect();
void inputData(int* ticketSelect, long long int* customerIDNumber,
			   int* orderCount, int* discountSelect);

int calcAge(long long int customerIDNumber);
int calcAgeGroup(int age);
int calcPriceProcess(int age, int ticketSelect);
int calcDiscount(int calcPrice, int discountSelect);
int calcPriceResult(int calcPrice, int orderCount);
int processIntergration(long long int customerIDNumber, int ticketSelect,
						int discountSelect, int orderCount, 
						int priceResult, int *age);
void saveOrderList(int ticketSelect, int age, int orderCount,
				   int priceResult, int discountSelect, 
				   int *position, int(*orderList)[5]);

void pricePrint(int priceResult);
void orderPrint(int totalPrice, int* position, int(*orderList)[5]);
void orderFilePrint(int totalPrice, int* position, int(*orderList)[5], int* filePosition);

int orderContinue();
/************************************************************
   메인
*************************************************************/
int main()
{
	int totalPrice = 0; // 주문 총액
	int position = 0; // 주문 내역 배열 탐색용
	int filePosition = 0; // 파일 출력 첫줄 구분
	int reportPosition = 0;
	int orderList[100][5] = { 0 }; // 주문 내역 저장
	int isExit = 0;
	do
	{	
		while (true)
		{
			long long int customerIDNumber = 0;	// 주민등록번호
			// 권종, 주문 갯수, 우대사항
			int ticketSelect = 0, orderCount = 0, discountSelect = 0;
			int priceResult = 0, age = 0; // 가격, 나이
			int continueSelect = 0; // 이어서 주문

			// 입력함수 호출
			inputData(&ticketSelect, &customerIDNumber, 
					  &orderCount, &discountSelect);

			// 요금 계산
			priceResult = processIntergration(customerIDNumber, 
						  ticketSelect, discountSelect, orderCount,
						  priceResult, &age);
			// 주문 내역 저장
			saveOrderList(ticketSelect, age, orderCount,
						  priceResult, discountSelect, 
						  &position, orderList);

			// 요금 합계 계산
			totalPrice += priceResult;

			// 가격 출력
			pricePrint(priceResult);

			// 이어서 주문할지 입력
			continueSelect = orderContinue();

			if (continueSelect == 2)
			{
				break;
			}
		}
		// 주문 내역 출력
		orderPrint(totalPrice, &position, orderList);
		// 주문 내역 파일로 출력
		orderFilePrint(totalPrice, &position, orderList, &filePosition);

		printf("계속 진행(1: 새로운 주문, 2: 프로그램 종료) : ");
		scanf("%d", &isExit);
		position = 0;
		totalPrice = 0;
	} while (isExit == 1);
	return 0;
}
/************************************************************
   입력부
*************************************************************/
// 권종 입력
int inputTicketSelect()
{
	int ticketSelect = 0;

	printf("권종을 선택하세요.\n");
	printf("1. 주간권\n");
	printf("2. 야간권\n");
	while (true)
	{
		scanf("%d", &ticketSelect);
		if (ticketSelect == 1 || ticketSelect == 2)
		{
			break;
		}
		else
		{
			errorMessagePrint();
		}
		getchar();
	}
	return ticketSelect;
}
// 주민등록번호 입력
long long int inputCustomerIDNumber()
{
	long long int customerIDNumber = 0;

	printf("주민번호를 입력하세요\n");
	while (true)
	{
		scanf("%lld", &customerIDNumber);
		if ((customerIDNumber >= FULL_DIGIT_MIN) &&
			(customerIDNumber < FULL_DIGIT))
		{
			break;
		}
		else
		{
			errorMessagePrint();
		}
		getchar();
	}
	return customerIDNumber;
}
// 주문 갯수 입력
int inputOrderCount()
{
	int orderCount = 0;

	printf("몇개를 주문하시겠습니까? (최대 10개)\n");
	while (true)
	{
		scanf("%d", &orderCount);
		if ((orderCount <= MAX_COUNT) && (orderCount >= MIN_COUNT))
		{
			break;
		}
		else
		{
			errorMessagePrint();
		}
		getchar();
	}
	return orderCount;
}
// 우대사항 입력
int inputDiscountSelect()
{
	int discountSelect = 0;

	printf("우대사항을 선택하세요.\n");
	printf("1. 없음 (나이 우대는 자동처리)\n");
	printf("2. 장애인\n");
	printf("3. 국가유공자\n");
	printf("4. 다자녀\n");
	printf("5. 임산부\n");

	while (true)
	{
		scanf("%d", &discountSelect);
		if (discountSelect >= 1 &&
			discountSelect <= 5)
		{
			break;
		}
		else
		{
			errorMessagePrint();
		}
		getchar();
	}
	return discountSelect;
}
// 입력 함수 호출
void inputData(int* ticketSelect, long long int* customerIDNumber,
			   int* orderCount, int* discountSelect)
{
	// 권종 입력
	*ticketSelect = inputTicketSelect();
	// 주민등록번호 입력
	*customerIDNumber = inputCustomerIDNumber();
	// 주문 갯수 입력
	*orderCount = inputOrderCount();
	// 우대사항 입력
	*discountSelect = inputDiscountSelect();
}
/************************************************************
   처리부
*************************************************************/
// 만나이 계산
int calcAge(long long int customerIDNumber)
{
	long int calcIDNumber = 0;	// 생년월일 계산
	int customerYear = 0, customerMonth = 0, customerDay = 0; // 구매자 생년월일
	int todayYear = 0, todayMonth = 0, todayDay = 0; // 오늘 날짜
	int type = 0;	// 구매자 성별 및 2000년생 구분
	int koreanAge = 0, age = 0;

	/* 주민등록번호로 생년월일 추출 */
	customerIDNumber += FULL_DIGIT;	// 앞자리 보존을 위해 해당값을 더해줌
	calcIDNumber = customerIDNumber / SEVEN_DIGIT;
	type = calcIDNumber % 10;			// 뒷자리의 첫 번호
	calcIDNumber /= ONE_DIGIT;
	customerDay = calcIDNumber % TWO_DIGIT;		// '일'
	calcIDNumber /= TWO_DIGIT;
	customerMonth = calcIDNumber % TWO_DIGIT;	// '월'
	calcIDNumber /= TWO_DIGIT;
	customerYear = calcIDNumber % TWO_DIGIT;	// '생년'

	if ((type == MALE_NEW) || (type == FEMALE_NEW))	// 2000년생 이후 태생인 경우
	{
		customerYear += NEW_GENERATION;
	}
	else
	{
		customerYear += OLD_GENERATION;
	}

	/* 오늘 날짜를 구하기 */
	time_t current;
	time(&current);
	struct tm* structTime;
	structTime = localtime(&current);
	
	todayYear = structTime->tm_year + OLD_GENERATION;	// 현재 년도
	todayMonth = structTime->tm_mon + 1;		// 현재 월
	todayDay = structTime->tm_mday;						// 현재 일
	koreanAge = todayYear - customerYear + 1;			// 한국식 나이

	/* 만나이 계산 */
	if ((customerMonth < todayMonth)
		|| ((customerMonth == todayMonth) && (customerDay <= todayDay)))
	{
		age = koreanAge - AFTER_BIRTH;
	}
	else
	{
		age = koreanAge - BEFORE_BIRTH;
	}
	return age;
}
// 연령대 별 분류
int calcAgeGroup(int age)
{
	if ((age < MIN_CHILD))
	{
		return 1;
	}
	else if ((age >= MIN_CHILD) && (age <= MAX_CHILD))
	{
		return 2;
	}
	else if ((age >= MIN_TEEN) && (age <= MAX_TEEN))
	{
		return 3;
	}
	else if ((age >= MIN_ADULT) && (age <= MAX_ADULT))
	{
		return 4;
	}
	else if ((age>MAX_ADULT))
	{
		return 5;
	}
}
// 주야권과 나이에 따른 금액 계산
int calcPriceProcess(int age, int ticketSelect)
{
	int calcPrice = 0;

	if (calcAgeGroup(age) == BABY)
	{
		calcPrice = BABY_PRICE;
	}
	else if (calcAgeGroup(age) == CHILD)
	{
		if (ticketSelect == 1)
		{
			calcPrice = CHILD_DAY_PRICE;
		}
		else if (ticketSelect == 2)
		{
			calcPrice = CHILD_NIGHT_PRICE;
		}
	}
	else if (calcAgeGroup(age) == TEEN)
	{
		if (ticketSelect == 1)
		{
			calcPrice = TEEN_DAY_PRICE;
		}
		else if (ticketSelect == 2)
		{
			calcPrice = TEEN_NIGHT_PRICE;
		}
	}
	else if (calcAgeGroup(age) == ADULT)
	{
		if (ticketSelect == 1)
		{
			calcPrice = ADULT_DAY_PRICE;
		}
		else if (ticketSelect == 2)
		{
			calcPrice = ADULT_NIGHT_PRICE;
		}
	}
	else
	{
		calcPrice = OLD_DAY_PRICE;
	}
	return calcPrice;
}
// 우대사항에 따른 할인 계산
int calcDiscount(int calcPrice, int discountSelect)
{
	switch (discountSelect)
	{
	case 2:	// 장애인
		calcPrice *= DISABLE_DISCOUNT_RATE;
		break;
	case 3:	// 국가유공자
		calcPrice *= MERIT_DISCOUNT_RATE;
		break;
	case 4:	// 다자녀
		calcPrice *= MULTICHILD_DISCOUNT_RATE;
		break;
	case 5:	// 임산부
		calcPrice *= PREGNANT_DISCOUNT_RATE;
		break;
	default:
		break;
	}
	return calcPrice;
}
// 주문 갯수에 따른 금액 계산
int calcPriceResult(int calcPrice, int orderCount)
{
	return  calcPrice * orderCount;
}
// 계산 함수 호출
int processIntergration(long long int customerIDNumber, int ticketSelect,
						int discountSelect, int orderCount, 
						int priceResult, int *age)
{
	int calcPrice = 0;

	// 만 나이 계산
	*age = calcAge(customerIDNumber);

	// 주야권과 나이에 따른 금액 계산
	calcPrice = calcPriceProcess(*age, ticketSelect);

	// 우대사항에 따른 할인 계산
	calcPrice = calcDiscount(calcPrice, discountSelect);

	// 주문 갯수에 따른 최종 금액 계산
	priceResult = calcPriceResult(calcPrice, orderCount);

	return priceResult; // 최종 요금 리턴
}
// 주문 내역 저장
void saveOrderList(int ticketSelect, int age, int orderCount,
				   int priceResult, int discountSelect, 
				   int *position, int(*orderList)[5])
{
	orderList[*position][0] = ticketSelect;
	orderList[*position][1] = age;
	orderList[*position][2] = orderCount;
	orderList[*position][3] = priceResult;
	orderList[*position][4] = discountSelect;
	(*position)++;
}
/************************************************************
	출력부
*************************************************************/
// 티켓 가격 출력
void pricePrint(int priceResult)
{
	printf("가격은 %d 원 입니다.\n", priceResult);
	printf("감사합니다.\n\n");
}
// 주문 내역 출력
void orderPrint(int totalPrice, int* position, int(*orderList)[5])
{
	printf("티켓 발권을 종료합니다. 감사합니다.\n");
	printf("\n");
	printf("==================== 에버랜드 ====================\n");

	for (int index = 0; index < *position; index++)
	{
		switch (orderList[index][0])
		{
		case 1:	// 주간권
			printf("주간권 ");
			break;
		case 2:	// 야간권
			printf("야간권 ");
			break;
		default:
			break;
		}

		if (calcAgeGroup(orderList[index][1]) == BABY)
		{
			printf("유아   ");
		}
		else if (calcAgeGroup(orderList[index][1]) == CHILD)
		{
			printf("어린이 ");
		}
		else if (calcAgeGroup(orderList[index][1]) == TEEN)
		{
			printf("청소년 ");
		}
		else if (calcAgeGroup(orderList[index][1]) == ADULT)
		{
			printf("어른   ");
		}
		else
		{
			printf("노인   ");
		}

		printf("X %3d ", orderList[index][2]);
		printf("%8d원	", orderList[index][3]);

		switch (orderList[index][4])
		{
		case 1:	// 없음
			printf("*우대적용 없음\n");
			break;
		case 2:	// 장애인
			printf("*장애인 우대적용\n");
			break;
		case 3:	// 국가유공자
			printf("*국가유공자 우대적용\n");
			break;
		case 4:	// 다자녀
			printf("*다자녀 우대적용\n");
			break;
		case 5:	// 임산부
			printf("*임산부 우대적용\n");
			break;
		default:
			break;
		}
	}
	printf("\n");
	printf("입장료 총액은 %d원 입니다.\n", totalPrice);
	printf("==================================================\n");
	printf("\n");
}
// 주문 내역 파일로 출력
void orderFilePrint(int totalPrice, int* position, int(*orderList)[5], int* filePosition)
{
	FILE *fp = fopen("report.csv", "a+");
	char temp = "";

	/* 오늘 날짜를 구하기 */
	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);

	for (int index = 0; index < *position; index++)
	{
		if (*filePosition == 0) // 첫줄일 경우 출력
		{
			if (fscanf(fp, "%c", &temp) == -1) //파일에 문자가 존재하지 않으면 출력
			{
				fprintf(fp, "날짜 ,권종 ,연령구분 ,수량 ,가격 ,우대사항\n");
			}
		}
		(*filePosition)++;
		fprintf(fp, "%d%02d%02d,",
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

		switch (orderList[index][0])
		{
		case 1:	// 주간권
			fprintf(fp, "주간권 ,");
			break;
		case 2:	// 야간권
			fprintf(fp, "야간권 ,");
			break;
		default:
			break;
		}

		if (calcAgeGroup(orderList[index][1]) == BABY)
		{
			fprintf(fp, "유아 ,");
		}
		else if (calcAgeGroup(orderList[index][1]) == CHILD)
		{
			fprintf(fp, "어린이 ,");
		}
		else if (calcAgeGroup(orderList[index][1]) == TEEN)
		{
			fprintf(fp, "청소년 ,");
		}
		else if (calcAgeGroup(orderList[index][1]) == ADULT)
		{
			fprintf(fp, "어른 ,");
		}
		else
		{
			fprintf(fp, "노인 ,");
		}

		fprintf(fp, "%d,", orderList[index][2]);
		fprintf(fp, "%d,", orderList[index][3]);

		switch (orderList[index][4])
		{
		case 1:	// 없음
			fprintf(fp, "없음\n");
			break;
		case 2:	// 장애인
			fprintf(fp, "장애인\n");
			break;
		case 3:	// 국가유공자
			fprintf(fp, "국가유공자\n");
			break;
		case 4:	// 다자녀
			fprintf(fp, "다자녀\n");
			break;
		case 5:	// 임산부
			fprintf(fp, "임산부\n");
			break;
		default:
			break;
		}
	}
	fclose(fp);
}
// 이어서 주문 or 주문내역 출력 후 종료
int orderContinue()
{
	int continueSelect = 0;

	printf("계속 발권 하시겠습니까?\n");
	printf("1. 티켓 발권\n");
	printf("2. 종료\n");
	while (true)
	{
		scanf("%d", &continueSelect);
		if (continueSelect == 1 || continueSelect == 2)
		{
			break;
		}
		else
		{
			errorMessagePrint();
		}
		getchar(); // 입력 버퍼를 비움
	}
	return continueSelect;
}
// 에러메세지 출력
void errorMessagePrint()
{
	printf("잘못 입력하셨습니다.\n");
}
