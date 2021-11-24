#include <vector>
#include <iostream>
#include <string>
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
    string filename;
	cout << "Introduce el nombre del archivo: (ejemplo, fri26.tsp.txt kroB100.tsp.txt) ";
	cin >> filename;
	ReadFile data(filename);
	data.readData();
	//accesar a la matriz con data.matrix
	for (int i = 0; i < data.cities; i++) {
		for (int j = 0; j < data.cities; j++)
			cout << data.matrix[i][j] << " ";
		cout << endl;
	}

    ACO b(mat, 0.1, 1, 1, 1, 0.01, 0, 3, 4, 4);
    vector<int> path = b.shortest_path(true);
    cout << "Mejor camino: ";
    for(int i = 0; i < path.size(); i++)
        cout << path[i] << " ";
    cout << endl;
    return 0;
}