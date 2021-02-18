#include <fstream>
#include <iostream>

#include "matrix.hpp"

using namespace simple_matrix;

void print_help() {
    std::cerr << "Usage: ./ukol1 A.txt b.txt {gd|cg}\n"
              << "cg (conjugate gradient) or gd (gradient descent)";
}

void print_header(std::ostream& out, uint n) {
    out << "iter,residual";
    for (uint i = 0; i < n; ++i)
        out << ",x" << i;
    out << std::endl;
}

void print_result_row(std::ostream& out, uint iter, double residual, matrix solution) {
    out << iter << "," << residual;
    for (double el : solution) {
        out << "," << el;
    }
    out << std::endl;

    // print to std:out
    std::cout << "iter " << iter
              << "  residual " << residual << std::endl;
}

void gradient_descent(matrix A, matrix b) {
    std::cout << "== GRADIENT DESCENT ==" << std::endl;

    std::ofstream out("bin/solution_gradient_descent.csv");
    print_header(out, A.n());

    matrix x = matrix(A.n(), 1);  // unknown solution
    matrix r = b - A * x;         // residual
    double alpha;

    for (uint k = 0; r.norm() > 0.001; ++k) {
        print_result_row(out, k, r.norm(), x);

        alpha = (r.transpose() * r).scalar() /
                ((r.transpose() * A * r).scalar() + EPSILON);
        x += alpha * r;
        r -= alpha * A * r;
    }
    std::cout << "x =\n"
              << x.pretty() << std::endl;
}

void conjugate_gradient(matrix A, matrix b) {
    std::cout << "== CONJUGATE GRADIENT ==" << std::endl;

    std::ofstream out("bin/solution_conjugate_gradient.csv");
    print_header(out, A.n());

    matrix x = matrix(A.n(), 1);  // solution vector
    matrix r = b - A * x;         // current residual
    matrix s = r;                 // direction vector
    double alpha, beta;           // learning steps for x, r and s
    double temp;                  // current residual norm squared

    uint k = 0;
    print_result_row(out, k, r.norm(), x);
    for (k = 1; r.norm() > 0.001; ++k) {
        temp = (r.transpose() * r).scalar();
        alpha = temp / ((s.transpose() * A * s).scalar() + EPSILON);
        x += alpha * s;
        r -= alpha * A * s;
        print_result_row(out, k, r.norm(), x);
        beta = (r.transpose() * r).scalar() / (temp + EPSILON);
        s = r + beta * s;
    }
    std::cout << "x = \n"
              << x.pretty() << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 4) {
        print_help();
        return 1;
    }

    std::ifstream Afile(argv[1]), bfile(argv[2]);
    std::string method = argv[3];

    matrix A, b;
    Afile >> A;
    bfile >> b;

    std::cout << "A = \n"
              << A.pretty() << std::endl;
    std::cout << "b = \n"
              << b.pretty() << std::endl;

    if (method == "gd")
        gradient_descent(A, b);
    else if (method == "cg")
        conjugate_gradient(A, b);
    else {
        print_help();
        return 1;
    }

    return 0;
}
