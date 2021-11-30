#include "aco.h"
#include <bits/stdc++.h>
using namespace std;

inline
ACO::ACO(
    vector<vector<int>> distances,
    double tau,
    double Q,
    double alpha,
    double beta,
    double rho,
    int initial,
    int final
) : distances(distances),
taui(tau),
Q(Q),
alpha(alpha),
beta(beta),
rho(rho),
initial(initial),
final(final)
{
    srand((unsigned int)time(NULL));
    time(NULL);
    for (int i = 0; i < distances.size(); i++) {
        vector<double> a;
        for (int j = 0; j < distances[i].size(); j++)
            if (distances[i][j] != 0)
                a.push_back(tau);
            else
                a.push_back(0);
        pheromones.push_back(a);
    }
}

inline
int ACO::travel(int node, vector<bool>& visited, vector<int>& path) const {
    visited[node] = true;
    if (find(visited.begin(), visited.end(), false) == visited.end()) {
        path.push_back(initial); 
        path.push_back(node);
        return 1;
    }
    vector<bool> possibilities(distances.size(), true);
    int new_node;
    do {
        vector<double> probability;
        for (int i = 0; i < distances.size(); i++) {
            if (!visited[i] && distances[node][i] != 0 && possibilities[i])
                probability.push_back(pow((double)pheromones[node][i], alpha) * pow((1.0 / (double)distances[node][i]), beta));
            else
                probability.push_back(0);
        }
        double sum = 0;
        for (int i = 0; i < probability.size(); i++) {
            sum += probability[i];
            probability[i] = sum;
        }
        if (sum == 0) {
            visited[node] = false;
            return -1;
        }
        double r = sum * ((double)rand() / (double)RAND_MAX);
        for (int i = 0; i < probability.size(); i++) {
            if (probability[i] >= r) {
                new_node = i;
                break;
            }
        }
        possibilities[node] = false;
    } while (travel(new_node, visited, path) == -1);
    path.push_back(node);
    return 1;
}

inline
void ACO::update_pheromones(const vector<vector<int>> paths) {
    for (int i = 0; i < pheromones.size(); i++)
        for (int j = 0; j < pheromones[i].size(); j++)
            pheromones[i][j] = (1 - rho) * pheromones[i][j];
    for (int i = 0; i < paths.size(); i++) {
        double cost = 0;
        for (int j = 0; j < paths[i].size() - 1; j++)
            cost += distances[paths[i][j]][paths[i][j + 1]];
        cost = Q / cost;
        for (int j = 0; j < paths[i].size() - 1; j++) {
            pheromones[paths[i][j]][paths[i][j + 1]] += cost;
            pheromones[paths[i][j + 1]][paths[i][j]] += cost;
        }
    }
}

inline
vector<int> ACO::shortest_path(int n_ants, int n_iterations, bool print_path) {
    for (int n = 0; n < n_iterations; n++) {
        vector<vector<int>> paths;
        for (int m = 0; m < n_ants; m++) {
            vector<bool> visited(distances.size(), false);
            vector<int> path;
            travel(initial, visited, path);
            if (print_path) {
                cout << "Camino encontrado: ";
                for (int i = path.size() - 1; i >= 0; i--)
                    cout << path[i] << " ";
                cout << endl;
            }
            paths.push_back(path);
        }
        update_pheromones(paths);
    }
    return get_path();
}

inline
bool sortbyfirinv(const pair<int, double>& a, const pair<int, double>& b) {
    return (a.second > b.second);
}

inline
int ACO::travel_path(int node, std::vector<bool>& visited, std::vector<int>& path) const {
    visited[node] = true;
    if (find(visited.begin(), visited.end(), false) == visited.end()) {
        path.push_back(initial);
        path.push_back(node);
        return 1;
    }
    vector<pair<int, double>> probability;
    for (int i = 0; i < distances.size(); i++) {
        if (!visited[i] && distances[node][i] != 0)
            probability.push_back(make_pair(i, pow((double)pheromones[node][i], alpha) * pow((1.0 / (double)distances[node][i]), beta)));
        else
            probability.push_back(make_pair(i, 0));
    }
    sort(probability.begin(), probability.end(), sortbyfirinv);
    for (int i = 0; i < probability.size(); i++) {
        if (probability[i].second == 0) {
            visited[node] = false;
            return -1;
        }
        int res = travel_path(probability[i].first, visited, path);
        if (res == 1) break;
    }
    path.push_back(node);
    return 1;
}

inline
vector<int> ACO::get_path() const {
    vector<bool> visited(distances.size(), false);
    vector<int> path, r_path;
    travel_path(initial, visited, path);
    for (int i = path.size() - 1; i >= 0; i--)
        r_path.push_back(path[i]);
    return r_path;
}

inline
int ACO::get_path_cost() const {
    vector<int> path = get_path();
    int cost = 0;
    for (int i = 0; i < path.size() - 1; i++)
        cost += distances[path[i]][path[i + 1]];
    return cost;
}