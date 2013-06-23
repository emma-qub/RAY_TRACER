#ifndef COLOR_H_
#define COLOR_H_

/**
 * \file Color.h
 * \brief Color creator
 * \author Quentin Grimaud, Michael Gygli, Valentin Michelet
 * \version 0.7
 * \date June 2011
 *
 * Program to generate and manipulate colors from red, green and blue values.
 *
 */
#include <iostream>
#include <string>

/**
 * \class Color
 * \brief color creator class
 *
 * Generate and manipulate colors from red, green and blue values.<br>
 * Caution: red, green and blue values are double between 0 and 1.
 */
class Color {
public:
    double _val[3]; /*!< array to stock red, green and blue values */

    /**
      * \brief Constructor
      *
      * Color class constructor from red, green and blue values
      *
      * \param r: red value
      * \param g: green value
      * \param b: blue value
      */
    Color(double r = 0.0, double g = 0.0, double b = 0.0);

    /**
      * \brief Constructor
      *
      * Color class constructor from another color
      *
      * \param color: the original color
      */
    Color(const Color& color);

    /**
      * \brief Destructor
      *
      * Color class destructor
      */
    virtual ~Color();

    /**
      * \bref operator []
      *
      * Get the color value at the specified index
      *
      * \param i: the specified index
      * \return a reference to the value at the specified index
      */
    double& operator[](unsigned i);

    /**
      * \bref operator []
      *
      * Get the color value at the specified index
      *
      * \param i: the specified index
      * \return the value at the specified index
      */
    double operator[](unsigned i) const;

    /**
      * \bref operator ==
      *
      * Compare to colors, that means compare red, green and blue values
      * from the specified colors
      *
      * \param color1: the first color
      * \param color2: the second color
      * \return true if the two colors specified are equal
      */
    friend bool operator==(const Color& color1, const Color& color2);

    /**
      * \bref operator !=
      *
      * Compare to colors, that means compare red, green and blue values
      * from the specified colors
      *
      * \param color1: the first color
      * \param color2: the second color
      * \return true if the two colors specified are unequal
      */
    friend bool operator!=(const Color& color1, const Color& color2);

    /**
      * \bref operator + (unary)
      *
      * Return a reference from the vector
      *
      * \return a reference from the vector
      */
    const Color& operator+() const;

    /**
      * \bref operator - (unary)
      *
      * Multiply every color by -1
      *
      * \param color1: the first color
      * \param color2: the second color
      * \return the vector but with the opposite coordinates
      */
    Color operator-() const;

    /**
      * \bref operator =
      *
      * Replace the color by the specified one and return a reference on this
      *
      * \param color: the color
      * \return a reference on the vector
      */
    Color& operator=(const Color& color);

    /**
      * \bref operator + (binary)
      *
      * Add the two specified colors
      *
      * \param color1: the first color
      * \param color2: the second color
      * \return the sum from the two specified colors
      */
    friend Color operator+(const Color& color1, const Color& color2);

    /**
      * \bref operator *
      *
      * Multiply the two specified colors
      *
      * \param color1: the first color
      * \param color2: the second color
      * \return the multiplication from the two specified colors
      */
    friend Color operator*(const Color& color1, const Color& color2);

    /**
      * \bref operator /
      *
      * Divide the two specified colors
      *
      * \param color1: the first color
      * \param color2: the second color
      * \return the division from the two specified colors
      */
    friend Color operator/(const Color& color1, const Color& color2);

    /**
      * \bref operator *
      *
      * Multiply the specified color by the specified constant
      *
      * \param k: the constant
      * \param color: the color
      * \return the multiplication from the specified colors
      *         and the specified constant
      */
    friend Color operator*(const double k, const Color& color);

    /**
      * \bref operator *
      *
      * Multiply the specified color by the specified constant
      *
      * \param color: the color
      * \param k: the constant
      * \return the multiplication from the specified colors
      *         and the specified constant
      */
    friend Color operator*(const Color& color, const double k);

    /**
      * \bref operator /
      *
      * Divide the specified color by the specified constant
      *
      * \param color: the color
      * \param k: the constant
      * \return the division from the specified colors
      *         and the specified constant
      */
    friend Color operator/(const Color& color, const double k);

    /**
      * \bref operator +=
      *
      * Add the specified color to the color and return a reference on it
      *
      * \param color: the color
      * \return a reference on the color after having added
      *         the specified color to it
      */
    Color& operator+=(const Color& color);

    /**
      * \bref operator *=
      *
      * Multiply the color by the specified color and return a reference on it
      *
      * \param color: the color
      * \return a reference on the color after having multiplyed
      *         by the specified color
      */
    Color& operator*=(const Color& color);

    /**
      * \bref operator /=
      *
      * Divide the color by the specified color and return a reference on it
      *
      * \param color: the color
      * \return a reference on the color after having divided
      *         by the specified color
      */
    Color& operator/=(const Color& color);

    /**
      * \bref operator *=
      *
      * Multiply the color by the specified constant
      * and return a reference on it
      *
      * \param k: the constant
      * \return a reference on the color after having multiplyed
      *         by the specified constant
      */
    Color& operator*=(const double k);

    /**
      * \bref operator /=
      *
      * Divide the color by the specified constant and return a reference on it
      *
      * \param k: the constant
      * \return a reference on the color after having divided
      *         by the specified constant
      */
    Color& operator/=(const double k);

    /**
      * \brief clamp
      *
      * Red, green and blue values must be double numbers between 0 and 1.<br />
      * This method sets to 1 each value if it is higher than 1
      * and to 0 if it is lower than 0.
      */
    void clamp();

    friend std::ostream& operator<<(std::ostream& os, const Color& color);

    //Improvement:
    //uint32_t getRGB () const;

};

#endif /* COLOR_H_ */
