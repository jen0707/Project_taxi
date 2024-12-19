#include <ctime>

const char* getTimeZone(int* status) {
    // 현재 시간을 가져옴
    time_t currentTime = time(nullptr);
    struct tm localTime;

    // 현재 시간을 로컬 시간으로 변환
    localtime_s(&localTime, &currentTime);

    int hour = localTime.tm_hour; // 현재 시간 (0 ~ 23)

    // 시간대를 분류
    if ((hour >= 22 && hour < 23) || (hour >= 2 && hour < 4)) {
        if (status) *status = 0; // 상태를 포인터로 반환
        return "심야 1구간";
    }
    else if (hour >= 23 || hour < 2) {
        if (status) *status = 1; // 상태를 포인터로 반환
        return "심야 2구간";
    }
    else {
        if (status) *status = 0; // 상태를 포인터로 반환
        return "주간";
    }
}
