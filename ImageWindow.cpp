#include "ImageWindow.h"
#include "AddShapeWindow.h"
#include "LightDialog.h"
#include "Scene.h"
#include "RayTracer.h"
#include "PhongModel.h"
#include "UpdateShapeDialog.h"
#include "UpdateCameraDialog.h"
#include "UpdateScreenDialog.h"
#include "ExportImageDialog.h"
#include "Commands.h"

ImageWindow::ImageWindow() {
    _undoStack = new QUndoStack(this);
    _undoAction = _undoStack->createUndoAction(this, "&Undo");
    _undoAction->setShortcuts(QKeySequence::Undo);
    _redoAction = _undoStack->createRedoAction(this, "&Redo");
    _redoAction->setShortcuts(QKeySequence::Redo);

    _fileName = "";
    _windowTitle = "Introduction";
    _imageLabel = new QLabel("<h1>Welcome!</h1><p>To start using <i>RayTracer Creator</i>, please open an xml file containing a picture elments, or just create a new image from scratch.<br />Afterward, add shapes, lights, set camera or screen information... in one word: enjoy!</p><p>This software is constaintly evolving. If you have any suggestion or question about it, please feel free to contact me:<br />shaolan60 at gmail dot com.</p><p>Below an exemple of picture you can create:<br /><br /><img width=\"500\" src=\"../RayTracer/exemples/exemple.png\" alt=\"Picture exemple\" /></p>", this);
    _saved = true;
    _neverSavedBefore = false;

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(_imageLabel);
    mainLayout->setAlignment(Qt::AlignTop);
    setLayout(mainLayout);
}

ImageWindow::ImageWindow(QString fileName) :
    _fileName(fileName) {

    _neverSavedBefore = false;
    _parser = ParserXML(_fileName);

    init();

    generate();
}

ImageWindow::ImageWindow(QString fileName, QVector<int> screen, RayTracer::Resolution resolution, const Camera& camera) :
    _fileName(fileName) {

    _neverSavedBefore = true;

    _parser = ParserXML();
    _parser.addScreensetup(screen.at(0), screen.at(1), resolution);
    _parser.addCamera(camera);

    init();

    QImage emptyImg(screen.at(0), screen.at(1), QImage::Format_RGB32);
    emptyImg.fill(Qt::black);
    _imageLabel->setPixmap(QPixmap::fromImage(emptyImg));
}

void ImageWindow::init() {
    qRegisterMetaType<Image>("Image");
    connect(&_renderThread, SIGNAL(renderedImage(QImage)), this, SLOT(updateImage(QImage)));

    _windowTitle = _fileName.split("/").last();

    _saved = true;

    _imageLabel = new QLabel(this);
    _imageLabel->setAlignment(Qt::AlignCenter);

    _xmlPath = "../RayTracer/xml";

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(_imageLabel);
    setLayout(mainLayout);
}

ImageWindow::~ImageWindow() {
}

QStringList ImageWindow::getShapesList() const {
    return _parser.getShapesList();
}

QStringList ImageWindow::getLightsList() const {
    return _parser.getLightsList();
}

QStringList ImageWindow::getCameraList() const {
    return _parser.getCameraList();
}

QStringList ImageWindow::getScreenList() const {
    return _parser.getScreenList();
}

QString ImageWindow::getWindowTitle() const {
    return _windowTitle;
}

QString ImageWindow::getFileName() const {
    return _fileName;
}

bool ImageWindow::getSaved() const {
    return _saved;
}

bool ImageWindow::getNeverSavedBefore() const {
    return _neverSavedBefore;
}

QVector<ParserXML> ImageWindow::getPreviousInfoImage() const {
    return _previousInfoImage;
}

QAction* ImageWindow::getUndoAction() {
    return _undoAction;
}

QAction* ImageWindow::getRedoAction() {
    return _redoAction;
}

void ImageWindow::setParser(const ParserXML &parser) {
    _parser = parser;
}

void ImageWindow::save() {
    writeXML();
    _saved = true;
}

void ImageWindow::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save a file", _xmlPath+"/"+_windowTitle, "XML Files (*.xml)");
    if (fileName != "") {
        _xmlPath = QDir(fileName).absolutePath();
        if (!fileName.endsWith("xml")) {
            fileName.append(".xml");
        }
        _fileName = fileName;
        _windowTitle = _fileName.split("/").last();
        writeXML();
        _saved = true;
        _neverSavedBefore = false;
    }
}

void ImageWindow::exportImage() {
    ExportImageDialog* exportImage = new ExportImageDialog(_imageLabel->pixmap(), _windowTitle.split(".").first(), this);
    exportImage->exec();
}

void ImageWindow::exportImage(const QString &fileName) {
    _imageLabel->pixmap()->save(fileName);
}

void ImageWindow::writeXML() {
    QFile file(_fileName);
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Image Window"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(_fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream inFile(&file);
    inFile << _parser.getDoc().toString();
    file.close();
}

QThread& ImageWindow::generate() {
    _renderThread.render(_parser);
    return _renderThread;
}

void ImageWindow::addShape() {
    AddShapeWindow* addShapeWindow = new AddShapeWindow(this);
    if (addShapeWindow->exec() == QDialog::Accepted) {
        _saved = false;

        QString shapeType = addShapeWindow->field("shapeType").toString();
        QString shapeName;

        if (shapeType == "0") {
            Color shapeColor(addShapeWindow->field("s_colorR").toDouble(),
                             addShapeWindow->field("s_colorG").toDouble(),
                             addShapeWindow->field("s_colorB").toDouble()
                  );
            Material shapeMaterial(addShapeWindow->field("s_materialKA").toDouble(),
                                   addShapeWindow->field("s_materialKD").toDouble(),
                                   addShapeWindow->field("s_materialKS").toDouble(),
                                   addShapeWindow->field("s_materialNS").toDouble(),
                                   addShapeWindow->field("s_materialKReflex").toDouble()
                     );
            shapeName = "Sphere";
            _parser.addSphere(Sphere(shapeColor,
                                     shapeMaterial,
                                     Vector3(addShapeWindow->field("s_centerOnlyX").toDouble(),
                                             addShapeWindow->field("s_centerOnlyY").toDouble(),
                                             addShapeWindow->field("s_centerOnlyZ").toDouble()
                                     ),
                                     addShapeWindow->field("s_radius").toDouble()
                              )
                    );
        } else if (shapeType == "1") {
            Color shapeColor(addShapeWindow->field("p_colorR").toDouble(),
                             addShapeWindow->field("p_colorG").toDouble(),
                             addShapeWindow->field("p_colorB").toDouble()
                  );
            Material shapeMaterial(addShapeWindow->field("p_materialKA").toDouble(),
                                   addShapeWindow->field("p_materialKD").toDouble(),
                                   addShapeWindow->field("p_materialKS").toDouble(),
                                   addShapeWindow->field("p_materialNS").toDouble(),
                                   addShapeWindow->field("p_materialKReflex").toDouble()
                     );
            shapeName = "Plane";
            _parser.addPlane(Plane(shapeColor,
                                   shapeMaterial,
                                   Ray(Vector3(addShapeWindow->field("p_centerX").toDouble(),
                                               addShapeWindow->field("p_centerY").toDouble(),
                                               addShapeWindow->field("p_centerZ").toDouble()
                                      ),
                                       Vector3(addShapeWindow->field("p_normalX").toDouble(),
                                               addShapeWindow->field("p_normalY").toDouble(),
                                               addShapeWindow->field("p_normalZ").toDouble()
                                      )
                                   )
                             )
                    );
        } else if (shapeType == "2") {
            Color shapeColor(addShapeWindow->field("r_colorR").toDouble(),
                             addShapeWindow->field("r_colorG").toDouble(),
                             addShapeWindow->field("r_colorB").toDouble()
                  );
            Material shapeMaterial(addShapeWindow->field("r_materialKA").toDouble(),
                                   addShapeWindow->field("r_materialKD").toDouble(),
                                   addShapeWindow->field("r_materialKS").toDouble(),
                                   addShapeWindow->field("r_materialNS").toDouble(),
                                   addShapeWindow->field("r_materialKReflex").toDouble()
                     );
            shapeName = "Rectangle";
            _parser.addRectangle(Rectangle(shapeColor,
                                           shapeMaterial,
                                           Ray(Vector3(addShapeWindow->field("r_centerX").toDouble(),
                                                       addShapeWindow->field("r_centerY").toDouble(),
                                                       addShapeWindow->field("r_centerZ").toDouble()
                                              ),
                                               Vector3(addShapeWindow->field("r_normalX").toDouble(),
                                                       addShapeWindow->field("r_normalY").toDouble(),
                                                       addShapeWindow->field("r_normalZ").toDouble()
                                              )
                                           ),
                                           addShapeWindow->field("r_height").toDouble(),
                                           addShapeWindow->field("r_width").toDouble()
                                )
                    );
        } else if (shapeType == "3") {
            Color shapeColor(addShapeWindow->field("d_colorR").toDouble(),
                             addShapeWindow->field("d_colorG").toDouble(),
                             addShapeWindow->field("d_colorB").toDouble()
                  );
            Material shapeMaterial(addShapeWindow->field("d_materialKA").toDouble(),
                                   addShapeWindow->field("d_materialKD").toDouble(),
                                   addShapeWindow->field("d_materialKS").toDouble(),
                                   addShapeWindow->field("d_materialNS").toDouble(),
                                   addShapeWindow->field("d_materialKReflex").toDouble()
                     );
            shapeName = "Draughtboard";
            _parser.addDraughtboard(Draughtboard(shapeColor,
                                                 shapeMaterial,
                                                 Color(addShapeWindow->field("d_colorDR").toDouble(),
                                                       addShapeWindow->field("d_colorDG").toDouble(),
                                                       addShapeWindow->field("d_colorDB").toDouble()
                                                 ),
                                                 Ray(Vector3(addShapeWindow->field("d_centerX").toDouble(),
                                                             addShapeWindow->field("d_centerY").toDouble(),
                                                             addShapeWindow->field("d_centerZ").toDouble()
                                                    ),
                                                     Vector3(addShapeWindow->field("d_normalX").toDouble(),
                                                             addShapeWindow->field("d_normalY").toDouble(),
                                                             addShapeWindow->field("d_normalZ").toDouble()
                                                    )
                                                 ),
                                                 addShapeWindow->field("d_width").toDouble(),
                                                 addShapeWindow->field("d_height").toDouble(),
                                                 addShapeWindow->field("d_caseSize").toDouble()
                                   )
                    );
        } else if (shapeType == "4") {
            Color shapeColor(addShapeWindow->field("c_colorR").toDouble(),
                             addShapeWindow->field("c_colorG").toDouble(),
                             addShapeWindow->field("c_colorB").toDouble()
                  );
            Material shapeMaterial(addShapeWindow->field("c_materialKA").toDouble(),
                                   addShapeWindow->field("c_materialKD").toDouble(),
                                   addShapeWindow->field("c_materialKS").toDouble(),
                                   addShapeWindow->field("c_materialNS").toDouble(),
                                   addShapeWindow->field("c_materialKReflex").toDouble()
                     );
            shapeName = "Cylindre";
            _parser.addCylindre(Cylindre(shapeColor,
                                     shapeMaterial,
                                     Vector3(addShapeWindow->field("c_bottomCenterX").toDouble(),
                                             addShapeWindow->field("c_bottomCenterY").toDouble(),
                                             addShapeWindow->field("c_bottomCenterZ").toDouble()
                                     ),
                                     addShapeWindow->field("c_length").toDouble(),
                                     addShapeWindow->field("c_radius").toDouble()
                              )
                    );
        } else if (shapeType == "5") {
            Color shapeColor(addShapeWindow->field("su_colorR").toDouble(),
                             addShapeWindow->field("su_colorG").toDouble(),
                             addShapeWindow->field("su_colorB").toDouble()
                  );
            Material shapeMaterial(addShapeWindow->field("su_materialKA").toDouble(),
                                   addShapeWindow->field("su_materialKD").toDouble(),
                                   addShapeWindow->field("su_materialKS").toDouble(),
                                   addShapeWindow->field("su_materialNS").toDouble(),
                                   addShapeWindow->field("su_materialKReflex").toDouble()
                     );
            QString eq1 = addShapeWindow->field("su_equation1").toString();
            QString eq2 = addShapeWindow->field("su_equation2").toString();
            QString eq3 = addShapeWindow->field("su_equation3").toString();
            QString eq4 = addShapeWindow->field("su_equation4").toString();
            QStringList shapeEquations;
            shapeEquations << eq1 << eq2 << eq3 << eq4;
            shapeName = "Surface";
            _parser.addSurface(Surface(shapeColor,
                                       shapeMaterial,
                                       shapeEquations
                              )
                    );
        } else if (shapeType == "6") {
            Color shapeColor(addShapeWindow->field("q_colorR").toDouble(),
                             addShapeWindow->field("q_colorG").toDouble(),
                             addShapeWindow->field("q_colorB").toDouble()
                  );
            Material shapeMaterial(addShapeWindow->field("q_materialKA").toDouble(),
                                   addShapeWindow->field("q_materialKD").toDouble(),
                                   addShapeWindow->field("q_materialKS").toDouble(),
                                   addShapeWindow->field("q_materialNS").toDouble(),
                                   addShapeWindow->field("q_materialKReflex").toDouble()
                     );
            double a = addShapeWindow->field("q_a").toDouble();
            double b = addShapeWindow->field("q_b").toDouble();
            double c = addShapeWindow->field("q_c").toDouble();
            double d = addShapeWindow->field("q_d").toDouble();
            double e = addShapeWindow->field("q_e").toDouble();
            double f = addShapeWindow->field("q_f").toDouble();
            double g = addShapeWindow->field("q_g").toDouble();
            double h = addShapeWindow->field("q_h").toDouble();
            double i = addShapeWindow->field("q_i").toDouble();
            double j = addShapeWindow->field("q_j").toDouble();
            shapeName = "Quadric";
            _parser.addQuadric(Quadrics(shapeColor,
                                       shapeMaterial,
                                       a, b, c,
                                       d, e, f,
                                       g, h, i, j
                              )
                    );
        } else if (shapeType == "7") {
            Color shapeColor(addShapeWindow->field("i_colorR").toDouble(),
                             addShapeWindow->field("i_colorG").toDouble(),
                             addShapeWindow->field("i_colorB").toDouble()
                  );
            Material shapeMaterial(addShapeWindow->field("i_materialKA").toDouble(),
                                   addShapeWindow->field("i_materialKD").toDouble(),
                                   addShapeWindow->field("i_materialKS").toDouble(),
                                   addShapeWindow->field("i_materialNS").toDouble(),
                                   addShapeWindow->field("i_materialKReflex").toDouble()
                     );
            QString equation = addShapeWindow->field("i_equation").toString();
            shapeName = "implicit";
            _parser.addImplicit(ImplicitSurface(shapeColor,
                                                shapeMaterial,
                                                equation
                               )
                    );
        } else if (shapeType == "8") {
            Color shapeColor(addShapeWindow->field("b_colorR").toDouble(),
                             addShapeWindow->field("b_colorG").toDouble(),
                             addShapeWindow->field("b_colorB").toDouble()
                  );
            Material shapeMaterial(addShapeWindow->field("b_materialKA").toDouble(),
                                   addShapeWindow->field("b_materialKD").toDouble(),
                                   addShapeWindow->field("b_materialKS").toDouble(),
                                   addShapeWindow->field("b_materialNS").toDouble(),
                                   addShapeWindow->field("b_materialKReflex").toDouble()
                     );
            Vector3 bottomLeftFrontCorner(addShapeWindow->field("b_x1").toDouble(),
                                          addShapeWindow->field("b_y1").toDouble(),
                                          addShapeWindow->field("b_z1").toDouble()
                    );
            Vector3 topRightBackCorner(addShapeWindow->field("b_x2").toDouble(),
                                       addShapeWindow->field("b_y2").toDouble(),
                                       addShapeWindow->field("b_z2").toDouble()
                    );
            shapeName = "box";
            _parser.addBox(Box(shapeColor,
                               shapeMaterial,
                               bottomLeftFrontCorner,
                               topRightBackCorner
                          )
                    );
        } else if (shapeType == "9") {
            Color shapeColor(addShapeWindow->field("t_colorR").toDouble(),
                             addShapeWindow->field("t_colorG").toDouble(),
                             addShapeWindow->field("t_colorB").toDouble()
                  );
            Material shapeMaterial(addShapeWindow->field("t_materialKA").toDouble(),
                                   addShapeWindow->field("t_materialKD").toDouble(),
                                   addShapeWindow->field("t_materialKS").toDouble(),
                                   addShapeWindow->field("t_materialNS").toDouble(),
                                   addShapeWindow->field("t_materialKReflex").toDouble()
                     );
            Vector3 point1(addShapeWindow->field("t_x1").toDouble(),
                           addShapeWindow->field("t_y1").toDouble(),
                           addShapeWindow->field("t_z1").toDouble()
                    );
            Vector3 point2(addShapeWindow->field("t_x2").toDouble(),
                           addShapeWindow->field("t_y2").toDouble(),
                           addShapeWindow->field("t_z2").toDouble()
                    );
            Vector3 point3(addShapeWindow->field("t_x3").toDouble(),
                           addShapeWindow->field("t_y3").toDouble(),
                           addShapeWindow->field("t_z3").toDouble()
                    );
            shapeName = "triangle";
            _parser.addTriangle(Triangle(shapeColor,
                                         shapeMaterial,
                                         point1,
                                         point2,
                                         point3
                          )
                    );
        } else if (shapeType == "10") {
            Color shapeColor(addShapeWindow->field("to_colorR").toDouble(),
                             addShapeWindow->field("to_colorG").toDouble(),
                             addShapeWindow->field("to_colorB").toDouble()
                  );
            Material shapeMaterial(addShapeWindow->field("to_materialKA").toDouble(),
                                   addShapeWindow->field("to_materialKD").toDouble(),
                                   addShapeWindow->field("to_materialKS").toDouble(),
                                   addShapeWindow->field("to_materialNS").toDouble(),
                                   addShapeWindow->field("to_materialKReflex").toDouble()
                     );
            shapeName = "torus";
            _parser.addTorus(Torus(shapeColor,
                                   shapeMaterial,
                                   addShapeWindow->field("to_ringRadius").toDouble(),
                                   addShapeWindow->field("to_crossRadius").toDouble()
                          )
                    );
        } else if (shapeType == "11") {
            Color shapeColor(addShapeWindow->field("di_colorR").toDouble(),
                             addShapeWindow->field("di_colorG").toDouble(),
                             addShapeWindow->field("di_colorB").toDouble()
                  );
            Material shapeMaterial(addShapeWindow->field("di_materialKA").toDouble(),
                                   addShapeWindow->field("di_materialKD").toDouble(),
                                   addShapeWindow->field("di_materialKS").toDouble(),
                                   addShapeWindow->field("di_materialNS").toDouble(),
                                   addShapeWindow->field("di_materialKReflex").toDouble()
                     );
            shapeName = "disk";
            _parser.addDisk(Disk(shapeColor,
                                 shapeMaterial,
                                 Ray(Vector3(addShapeWindow->field("di_centerX").toDouble(),
                                             addShapeWindow->field("di_centerY").toDouble(),
                                             addShapeWindow->field("di_centerZ").toDouble()
                                    ),
                                     Vector3(addShapeWindow->field("di_normalX").toDouble(),
                                             addShapeWindow->field("di_normalY").toDouble(),
                                             addShapeWindow->field("di_normalZ").toDouble()
                                    )
                                 ),
                                 addShapeWindow->field("di_radius").toDouble()
                          )
                    );
        } else {
            QMessageBox::critical(this, "Error", "This shape does not even exist!\nError occurred in addShape() function in ImageWindow.cpp");
        }
    }
}

void ImageWindow::addLight() {
    LightDialog* lightDialog = new LightDialog(this);
    if (lightDialog->exec() == QDialog::Accepted) {
        LightSource light(lightDialog->getIntensity(),
                          lightDialog->getPosition(),
                          lightDialog->getColor()
                    );
        _parser.addLight(light);
        //QUndoCommand* addLightCommand = new AddLightCommand(&_parser, light);
        //_undoStack->push(addLightCommand);
        _saved = false;
    }
}

void ImageWindow::updateShape(int idShape) {
    QString shapeType = _parser.getShapeType(idShape);
    Shape* shape = _parser.createShape(idShape);
    if (shapeType == "sphere") {
        UpdateSphere* updateShape = new UpdateSphere((Sphere*) shape, this);
        if (updateShape->exec() == QDialog::Accepted) {
            Sphere newSphere(updateShape->getColor(),
                             updateShape->getMaterial(),
                             updateShape->getCenter(),
                             updateShape->getRadius()
                   );
            _parser.replaceSphere(newSphere, idShape);
            _saved = false;
        }
    } else if (shapeType == "plane") {
        UpdatePlane* updateShape = new UpdatePlane((Plane*) shape, this);
        if (updateShape->exec() == QDialog::Accepted) {
            Plane newPlane(updateShape->getColor(),
                           updateShape->getMaterial(),
                           updateShape->getNormAndPoint()
                  );
            _parser.replacePlane(newPlane, idShape);
            _saved = false;
        }
    } else if (shapeType == "rectangle") {
        UpdateRectangle* updateShape = new UpdateRectangle((Rectangle*) shape, this);
        if (updateShape->exec() == QDialog::Accepted) {
            Rectangle newRectangle(updateShape->getColor(),
                                   updateShape->getMaterial(),
                                   updateShape->getNormAndPoint(),
                                   updateShape->getHeight(),
                                   updateShape->getWidth()
                      );
            _parser.replaceRectangle(newRectangle, idShape);
            _saved = false;
        }

    } else if (shapeType == "draughtboard") {
        UpdateDraughtboard* updateShape = new UpdateDraughtboard((Draughtboard*) shape, this);
        if (updateShape->exec() == QDialog::Accepted) {
            Draughtboard newDraughtboard(updateShape->getColor(),
                                         updateShape->getMaterial(),
                                         updateShape->getColorD(),
                                         updateShape->getNormAndPoint(),
                                         updateShape->getHeight(),
                                         updateShape->getWidth(),
                                         updateShape->getCaseSize()
                         );
            _parser.replaceDraughtboard(newDraughtboard, idShape);
            _saved = false;
        }
    } else if (shapeType == "cylindre") {
        UpdateCylindre* updateShape = new UpdateCylindre((Cylindre*) shape, this);
        if (updateShape->exec() == QDialog::Accepted) {
            Cylindre newCylindre(updateShape->getColor(),
                                 updateShape->getMaterial(),
                                 updateShape->getbottomCenter(),
                                 updateShape->getLength(),
                                 updateShape->getRadius()
                   );
            _parser.replaceCylindre(newCylindre, idShape);
            _saved = false;
        }
    } else if (shapeType == "surface") {
        UpdateSurface* updateShape = new UpdateSurface((Surface*) shape, this);
        if (updateShape->exec() == QDialog::Accepted) {
            Surface newSurface(updateShape->getColor(),
                               updateShape->getMaterial(),
                               updateShape->getEquations()
                   );
            _parser.replaceSurface(newSurface, idShape);
            _saved = false;
        }
    } else if (shapeType == "quadric") {
        UpdateQuadric* updateShape = new UpdateQuadric((Quadrics*) shape, this);
        if (updateShape->exec() == QDialog::Accepted) {
            Quadrics newQuadric(updateShape->getColor(),
                                updateShape->getMaterial(),
                                updateShape->getA(),
                                updateShape->getB(),
                                updateShape->getC(),
                                updateShape->getD(),
                                updateShape->getE(),
                                updateShape->getF(),
                                updateShape->getG(),
                                updateShape->getH(),
                                updateShape->getI(),
                                updateShape->getJ()
                   );
            _parser.replaceQuadric(newQuadric, idShape);
            _saved = false;
        }
    } else if (shapeType == "implicit") {
        UpdateImplicit* updateShape = new UpdateImplicit((ImplicitSurface*) shape, this);
        if (updateShape->exec() == QDialog::Accepted) {
            ImplicitSurface newImplicit(updateShape->getColor(),
                                        updateShape->getMaterial(),
                                        updateShape->getEquation()
                   );
            _parser.replaceImplicit(newImplicit, idShape);
            _saved = false;
        }
    } else if (shapeType == "box") {
        UpdateBox* updateShape = new UpdateBox((Box*) shape, this);
        if (updateShape->exec() == QDialog::Accepted) {
            Box newBox(updateShape->getColor(),
                       updateShape->getMaterial(),
                       updateShape->getBLFC(),
                       updateShape->getTRBC()
                   );
            _parser.replaceBox(newBox, idShape);
            _saved = false;
        }
    } else if (shapeType == "triangle") {
        UpdateTriangle* updateShape = new UpdateTriangle((Triangle*) shape, this);
        if (updateShape->exec() == QDialog::Accepted) {
            Triangle newTriangle(updateShape->getColor(),
                                 updateShape->getMaterial(),
                                 updateShape->getPoint1(),
                                 updateShape->getPoint2(),
                                 updateShape->getPoint3()
                   );
            _parser.replaceTriangle(newTriangle, idShape);
            _saved = false;
        }
    } else if (shapeType == "torus") {
        UpdateTorus* updateShape = new UpdateTorus((Torus*) shape, this);
        if (updateShape->exec() == QDialog::Accepted) {
            Torus newTorus(updateShape->getColor(),
                              updateShape->getMaterial(),
                              updateShape->getRingRadius(),
                              updateShape->getCrossRadius()
                   );
            _parser.replaceTorus(newTorus, idShape);
            _saved = false;
        }
    } else if (shapeType == "disk") {
        UpdateDisk* updateShape = new UpdateDisk((Disk*) shape, this);
        if (updateShape->exec() == QDialog::Accepted) {
            Disk newDisk(updateShape->getColor(),
                         updateShape->getMaterial(),
                         updateShape->getNormAndPoint(),
                         updateShape->getRadius()
                   );
            _parser.replaceDisk(newDisk, idShape);
            _saved = false;
        }
    } else {
        QMessageBox::critical(this, "Shape update", shapeType + " does not name a shape type");
    }
}

void ImageWindow::removeShape(int idShape) {
    int answer = QMessageBox::warning(this, "Remove shape", "Warning, you are about to remove a shape.\nContinue?", QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes) {
        _parser.removeShape(idShape);
        _saved = false;
    }
}

void ImageWindow::updateLight(int idLight) {
    LightSource* oldLight = _parser.createLight(idLight);
    LightDialog* lightDialog = new LightDialog(this, oldLight);
    if (lightDialog->exec() == QDialog::Accepted) {
        LightSource newLight(lightDialog->getIntensity(),
                             lightDialog->getPosition(),
                             lightDialog->getColor()
                    );
        _parser.replaceLight(newLight, idLight);
        _saved = false;
    }
}

void ImageWindow::removeLight(int idLight) {
    int answer = QMessageBox::warning(this, "Remove light", "Warning, you are about to remove a light.\nContinue?", QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes) {
        _parser.removeLight(idLight);
        _saved = false;
    }
}

void ImageWindow::setCamera() {
    UpdateCameraDialog* cameraDialog = new UpdateCameraDialog(_parser.createCamera(), this);
    if (cameraDialog->exec() == QDialog::Accepted) {
        Camera newCamera(cameraDialog->getObserver(),
                         cameraDialog->getAimedPoint(),
                         cameraDialog->getViewAngle(),
                         _parser.getScreenList().at(0).toDouble(),
                         _parser.getScreenList().at(1).toDouble()
               );
        newCamera.initFromDistScreen(cameraDialog->getDistanceScreen());
        _parser.replaceCamera(newCamera);
        _saved = false;
    }
}

void ImageWindow::setCamera(const Vector3& observer, const Vector3& aimedPoint) {

        Camera newCamera(observer,
                         aimedPoint,
                         _parser.getCameraList().at(2).toDouble(),
                         _parser.getScreenList().at(0).toDouble(),
                         _parser.getScreenList().at(1).toDouble()
               );
        newCamera.initFromDistScreen(_parser.getCameraList().at(3).toDouble());
        _parser.replaceCamera(newCamera);
        _saved = false;
}

void ImageWindow::setScreen() {
    UpdateScreenDialog* screenDialog = new UpdateScreenDialog(_parser.createScreenSetup(), _parser.createScreenResolution(), this);
    if (screenDialog->exec() == QDialog::Accepted) {
        _parser.replaceScreensetup(screenDialog->getWidth(), screenDialog->getHeight(), screenDialog->getResolution());
        _saved = false;
    }
}

void ImageWindow::setSaved(bool b) {
    _saved = b;
}

void ImageWindow::updateImage(const QImage& image) {
    _imageLabel->setPixmap(QPixmap::fromImage(image));
}

void ImageWindow::mousePressEvent(QMouseEvent* event) {
    if (_windowTitle != "Introduction") {
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);

        QPixmap pixmap = *_imageLabel->pixmap();
        dataStream << (pixmap.scaled(60, 60));

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("image/jpg", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setHotSpot(event->pos());
        drag->setPixmap(pixmap);

        drag->exec(Qt::MoveAction);
    }
}
