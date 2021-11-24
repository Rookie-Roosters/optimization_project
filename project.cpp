#include <vector>
#include <iostream>
#include "aco.h"
#include "read_file.h"
using namespace std;

vector<vector<int>> mat = {{0 ,5 ,3 ,0 ,0 ,6 ,0},
                           {5 ,0 ,6 ,0 ,0 ,0 ,5},
                           {3 ,6 ,0 ,0 ,6 ,3 ,3},
                           {0 ,0 ,0 ,0 ,5 ,0 ,4},
                           {0 ,0 ,6 ,5 ,0 ,5 ,0},
                           {6 ,0 ,3 ,0 ,5 ,0 ,0},
                           {0 ,5 ,3 ,4 ,0 ,0 ,0}};

int main() {
    ACO b(mat, 0.1, 1, 1, 1, 0.01, 0, 3, 4, 4);
    vector<int> path = b.shortest_path(true);
    cout << "Mejor camino: ";
    for(int i = 0; i < path.size(); i++)
        cout << path[i] << " ";
    cout << endl;
    return 0;
}