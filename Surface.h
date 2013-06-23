#ifndef SURFACE_H
#define SURFACE_H

#include <itpp/itbase.h>
#include "Vector2.h"
#include "Polynome.h"
#include "Ray.h"
#include "Pencil.h"
#include "ParserExpr.h"
#include "Shape.h"
#include <vector>
#include <QStringList>

class Surface : public Shape {

public:
    std::vector<itpp::mat> _matrix;
    std::vector<Polynome> _polynome;
    QString _equation1, _equation2, _equation3, _equation4;

    Surface(const Color& color, const Material& material, std::vector<Polynome> polynome, std::vector<itpp::mat> matrix);
    Surface(const Color& color, const Material& material, const QStringList& fourParams);
    Surface(const Surface& surface);
    virtual ~Surface();

    virtual Vector3 normal(const Vector3& ptIntersect) const;
    virtual std::vector<double> ensIntersect(const Ray& rayon) const;
    virtual bool belongsTo(const Vector3 &ptIntersect) const;
    virtual Surface* clone() const;

public:
    void initPolynome(const ParserExpr& formatedExpr);
    void initMatrix();
    itpp::mat buildMat(int nu);

    Pencil getPencil(const Ray& ray) const;
    itpp::mat derive_table(double s, double t)const;
    Vector3 gradient(double s, double t)const;

};

#endif // SURFACE_H
