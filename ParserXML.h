#ifndef PARSERXML_H
#define PARSERXML_H

#include <QtXml>

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
#include "LightSource.h"
#include "Camera.h"
#include "RayTracer.h"

class ParserXML {

public:
    ParserXML();
    ParserXML(QString xmlFileName);
    ParserXML(const ParserXML& parserXML);
    virtual ~ParserXML();

    QDomElement colorToNode(const Color& color, QString nodeName);
    QDomElement materialToNode(const Material& material);
    QDomElement vector3ToNode(const Vector3& vector, QString nodeName);
    QDomElement doubleToNode(double d, QString nodeName);
    QDomElement qStringToNode(QString str, QString nodeName);

    QDomElement screensetupToNode(int width, int height, RayTracer::Resolution resolution);
    QDomElement sphereToNode(const Sphere& sphere, int id);
    QDomElement planeToNode(const Plane& plane, int id);
    QDomElement rectangleToNode(const Rectangle& rectangle, int id);
    QDomElement draughtboardToNode(const Draughtboard& draughtboard, int id);
    QDomElement cylindreToNode(const Cylindre& cylindre, int id);
    QDomElement surfaceToNode(const Surface& surface, int id);
    QDomElement quadricToNode(const Quadrics& quadric, int id);
    QDomElement implicitToNode(const ImplicitSurface& implicit, int id);
    QDomElement boxToNode(const Box& box, int id);
    QDomElement triangleToNode(const Triangle &triangle, int id);
    QDomElement torusToNode(const Torus &torus, int id);
    QDomElement diskToNode(const Disk &disk, int id);
    QDomElement lightToNode(const LightSource& light, int id);
    QDomElement cameraToNode(const Camera& camera);

    QDomElement getShape(int id) const;
    QDomElement getLight(int id) const;
    QDomDocument getDoc() const;

    void addScreensetup(int width, int height, RayTracer::Resolution resolution);
    void addSphere(const Sphere& sphere, int id = -1);
    void addPlane(const Plane& plane, int id = -1);
    void addRectangle(const Rectangle& rectangle, int id = -1);
    void addDraughtboard(const Draughtboard& draughtboard, int id = -1);
    void addCylindre(const Cylindre& cylindre, int id = -1);
    void addSurface(const Surface& surface, int id = -1);
    void addQuadric(const Quadrics& quadric, int id = -1);
    void addImplicit(const ImplicitSurface& implicit, int id = -1);
    void addBox(const Box& box, int id = -1);
    void addTriangle(const Triangle& triangle, int id = -1);
    void addTorus(const Torus& torus, int id = -1);
    void addDisk(const Disk& disk, int id = -1);
    void addLight(const LightSource& light, int id = -1);
    void addCamera(const Camera& camera);

    void replaceScreensetup(int width, int height, RayTracer::Resolution resolution);
    void replaceSphere(const Sphere& sphere, int id);
    void replacePlane(const Plane& plane, int id);
    void replaceRectangle(const Rectangle& rectangle, int id);
    void replaceDraughtboard(const Draughtboard& draughtboard, int id);
    void replaceCylindre(const Cylindre& cylindre, int id);
    void replaceSurface(const Surface& surface, int id);
    void replaceQuadric(const Quadrics& quadric, int id);
    void replaceImplicit(const ImplicitSurface& implicit, int id);
    void replaceBox(const Box& box, int id);
    void replaceTriangle(const Triangle& triangle, int id);
    void replaceTorus(const Torus& torus, int id);
    void replaceDisk(const Disk& disk, int id);
    void replaceLight(const LightSource& light, int id);
    void replaceCamera(const Camera& camera);

    void removeShape(int id);
    void removeLight(int id);

    Color createColor(const QDomElement& colorElem) const;
    Material createMaterial(const QDomElement& materialElem) const;
    Vector3 createVector3(const QDomElement& vector3Elem) const;
    double createDouble(const QDomElement& doubleElem) const;
    int createInt(const QDomElement& intElem) const;
    QString createQString(const QDomElement& qStringElem) const;
    RayTracer::Resolution createResolution(const QDomElement& resolutionElem) const;

    QVector<double> createScreenSetup() const;
    RayTracer::Resolution createScreenResolution() const;
    Shape* createShape(int id) const;
    LightSource* createLight(int id) const;
    Camera createCamera() const;

    int nbShapes() const;
    int nbLights() const;

    QString getShapeType(int idShape) const;

    void initShapesList();
    QStringList getShapesList() const;
    void initLightsList();
    QStringList getLightsList() const;
    void initCameraList();
    void updateCameraList(const Camera& camera);
    QStringList getCameraList() const;
    void initScreenList();
    void updateScreenList(int width, int height, RayTracer::Resolution resolution);
    QStringList getScreenList() const;

    ParserXML& operator=(const ParserXML& parser);

private:
    QString _xmlFileName;
    QDomDocument _doc;
    QStringList _shapesList;
    QStringList _lightsList;
    QStringList _cameraList;
    QStringList _screenList;
};

#endif // PARSERXML_H
