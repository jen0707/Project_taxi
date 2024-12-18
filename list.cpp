#include <stdio.h>
#include <string.h>

struct TaxiData {
    char start[50];       // 출발지
    char destination[50]; // 목적지
    double fare;          // 요금
};

// 데이터를 파일에 저장하는 함수
void saveData(const TaxiData* data) {
    FILE* file = NULL;
    if (fopen_s(&file, "taxi_data.txt", "w") == 0) { // fopen_s requires a pointer to FILE*
        fprintf(file, "%s\n%s\n%.2f\n", data->start, data->destination, data->fare);
        fclose(file);
        printf("데이터가 저장되었습니다.\n");
    }
    else {
        printf("파일을 열 수 없습니다!\n");
    }
}

// 파일에서 데이터를 읽는 함수
int loadData(TaxiData* data) {
    FILE* file = NULL;
    if (fopen_s(&file, "taxi_data.txt", "r") == 0) {
        if (fgets(data->start, sizeof(data->start), file) != NULL) {
            data->start[strcspn(data->start, "\n")] = '\0'; // 개행 문자 제거
        }

        if (fgets(data->destination, sizeof(data->destination), file) != NULL) {
            data->destination[strcspn(data->destination, "\n")] = '\0'; // 개행 문자 제거
        }

        if (fscanf_s(file, "%lf", &data->fare) == 1) {
            fclose(file);
            return 1; // 성공
        }
        fclose(file);
    }
    else {
        printf("파일을 열 수 없습니다!\n");
    }
    return 0; // 실패
}
