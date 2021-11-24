#include "read_file.h"
#include <string>
#include <cstring>
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

inline
void ReadFile::calculateDistances() {
    float distance = 0;
    for (int i = 0; i < cities; i++) {
        for (int j = 0; j < cities; j++) {
            float x = euDist[i][0] - euDist[j][0];
            float y = euDist[i][1] - euDist[j][1];
            matrix[i][j] = sqrt((x * x) + (y * y));
        }       
    }
}

inline
ReadFile::ReadFile(string file) {
    filename = file;
}

inline
void ReadFile::readData(){
    FILE* file;
    file = fopen(filename.c_str(), "r");
    if (file != NULL) {
        bool found = false, euclidean = false;
        int lineCount = 0, limit = 0, numbCount = 0;
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
                if (strcmp(line, "EDGE_WEIGHT_TYPE : EUC_2D\n") == 0) {
                    euclidean = true;
                    euDist.resize(cities, vector<int>(2));
                }

            }
            else if (found) {
                if (!euclidean && (lineCount < cities)) {
                    matrix[lineCount][numbCount] = atoi(line);
                    matrix[numbCount][lineCount] = atoi(line);
                    numbCount++;
                    if (numbCount > limit) {
                        lineCount++;
                        limit++;
                        numbCount = 0;
                    }
                }

                if (euclidean && (lineCount < cities)) {
                    number = strtok(line, " ");
                    number = strtok(NULL, " ");
                    while (number != NULL) {
                        euDist[lineCount][limit] = atoi(number);
                        number = strtok(NULL, " ");
                        limit++;
                        if (limit > 1)
                            limit = 0;
                    }
                    lineCount++;

                }
            }
                if ((strcmp(line, "EDGE_WEIGHT_SECTION\n") == 0) || (strcmp(line, "NODE_COORD_SECTION\n") == 0))
                    found = true;
        }
            if (euclidean) calculateDistances();
            fclose(file);
        }
}