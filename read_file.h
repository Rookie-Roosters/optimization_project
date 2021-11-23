#ifndef _READ_FILE_H_
#define _READ_FILE_H_
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <string>
using namespace std;

class ReadFile {
private:
    string filename;

public:
    ReadFile(string file);
    int cities = 0;
    vector <vector <int>>matrix;
    void createMatrix();
};

#endif