#include "../include/hw1.h"
#include <iostream>
#include <random>
#include <iomanip>

namespace algebra
{
    // Create martix
    Matrix create_matrix(size_t n, size_t m, double v) {
        if (n<=0 || m<=0)
            throw std::logic_error("invalid matrix\n");
        Matrix x;
        for (int i=0; i<n; ++i) {
            std::vector<double> vect(m, v);
            x.push_back(vect);
        }
        return x;
    }
    
    Matrix zeros(size_t n, size_t m) { return create_matrix(n, m, 0); }

    Matrix ones(size_t n, size_t m) { return create_matrix(n, m, 1); }

    Matrix random(size_t n, size_t m, double min, double max) {
        if (min > max)
            throw std::logic_error("min can't not greater than max!\n");

        auto x = create_matrix(n, m, min);
        if (min!=max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<double> dis(min, max);

            for (int i=0; i<n; ++i)
                for (int j=0; j<m; ++j)
                    x[i][j] = dis(gen);
        }

        return x;        
    }

    // Display matrix
    void show(const Matrix& matrix) {
        auto n = matrix[0].size();
        auto m = matrix.size();

        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++)
                std::cout << std::setw(5) << std::setprecision(3) << matrix[i][j];
            std::cout << std::endl;
        }
    }
}


