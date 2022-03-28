#include <iostream>
#include "math.h"
#include "utils.h"

int main(int argc, char *argv[]){
    if(argc != 5){
        std::cout << "Bad arguments" << std::endl;
    }else {
        float *coords = read_argv(argc, argv);
        std::cout << distance(coords[0], coords[1], coords[2], coords[3]) << std::endl;
    }
}