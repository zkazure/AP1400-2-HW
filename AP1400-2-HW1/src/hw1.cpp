#include "hw1.h"
#include <iostream>
#include <random>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

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
        
        auto n = matrix.size(), m = matrix[0].size();
        auto x = zeros(n, m);
        if (c!=0) {
            for (int i=0; i<n; ++i)
                for (int j=0; j<m; ++j)
                    x[i][j] = matrix[i][j] * c;            
        }

        return x;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
        if (matrix1.empty() && matrix2.empty())
            return Matrix{};
        if (matrix1.empty() || matrix2.empty())
            throw std::logic_error("one matrix is None!\n");
        auto n1 = matrix1.size(), m1 = matrix1[0].size();
        auto n2 = matrix2.size(), m2 = matrix2[0].size();
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
        
        auto n = matrix.size(), m = matrix[0].size();
        auto x = zeros(n, m);
        if (c==0)
            return matrix;
        
        for (int i=0; i<n; ++i)
            for (int j=0; j<m; ++j)
                x[i][j] = matrix[i][j] + c;

        return x;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
        if (matrix1.empty() && matrix2.empty())
            return Matrix{};
        if (matrix1.empty() || matrix2.empty())
            throw std::logic_error("at least one matrix is None!\n");
        
        auto n1 = matrix1.size(), m1 = matrix1[0].size();
        auto n2 = matrix2.size(), m2 = matrix2[0].size();
        if (matrix1.size()!=matrix2.size() || matrix1[0].size()!=matrix2[0].size())
            throw std::logic_error("wrong col or row for multiply!\n");

        auto n=matrix1.size(), m=matrix1[0].size();
        auto matrix = zeros(n, m);

        for (int i=0; i<n; ++i)
            for (int j=0; j<m; ++j)
                    matrix[i][j] += matrix1[i][j]+matrix2[i][j];

        return matrix;
    }

    Matrix transpose(const Matrix& matrix) {
        auto n=matrix.size(), m=matrix[0].size();
        auto x = zeros(n,m);
        
        for (int i=0; i<n; ++i)
            for(int j=0; j<m; ++j)
                x[i][j] = matrix[j][i];

        return x;
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m) {
        if (n<0 || m<0 || matrix.empty() || n>=matrix.size() || m>=matrix[0].size())
            throw std::logic_error("nxm out of bound!\n");

        Matrix x;
        for (int i=0; i<n-1; ++i) {
            for (int j=0; j<m-1; ++j)
                x[i].push_back(matrix[i][j]);
            for (int j=n; j<matrix.size(); ++j)
                x[i].push_back(matrix[i][j]);
        }
        for (int i=n; i<matrix[0].size(); ++i) {
            for (int j=0; j<m-1; ++j)
                x[i].push_back(matrix[i][j]);
            for (int j=n; j<matrix.size(); ++j)
                x[i].push_back(matrix[i][j]);
        }

        return x;
    }

    double determinant(const Matrix& matrix) {
        if (matrix.empty())
            throw std::logic_error("None matrix\n");
        auto n=matrix.size(), m=matrix[0].size();
        if (n!=m)
            throw std::logic_error("det for only square matrix!\n");
        double det = 0;

        if (n==1)
            det = matrix[0][0];
        else if (n==2)
            det = matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
        else {
            for (int i=0; i<m; ++i) {
                det += pow(-1, i) * matrix[0][i] * determinant(minor(matrix, 1, i+1));
            }            
        }
        
        return det;
    }

    Matrix inverse(const Matrix& matrix) {
        if (determinant(matrix)==0)
            throw std::logic_error("No inverse!\n");
        auto n=matrix.size();

        Matrix x = zeros(n, n);
        const double det_a = determinant(matrix);
        for (int i=0; i<n; ++i) {
            for (int j=0; j<n; ++j) {
                x[i][j] = determinant(minor(matrix, i+1, i+1)) / det_a;
            }
        }

        return x;
    }

    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
        if (matrix1.empty() && matrix2.empty())
            throw std::logic_error("both matrix is empty!\n");
        if (matrix1.empty())
            return matrix2;
        if (matrix2.empty())
            return matrix1;

        auto n1=matrix1.size(), m1=matrix1[0].size();
        auto n2=matrix2.size(), m2=matrix2[0].size();
        Matrix x;
        if (axis) {
            if (n1 != n2)
                throw std::logic_error("no same rows!\n");

            for (int i=0; i<n1+n2; ++i) {
                x.push_back(matrix1[i]);
                for (int j=0; j<m2; ++j)
                    x[i].push_back(matrix2[i][j]);
            }
            
        } else {
            if (m1 != m2)
                throw std::logic_error("no same columns!\n");

            for (int i=0; i<n1; ++i) 
                x.push_back(matrix1[i]);
            for (int i=0; i<n2; ++i)
                x.push_back(matrix2[i]);
        }

        return x;
    }

    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
        Matrix x = matrix;
        swap(x[r1-1], x[r2-1]);
        return x;
    }

    Matrix ero_multiply(const Matrix& matrix, size_t r, double c) {
        Matrix x = matrix;
        for (int i=0; i<x.size(); ++i)
            x[r-1][i] *= c;

        return x;
    }

    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
        Matrix x = matrix;
        for (int i=0; i<x.size(); ++i)
            x[r2-1][i] += x[r1-1][i] * c;

        return x;
    }

    Matrix upper_triangular(const Matrix& matrix) {
        if (matrix.empty())
            return Matrix{};
        if (matrix.size()==1)
            return matrix;
        
        Matrix x = matrix;
        auto n=x.size(), m=x[0].size();
        
        for (int i=0; i<std::min(n, m); ++i) {
            if (x[i][i] == 0) {
                int j = i+1;
                for (; j<n; ++j) {
                    if (x[j][i] != 0)
                        x = ero_swap(x, i+1, j+1);
                }
                for (; j<n; ++j) {
                    x = ero_sum(x, i+1, - x[j][i]/x[i][i], j+1);
                }
            }
        }

        return x;
    }
}
