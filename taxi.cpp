#include <stdio.h>
#include <string.h>

#define _countof(array) (sizeof(array) / sizeof(array[0]))

// 전역 변수
int grade, status, distance;
char departure[50], arrival[50];

// 데이터 저장 및 로드 기능을 위한 구조체 선언
struct TaxiData {
    char start[50];
    char destination[50];
    double fare;
};

extern void saveData(const TaxiData* data);
extern int loadData(TaxiData* data);

// 택시 등급 선택
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

// 시간대 정보 불러오기 (외부 함수)
extern const char* getTimeZone(int* status);

int timeline() {
    int timeStatus;
    const char* timeZone = getTimeZone(&timeStatus);
    printf("현재 시간대는 '%s'입니다. (timeStatus: %d)\n", timeZone, timeStatus);
    return timeStatus;
}

// 출발지와 도착지 입력
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

// 요금 계산 함수 (외부 함수)
extern float Cost(int grade, int status, float distance);

int cost() {
    float cost = Cost(grade, status, distance);
    printf("최종 요금은 %.0f원입니다.\n", cost);
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
        data.fare = cost();
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
