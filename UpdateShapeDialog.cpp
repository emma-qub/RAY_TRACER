#include "UpdateShapeDialog.h"

UpdateShape::UpdateShape(Shape* shape, QWidget* parent) :
    QDialog(parent) {

    _colorREdit = new QLineEdit(QString::number(shape->_color[0]));
    _colorREdit->setVisible(false);
    _colorGEdit = new QLineEdit(QString::number(shape->_color[1]));
    _colorGEdit->setVisible(false);
    _colorBEdit = new QLineEdit(QString::number(shape->_color[2]));
    _colorBEdit->setVisible(false);

    _colorRender = new QLabel;
    _colorRender->setFixedSize(50, 20);
    QPixmap colorPixmap(50, 20);
    colorPixmap.fill(QColor(_colorREdit->text().toDouble()*255, _colorGEdit->text().toDouble()*255, _colorBEdit->text().toDouble()*255));
    _colorRender->setPixmap(colorPixmap);
    _paletteButton = new QPushButton("Palette", this);
    _paletteButton->setFixedWidth(100);
    connect(_paletteButton, SIGNAL(clicked()), this, SLOT(browsePalette()));
    QHBoxLayout* colorLayout = new QHBoxLayout;
    colorLayout->setAlignment(Qt::AlignLeft);
    colorLayout->addWidget(_colorRender);
    colorLayout->addWidget(_paletteButton);
    QGroupBox* colorGroupBox = new QGroupBox("Color", this);
    colorGroupBox->setLayout(colorLayout);

    _materialKAEdit = new QLineEdit(QString::number(shape->_material.k_a), this);
    _materialKAEdit->setFixedWidth(50);
    _materialKDEdit = new QLineEdit(QString::number(shape->_material.k_d), this);
    _materialKDEdit->setFixedWidth(50);
    _materialKSEdit = new QLineEdit(QString::number(shape->_material.k_s), this);
    _materialKSEdit->setFixedWidth(50);
    _materialNSEdit = new QLineEdit(QString::number(shape->_material.n_s), this);
    _materialNSEdit->setFixedWidth(50);
    _materialKReflexEdit = new QLineEdit(QString::number(shape->_material.k_reflex), this);
    _materialKReflexEdit->setFixedWidth(50);

    QLabel* materialKALabel = new QLabel("Ambiant light:");
    QLabel* materialKDLabel = new QLabel("Diffuse light:");
    QLabel* materialKSLabel = new QLabel("Specular light:");
    QLabel* materialNSLabel = new QLabel("Cosine power:");
    QLabel* materialKReflexLabel = new QLabel("Reflexion:");

    QGridLayout* materialLayout = new QGridLayout;
    materialLayout->setAlignment(Qt::AlignLeft);
    materialLayout->addWidget(materialKALabel ,0, 0, Qt::AlignRight);
    materialLayout->addWidget(_materialKAEdit ,0, 1, Qt::AlignLeft);
    materialLayout->addWidget(materialKDLabel ,1, 0, Qt::AlignRight);
    materialLayout->addWidget(_materialKDEdit ,1, 1, Qt::AlignLeft);
    materialLayout->addWidget(materialKSLabel ,2, 0, Qt::AlignRight);
    materialLayout->addWidget(_materialKSEdit ,2, 1, Qt::AlignLeft);
    materialLayout->addWidget(materialNSLabel ,3, 0, Qt::AlignRight);
    materialLayout->addWidget(_materialNSEdit ,3, 1, Qt::AlignLeft);
    materialLayout->addWidget(materialKReflexLabel ,4, 0, Qt::AlignRight);
    materialLayout->addWidget(_materialKReflexEdit ,4, 1, Qt::AlignLeft);

    QGroupBox* materialGroupBox = new QGroupBox("Material", this);
    materialGroupBox->setLayout(materialLayout);
    materialGroupBox->setAlignment(Qt::AlignRight);

    _mainLayout = new QVBoxLayout;
    _mainLayout->setAlignment(Qt::AlignLeft);
    _mainLayout->addWidget(colorGroupBox);
    _mainLayout->addWidget(materialGroupBox);


    _updateButton = new QPushButton("Update", this);
    connect(_updateButton, SIGNAL(clicked()), this, SLOT(accept()));
    _cancelButton = new QPushButton("Cancel", this);
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->addWidget(_updateButton);
    buttonsLayout->addWidget(_cancelButton);


    QHBoxLayout* globalLayout = new QHBoxLayout;
    globalLayout->addLayout(_mainLayout);
    globalLayout->addLayout(buttonsLayout);

    setLayout(globalLayout);
}

Color UpdateShape::getColor() const {
    return Color(_colorREdit->text().toDouble(),
                 _colorGEdit->text().toDouble(),
                 _colorBEdit->text().toDouble()
           );
}

Material UpdateShape::getMaterial() const {
    return Material(_materialKAEdit->text().toDouble(),
                    _materialKDEdit->text().toDouble(),
                    _materialKSEdit->text().toDouble(),
                    _materialNSEdit->text().toDouble(),
                    _materialKReflexEdit->text().toDouble()
           );
}

void UpdateShape::browsePalette() {
    QColor colorSelected = QColorDialog::getColor(QColor(_colorREdit->text().toDouble()*255, _colorGEdit->text().toDouble()*255, _colorBEdit->text().toDouble()*255), this);

    QLabel label("");
    label.setNum(colorSelected.red() / 255.0);
    _colorREdit->setText(label.text());
    label.setNum(colorSelected.green() / 255.0);
    _colorGEdit->setText(label.text());
    label.setNum(colorSelected.blue() / 255.0);
    _colorBEdit->setText(label.text());

    QPixmap colorPixmap(50, 20);
    colorPixmap.fill(colorSelected);
    _colorRender->setPixmap(colorPixmap);
}



UpdateSphere::UpdateSphere(Sphere* sphere, QWidget* parent) :
    UpdateShape(sphere, parent) {

    _centerOnlyXEdit = new QLineEdit(QString::number(sphere->_center[0]), this);
    _centerOnlyXEdit->setFixedWidth(50);
    _centerOnlyYEdit = new QLineEdit(QString::number(sphere->_center[1]), this);
    _centerOnlyYEdit->setFixedWidth(50);
    _centerOnlyZEdit = new QLineEdit(QString::number(sphere->_center[2]), this);
    _centerOnlyZEdit->setFixedWidth(50);
    QFormLayout* centerXLayout = new QFormLayout;
    centerXLayout->addRow("X:", _centerOnlyXEdit);
    QFormLayout* centerYLayout = new QFormLayout;
    centerYLayout->addRow("Y:", _centerOnlyYEdit);
    QFormLayout* centerZLayout = new QFormLayout;
    centerZLayout->addRow("Z:", _centerOnlyZEdit);
    QHBoxLayout* centerLayout = new QHBoxLayout;
    centerLayout->addLayout(centerXLayout);
    centerLayout->addLayout(centerYLayout);
    centerLayout->addLayout(centerZLayout);
    QGroupBox* centerGroupBox = new QGroupBox("Center", this);
    centerGroupBox->setFixedWidth(250);
    centerGroupBox->setLayout(centerLayout);

    _radiusEdit = new QLineEdit(QString::number(sphere->_radius), this);
    _radiusEdit->setFixedWidth(50);
    QFormLayout* radiusLayout = new QFormLayout;
    radiusLayout->addRow("Value:", _radiusEdit);
    QGroupBox* radiusGroupBox = new QGroupBox("Radius", this);
    radiusGroupBox->setLayout(radiusLayout);

    _mainLayout->addWidget(centerGroupBox);
    _mainLayout->addWidget(radiusGroupBox);
}

Vector3 UpdateSphere::getCenter() const {
    return Vector3(_centerOnlyXEdit->text().toDouble(),
                   _centerOnlyYEdit->text().toDouble(),
                   _centerOnlyZEdit->text().toDouble()
           );
}

double UpdateSphere::getRadius() const {
    return _radiusEdit->text().toDouble();
}



UpdatePlane::UpdatePlane(Plane* plane, QWidget* parent) :
    UpdateShape(plane, parent) {

    _centerXEdit = new QLineEdit(QString::number(plane->_normAndPoint[0][0]), this);
    _centerXEdit->setFixedWidth(50);
    _centerYEdit = new QLineEdit(QString::number(plane->_normAndPoint[0][1]), this);
    _centerYEdit->setFixedWidth(50);
    _centerZEdit = new QLineEdit(QString::number(plane->_normAndPoint[0][2]), this);
    _centerZEdit->setFixedWidth(50);
    QFormLayout* centerXLayout = new QFormLayout;
    centerXLayout->addRow("X:", _centerXEdit);
    QFormLayout* centerYLayout = new QFormLayout;
    centerYLayout->addRow("Y:", _centerYEdit);
    QFormLayout* centerZLayout = new QFormLayout;
    centerZLayout->addRow("Z:", _centerZEdit);
    QHBoxLayout* centerLayout = new QHBoxLayout;
    centerLayout->addLayout(centerXLayout);
    centerLayout->addLayout(centerYLayout);
    centerLayout->addLayout(centerZLayout);
    QGroupBox* centerGroupBox = new QGroupBox("Center", this);
    centerGroupBox->setFixedWidth(250);
    centerGroupBox->setLayout(centerLayout);

    _normalXEdit = new QLineEdit(QString::number(plane->_normAndPoint[1][0]), this);
    _normalXEdit->setFixedWidth(50);
    _normalYEdit = new QLineEdit(QString::number(plane->_normAndPoint[1][1]), this);
    _normalYEdit->setFixedWidth(50);
    _normalZEdit = new QLineEdit(QString::number(plane->_normAndPoint[1][2]), this);
    _normalZEdit->setFixedWidth(50);
    QFormLayout* normalXLayout = new QFormLayout;
    normalXLayout->addRow("X:", _normalXEdit);
    QFormLayout* normalYLayout = new QFormLayout;
    normalYLayout->addRow("Y:", _normalYEdit);
    QFormLayout* normalZLayout = new QFormLayout;
    normalZLayout->addRow("Z:", _normalZEdit);
    QHBoxLayout* normalLayout = new QHBoxLayout;
    normalLayout->addLayout(normalXLayout);
    normalLayout->addLayout(normalYLayout);
    normalLayout->addLayout(normalZLayout);
    QGroupBox* normalGroupBox = new QGroupBox("Normal", this);
    normalGroupBox->setFixedWidth(250);
    normalGroupBox->setLayout(normalLayout);

    _mainLayout->addWidget(centerGroupBox);
    _mainLayout->addWidget(normalGroupBox);
}

Ray UpdatePlane::getNormAndPoint() const {
    return Ray(Vector3(_centerXEdit->text().toDouble(),
                       _centerYEdit->text().toDouble(),
                       _centerZEdit->text().toDouble()),
               Vector3(_normalXEdit->text().toDouble(),
                       _normalYEdit->text().toDouble(),
                       _normalZEdit->text().toDouble())
           );
}



UpdateRectangle::UpdateRectangle(Rectangle* rectangle, QWidget* parent) :
    UpdatePlane(rectangle, parent) {

    _widthEdit = new QLineEdit(QString::number(rectangle->_width), this);
    _widthEdit->setFixedWidth(50);
    _heightEdit = new QLineEdit(QString::number(rectangle->_height), this);
    _heightEdit->setFixedWidth(50);
    QFormLayout* widthLayout = new QFormLayout;
    widthLayout->addRow("Width:", _widthEdit);
    QFormLayout* heightLayout = new QFormLayout;
    heightLayout->addRow("Height:", _heightEdit);
    QHBoxLayout* dimensionsLayout = new QHBoxLayout;
    dimensionsLayout->addLayout(widthLayout);
    dimensionsLayout->addLayout(heightLayout);
    QGroupBox* dimensionsGroupBox = new QGroupBox("Dimensions", this);
    dimensionsGroupBox->setFixedWidth(250);
    dimensionsGroupBox->setLayout(dimensionsLayout);

    _mainLayout->addWidget(dimensionsGroupBox);
}

double UpdateRectangle::getWidth() const {
    return _widthEdit->text().toDouble();
}

double UpdateRectangle::getHeight() const {
    return _heightEdit->text().toDouble();
}



UpdateDraughtboard::UpdateDraughtboard(Draughtboard* draughtboard, QWidget* parent) :
    UpdateRectangle(draughtboard, parent) {

    _colorDREdit = new QLineEdit(QString::number(draughtboard->_colorD[0]));
    _colorDREdit->setVisible(false);
    _colorDGEdit = new QLineEdit(QString::number(draughtboard->_colorD[1]));
    _colorDGEdit->setVisible(false);
    _colorDBEdit = new QLineEdit(QString::number(draughtboard->_colorD[2]));
    _colorDBEdit->setVisible(false);

    _colorDRender = new QLabel;
    _colorDRender->setFixedSize(50, 20);
    QPixmap colorPixmap(50, 20);
    colorPixmap.fill(QColor(_colorDREdit->text().toDouble()*255, _colorDGEdit->text().toDouble()*255, _colorDBEdit->text().toDouble()*255));
    _colorDRender->setPixmap(colorPixmap);
    _paletteDButton = new QPushButton("Palette", this);
    _paletteDButton->setFixedWidth(100);
    connect(_paletteDButton, SIGNAL(clicked()), this, SLOT(browseDPalette()));
    QHBoxLayout* colorLayout = new QHBoxLayout;
    colorLayout->setAlignment(Qt::AlignLeft);
    colorLayout->addWidget(_colorDRender);
    colorLayout->addWidget(_paletteDButton);
    QGroupBox* colorGroupBox = new QGroupBox("Other color", this);
    colorGroupBox->setLayout(colorLayout);

    _caseSize = new QLineEdit(QString::number(draughtboard->_caseSize), this);
    _caseSize->setFixedWidth(50);
    QFormLayout* caseSizeLayout = new QFormLayout;
    caseSizeLayout->addRow("Value:", _caseSize);
    QGroupBox* caseSizeGroupBox = new QGroupBox("Cases size", this);
    caseSizeGroupBox->setLayout(caseSizeLayout);

    _mainLayout->addWidget(colorGroupBox);
    _mainLayout->addWidget(caseSizeGroupBox);
}

Color UpdateDraughtboard::getColorD() const {
    return Color(_colorDREdit->text().toDouble(),
                 _colorDGEdit->text().toDouble(),
                 _colorDBEdit->text().toDouble()
           );
}

double UpdateDraughtboard::getCaseSize() const {
    return _caseSize->text().toDouble();
}

void UpdateDraughtboard::browseDPalette() {
    QColor colorSelected = QColorDialog::getColor(QColor(_colorDREdit->text().toDouble()*255, _colorDGEdit->text().toDouble()*255, _colorDBEdit->text().toDouble()*255), this);

    QLabel label("");
    label.setNum(colorSelected.red() / 255.0);
    _colorDREdit->setText(label.text());
    label.setNum(colorSelected.green() / 255.0);
    _colorDGEdit->setText(label.text());
    label.setNum(colorSelected.blue() / 255.0);
    _colorDBEdit->setText(label.text());

    QPixmap colorPixmap(50, 20);
    colorPixmap.fill(colorSelected);
    _colorDRender->setPixmap(colorPixmap);
}



UpdateCylindre::UpdateCylindre(Cylindre* cylindre, QWidget* parent) :
    UpdateShape(cylindre, parent) {

    _bottomCenterXEdit = new QLineEdit(QString::number(cylindre->_bottomCenter[0]), this);
    _bottomCenterXEdit->setFixedWidth(50);
    _bottomCenterYEdit = new QLineEdit(QString::number(cylindre->_bottomCenter[1]), this);
    _bottomCenterYEdit->setFixedWidth(50);
    _bottomCenterZEdit = new QLineEdit(QString::number(cylindre->_bottomCenter[2]), this);
    _bottomCenterZEdit->setFixedWidth(50);
    QFormLayout* bottomCenterXLayout = new QFormLayout;
    bottomCenterXLayout->addRow("X:", _bottomCenterXEdit);
    QFormLayout* bottomCenterYLayout = new QFormLayout;
    bottomCenterYLayout->addRow("Y:", _bottomCenterYEdit);
    QFormLayout* bottomCenterZLayout = new QFormLayout;
    bottomCenterZLayout->addRow("Z:", _bottomCenterZEdit);
    QHBoxLayout* bottomCenterLayout = new QHBoxLayout;
    bottomCenterLayout->addLayout(bottomCenterXLayout);
    bottomCenterLayout->addLayout(bottomCenterYLayout);
    bottomCenterLayout->addLayout(bottomCenterZLayout);
    QGroupBox* bottomCenterGroupBox = new QGroupBox("Bottom center", this);
    bottomCenterGroupBox->setFixedWidth(250);
    bottomCenterGroupBox->setLayout(bottomCenterLayout);

    _lengthEdit = new QLineEdit(QString::number(cylindre->_length), this);
    _lengthEdit->setFixedWidth(50);
    QFormLayout* lengthLayout = new QFormLayout;
    lengthLayout->addRow("Value:", _lengthEdit);
    QGroupBox* lengthGroupBox = new QGroupBox("Length", this);
    lengthGroupBox->setLayout(lengthLayout);

    _radiusEdit = new QLineEdit(QString::number(cylindre->_radius), this);
    _radiusEdit->setFixedWidth(50);
    QFormLayout* radiusLayout = new QFormLayout;
    radiusLayout->addRow("Value:", _radiusEdit);
    QGroupBox* radiusGroupBox = new QGroupBox("Radius", this);
    radiusGroupBox->setLayout(radiusLayout);

    _mainLayout->addWidget(bottomCenterGroupBox);
    _mainLayout->addWidget(lengthGroupBox);
    _mainLayout->addWidget(radiusGroupBox);
}

Vector3 UpdateCylindre::getbottomCenter() const {
    return Vector3(_bottomCenterXEdit->text().toDouble(),
                   _bottomCenterYEdit->text().toDouble(),
                   _bottomCenterZEdit->text().toDouble()
           );
}

double UpdateCylindre::getLength() const {
    return _lengthEdit->text().toDouble();
}

double UpdateCylindre::getRadius() const {
    return _radiusEdit->text().toDouble();
}



UpdateSurface::UpdateSurface(Surface* surface, QWidget* parent) :
    UpdateShape(surface, parent) {

    _equation1Edit = new QLineEdit(surface->_equation1);
    _equation1Edit->setFixedWidth(400);
    _equation2Edit = new QLineEdit(surface->_equation2);
    _equation2Edit->setFixedWidth(400);
    _equation3Edit = new QLineEdit(surface->_equation3);
    _equation3Edit->setFixedWidth(400);
    _equation4Edit = new QLineEdit(surface->_equation4);
    _equation4Edit->setFixedWidth(400);
    QFormLayout* equation1Layout = new QFormLayout;
    equation1Layout->addRow("Equation #1:", _equation1Edit);
    QFormLayout* equation2Layout = new QFormLayout;
    equation2Layout->addRow("Equation #2:", _equation2Edit);
    QFormLayout* equation3Layout = new QFormLayout;
    equation3Layout->addRow("Equation #3:", _equation3Edit);
    QFormLayout* equation4Layout = new QFormLayout;
    equation4Layout->addRow("Equation #4:", _equation4Edit);
    QVBoxLayout* equationsLayout = new QVBoxLayout;
    equationsLayout->addLayout(equation1Layout);
    equationsLayout->addLayout(equation2Layout);
    equationsLayout->addLayout(equation3Layout);
    equationsLayout->addLayout(equation4Layout);
    QGroupBox* equationsGroupBox = new QGroupBox("Equations", this);
    equationsGroupBox->setFixedWidth(600);
    equationsGroupBox->setLayout(equationsLayout);

    _mainLayout->addWidget(equationsGroupBox);
}

QStringList UpdateSurface::getEquations() const {
    QStringList equations;
    equations << _equation1Edit->text()
              << _equation2Edit->text()
              << _equation3Edit->text()
              << _equation4Edit->text();
    return equations;
}



UpdateQuadric::UpdateQuadric(Quadrics* quadric, QWidget* parent) :
    UpdateShape(quadric, parent) {

    _aEdit = new QLineEdit(QString::number(quadric->_a));
    _aEdit->setFixedWidth(50);
    _bEdit = new QLineEdit(QString::number(quadric->_b));
    _bEdit->setFixedWidth(50);
    _cEdit = new QLineEdit(QString::number(quadric->_c));
    _cEdit->setFixedWidth(50);
    _dEdit = new QLineEdit(QString::number(quadric->_d));
    _dEdit->setFixedWidth(50);
    _eEdit = new QLineEdit(QString::number(quadric->_e));
    _eEdit->setFixedWidth(50);
    _fEdit = new QLineEdit(QString::number(quadric->_f));
    _fEdit->setFixedWidth(50);
    _gEdit = new QLineEdit(QString::number(quadric->_g));
    _gEdit->setFixedWidth(50);
    _hEdit = new QLineEdit(QString::number(quadric->_h));
    _hEdit->setFixedWidth(50);
    _iEdit = new QLineEdit(QString::number(quadric->_i));
    _iEdit->setFixedWidth(50);
    _jEdit = new QLineEdit(QString::number(quadric->_j));
    _jEdit->setFixedWidth(50);
    QFormLayout* aLayout = new QFormLayout;
    aLayout->addRow("a:", _aEdit);
    QFormLayout* bLayout = new QFormLayout;
    bLayout->addRow("b:", _bEdit);
    QFormLayout* cLayout = new QFormLayout;
    cLayout->addRow("c:", _cEdit);
    QFormLayout* dLayout = new QFormLayout;
    dLayout->addRow("d:", _dEdit);
    QFormLayout* eLayout = new QFormLayout;
    eLayout->addRow("e:", _eEdit);
    QFormLayout* fLayout = new QFormLayout;
    fLayout->addRow("f:", _fEdit);
    QFormLayout* gLayout = new QFormLayout;
    gLayout->addRow("g:", _gEdit);
    QFormLayout* hLayout = new QFormLayout;
    hLayout->addRow("h:", _hEdit);
    QFormLayout* iLayout = new QFormLayout;
    iLayout->addRow("i:", _iEdit);
    QFormLayout* jLayout = new QFormLayout;
    jLayout->addRow("j:", _jEdit);

    QHBoxLayout* abcLayout = new QHBoxLayout;
    abcLayout->addLayout(aLayout);
    abcLayout->addLayout(bLayout);
    abcLayout->addLayout(cLayout);
    QGroupBox* abcGroupBox = new QGroupBox("Square terms", this);
    abcGroupBox->setFixedWidth(250);
    abcGroupBox->setLayout(abcLayout);

    QHBoxLayout* defLayout = new QHBoxLayout;
    defLayout->addLayout(dLayout);
    defLayout->addLayout(eLayout);
    defLayout->addLayout(fLayout);
    QGroupBox* defGroupBox = new QGroupBox("Quadratic terms", this);
    defGroupBox->setFixedWidth(250);
    defGroupBox->setLayout(defLayout);

    QHBoxLayout* ghijLayout = new QHBoxLayout;
    ghijLayout->addLayout(gLayout);
    ghijLayout->addLayout(hLayout);
    ghijLayout->addLayout(iLayout);
    ghijLayout->addLayout(jLayout);
    ghijLayout->setAlignment(Qt::AlignLeft);
    QGroupBox* ghijGroupBox = new QGroupBox("Linear terms", this);
    ghijGroupBox->setFixedWidth(330);
    ghijGroupBox->setLayout(ghijLayout);

    _mainLayout->addWidget(abcGroupBox);
    _mainLayout->addWidget(defGroupBox);
    _mainLayout->addWidget(ghijGroupBox);
}



UpdateImplicit::UpdateImplicit(ImplicitSurface* implicit, QWidget* parent) :
    UpdateShape(implicit, parent) {

    _equationEdit = new QLineEdit(implicit->_equation);
    _equationEdit->setFixedWidth(400);
    QFormLayout* equationLayout = new QFormLayout;
    equationLayout->addRow("Equation:", _equationEdit);
    QGroupBox* equationGroupBox = new QGroupBox("Equation", this);
    equationGroupBox->setFixedWidth(600);
    equationGroupBox->setLayout(equationLayout);

    _mainLayout->addWidget(equationGroupBox);
}

QString UpdateImplicit::getEquation() const {
    return _equationEdit->text();
}



UpdateBox::UpdateBox(Box* box, QWidget* parent) :
    UpdateShape(box, parent) {

    _x1Edit = new QLineEdit(QString::number(box->_bottomLeftFrontCorner[0]), this);
    _x1Edit->setFixedWidth(50);
    _y1Edit = new QLineEdit(QString::number(box->_bottomLeftFrontCorner[1]), this);
    _y1Edit->setFixedWidth(50);
    _z1Edit = new QLineEdit(QString::number(box->_bottomLeftFrontCorner[2]), this);
    _z1Edit->setFixedWidth(50);
    QFormLayout* centerX1Layout = new QFormLayout;
    centerX1Layout->addRow("X:", _x1Edit);
    QFormLayout* centerY1Layout = new QFormLayout;
    centerY1Layout->addRow("Y:", _y1Edit);
    QFormLayout* centerZ1Layout = new QFormLayout;
    centerZ1Layout->addRow("Z:", _z1Edit);
    QHBoxLayout* bLFPLayout = new QHBoxLayout;
    bLFPLayout->addLayout(centerX1Layout);
    bLFPLayout->addLayout(centerY1Layout);
    bLFPLayout->addLayout(centerZ1Layout);
    QGroupBox* bLFPGroupBox = new QGroupBox("Bottom left front point", this);
    bLFPGroupBox->setFixedWidth(250);
    bLFPGroupBox->setLayout(bLFPLayout);

    _x2Edit = new QLineEdit(QString::number(box->_topRightBackCorner[0]), this);
    _x2Edit->setFixedWidth(50);
    _y2Edit = new QLineEdit(QString::number(box->_topRightBackCorner[1]), this);
    _y2Edit->setFixedWidth(50);
    _z2Edit = new QLineEdit(QString::number(box->_topRightBackCorner[2]), this);
    _z2Edit->setFixedWidth(50);
    QFormLayout* centerX2Layout = new QFormLayout;
    centerX2Layout->addRow("X:", _x2Edit);
    QFormLayout* centerY2Layout = new QFormLayout;
    centerY2Layout->addRow("Y:", _y2Edit);
    QFormLayout* centerZ2Layout = new QFormLayout;
    centerZ2Layout->addRow("Z:", _z2Edit);
    QHBoxLayout* tRBPLayout = new QHBoxLayout;
    tRBPLayout->addLayout(centerX2Layout);
    tRBPLayout->addLayout(centerY2Layout);
    tRBPLayout->addLayout(centerZ2Layout);
    QGroupBox* tRBPGroupBox = new QGroupBox("Top right back point", this);
    tRBPGroupBox->setFixedWidth(250);
    tRBPGroupBox->setLayout(tRBPLayout);

    _mainLayout->addWidget(bLFPGroupBox);
    _mainLayout->addWidget(tRBPGroupBox);
}

Vector3 UpdateBox::getBLFC() const {
    return Vector3(_x1Edit->text().toDouble(),
                   _y1Edit->text().toDouble(),
                   _z1Edit->text().toDouble()
           );
}

Vector3 UpdateBox::getTRBC() const {
    return Vector3(_x2Edit->text().toDouble(),
                   _y2Edit->text().toDouble(),
                   _z2Edit->text().toDouble()
           );
}



UpdateTriangle::UpdateTriangle(Triangle* triangle, QWidget* parent) :
    UpdateShape(triangle, parent) {

    _x1Edit = new QLineEdit(QString::number(triangle->_point1[0]), this);
    _x1Edit->setFixedWidth(50);
    _y1Edit = new QLineEdit(QString::number(triangle->_point1[1]), this);
    _y1Edit->setFixedWidth(50);
    _z1Edit = new QLineEdit(QString::number(triangle->_point1[2]), this);
    _z1Edit->setFixedWidth(50);
    QFormLayout* centerX1Layout = new QFormLayout;
    centerX1Layout->addRow("X:", _x1Edit);
    QFormLayout* centerY1Layout = new QFormLayout;
    centerY1Layout->addRow("Y:", _y1Edit);
    QFormLayout* centerZ1Layout = new QFormLayout;
    centerZ1Layout->addRow("Z:", _z1Edit);
    QHBoxLayout* point1Layout = new QHBoxLayout;
    point1Layout->addLayout(centerX1Layout);
    point1Layout->addLayout(centerY1Layout);
    point1Layout->addLayout(centerZ1Layout);
    QGroupBox* point1GroupBox = new QGroupBox("Point #1", this);
    point1GroupBox->setFixedWidth(250);
    point1GroupBox->setLayout(point1Layout);

    _x2Edit = new QLineEdit(QString::number(triangle->_point2[0]), this);
    _x2Edit->setFixedWidth(50);
    _y2Edit = new QLineEdit(QString::number(triangle->_point2[1]), this);
    _y2Edit->setFixedWidth(50);
    _z2Edit = new QLineEdit(QString::number(triangle->_point2[2]), this);
    _z2Edit->setFixedWidth(50);
    QFormLayout* centerX2Layout = new QFormLayout;
    centerX2Layout->addRow("X:", _x2Edit);
    QFormLayout* centerY2Layout = new QFormLayout;
    centerY2Layout->addRow("Y:", _y2Edit);
    QFormLayout* centerZ2Layout = new QFormLayout;
    centerZ2Layout->addRow("Z:", _z2Edit);
    QHBoxLayout* point2Layout = new QHBoxLayout;
    point2Layout->addLayout(centerX2Layout);
    point2Layout->addLayout(centerY2Layout);
    point2Layout->addLayout(centerZ2Layout);
    QGroupBox* point2GroupBox = new QGroupBox("Point #2", this);
    point2GroupBox->setFixedWidth(250);
    point2GroupBox->setLayout(point2Layout);

    _x3Edit = new QLineEdit(QString::number(triangle->_point3[0]), this);
    _x3Edit->setFixedWidth(50);
    _y3Edit = new QLineEdit(QString::number(triangle->_point3[1]), this);
    _y3Edit->setFixedWidth(50);
    _z3Edit = new QLineEdit(QString::number(triangle->_point3[2]), this);
    _z3Edit->setFixedWidth(50);
    QFormLayout* centerX3Layout = new QFormLayout;
    centerX3Layout->addRow("X:", _x3Edit);
    QFormLayout* centerY3Layout = new QFormLayout;
    centerY3Layout->addRow("Y:", _y3Edit);
    QFormLayout* centerZ3Layout = new QFormLayout;
    centerZ3Layout->addRow("Z:", _z3Edit);
    QHBoxLayout* point3Layout = new QHBoxLayout;
    point3Layout->addLayout(centerX3Layout);
    point3Layout->addLayout(centerY3Layout);
    point3Layout->addLayout(centerZ3Layout);
    QGroupBox* point3GroupBox = new QGroupBox("Point #3", this);
    point3GroupBox->setFixedWidth(250);
    point3GroupBox->setLayout(point3Layout);

    _mainLayout->addWidget(point1GroupBox);
    _mainLayout->addWidget(point2GroupBox);
    _mainLayout->addWidget(point3GroupBox);
}

Vector3 UpdateTriangle::getPoint1() const {
    return Vector3(_x1Edit->text().toDouble(),
                   _y1Edit->text().toDouble(),
                   _z1Edit->text().toDouble()
           );
}

Vector3 UpdateTriangle::getPoint2() const {
    return Vector3(_x2Edit->text().toDouble(),
                   _y2Edit->text().toDouble(),
                   _z2Edit->text().toDouble()
           );
}

Vector3 UpdateTriangle::getPoint3() const {
    return Vector3(_x3Edit->text().toDouble(),
                   _y3Edit->text().toDouble(),
                   _z3Edit->text().toDouble()
           );
}



UpdateTorus::UpdateTorus(Torus* torus, QWidget* parent) :
    UpdateShape(torus, parent) {

    _ringRadiusEdit = new QLineEdit(QString::number(torus->_ringRadius), this);
    _ringRadiusEdit->setFixedWidth(50);
    QFormLayout* ringRadiusLayout = new QFormLayout;
    ringRadiusLayout->addRow("Value:", _ringRadiusEdit);
    QGroupBox* ringRadiusGroupBox = new QGroupBox("Ring radius", this);
    ringRadiusGroupBox->setLayout(ringRadiusLayout);

    _crossRadiusEdit = new QLineEdit(QString::number(torus->_crossRadius), this);
    _crossRadiusEdit->setFixedWidth(50);
    QFormLayout* crossRadiusLayout = new QFormLayout;
    crossRadiusLayout->addRow("Value:", _crossRadiusEdit);
    QGroupBox* crossRadiusGroupBox = new QGroupBox("Cross radius", this);
    crossRadiusGroupBox->setLayout(crossRadiusLayout);

    _mainLayout->addWidget(ringRadiusGroupBox);
    _mainLayout->addWidget(crossRadiusGroupBox);
}

double UpdateTorus::getRingRadius() const {
    return _ringRadiusEdit->text().toDouble();
}

double UpdateTorus::getCrossRadius() const {
    return _crossRadiusEdit->text().toDouble();
}



UpdateDisk::UpdateDisk(Disk* disk, QWidget* parent) :
    UpdatePlane(disk, parent) {

    _radiusEdit = new QLineEdit(QString::number(disk->_radius), this);
    _radiusEdit->setFixedWidth(50);
    QFormLayout* radiusLayout = new QFormLayout;
    radiusLayout->addRow("Value:", _radiusEdit);
    QGroupBox* radiusGroupBox = new QGroupBox("Radius", this);
    radiusGroupBox->setFixedWidth(250);
    radiusGroupBox->setLayout(radiusLayout);

    _mainLayout->addWidget(radiusGroupBox);
}

double UpdateDisk::getRadius() const {
    return _radiusEdit->text().toDouble();
}
