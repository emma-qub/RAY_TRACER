#ifndef DRAUGHTBOARD_H_
#define DRAUGHTBOARD_H_

/**
 * \file Draughtboard.h
 * \brief Draughtboard creator
 * \author Quentin Grimaud, Michael Gygli, Valentin Michelet
 * \version 0.7
 * \date June 2011
 *
 * Program to create a draughtboard with two case colors, case size,
 * width and height parameterizable
 *
 */
#include <iostream>

#include "Color.h"
#include "Vector3.h"
#include "Rectangle.h"

/**
 * \class Draughtboard
 * \brief draughtboard creator class
 *
 * Create a draughtboard with two case colors, case size,
 * width and height parameterizable
 */
class Draughtboard: public Rectangle {
public:
    Color _colorD;      /*!< one case color, the other one is in the
                        rectangle constructor which this class inherits */
    double _caseSize;	/*!< the size edge of each case */

    /**
      * \brief Constructor
      *
      * Draughtboard class constructor
      *
      * \param color: the main color, from rectangle class
      * \param material: the material
      * \param colorD: the other case color
      * \param normAndPoint: the ray made with the middle of the draughtboard
      *        for origin, and the plane normal for direction
      * \param height: the height
      * \param width: the width
      * \param caseSize: the size of each case
      */
    Draughtboard(const Color &color, const Material &material,
                 const Color &colorD, const Ray &normAndPoint,
                 double height, double width, double caseSize);

    /**
      * \brief Destructor
      *
      * Draughtboard class destructor
      */
    virtual ~Draughtboard();

    /**
      * \brief get color
      *
      * Get the color of the draughtboard on the specified intersection point
      *
      * \param pt: the intersection point
      * \return the color of the draughtboard at the intersection pôint
      */
    virtual Color getColor(const Vector3 &pt);

    virtual Draughtboard* clone() const;

    friend std::ostream& operator<<(std::ostream& os,
                                    const Draughtboard& draughtboard);
};

#endif /* DRAUGHTBOARD_H_ */
