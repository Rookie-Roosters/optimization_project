#ifndef _READ_FILE_H_
#define _READ_FILE_H_
#include <vector>
#include <string>
using namespace std;

class ReadFile {
private:
    string filename;
    vector <vector <int>>euDist;
    void calculateDistances();

public:
    ReadFile(string file);
    int cities = 0;
    vector <vector <int>>matrix;
    void readData();
};

#endif