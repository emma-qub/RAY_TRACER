#ifndef UPDATESHAPE_H
#define UPDATESHAPE_H

#include <QWidget>
#include <QApplication>
#include <QtGui>

#include "Shape.h"
#include "Sphere.h"
#include "Plane.h"
#include "Rectangle.h"
#include "Draughtboard.h"
#include "Cylindre.h"
#include "Surface.h"
#include "Quadrics.h"
#include "ImplicitSurface.h"
#include "Box.h"
#include "Triangle.h"
#include "Torus.h"
#include "Disk.h"

class UpdateShape : public QDialog {
    Q_OBJECT

public:
    UpdateShape(Shape* shape, QWidget* parent = 0);

    Material getMaterial() const;
    Color getColor() const;

protected:
    QVBoxLayout* _mainLayout;

    QLabel* _colorRender;
    QLineEdit* _materialKAEdit;
    QLineEdit* _materialKDEdit;
    QLineEdit* _materialKSEdit;
    QLineEdit* _materialNSEdit;
    QLineEdit* _materialKReflexEdit;

    QPushButton* _paletteButton;

    QLineEdit* _colorREdit;
    QLineEdit* _colorGEdit;
    QLineEdit* _colorBEdit;

    QPushButton* _updateButton;
    QPushButton* _cancelButton;

public slots:
    void browsePalette();
};



class UpdateSphere : public UpdateShape {
    Q_OBJECT

public:
    UpdateSphere(Sphere* sphere, QWidget* parent = 0);

    Vector3 getCenter() const;
    double getRadius() const;

protected:
    QLineEdit* _centerOnlyXEdit;
    QLineEdit* _centerOnlyYEdit;
    QLineEdit* _centerOnlyZEdit;
    QLineEdit* _radiusEdit;
};



class UpdatePlane : public UpdateShape {
    Q_OBJECT

public:
    UpdatePlane(Plane* plane, QWidget* parent = 0);

    Ray getNormAndPoint() const;

protected:
    QLineEdit* _centerXEdit;
    QLineEdit* _centerYEdit;
    QLineEdit* _centerZEdit;
    QLineEdit* _normalXEdit;
    QLineEdit* _normalYEdit;
    QLineEdit* _normalZEdit;
};



class UpdateRectangle : public UpdatePlane {
    Q_OBJECT

public:
    UpdateRectangle(Rectangle* rectangle, QWidget* parent = 0);

    double getWidth() const;
    double getHeight() const;

protected:
    QLineEdit* _heightEdit;
    QLineEdit* _widthEdit;
};



class UpdateDraughtboard : public UpdateRectangle {
    Q_OBJECT

public:
    UpdateDraughtboard(Draughtboard* draughtboard, QWidget* parent = 0);

    Color getColorD() const;
    double getCaseSize() const;

protected:
    QLabel* _colorDRender;

    QPushButton* _paletteDButton;

    QLineEdit* _colorDREdit;
    QLineEdit* _colorDGEdit;
    QLineEdit* _colorDBEdit;

    QLineEdit* _caseSize;

public slots:
    void browseDPalette();
};



class UpdateCylindre : public UpdateShape {
    Q_OBJECT

public:
    UpdateCylindre(Cylindre* cylindre, QWidget* parent = 0);

    Vector3 getbottomCenter() const;
    double getLength() const;
    double getRadius() const;

protected:
    QLineEdit* _bottomCenterXEdit;
    QLineEdit* _bottomCenterYEdit;
    QLineEdit* _bottomCenterZEdit;
    QLineEdit* _lengthEdit;
    QLineEdit* _radiusEdit;
};



class UpdateSurface : public UpdateShape {
    Q_OBJECT

public:
    UpdateSurface(Surface* surface, QWidget* parent = 0);

    QStringList getEquations() const;

protected:
    QLineEdit* _equation1Edit;
    QLineEdit* _equation2Edit;
    QLineEdit* _equation3Edit;
    QLineEdit* _equation4Edit;
};



class UpdateQuadric : public UpdateShape {
    Q_OBJECT

public:
    UpdateQuadric(Quadrics* quadric, QWidget* parent = 0);

    double getA() const { return _aEdit->text().toDouble(); }
    double getB() const { return _bEdit->text().toDouble(); }
    double getC() const { return _cEdit->text().toDouble(); }
    double getD() const { return _dEdit->text().toDouble(); }
    double getE() const { return _eEdit->text().toDouble(); }
    double getF() const { return _fEdit->text().toDouble(); }
    double getG() const { return _gEdit->text().toDouble(); }
    double getH() const { return _hEdit->text().toDouble(); }
    double getI() const { return _iEdit->text().toDouble(); }
    double getJ() const { return _jEdit->text().toDouble(); }

protected:
    QLineEdit* _aEdit;
    QLineEdit* _bEdit;
    QLineEdit* _cEdit;
    QLineEdit* _dEdit;
    QLineEdit* _eEdit;
    QLineEdit* _fEdit;
    QLineEdit* _gEdit;
    QLineEdit* _hEdit;
    QLineEdit* _iEdit;
    QLineEdit* _jEdit;
};



class UpdateImplicit : public UpdateShape {
    Q_OBJECT

public:
    UpdateImplicit(ImplicitSurface* implicit, QWidget* parent = 0);

    QString getEquation() const;

protected:
    QLineEdit* _equationEdit;
};



class UpdateBox : public UpdateShape {
    Q_OBJECT

public:
    UpdateBox(Box* box, QWidget* parent = 0);

    Vector3 getBLFC() const;
    Vector3 getTRBC() const;

protected:
    QLineEdit* _x1Edit;
    QLineEdit* _y1Edit;
    QLineEdit* _z1Edit;
    QLineEdit* _x2Edit;
    QLineEdit* _y2Edit;
    QLineEdit* _z2Edit;
};



class UpdateTriangle : public UpdateShape {
    Q_OBJECT

public:
    UpdateTriangle(Triangle* triangle, QWidget* parent = 0);

    Vector3 getPoint1() const;
    Vector3 getPoint2() const;
    Vector3 getPoint3() const;

protected:
    QLineEdit* _x1Edit;
    QLineEdit* _y1Edit;
    QLineEdit* _z1Edit;
    QLineEdit* _x2Edit;
    QLineEdit* _y2Edit;
    QLineEdit* _z2Edit;
    QLineEdit* _x3Edit;
    QLineEdit* _y3Edit;
    QLineEdit* _z3Edit;
};



class UpdateTorus : public UpdateShape {
    Q_OBJECT

public:
    UpdateTorus(Torus* torus, QWidget* parent = 0);

    double getRingRadius() const;
    double getCrossRadius() const;

protected:
    QLineEdit* _ringRadiusEdit;
    QLineEdit* _crossRadiusEdit;
};



class UpdateDisk : public UpdatePlane {
    Q_OBJECT

public:
    UpdateDisk(Disk* disk, QWidget* parent = 0);

    double getRadius() const;

protected:
    QLineEdit* _radiusEdit;
};

#endif // UPDATESHAPE_H
