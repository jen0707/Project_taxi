#include <cstdio>

float calculateCost1(float baseCost, float extraCostPerUnit, float distance) {

    if (distance <= 1.6) {
        return baseCost;
    }
    else {
        float extraDistance = distance - 1.6;
        return baseCost + extraCostPerUnit * (extraDistance / 0.131);
    }
}

float calculateCost2(float baseCost, float extraCostPerUnit, float distance) {

        if (distance <= 3) {
            return baseCost;
        }
        else {
            float extraDistance = distance - 3;
            return baseCost + extraCostPerUnit * (extraDistance / 0.151);
        }
}

float calculateCost3(float baseCost, float extraCostPerUnit, float distance) {
  
    return baseCost + extraCostPerUnit * (distance/ 0.0714);
       
}
float calculateCost4(float baseCost, float extraCostPerUnit, float distance) {

    if (distance <= 0.8) {
        return baseCost;
    }
    else {
        float extraDistance = distance - 0.8;
        return baseCost + extraCostPerUnit * (extraDistance / 0.123);
    }
}

float Cost(int grade, int status, float distance) {
    float taxi_cost = 0.0f;

    if (grade == 1) { // �����ý�
        if (status == 0) { // �ְ�
            taxi_cost = calculateCost1(4800.0f, 100.0f, distance);
        }
        else if (status == 1) { // �ɾ� 1����
            taxi_cost = calculateCost1(5800.0f, 120.0f, distance);
        }
        else { // �ɾ� 2����
            taxi_cost = calculateCost1(6700.0f, 140.0f, distance);
        }
    }
    if (grade == 2) { // �����¿� �� ����ý�
        if (status == 0) { // �ְ�
            taxi_cost = calculateCost2(7000.0f, 200.0f, distance);
        }
        else{ // �ɾ� 1,2����
            taxi_cost = calculateCost2(8400.0f, 240.0f, distance);
        }
     
    }
    if (grade == 3) { // ����ý�
        
            taxi_cost = calculateCost3(6000.0f, 100.0f, distance);
       
    }
    if (grade == 4) { // ���������ý�
        
            taxi_cost = calculateCost4(4000.0f, 100.0f, distance);
        
    }

    return taxi_cost;
}