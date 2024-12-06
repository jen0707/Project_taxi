#include <ctime>

const char* getTimeZone() {
    // C 스타일로 현재 시간을 가져옴
    time_t currentTime = time(nullptr); // 현재 시간 (time_t 타입)
    struct tm localTime;

    // time_t를 로컬 시간(struct tm)으로 변환
    localtime_s(&localTime, &currentTime);

    int hour = localTime.tm_hour; // 현재 시간 (0 ~ 23)

    // 시간대를 분류
    if ((hour >= 22 && hour < 23) || (hour >= 2 && hour < 4)) {
        return "심야 1구간";
    }
    else if (hour >= 23 || hour < 2) {
        return "심야 2구간";
    }
    else {
        return "주간";
    }
}