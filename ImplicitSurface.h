#ifndef IMPLICITSURFACES_H
#define IMPLICITSURFACES_H

#include <QString>
#include <vector>

#include "Shape.h"
#include "ParserExpr.h"
#include "Matrix.h"

typedef Matrix<double> doubleMat;

class ImplicitSurface : public Shape {

public:
    QString _equation;
    ParserExpr _parsedEq;
    doubleMat _deg4Mat, _deg3Mat, _deg2Mat, _deg1Mat,
              _deg4MatDerX, _deg3MatDerX, _deg2MatDerX, _deg1MatDerX,
              _deg4MatDerY, _deg3MatDerY, _deg2MatDerY, _deg1MatDerY,
              _deg4MatDerZ, _deg3MatDerZ, _deg2MatDerZ, _deg1MatDerZ;
    double _constant;

    ImplicitSurface(const Color& color, const Material& material, const QString& equation);
    ImplicitSurface(const ImplicitSurface& implcitSurface);
    virtual ~ImplicitSurface();

    QString getEquation() const { return _equation; }
    ParserExpr getParsedEq() const { return _parsedEq; }
    doubleMat getDeg4Mat() const { return _deg4Mat; }
    doubleMat getDeg3Mat() const { return _deg3Mat; }
    doubleMat getDeg2Mat() const { return _deg2Mat; }
    doubleMat getDeg1Mat() const { return _deg1Mat; }
    double getConstant() const { return _constant; }

    void initMatrixAdConstant();
    void initMatrixDerivated();

    doubleMat derivateX(const doubleMat& matrix) const;
    doubleMat derivateY(const doubleMat& matrix) const;
    doubleMat derivateZ(const doubleMat& matrix) const;
    double evaluate(const Vector3& ptIntersect, const doubleMat& matrix) const;

    virtual Vector3 normal(const Vector3& ptIntersect) const;
    virtual std::vector<double> ensIntersect(const Ray& rayon) const;
    virtual bool belongsTo(const Vector3& ptIntersect) const;

    virtual Shape* clone() const;
};

#endif // IMPLICITSURFACES_H
