#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

vector<int> readFile(string path){
    vector<int> result;
    ifstream file(path);

    string line;
    while(getline(file, line)){
        result.push_back(stoi(line));
    }

    return result;
}

void search(string path, vector<int> *result){
    for(const auto &entry : filesystem::directory_iterator(path)){
        string currentPath = entry.path();
        if(entry.is_directory()){
            search(currentPath, result);
        }else if(entry.is_regular_file()){
            vector<int> data = readFile(currentPath);
            result->insert(result->end(), data.begin(), data.end());
        }
    }
}

int main(){
    string path = "./data";
    vector<int> *data = new vector<int>;

    search(path, data);

    int result = 0;
    for (auto it = data->begin(); it != data->end(); it++) {
        result += *it;
    }

    cout << result << endl;

    return 0;
}