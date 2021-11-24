#ifndef _ACO_H_
#define _ACO_H_
#include <vector>

class ACO {
private:
    std::vector<std::vector<int>> distances;
    std::vector<std::vector<double>> pheromones;
    double taui, Q, alpha, beta, rho;
    int initial, final, n_ants, n_iterations;

    int travel(int, std::vector<bool>&, std::vector<int>&) const;
    void update_pheromones(const std::vector<std::vector<int>>);
public:
    ACO(
        std::vector<std::vector<int>> distances,
        double tau,
        double Q,
        double alpha,
        double beta,
        double rho,
        int initial,
        int final,
        int n_ants,
        int n_iterations
    );
    std::vector<int> shortest_path(bool print_path = false);
};

#endif