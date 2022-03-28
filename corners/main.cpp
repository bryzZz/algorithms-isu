#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <cmath>

using namespace std;

int main(int argc, char *argv[]){
    srand(time(0));

    if(argc != 3){
        cout << "Bad arguments" << endl;
    }else {
        int n = atof(argv[1]);
        string outFileName = argv[2];
        outFileName = outFileName + ".txt";

        ofstream outFile(outFileName);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 3; j++){
                float angle = -M_PI + (((float)rand() / RAND_MAX) * (2 * M_PI));
                if(j == 2){
                    outFile << angle << "\n";
                }else {
                    outFile << angle << " ";
                }
            }
        }
        outFile.close();
    }

    return 0;
}