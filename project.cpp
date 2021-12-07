#include <vector>
#include <iostream>
#include <string>
#include "aco.h"
#include "read_file.h"
using namespace std;

vector<vector<int>> mat;
ACO aco(mat,0,0,0,0,0,0);
bool set_parameters = false;
bool set_matrix = false;

int menu() {
    int op;
    cout << "1. Leer un archivo." << endl;
    cout << "2. Agregar parametros." << endl;
    cout << "3. Mandar hormigas." << endl;
    cout << "4. Imprimir camino mas corto." << endl;
    cout << "5. Imprimir matriz de feromonas." << endl;
    cout << "6. Imprimir costo del camino" << endl;
    cout << "7. Salir." << endl;
    do {
        do {
            fflush(stdin);
            cout << "Opcion [1-7]: ";
        } while(scanf("%d", &op) != 1);
    } while(op < 0 || op > 7);
    return op;
}

void read_file() {
    string filename;
    cout << "Introduce el nombre del archivo [fri26.tsp.txt, kroB100.tsp.txt]: ";
	cin >> filename;
    ReadFile data(filename);
    data.readData();
    mat = data.matrix;
    set_matrix = true;
    set_parameters = false;
}

void add_parameters() {
    if(set_matrix) {
        double tau, Q, alpha, beta, rho;
        int initial;
        do {
            fflush(stdin);
            cout << "Valor de tau inicial: ";
        } while(scanf("%lf", &tau) != 1);
        do {
            fflush(stdin);
            cout << "Valor de Q: ";
        } while(scanf("%lf", &Q) != 1);
        do {
            fflush(stdin);
            cout << "Valor de alpha: ";
        } while(scanf("%lf", &alpha) != 1);
        do {
            fflush(stdin);
            cout << "Valor de beta: ";
        } while(scanf("%lf", &beta) != 1);
        do {
            fflush(stdin);
            cout << "Valor de rho: ";
        } while(scanf("%lf", &rho) != 1);
        do {
            fflush(stdin);
            cout << "Nodo de inicio[0," << mat.size() - 1 << "]: ";
        } while(scanf("%d", &initial) != 1);
        aco = ACO(mat, tau, Q, alpha, beta, rho, initial);
        set_parameters = true;
    } else cout << "Debe primero leer una matriz" << endl;
}

void send_ants() {
    if(set_parameters) {
        int n_ants, n_iterations, print;
        do {
            fflush(stdin);
            cout << "Numero de hormigas: ";
        } while(scanf("%d", &n_ants) != 1);
        do {
            fflush(stdin);
            cout << "Numero de iteraciones: ";
        } while(scanf("%d", &n_iterations) != 1);
        do {
            do {
                fflush(stdin);
                cout << "Imprimir caminos encontrados [0,1]: ";
            } while(scanf("%d", &print) != 1);
        } while(print < 0 || print > 1);
        aco.shortest_path(n_ants, n_iterations, print);
    } else cout << "Debe primero agregar los parametros" << endl;
}

void print_path() {
    if(set_parameters) {
        vector<int> path = aco.get_path();
        cout << "Camino encontrado: ";
        for(int i = 0; i < path.size(); i++)
            cout << path[i] << " ";
        cout << endl;
    } else cout << "Debe primero agregar los parametros" << endl;
}

void print_pheromones() {
    if(set_parameters) {
        cout << endl << "Matriz de feromonas" << endl;
        vector<vector<double>> phe = aco.get_pheromones();
        for(int i = 0; i < phe.size(); i++) {
            for(int j = 0; j < phe[i].size(); j++)
                cout << phe[i][j] << " ";
            cout << endl;
        }
    } else cout << "Debe primero agregar los parametros" << endl;
}

void print_cost() {
    if(set_parameters) {
        cout << "Costo del camino: " << aco.get_path_cost() << endl;
    } cout << "Debe primero agregar los parametros" << endl;
}

int main() {
    int op;
    do {
        system("cls");
        op = menu();
        cout << endl;
        switch(op) {
            case 1: read_file(); break;
            case 2: add_parameters(); break;
            case 3: send_ants(); break;
            case 4: print_path(); break;
            case 5: print_pheromones(); break;
            case 6: print_cost(); break;
        }
        cout << endl;
        if(op != 7) system("pause");
    } while(op != 7);
    return 0;
}