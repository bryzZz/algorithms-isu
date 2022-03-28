#include "math.h"

float distance(float x1, float y1, float x2, float y2){
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}