#ifndef MATRIX_H
#define MATRIX_H

#include "MVector.h"

template<class T>
class Matrix;

template<class T>
bool operator==(const Matrix<T>& matrix1, const Matrix<T>& matrix2);

template<class T>
bool operator!=(const Matrix<T>& matrix1, const Matrix<T>& matrix2);

template<class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);

template<class T>
class Matrix {
public:

    std::vector<MVector<T> > _components;

    class BadDimensions {
    private:
        std::string _message;
    public:
        BadDimensions(std::string message = "") {
            _message = message;
        }

        const virtual char *what() const throw () {
            return _message.c_str();
        }
    };

    class OutOfBounds {
    private:
        std::string _message;
    public:
        OutOfBounds(std::string message = "") {
            _message = message;
        }

        const virtual char *what() const throw () {
            return _message.c_str();
        }
    };

    class NotInversible {
    private:
        std::string _message;
    public:
        NotInversible(std::string message = "") {
            _message = message;
        }

        const virtual char *what() const throw () {
            return _message.c_str();
        }
    };

    Matrix(unsigned line, unsigned column, bool random = false, T value = 0.0);
    Matrix(unsigned size = 0);
    Matrix(const Matrix& matrix);
    Matrix(const MVector<T>& mVector);

    void setElementK(unsigned line, unsigned column, T value);
    void insertBack(const MVector<T>& mVector);
    Matrix transpose() const;

    MVector<T> getLine(unsigned line) const;
    MVector<T> getColumn(unsigned column) const;
    unsigned nbLines() const;
    unsigned nbColumns() const;

    /*
    void swapLine(unsigned line1, unsigned line2);
    void setLine(unsigned line, const MVector& newLine);
    */
    MVector<T>& operator[](unsigned index);
    MVector<T> operator[](unsigned index) const;
    T& operator()(unsigned line, unsigned column);
    T operator()(unsigned line, unsigned column) const;
    /*
    friend Matrix operator+(const Matrix& matrix1, const Matrix& matrix2);
    Matrix operator-() const;
    friend Matrix operator-(const Matrix& matrix1, const Matrix& matrix2);
    friend Matrix operator*(const Matrix& matrix1, const Matrix& matrix2);
    friend Matrix operator*(double scalar, const Matrix& matrix);
    friend Matrix pow(const Matrix& matrix, int n);

    unsigned getGreaterPivot(unsigned line, unsigned column) const;
    Matrix gaussJordan() const;

    operator MVector() const;

    Matrix& operator+=(const Matrix& matrix);
    Matrix& operator-=(const Matrix& matrix);

    Matrix& operator=(const Matrix& matrix);
    */
};

#include "Matrix.cpp"

#endif
