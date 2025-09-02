#include "../include/hw1.h"
#include <iostream>
#include <random>
#include <iomanip>
#include <stdexcept>

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

    Matrix multiply(const Matrix& matrix, double c) {
        if (matrix.empty())
            return Matrix{};
        
        auto n = matrix[0].size(), m = matrix.size();
        auto x = zeros(n, m);
        if (c!=0) {
            for (int i=0; i<n; ++i)
                for (int j=0; j<n; ++j)
                    x[i][j] = matrix[i][j] * c;            
        }

        return x;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
        if (matrix1.empty() && matrix2.empty())
            return Matrix{};
        if (matrix1.empty() || matrix2.empty())
            throw std::logic_error("one matrix is None!\n");
        auto n1 = matrix1[0].size(), m1 = matrix1.size();
        auto n2 = matrix2[0].size(), m2 = matrix2.size();
        if (m1!=n2)
            throw std::logic_error("wrong dimension!\n");

        auto n=n1, m=m2;
        auto matrix = zeros(n, m);

        for (int i=0; i<n; ++i)
            for (int j=0; j<m; ++j)
                for (int k=0; k<m1; ++k)
                    matrix[i][j] += matrix1[i][k]*matrix2[k][j];

        return matrix;
    }

    Matrix sum(const Matrix& matrix, double c) {
        if (matrix.empty())
            return Matrix{};
        
        auto n = matrix[0].size(), m = matrix.size();
        auto x = zeros(n, m);
        if (c==0)
            return matrix;
        
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j)
                x[i][j] = matrix[i][j] + c;

        return x;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
        if (matrix1.empty() && matrix2.empty())
            return Matrix{};
        if (matrix1.empty() || matrix2.empty())
            throw std::logic_error("at least one matrix is None!\n");
        
        auto n1 = matrix1[0].size(), m1 = matrix1.size();
        auto n2 = matrix2[0].size(), m2 = matrix2.size();
        if (m1!=n2)
            throw std::logic_error("wrong col or row for multiply!\n");

        auto n=n1, m=m2;
        auto matrix = zeros(n, m);

        for (int i=0; i<n; ++i)
            for (int j=0; j<m; ++j)
                for (int k=0; k<m1; ++k)
                    matrix[i][j] += matrix1[i][k]+matrix2[k][j];

        return matrix;
    }

    Matrix transpose(const Matrix& matrix) {
        auto n=matrix[0].size(), m=matrix.size();
        auto x = zeros(n,m);
        
        for (int i=0; i<n; ++i)
            for(int j=0; j<m; ++j)
                x[i][j] = matrix[j][i];

        return x;
    }
}
