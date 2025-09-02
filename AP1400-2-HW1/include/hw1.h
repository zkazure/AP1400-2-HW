#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
using std::size_t;

namespace algebra
{
    using Matrix = std::vector<std::vector<double>>;
    
    Matrix zeros(size_t n, size_t m);
    Matrix ones(size_t n, size_t m);
    Matrix random(size_t n, size_t m, double min, double max);

    void show(const Matrix& matrix);

    // basic operations
    Matrix multiply(const Matrix& matrix, double c);
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);
    Matrix sum(const Matrix& matrix, double c);
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2);

    Matrix transpose(const Matrix& matrix);
    Matrix minor(const Matrix& matrix, size_t n, size_t m);
}

#endif //AP_HW1_H
