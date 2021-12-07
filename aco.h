#ifndef _ACO_H_
#define _ACO_H_
#include <bits/stdc++.h>

class ACO {
private:
    std::vector<std::vector<int>> distances;
    std::vector<std::vector<double>> pheromones;
    double taui, Q, alpha, beta, rho;
    int initial, final;

    int travel(int, std::vector<bool>&, std::vector<int>&) const;
    int travel_path(int, std::vector<bool>&, std::vector<int>&) const;
    void update_pheromones(const std::vector<std::vector<int>>);
public:
    ACO(
        std::vector<std::vector<int>> distances,
        double tau,
        double Q,
        double alpha,
        double beta,
        double rho,
        int initial
    );
    std::vector<int> shortest_path(int n_ants, int n_iterations, bool print_paths = false);
    std::vector<std::vector<double>> get_pheromones() const { return pheromones; }
    std::vector<int> get_path() const;
    int get_path_cost() const;
};

#endif