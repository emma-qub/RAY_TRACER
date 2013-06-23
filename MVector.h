#ifndef MVECTOR_H
#define MVECTOR_H

#include <iostream>
#include <vector>

template<class T>
class MVector;

template<class T>
bool operator==(const MVector<T>& mVector1, const MVector<T>& mVector2);

template<class T>
bool operator!=(const MVector<T>& mVector1, const MVector<T>& mVector2);

template<class T>
std::ostream& operator<<(std::ostream& os, const MVector<T>& mvector);

template<class T>
class MVector {
public:

    std::vector<T> _coords;


    class BadDimensions {
    private:
        std::string _message;
    public:
        BadDimensions(std::string message = "") {
            _message = message;
        }

        const virtual char *what() const throw ()
        {
            return _message.c_str();
        }

    };
    class OutOfBounds
    {
    private:
        std::string _message;
    public:
        OutOfBounds(std::string message = "")
        {
            _message = message;
        }

        const virtual char *what() const throw ()
        {
            return _message.c_str();
        }

    };

    MVector(unsigned int size = 0, T valeur = 0);
    MVector(const MVector & mvector);

    unsigned getSize() const;
    void insertBack(T value);
    void setAt(unsigned index, T value);

    /*
    double dotProduct() const;
    double norm() const;
    */
    T& operator[](unsigned);
    T operator[](unsigned) const;

    /*
    friend MVector operator+(const MVector& mVector1, const MVector& mVector2);
    friend MVector operator-(const MVector& mVector1, const MVector& mVector2);
    MVector operator-() const;
    friend T operator*(const MVector& mVector1, const MVector& mVector2);
    friend MVector operator*(T scalar, const MVector& mVector);

    MVector& operator+=(const MVector& mVector);
    MVector& operator-=(const MVector& mVector);
    MVector& operator*=(T scalar);
    */

    MVector& operator=(const MVector& mVector);
};

#include "MVector.cpp"

#endif
