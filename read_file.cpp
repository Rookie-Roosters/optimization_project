#include "read_file.h"
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;

inline
ReadFile::ReadFile(string file) {
    filename = file;
}

inline
void ReadFile::createMatrix(){
    FILE* file;
    file = fopen(filename.c_str(), "r");
    if (file != NULL) {
        bool found = false;
        int lineCount = 0, limit = 0, numbCount=0;
        char line[256], * number;
        while (fgets(line, sizeof line, file) != NULL) { 
            if (!found) {
                if (strncmp(line, "DIMENSION:", strlen("DIMENSION:")) == 0) {
                    char* last = strrchr(line, ' ');
                    if (last != NULL) {
                        cities = atoi(last + 1);
                        matrix.resize(cities, vector<int>(cities));
                    }
                }
            }
            else if (found && (lineCount < cities)) {
                matrix[lineCount][numbCount] = atoi(line);
                matrix[numbCount][lineCount] = atoi(line);
                numbCount++;
                if (numbCount > limit) {
                    lineCount++;
                    limit++;
                    numbCount = 0;
                }
            }

            if (strcmp(line, "EDGE_WEIGHT_SECTION\n") == 0)
                found = true;
        }
        fclose(file);
    }
}