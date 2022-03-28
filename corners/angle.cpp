#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector<string> split(string str, string delimiter){
    vector<string> words{};

    size_t pos = 0;
    while ((pos = str.find(delimiter)) != string::npos) {
        words.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }

    if(str.length() > 0){
        words.push_back(str);
    }

    return words;
}

int main(){
    string line;
    ifstream myfile("out.txt");
    if (myfile.is_open()){
        while (getline(myfile, line)){
            vector<string> splitted = split(line, " ");
            vector<float> coords;

            for (int i = 0; i < splitted.size(); i++) {
                coords.push_back(stof(splitted[i]));
            }

            float angle = 2 * sin(coords[0]) * sin(coords[1]) + cos(coords[2]);
            cout << angle << " ";
        }
        cout << endl;

        myfile.close();
    }

    return 0;
}