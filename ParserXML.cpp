#include "ParserXML.h"

#include <iostream>
#include <QLabel>

using namespace std;

/****************
 * Constructors *
 ****************/
ParserXML::ParserXML() :
    _xmlFileName(),
    _shapesList() {
    _doc = QDomDocument("RayTracerML");

    QDomElement root = _doc.createElement("scene");
    _doc.appendChild(root);

    QDomElement shapes = _doc.createElement("shapes");
    root.appendChild(shapes);

    QDomElement lights = _doc.createElement("lights");
    root.appendChild(lights);
}

ParserXML::ParserXML(QString xmlFileName) :
    _xmlFileName(xmlFileName) {
    _doc = QDomDocument("RayTracerML");

    QFile XMLDoc(_xmlFileName);
    if(!XMLDoc.open(QIODevice::ReadOnly)) {
        cerr << "Cannot open XML file in main()" << endl;
        return;
    }

    if(!_doc.setContent(&XMLDoc)) {
        XMLDoc.close();
        cerr << "Cannot set content of dom in main()" << endl;
        return;
    }

    XMLDoc.close();

    initShapesList();
    initLightsList();
    initCameraList();
    initScreenList();

}

ParserXML::ParserXML(const ParserXML& parserXML) {
    _xmlFileName = parserXML._xmlFileName;
    _doc = parserXML._doc;
    _shapesList = parserXML._shapesList;
    _lightsList = parserXML._lightsList;
    _cameraList = parserXML._cameraList;
    _screenList = parserXML._screenList;
}

/***************
 * Destructors *
 ***************/
ParserXML::~ParserXML() {
}

/***********
 * Methods *
 ***********/

/********************************
 * Transform objects into nodes *
 ********************************/
QDomElement ParserXML::colorToNode(const Color &color, QString nodeName) {
    QDomElement colorElem = _doc.createElement(nodeName);
    colorElem.setAttribute("r", color[0]);
    colorElem.setAttribute("g", color[1]);
    colorElem.setAttribute("b", color[2]);

    return colorElem;
}

QDomElement ParserXML::materialToNode(const Material &material) {
    QDomElement materialElem = _doc.createElement("material");
    materialElem.setAttribute("kreflex", material.k_reflex);
    materialElem.setAttribute("ns", material.n_s);
    materialElem.setAttribute("ka", material.k_a);
    materialElem.setAttribute("ks", material.k_s);
    materialElem.setAttribute("kd", material.k_d);

    return materialElem;
}

QDomElement ParserXML::vector3ToNode(const Vector3& vector, QString nodeName) {
    QDomElement vectorElem = _doc.createElement(nodeName);
    vectorElem.setAttribute("x", vector[0]);
    vectorElem.setAttribute("y", vector[1]);
    vectorElem.setAttribute("z", vector[2]);

    return vectorElem;
}

QDomElement ParserXML::doubleToNode(double d, QString nodeName) {
    QDomElement dElem = _doc.createElement(nodeName);
    dElem.setAttribute("value", d);

    return dElem;
}

QDomElement ParserXML::qStringToNode(QString str, QString nodeName) {
    QDomElement dElem = _doc.createElement(nodeName);
    dElem.setAttribute("value", str);

    return dElem;
}

QDomElement ParserXML::screensetupToNode(int width, int height, RayTracer::Resolution resolution) {
    QDomElement screenSetupElem = _doc.createElement("screensetup");

    QDomElement widthElem = _doc.createElement("width");
    widthElem.setAttribute("value", width);
    screenSetupElem.appendChild(widthElem);

    QDomElement heightElem = _doc.createElement("height");
    heightElem.setAttribute("value", height);
    screenSetupElem.appendChild(heightElem);

    QDomElement overSamplingElem = _doc.createElement("oversampling");
    overSamplingElem.setAttribute("value", resolution);
    screenSetupElem.appendChild(overSamplingElem);

    return screenSetupElem;
}

QDomElement ParserXML::sphereToNode(const Sphere& sphere, int id) {
    QDomElement shape = _doc.createElement("shape");
    shape.setAttribute("id", id);
    shape.setAttribute("type", "sphere");

    shape.appendChild(colorToNode(sphere._color, "color"));
    shape.appendChild(materialToNode(sphere._material));
    shape.appendChild(vector3ToNode(sphere._center, "center"));
    shape.appendChild(doubleToNode(sphere._radius, "radius"));

    return shape;
}

QDomElement ParserXML::planeToNode(const Plane& plane, int id) {
    QDomElement shape = _doc.createElement("shape");
    shape.setAttribute("id", id);
    shape.setAttribute("type", "plane");

    shape.appendChild(colorToNode(plane._color, "color"));
    shape.appendChild(materialToNode(plane._material));
    shape.appendChild(vector3ToNode(plane._normAndPoint[0], "center"));
    shape.appendChild(vector3ToNode(plane._normAndPoint[1], "normal"));

    return shape;
}

QDomElement ParserXML::rectangleToNode(const Rectangle& rectangle, int id) {
    QDomElement shape = _doc.createElement("shape");
    shape.setAttribute("id", id);
    shape.setAttribute("type", "rectangle");

    shape.appendChild(colorToNode(rectangle._color, "color"));
    shape.appendChild(materialToNode(rectangle._material));
    shape.appendChild(vector3ToNode(rectangle._normAndPoint[0], "center"));
    shape.appendChild(vector3ToNode(rectangle._normAndPoint[1], "normal"));
    shape.appendChild(doubleToNode(rectangle._height, "height"));
    shape.appendChild(doubleToNode(rectangle._width, "width"));

    return shape;
}

QDomElement ParserXML::draughtboardToNode(const Draughtboard& draughtboard, int id) {
    QDomElement shape = _doc.createElement("shape");
    shape.setAttribute("id", id);
    shape.setAttribute("type", "draughtboard");

    shape.appendChild(colorToNode(draughtboard._color, "color"));
    shape.appendChild(materialToNode(draughtboard._material));
    shape.appendChild(vector3ToNode(draughtboard._normAndPoint[0], "center"));
    shape.appendChild(vector3ToNode(draughtboard._normAndPoint[1], "normal"));
    shape.appendChild(doubleToNode(draughtboard._height, "height"));
    shape.appendChild(doubleToNode(draughtboard._width, "width"));
    shape.appendChild(colorToNode(draughtboard._colorD, "colord"));
    shape.appendChild(doubleToNode(draughtboard._caseSize, "casesize"));

    return shape;
}

QDomElement ParserXML::cylindreToNode(const Cylindre &cylindre, int id) {
    QDomElement shape = _doc.createElement("shape");
    shape.setAttribute("id", id);
    shape.setAttribute("type", "cylindre");

    shape.appendChild(colorToNode(cylindre._color, "color"));
    shape.appendChild(materialToNode(cylindre._material));
    shape.appendChild(vector3ToNode(cylindre._bottomCenter, "bottomcenter"));
    shape.appendChild(doubleToNode(cylindre._length, "length"));
    shape.appendChild(doubleToNode(cylindre._radius, "radius"));

    return shape;
}

QDomElement ParserXML::surfaceToNode(const Surface &surface, int id) {
    QDomElement shape = _doc.createElement("shape");
    shape.setAttribute("id", id);
    shape.setAttribute("type", "surface");

    shape.appendChild(colorToNode(surface._color, "color"));
    shape.appendChild(materialToNode(surface._material));
    shape.appendChild(qStringToNode(surface._equation1, "equation1"));
    shape.appendChild(qStringToNode(surface._equation2, "equation2"));
    shape.appendChild(qStringToNode(surface._equation3, "equation3"));
    shape.appendChild(qStringToNode(surface._equation4, "equation4"));

    return shape;
}

QDomElement ParserXML::quadricToNode(const Quadrics& quadric, int id) {
    QDomElement shape = _doc.createElement("shape");
    shape.setAttribute("id", id);
    shape.setAttribute("type", "quadric");

    shape.appendChild(colorToNode(quadric._color, "color"));
    shape.appendChild(materialToNode(quadric._material));
    shape.appendChild(doubleToNode(quadric._a, "a"));
    shape.appendChild(doubleToNode(quadric._b, "b"));
    shape.appendChild(doubleToNode(quadric._c, "c"));
    shape.appendChild(doubleToNode(quadric._d, "d"));
    shape.appendChild(doubleToNode(quadric._e, "e"));
    shape.appendChild(doubleToNode(quadric._f, "f"));
    shape.appendChild(doubleToNode(quadric._g, "g"));
    shape.appendChild(doubleToNode(quadric._h, "h"));
    shape.appendChild(doubleToNode(quadric._i, "i"));
    shape.appendChild(doubleToNode(quadric._j, "j"));

    return shape;
}

QDomElement ParserXML::implicitToNode(const ImplicitSurface &implicit, int id) {
    QDomElement shape = _doc.createElement("shape");
    shape.setAttribute("id", id);
    shape.setAttribute("type", "implicit");

    shape.appendChild(colorToNode(implicit._color, "color"));
    shape.appendChild(materialToNode(implicit._material));
    shape.appendChild(qStringToNode(implicit._equation, "equation"));

    return shape;
}

QDomElement ParserXML::boxToNode(const Box &box, int id) {
    QDomElement shape = _doc.createElement("shape");
    shape.setAttribute("id", id);
    shape.setAttribute("type", "box");

    shape.appendChild(colorToNode(box._color, "color"));
    shape.appendChild(materialToNode(box._material));
    shape.appendChild(vector3ToNode(box._bottomLeftFrontCorner, "blfc"));
    shape.appendChild(vector3ToNode(box._topRightBackCorner, "trbc"));

    return shape;
}

QDomElement ParserXML::triangleToNode(const Triangle &triangle, int id) {
    QDomElement shape = _doc.createElement("shape");
    shape.setAttribute("id", id);
    shape.setAttribute("type", "triangle");

    shape.appendChild(colorToNode(triangle._color, "color"));
    shape.appendChild(materialToNode(triangle._material));
    shape.appendChild(vector3ToNode(triangle._point1, "point1"));
    shape.appendChild(vector3ToNode(triangle._point2, "point2"));
    shape.appendChild(vector3ToNode(triangle._point3, "point3"));

    return shape;
}

QDomElement ParserXML::torusToNode(const Torus &torus, int id) {
    QDomElement shape = _doc.createElement("shape");
    shape.setAttribute("id", id);
    shape.setAttribute("type", "torus");

    shape.appendChild(colorToNode(torus._color, "color"));
    shape.appendChild(materialToNode(torus._material));
    shape.appendChild(doubleToNode(torus._ringRadius, "ringradius"));
    shape.appendChild(doubleToNode(torus._crossRadius, "crossradius"));

    return shape;
}

QDomElement ParserXML::diskToNode(const Disk &disk, int id) {
    QDomElement shape = _doc.createElement("shape");
    shape.setAttribute("id", id);
    shape.setAttribute("type", "disk");

    shape.appendChild(colorToNode(disk._color, "color"));
    shape.appendChild(materialToNode(disk._material));
    shape.appendChild(vector3ToNode(disk._normAndPoint[0], "center"));
    shape.appendChild(vector3ToNode(disk._normAndPoint[1], "normal"));
    shape.appendChild(doubleToNode(disk._radius, "radius"));

    return shape;
}

QDomElement ParserXML::lightToNode(const LightSource& light, int id) {
    QDomElement lightElem = _doc.createElement("light");
    lightElem.setAttribute("id", id);

    lightElem.appendChild(doubleToNode(light._intensity, "intensity"));
    lightElem.appendChild(vector3ToNode(light._position, "position"));
    lightElem.appendChild(colorToNode(light._color, "color"));

    return lightElem;
}

QDomElement ParserXML::cameraToNode(const Camera& camera) {
    QDomElement cameraElem = _doc.createElement("camera");

    cameraElem.appendChild(vector3ToNode(camera._observer, "observer"));
    cameraElem.appendChild(vector3ToNode(camera._aimedPoint, "aimedpoint"));
    cameraElem.appendChild(doubleToNode(camera._viewAngle/M_PI, "viewangle"));
    cameraElem.appendChild(doubleToNode(camera._distScreen, "distscreen"));

    return cameraElem;
}

/***************
 * Get objects *
 ***************/
QDomElement ParserXML::getShape(int id) const {
    QDomNodeList shapeList = _doc.elementsByTagName("shape");

    for(int k = 0; k < shapeList.size(); k++) {
        QDomElement currentShape = shapeList.at(k).toElement();
        int currentId = currentShape.attributeNode("id").value().toInt();
        if(currentId == id) {
            return currentShape;
        }
    }
    cerr << "You specified a wrong id" << endl;
    return QDomElement();
}

QDomElement ParserXML::getLight(int id) const {
    QDomNodeList lightList = _doc.elementsByTagName("light");

    for(int k = 0; k < lightList.size(); k++) {
        QDomElement currentLight = lightList.at(k).toElement();
        int currentId = currentLight.attributeNode("id").value().toInt();
        if(currentId == id) {
            return currentLight;
        }
    }
    cerr << "You specified a wrong id" << endl;
    return QDomElement();
}


QDomDocument ParserXML::getDoc() const {
    return _doc;
}

/***************
 * Add objects *
 ***************/
void ParserXML::addScreensetup(int width, int height, RayTracer::Resolution resolution) {
    _doc.firstChild().appendChild(screensetupToNode(width, height, resolution));
    updateScreenList(width, height, resolution);
}

void ParserXML::addSphere(const Sphere& sphere, int id) {
    if (id == -1) {
        id = nbShapes();
    }
    QDomNode shapes = _doc.elementsByTagName("shapes").at(0);
    shapes.appendChild(sphereToNode(sphere, id));
    _shapesList << "shape "+ QString::number(id) +" (sphere)";
}

void ParserXML::addPlane(const Plane& plane, int id) {
    if (id == -1) {
        id = nbShapes();
    }
    QDomNode shapes = _doc.elementsByTagName("shapes").at(0);
    shapes.appendChild(planeToNode(plane, id));
    _shapesList << "shape "+ QString::number(id) +" (plane)";
}

void ParserXML::addRectangle(const Rectangle& rectangle, int id) {
    if (id == -1) {
        id = nbShapes();
    }
    QDomNode shapes = _doc.elementsByTagName("shapes").at(0);
    shapes.appendChild(rectangleToNode(rectangle, id));
    _shapesList << "shape "+ QString::number(id) +" (rectangle)";
}

void ParserXML::addDraughtboard(const Draughtboard& draughtboard, int id) {
    if (id == -1) {
        id = nbShapes();
    }
    QDomNode shapes = _doc.elementsByTagName("shapes").at(0);
    shapes.appendChild(draughtboardToNode(draughtboard, id));
    _shapesList << "shape "+ QString::number(id) +" (draughtboard)";
}

void ParserXML::addCylindre(const Cylindre& cylindre, int id) {
    if (id == -1) {
        id = nbShapes();
    }
    QDomNode shapes = _doc.elementsByTagName("shapes").at(0);
    shapes.appendChild(cylindreToNode(cylindre, id));
    _shapesList << "shape "+ QString::number(id) +" (cylindre)";
}

void ParserXML::addSurface(const Surface& surface, int id) {
    if (id == -1) {
        id = nbShapes();
    }
    QDomNode shapes = _doc.elementsByTagName("shapes").at(0);
    shapes.appendChild(surfaceToNode(surface, id));
    _shapesList << "shape "+ QString::number(id) +" (surface)";
}

void ParserXML::addQuadric(const Quadrics& quadric, int id) {
    if (id == -1) {
        id = nbShapes();
    }
    QDomNode shapes = _doc.elementsByTagName("shapes").at(0);
    shapes.appendChild(quadricToNode(quadric, id));
    _shapesList << "shape "+ QString::number(id) +" (quadric)";
}

void ParserXML::addImplicit(const ImplicitSurface& implicit, int id) {
    if (id == -1) {
        id = nbShapes();
    }
    QDomNode shapes = _doc.elementsByTagName("shapes").at(0);
    shapes.appendChild(implicitToNode(implicit, id));
    _shapesList << "shape "+ QString::number(id) +" (implicit)";
}

void ParserXML::addBox(const Box &box, int id) {
    if (id == -1) {
        id = nbShapes();
    }
    QDomNode shapes = _doc.elementsByTagName("shapes").at(0);
    shapes.appendChild(boxToNode(box, id));
    _shapesList << "shape "+ QString::number(id) +" (box)";
}

void ParserXML::addTriangle(const Triangle &triangle, int id) {
    if (id == -1) {
        id = nbShapes();
    }
    QDomNode shapes = _doc.elementsByTagName("shapes").at(0);
    shapes.appendChild(triangleToNode(triangle, id));
    _shapesList << "shape "+ QString::number(id) +" (triangle)";
}

void ParserXML::addTorus(const Torus &torus, int id) {
    if (id == -1) {
        id = nbShapes();
    }
    QDomNode shapes = _doc.elementsByTagName("shapes").at(0);
    shapes.appendChild(torusToNode(torus, id));
    _shapesList << "shape "+ QString::number(id) +" (torus)";
}

void ParserXML::addDisk(const Disk &disk, int id) {
    if (id == -1) {
        id = nbShapes();
    }
    QDomNode shapes = _doc.elementsByTagName("shapes").at(0);
    shapes.appendChild(diskToNode(disk, id));
    _shapesList << "shape "+ QString::number(id) +" (disk)";
}

void ParserXML::addLight(const LightSource& light, int id) {
    if (id == -1) {
        id = nbLights();
    }
    QDomNode lights = _doc.elementsByTagName("lights").at(0);
    lights.appendChild(lightToNode(light, id));
    _lightsList << "light "+QString::number(id);
}

void ParserXML::addCamera(const Camera& camera) {
    _doc.firstChild().appendChild(cameraToNode(camera));
    updateCameraList(camera);
}

/*******************
 * Replace objects *
 *******************/
void ParserXML::replaceScreensetup(int width, int height, RayTracer::Resolution resolution) {
    QDomNode oldScreenSetup = _doc.elementsByTagName("screensetup").at(0);
    QDomElement newScreenSetup = screensetupToNode(width, height, resolution);
    _doc.firstChild().replaceChild(newScreenSetup, oldScreenSetup);
    updateScreenList(width, height, resolution);
}

void ParserXML::replaceSphere(const Sphere& sphere, int id) {
    QDomElement oldSphere = getShape(id);
    QDomElement newSphere = sphereToNode(sphere, id);
    _doc.elementsByTagName("shapes").at(0).replaceChild(newSphere, oldSphere);
}

void ParserXML::replacePlane(const Plane& plane, int id) {
    QDomElement oldPlane = getShape(id);
    QDomElement newPlane = planeToNode(plane, id);
    _doc.elementsByTagName("shapes").at(0).replaceChild(newPlane, oldPlane);
}

void ParserXML::replaceRectangle(const Rectangle& rectangle, int id) {
    QDomElement oldRectangle = getShape(id);
    QDomElement newRectangle = rectangleToNode(rectangle, id);
    _doc.elementsByTagName("shapes").at(0).replaceChild(newRectangle, oldRectangle);
}

void ParserXML::replaceDraughtboard(const Draughtboard& draughtboard, int id) {
    QDomElement oldDraughtboard = getShape(id);
    QDomElement newDraughtboard = draughtboardToNode(draughtboard, id);
    _doc.elementsByTagName("shapes").at(0).replaceChild(newDraughtboard, oldDraughtboard);
}

void ParserXML::replaceCylindre(const Cylindre& cylindre, int id) {
    QDomElement oldCylindre = getShape(id);
    QDomElement newCylindre = cylindreToNode(cylindre, id);
    _doc.elementsByTagName("shapes").at(0).replaceChild(newCylindre, oldCylindre);
}

void ParserXML::replaceSurface(const Surface& surface, int id) {
    QDomElement oldSurface = getShape(id);
    QDomElement newSurface = surfaceToNode(surface, id);
    _doc.elementsByTagName("shapes").at(0).replaceChild(newSurface, oldSurface);
}

void ParserXML::replaceQuadric(const Quadrics& quadric, int id) {
    QDomElement oldQuadric = getShape(id);
    QDomElement newQuadric = quadricToNode(quadric, id);
    _doc.elementsByTagName("shapes").at(0).replaceChild(newQuadric, oldQuadric);
}

void ParserXML::replaceImplicit(const ImplicitSurface& implicit, int id) {
    QDomElement oldImplicit = getShape(id);
    QDomElement newImplicit = implicitToNode(implicit, id);
    _doc.elementsByTagName("shapes").at(0).replaceChild(newImplicit, oldImplicit);
}

void ParserXML::replaceBox(const Box &box, int id) {
    QDomElement oldBox = getShape(id);
    QDomElement newBox = boxToNode(box, id);
    _doc.elementsByTagName("shapes").at(0).replaceChild(newBox, oldBox);
}

void ParserXML::replaceTriangle(const Triangle &triangle, int id) {
    QDomElement oldTriangle = getShape(id);
    QDomElement newTriangle = triangleToNode(triangle, id);
    _doc.elementsByTagName("shapes").at(0).replaceChild(newTriangle, oldTriangle);
}

void ParserXML::replaceTorus(const Torus &torus, int id) {
    QDomElement oldTorus = getShape(id);
    QDomElement newTorus = torusToNode(torus, id);
    _doc.elementsByTagName("shapes").at(0).replaceChild(newTorus, oldTorus);
}

void ParserXML::replaceDisk(const Disk &disk, int id) {
    QDomElement oldDisk = getShape(id);
    QDomElement newDisk = diskToNode(disk, id);
    _doc.elementsByTagName("shapes").at(0).replaceChild(newDisk, oldDisk);
}

void ParserXML::replaceLight(const LightSource& light, int id) {
    QDomElement oldLight = getLight(id);
    QDomElement newLight = lightToNode(light, id);
    _doc.elementsByTagName("lights").at(0).replaceChild(newLight, oldLight);
}

void ParserXML::replaceCamera(const Camera& camera) {
    QDomNode oldCamera = _doc.elementsByTagName("camera").at(0);
    QDomElement newCamera = cameraToNode(camera);
    _doc.firstChild().replaceChild(newCamera, oldCamera);
    updateCameraList(camera);
}

/******************
 * Remove objects *
 ******************/
void ParserXML::removeShape(int id) {
    _doc.elementsByTagName("shapes").at(0).removeChild(getShape(id));
    for (int k = 0; k < nbShapes(); k++) {
        _doc.elementsByTagName("shape").at(k).toElement().setAttribute("id", k);
    }
    _shapesList.removeAt(id);
}

void ParserXML::removeLight(int id) {
    _doc.elementsByTagName("lights").at(0).removeChild(getLight(id));
    for (int k = 0; k < nbLights(); k++) {
        _doc.elementsByTagName("light").at(k).toElement().setAttribute("id", k);
    }
    _lightsList.removeAt(id);
}

/******************
 * Create objects *
 ******************/
Color ParserXML::createColor(const QDomElement& colorElem) const {
    return Color(
        colorElem.attribute("r").toDouble(),
        colorElem.attribute("g").toDouble(),
        colorElem.attribute("b").toDouble()
    );
}

Material ParserXML::createMaterial(const QDomElement& materialElem) const {
    return Material(
        materialElem.attribute("ka").toDouble(),
        materialElem.attribute("kd").toDouble(),
        materialElem.attribute("ks").toDouble(),
        materialElem.attribute("ns").toDouble(),
        materialElem.attribute("kreflex").toDouble()
    );
}

Vector3 ParserXML::createVector3(const QDomElement& vector3Elem) const {
    return Vector3(
        vector3Elem.attribute("x").toDouble(),
        vector3Elem.attribute("y").toDouble(),
        vector3Elem.attribute("z").toDouble()
    );
}

double ParserXML::createDouble(const QDomElement& doubleElem) const {
    return doubleElem.attribute("value").toDouble();
}

int ParserXML::createInt(const QDomElement& intElem) const {
    return intElem.attribute("value").toInt();
}

QString ParserXML::createQString(const QDomElement& qStringElem) const {
    return qStringElem.attribute("value");
}

RayTracer::Resolution ParserXML::createResolution(const QDomElement &resolutionElem) const {
    switch (resolutionElem.attribute("value").toInt()) {
    case 0:
        return RayTracer::low;
    case 1:
        return RayTracer::medium;
    case 2:
        return RayTracer::high;
    }
}

QVector<double> ParserXML::createScreenSetup() const {
    QDomElement screenSetupElem = _doc.elementsByTagName("screensetup").at(0).toElement();

    QVector<double> res;
    res.push_back(createInt(screenSetupElem.elementsByTagName("width").at(0).toElement()));
    res.push_back(createInt(screenSetupElem.elementsByTagName("height").at(0).toElement()));

    return res;
}

RayTracer::Resolution ParserXML::createScreenResolution() const {
    QDomElement screenSetupElem = _doc.elementsByTagName("screensetup").at(0).toElement();

    return createResolution(screenSetupElem.elementsByTagName("oversampling").at(0).toElement());
}

Shape* ParserXML::createShape(int id) const {
    QDomElement shape = getShape(id);
    QString shapeType = shape.attributeNode("type").value();
    if(shapeType == "sphere") {
        return new Sphere(
            createColor(shape.elementsByTagName("color").at(0).toElement()),
            createMaterial(shape.elementsByTagName("material").at(0).toElement()),
            createVector3(shape.elementsByTagName("center").at(0).toElement()),
            createDouble(shape.elementsByTagName("radius").at(0).toElement())
        );
    } else if(shapeType == "plane") {
        return new Plane(
            createColor(shape.elementsByTagName("color").at(0).toElement()),
            createMaterial(shape.elementsByTagName("material").at(0).toElement()),
            Ray(createVector3(shape.elementsByTagName("center").at(0).toElement()),
                createVector3(shape.elementsByTagName("normal").at(0).toElement())
            )
        );
    } else if(shapeType == "rectangle") {
        return new Rectangle(
            createColor(shape.elementsByTagName("color").at(0).toElement()),
            createMaterial(shape.elementsByTagName("material").at(0).toElement()),
            Ray(createVector3(shape.elementsByTagName("center").at(0).toElement()),
                createVector3(shape.elementsByTagName("normal").at(0).toElement())),
            createDouble(shape.elementsByTagName("height").at(0).toElement()),
            createDouble(shape.elementsByTagName("width").at(0).toElement())
        );
    } else if(shapeType == "draughtboard") {
        return new Draughtboard(
            createColor(shape.elementsByTagName("color").at(0).toElement()),
            createMaterial(shape.elementsByTagName("material").at(0).toElement()),
            createColor(shape.elementsByTagName("colord").at(0).toElement()),
            Ray(createVector3(shape.elementsByTagName("center").at(0).toElement()),
                createVector3(shape.elementsByTagName("normal").at(0).toElement())),
            createDouble(shape.elementsByTagName("height").at(0).toElement()),
            createDouble(shape.elementsByTagName("width").at(0).toElement()),
            createDouble(shape.elementsByTagName("casesize").at(0).toElement())
        );
    } else if(shapeType == "cylindre") {
        return new Cylindre(
            createColor(shape.elementsByTagName("color").at(0).toElement()),
            createMaterial(shape.elementsByTagName("material").at(0).toElement()),
            createVector3(shape.elementsByTagName("bottomcenter").at(0).toElement()),
            createDouble(shape.elementsByTagName("length").at(0).toElement()),
            createDouble(shape.elementsByTagName("radius").at(0).toElement())
        );
    } else if(shapeType == "surface") {
        QStringList equations;
        equations << createQString(shape.elementsByTagName("equation1").at(0).toElement())
                  << createQString(shape.elementsByTagName("equation2").at(0).toElement())
                  << createQString(shape.elementsByTagName("equation3").at(0).toElement())
                  << createQString(shape.elementsByTagName("equation4").at(0).toElement());
        return new Surface(
            createColor(shape.elementsByTagName("color").at(0).toElement()),
            createMaterial(shape.elementsByTagName("material").at(0).toElement()),
            equations
        );
    } else if(shapeType == "quadric") {
        return new Quadrics(
            createColor(shape.elementsByTagName("color").at(0).toElement()),
            createMaterial(shape.elementsByTagName("material").at(0).toElement()),
            createDouble(shape.elementsByTagName("a").at(0).toElement()),
            createDouble(shape.elementsByTagName("b").at(0).toElement()),
            createDouble(shape.elementsByTagName("c").at(0).toElement()),
            createDouble(shape.elementsByTagName("d").at(0).toElement()),
            createDouble(shape.elementsByTagName("e").at(0).toElement()),
            createDouble(shape.elementsByTagName("f").at(0).toElement()),
            createDouble(shape.elementsByTagName("g").at(0).toElement()),
            createDouble(shape.elementsByTagName("h").at(0).toElement()),
            createDouble(shape.elementsByTagName("i").at(0).toElement()),
            createDouble(shape.elementsByTagName("j").at(0).toElement())
        );
    } else if(shapeType == "implicit") {
        return new ImplicitSurface(
            createColor(shape.elementsByTagName("color").at(0).toElement()),
            createMaterial(shape.elementsByTagName("material").at(0).toElement()),
            createQString(shape.elementsByTagName("equation").at(0).toElement())
        );
    } else if(shapeType == "box") {
        return new Box(
            createColor(shape.elementsByTagName("color").at(0).toElement()),
            createMaterial(shape.elementsByTagName("material").at(0).toElement()),
            createVector3(shape.elementsByTagName("blfc").at(0).toElement()),
            createVector3(shape.elementsByTagName("trbc").at(0).toElement())
        );
    } else if(shapeType == "triangle") {
        return new Triangle(
            createColor(shape.elementsByTagName("color").at(0).toElement()),
            createMaterial(shape.elementsByTagName("material").at(0).toElement()),
            createVector3(shape.elementsByTagName("point1").at(0).toElement()),
            createVector3(shape.elementsByTagName("point2").at(0).toElement()),
            createVector3(shape.elementsByTagName("point3").at(0).toElement())
        );
    } else if(shapeType == "torus") {
        return new Torus(
            createColor(shape.elementsByTagName("color").at(0).toElement()),
            createMaterial(shape.elementsByTagName("material").at(0).toElement()),
            createDouble(shape.elementsByTagName("ringradius").at(0).toElement()),
            createDouble(shape.elementsByTagName("crossradius").at(0).toElement())
        );
    } else if(shapeType == "disk") {
        return new Disk(
            createColor(shape.elementsByTagName("color").at(0).toElement()),
            createMaterial(shape.elementsByTagName("material").at(0).toElement()),
            Ray(createVector3(shape.elementsByTagName("center").at(0).toElement()),
                createVector3(shape.elementsByTagName("normal").at(0).toElement())),
            createDouble(shape.elementsByTagName("radius").at(0).toElement())
        );
    } else {
        cerr << "Shape type unknown in createShape() in ParserXML.cpp" << endl;
    }
    return NULL;
}

LightSource* ParserXML::createLight(int id) const {
    QDomElement light = getLight(id);

    return new LightSource(
        createDouble(light.elementsByTagName("intensity").at(0).toElement()),
        createVector3(light.elementsByTagName("position").at(0).toElement()),
        createColor(light.elementsByTagName("color").at(0).toElement())
    );
}

Camera ParserXML::createCamera() const {
    QDomElement cameraElem = _doc.elementsByTagName("camera").at(0).toElement();

    double width = createScreenSetup().at(0);
    double height = createScreenSetup().at(1);

    Camera camera(
        createVector3(cameraElem.elementsByTagName("observer").at(0).toElement()),
        createVector3(cameraElem.elementsByTagName("aimedpoint").at(0).toElement()),
        M_PI*createDouble(cameraElem.elementsByTagName("viewangle").at(0).toElement()),
        width,
        height
    );
    camera.initFromDistScreen(createDouble(cameraElem.elementsByTagName("distscreen").at(0).toElement()));

    return camera;
}

/*********************
 * Number of objects *
 *********************/
int ParserXML::nbShapes() const {
    return _doc.elementsByTagName("shape").size();
}

int ParserXML::nbLights() const {
    return _doc.elementsByTagName("light").size();
}

QString ParserXML::getShapeType(int idShape) const {
    return _doc.elementsByTagName("shape").at(idShape).toElement().attribute("type");
}

/***************
 * Scene lists *
 ***************/
void ParserXML::initShapesList() {
    _shapesList.clear();
    QDomNodeList nodeShapes = _doc.elementsByTagName("shape");
    for (int k = 0; k < nodeShapes.size(); k++) {
        _shapesList.push_back("shape "+ QString::number(k) + " (" + nodeShapes.at(k).toElement().attribute("type") + ")");
    }
}

QStringList ParserXML::getShapesList() const {
    return _shapesList;
}

void ParserXML::initLightsList() {
    _lightsList.clear();
    for (int k = 0; k < nbLights(); k++) {
        _lightsList.push_back("light "+QString::number(k));
    }
}

QStringList ParserXML::getLightsList() const {
    return _lightsList;
}

void ParserXML::initCameraList() {
    updateCameraList(createCamera());
}

void ParserXML::updateCameraList(const Camera &camera) {
    _cameraList.clear();
    QLabel dToStr0, dToStr1, dToStr2;
    dToStr0.setNum(camera._observer[0]);
    dToStr1.setNum(camera._observer[1]);
    dToStr2.setNum(camera._observer[2]);
    _cameraList << "(" + dToStr0.text() + ", " + dToStr1.text() + ", " + dToStr2.text() + ")";
    dToStr0.setNum(camera._aimedPoint[0]);
    dToStr1.setNum(camera._aimedPoint[1]);
    dToStr2.setNum(camera._aimedPoint[2]);
    _cameraList << "(" + dToStr0.text() + ", " + dToStr1.text() + ", " + dToStr2.text() + ")";
    dToStr0.setNum(camera._viewAngle);
    _cameraList << dToStr0.text();
    dToStr0.setNum(camera._distScreen);
    _cameraList << dToStr0.text();
}

QStringList ParserXML::getCameraList() const {
    return _cameraList;
}

void ParserXML::initScreenList() {
    QVector<double> screenElements = createScreenSetup();
    RayTracer::Resolution resolution = createScreenResolution();
    updateScreenList(screenElements.at(0), screenElements.at(1), resolution);
}

void ParserXML::updateScreenList(int width, int height, RayTracer::Resolution resolution) {
    _screenList.clear();
    QLabel dToStr;
    dToStr.setNum(width);
    _screenList << dToStr.text();
    dToStr.setNum(height);
    _screenList << dToStr.text();
    switch (resolution) {
    case 0:
        _screenList << "Low";
    case 1:
        _screenList << "Medium";
    case 2:
        _screenList << "High";
    }
}

QStringList ParserXML::getScreenList() const {
    return _screenList;
}

ParserXML& ParserXML::operator=(const ParserXML& parser) {
    _xmlFileName = parser._xmlFileName;
    _doc = parser._doc;
    _shapesList = parser._shapesList;
    _lightsList = parser._lightsList;
    _cameraList = parser._cameraList;
    _screenList = parser._screenList;

    return (*this);
}
