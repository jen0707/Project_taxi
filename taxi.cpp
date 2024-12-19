#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _countof(array) (sizeof(array) / sizeof(array[0]))

// 전역 변수
int grade, status;
float distance;
char departure[50], arrival[50];

// 데이터 저장 및 로드 기능을 위한 구조체 선언
struct TaxiData {
    char start[50];
    char destination[50];
    double fare;
};

// 외부 함수 선언
extern void saveData(const TaxiData* data);
extern int loadData(TaxiData* data);
extern float Cost(int grade, int status, float distance);
extern const char* getTimeZone(int* status);

// 택시 등급 선택 함수
void taxi_grade(void) {
    printf("택시 등급을 선택하시오(번호 입력)\n1. 중형택시\n2. 대형승용 및 모범택시\n3. 고급택시\n4. 대형승합택시\n");
    while (1) {
        scanf_s("%d", &grade);
        if (grade >= 1 && grade <= 4) {
            const char* grades[] = { "중형택시", "대형승용 및 모범택시", "고급택시", "대형승합택시" };
            printf("%s를 선택하셨습니다.\n", grades[grade - 1]);
            break;
        }
        else {
            printf("잘못된 입력입니다. 다시 입력해주세요.\n");
        }
    }
}

// 시간대 정보 확인 함수
int timeline() {
    int timeStatus;
    const char* timeZone = getTimeZone(&timeStatus);
    printf("현재 시간대는 '%s'입니다. (timeStatus: %d)\n", timeZone, timeStatus);
    return timeStatus;
}

// 출발지와 도착지 입력 함수
void place(void) {
    printf("출발지와 도착지를 입력하세요: ");
    while (1) {
        if (scanf_s("%49s %49s", departure, (unsigned)_countof(departure), arrival, (unsigned)_countof(arrival)) == 2) {
            printf("출발지: %s, 도착지: %s\n", departure, arrival);
            break;
        }
        else {
            printf("입력이 잘못되었습니다. 다시 시도하세요.\n");
            while (getchar() != '\n'); // 입력 버퍼 비우기
        }
    }
}

// 네이버지도 링크 생성 함수
void openDistanceURL(const char* start, const char* destination) {
    char url[300];
    snprintf(url, sizeof(url),
        "https://map.naver.com/p/directions/-/-/-/car?c=15.00,0,0,0,dh",
        start, destination);
    printf("브라우저를 열어 거리를 확인하세요: %s\n", url);
    char command[350];  // 충분히 큰 버퍼
    snprintf(command, sizeof(command), "start %s", url);  // 'start' 명령 사용
    system(command);  // system을 통해 브라우저 열기
}


// 택시 요금 계산 및 출력 함수
float cost() {
   
    float cost = Cost(grade, status, (float)distance);

    return cost;
}

int main() {
    TaxiData data;

    // 이전 데이터 불러올지 여부 확인
    int choice;
    printf("이전에 저장된 데이터를 불러오시겠습니까?\n1. 네\n2. 아니오\n");
    scanf_s("%d", &choice);

    if (choice == 1) {
        if (loadData(&data)) {
            printf("저장된 데이터를 불러왔습니다:\n");
            printf("출발지: %s, 도착지: %s, 요금: %.0f원\n", data.start, data.destination, data.fare);
        }
        else {
            printf("저장된 데이터가 없습니다. 새로운 데이터를 입력하세요.\n");
            taxi_grade();
            status = timeline();
            place();
            data.fare = cost();
        }
    }
    else if (choice == 2) {
        printf("새로운 데이터를 입력하세요.\n");
        taxi_grade();
        status = timeline();
        place();

        // 거리 확인 및 입력
        openDistanceURL(departure, arrival);
        printf("브라우저에서 확인한 거리를 km 단위로 입력하세요: ");
        scanf_s("%f", &distance);
        printf("출발지 '%s'와 도착지 '%s'의 거리는 %.2f km입니다.\n", departure, arrival, distance);

        //요금 계산
        data.fare = cost();
        float final_cost = Cost(grade, status, distance);
        printf("최종 요금은 %.0f원입니다.\n", final_cost);
    }
    else {
        printf("잘못된 입력입니다. 프로그램을 종료합니다.\n");
        while (getchar() != '\n'); // 입력 버퍼 비우기
        return 0;
    }
    
    // 데이터 저장
    strcpy_s(data.start, sizeof(data.start), departure);
    strcpy_s(data.destination, sizeof(data.destination), arrival);
    saveData(&data);

    return 0;
}
