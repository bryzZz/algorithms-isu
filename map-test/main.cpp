#include <iostream>
#include <map>
#include <cmath>
#include <chrono>

using namespace std;

int main(){
    map<int, int> test;
    int s;

    for(int i = 0; i < 8; i++){
        s = pow(10, i);
        test.clear();

        auto begin = std::chrono::steady_clock::now();

        for(int j = 0; j < s; j++){
            test[j] = j;
        }

        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        cout << s << " " << sizeof(map<int, int>) + (sizeof(int) * 2) * test.size() << " " << elapsed_ms.count() << " ";
    }

    cout << endl;

    return 0;
}