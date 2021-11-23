#include "read_file.h"
#include "read_file.cpp"
#include <iostream>
#include <string>
using namespace std;

int main() {
	string filename;
	cout << "Introduce el nombre del archivo: (ejemplo, fri26.tsp.txt) ";
	cin >> filename;
	ReadFile data(filename);
	data.createMatrix();
	//accesar a la matriz con data.matrix
	for (int i = 0; i < data.cities; i++) {
		for (int j = 0; j < data.cities; j++)
			cout << data.matrix[i][j] << " ";
		cout << endl;
	}
    return 0;
}