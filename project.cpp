#include <vector>
#include <iostream>
#include <string>
#include "aco.h"
#include "read_file.h"
using namespace std;

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

    ACO b(data.matrix, 0.1, 1, 2, 3, 0.1, 0, 0);
    b.shortest_path(100, 100, true);

    vector<int> path = b.get_path();
    cout << endl << "Mejor camino: ";
    for(int i = 0; i < path.size(); i++)
        cout << path[i] << " ";
    cout << endl;
    cout << "Costo del camino: " << b.get_path_cost() << endl;
    cout << endl << "Matriz de feromonas" << endl;
    vector<vector<double>> phe = b.get_pheromones();
    for(int i = 0; i < phe.size(); i++) {
        for(int j = 0; j < phe[i].size(); j++)
            cout << phe[i][j] << " ";
        cout << endl;
    }

    return 0;
}