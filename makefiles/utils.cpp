#include "utils.h"

float *read_argv(int argc, char *argv[]) {
    float *array = new float[argc - 1];
    for(int i = 1; i < argc; i++){
        array[i - 1] = atof(argv[i]);
    }
    return array;
}