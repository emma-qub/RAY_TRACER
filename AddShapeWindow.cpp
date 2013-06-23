#include "AddShapeWindow.h"

AddShapeWindow::AddShapeWindow(QWidget* parent) :
    QWizard(parent) {

    setPage(chooseShapeTypePage, new ChooseShapeTypePage);
    setPage(addShapePage, new AddShapePage);
    setPage(addSpherePage, new AddSpherePage);
    setPage(addPlanePage, new AddPlanePage);
    setPage(addRectanglePage, new AddRectanglePage);
    setPage(addDraughtboardPage, new AddDraughtboardPage);
    setPage(addCylindrePage, new AddCylindrePage);
    setPage(addSurfacePage, new AddSurfacePage);
    setPage(addQuadricPage, new AddQuadricPage);
    setPage(addImplicitPage, new AddImplicitPage);
    setPage(addBoxPage, new AddBoxPage);
    setPage(addTrianglePage, new AddTrianglePage);
    setPage(addTorusPage, new AddTorusPage);
    setPage(addDiskPage, new AddDiskPage);

    setStartId(chooseShapeTypePage);

    setOption(QWizard::IndependentPages);

#ifndef Q_WS_MAC
     setWizardStyle(ModernStyle);
 #endif

     setWindowTitle("Add a shape");
}



ChooseShapeTypePage::ChooseShapeTypePage(QWidget* parent) :
    QWizardPage(parent) {

    setTitle("Add a shape");

    _topLabel = new QLabel("Choose a shape in the list below:");
    _shapesTypeList = new QComboBox;
    _shapesTypeList->addItem("Sphere");
    _shapesTypeList->addItem("Plane");
    _shapesTypeList->addItem("Rectangle");
    _shapesTypeList->addItem("Draughtboard");
    _shapesTypeList->addItem("Cylindre");
    _shapesTypeList->addItem("Surface");
    _shapesTypeList->addItem("Quadric");
    _shapesTypeList->addItem("Implicit");
    _shapesTypeList->addItem("Box");
    _shapesTypeList->addItem("Triangle");
    _shapesTypeList->addItem("Torus");
    _shapesTypeList->addItem("Disk");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(_topLabel);
    mainLayout->addWidget(_shapesTypeList);
    setLayout(mainLayout);

    registerField("shapeType", _shapesTypeList);
}

int ChooseShapeTypePage::nextId() const {
    if (field("shapeType").toString() == "0")
        return AddShapeWindow::addSpherePage;
    else if (field("shapeType").toString() == "1")
        return AddShapeWindow::addPlanePage;
    else if (field("shapeType").toString() == "2")
        return AddShapeWindow::addRectanglePage;
    else if (field("shapeType").toString() == "3")
        return AddShapeWindow::addDraughtboardPage;
    else if (field("shapeType").toString() == "4")
        return AddShapeWindow::addCylindrePage;
    else if (field("shapeType").toString() == "5")
        return AddShapeWindow::addSurfacePage;
    else if (field("shapeType").toString() == "6")
        return AddShapeWindow::addQuadricPage;
    else if (field("shapeType").toString() == "7")
        return AddShapeWindow::addImplicitPage;
    else if (field("shapeType").toString() == "8")
        return AddShapeWindow::addBoxPage;
    else if (field("shapeType").toString() == "9")
        return AddShapeWindow::addTrianglePage;
    else if (field("shapeType").toString() == "10")
        return AddShapeWindow::addTorusPage;
    else if (field("shapeType").toString() == "11")
        return AddShapeWindow::addDiskPage;
    return -1;
}



AddShapePage::AddShapePage(QWidget* parent) :
    QWizardPage(parent) {

    QLabel label("0.0");
    _colorREdit = new QLineEdit(label.text());
    _colorREdit->setVisible(false);
    _colorGEdit = new QLineEdit(label.text());
    _colorGEdit->setVisible(false);
    _colorBEdit = new QLineEdit(label.text());
    _colorBEdit->setVisible(false);

    _colorRender = new QLabel;
    _colorRender->setFixedSize(50, 20);
    QPixmap colorPixmap(50, 20);
    colorPixmap.fill(Qt::black);
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

    _materialKAEdit = new QLineEdit("0.3", this);
    _materialKAEdit->setFixedWidth(50);
    _materialKDEdit = new QLineEdit("0.7", this);
    _materialKDEdit->setFixedWidth(50);
    _materialKSEdit = new QLineEdit("0.3", this);
    _materialKSEdit->setFixedWidth(50);
    _materialNSEdit = new QLineEdit("80", this);
    _materialNSEdit->setFixedWidth(50);
    _materialKReflexEdit = new QLineEdit("0.3", this);
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

    setLayout(_mainLayout);
}

void AddShapePage::browsePalette() {
    QColor colorSelected = QColorDialog::getColor(Qt::black, this);

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



AddSpherePage::AddSpherePage(QWidget* parent) :
    AddShapePage(parent) {

    setTitle("New Sphere");
    setSubTitle("Set every field to create a new sphere.");

    _centerOnlyXEdit = new QLineEdit("0", this);
    _centerOnlyXEdit->setFixedWidth(50);
    _centerOnlyYEdit = new QLineEdit("0", this);
    _centerOnlyYEdit->setFixedWidth(50);
    _centerOnlyZEdit = new QLineEdit("0", this);
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

    _radiusEdit = new QLineEdit("4", this);
    _radiusEdit->setFixedWidth(50);
    QFormLayout* radiusLayout = new QFormLayout;
    radiusLayout->addRow("Value:", _radiusEdit);
    QGroupBox* radiusGroupBox = new QGroupBox("Radius", this);
    radiusGroupBox->setLayout(radiusLayout);

    _mainLayout->addWidget(centerGroupBox);
    _mainLayout->addWidget(radiusGroupBox);
}

int AddSpherePage::nextId() const {
    return -1;
}

void AddSpherePage::initializePage() {
    registerField("s_colorR", _colorREdit);
    registerField("s_colorG", _colorGEdit);
    registerField("s_colorB", _colorBEdit);
    registerField("s_materialKA", _materialKAEdit);
    registerField("s_materialKD", _materialKDEdit);
    registerField("s_materialKS", _materialKSEdit);
    registerField("s_materialNS", _materialNSEdit);
    registerField("s_materialKReflex", _materialKReflexEdit);
    registerField("s_centerOnlyX", _centerOnlyXEdit);
    registerField("s_centerOnlyY", _centerOnlyYEdit);
    registerField("s_centerOnlyZ", _centerOnlyZEdit);
    registerField("s_radius", _radiusEdit);
}



AddPlanePage::AddPlanePage(QWidget* parent) :
    AddShapePage(parent) {

    setTitle("New plane");
    setSubTitle("Set every field to create a new plane.");

    _centerXEdit = new QLineEdit("0", this);
    _centerXEdit->setFixedWidth(50);
    _centerYEdit = new QLineEdit("0", this);
    _centerYEdit->setFixedWidth(50);
    _centerZEdit = new QLineEdit("0", this);
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

    _normalXEdit = new QLineEdit("0", this);
    _normalXEdit->setFixedWidth(50);
    _normalYEdit = new QLineEdit("0", this);
    _normalYEdit->setFixedWidth(50);
    _normalZEdit = new QLineEdit("0", this);
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

int AddPlanePage::nextId() const {
    return -1;
}

void AddPlanePage::initializePage() {
    registerField("p_colorR", _colorREdit);
    registerField("p_colorG", _colorGEdit);
    registerField("p_colorB", _colorBEdit);
    registerField("p_materialKA", _materialKAEdit);
    registerField("p_materialKD", _materialKDEdit);
    registerField("p_materialKS", _materialKSEdit);
    registerField("p_materialNS", _materialNSEdit);
    registerField("p_materialKReflex", _materialKReflexEdit);
    registerField("p_centerX", _centerXEdit);
    registerField("p_centerY", _centerYEdit);
    registerField("p_centerZ", _centerZEdit);
    registerField("p_normalX", _normalXEdit);
    registerField("p_normalY", _normalYEdit);
    registerField("p_normalZ", _normalZEdit);
}



AddRectanglePage::AddRectanglePage(QWidget* parent) :
    AddPlanePage(parent) {

    setTitle("New rectangle");
    setSubTitle("Set every field to create a new rectangle.");

    _widthEdit = new QLineEdit;
    _widthEdit->setFixedWidth(50);
    _heightEdit = new QLineEdit;
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

int AddRectanglePage::nextId() const {
    return -1;
}

void AddRectanglePage::initializePage() {
    registerField("r_colorR", _colorREdit);
    registerField("r_colorG", _colorGEdit);
    registerField("r_colorB", _colorBEdit);
    registerField("r_materialKA", _materialKAEdit);
    registerField("r_materialKD", _materialKDEdit);
    registerField("r_materialKS", _materialKSEdit);
    registerField("r_materialNS", _materialNSEdit);
    registerField("r_materialKReflex", _materialKReflexEdit);
    registerField("r_centerX", _centerXEdit);
    registerField("r_centerY", _centerYEdit);
    registerField("r_centerZ", _centerZEdit);
    registerField("r_normalX", _normalXEdit);
    registerField("r_normalY", _normalYEdit);
    registerField("r_normalZ", _normalZEdit);
    registerField("r_width*", _widthEdit);
    registerField("r_height*", _heightEdit);
}



AddDraughtboardPage::AddDraughtboardPage(QWidget* parent) :
    AddRectanglePage(parent) {

    setTitle("New draughtboard");
    setSubTitle("Set every field to create a new draughtboard.");

    QLabel label("1.0");
    _colorDREdit = new QLineEdit(label.text());
    _colorDREdit->setVisible(false);
    _colorDGEdit = new QLineEdit(label.text());
    _colorDGEdit->setVisible(false);
    _colorDBEdit = new QLineEdit(label.text());
    _colorDBEdit->setVisible(false);

    _colorDRender = new QLabel;
    _colorDRender->setFixedSize(50, 20);
    QPixmap colorPixmap(50, 20);
    colorPixmap.fill(Qt::white);
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

    _caseSize = new QLineEdit("4", this);
    _caseSize->setFixedWidth(50);
    QFormLayout* caseSizeLayout = new QFormLayout;
    caseSizeLayout->addRow("Value:", _caseSize);
    QGroupBox* caseSizeGroupBox = new QGroupBox("Cases size", this);
    caseSizeGroupBox->setLayout(caseSizeLayout);

    _mainLayout->addWidget(colorGroupBox);
    _mainLayout->addWidget(caseSizeGroupBox);
}

int AddDraughtboardPage::nextId() const {
    return -1;
}

void AddDraughtboardPage::initializePage() {
    registerField("d_colorR", _colorREdit);
    registerField("d_colorG", _colorGEdit);
    registerField("d_colorB", _colorBEdit);
    registerField("d_materialKA", _materialKAEdit);
    registerField("d_materialKD", _materialKDEdit);
    registerField("d_materialKS", _materialKSEdit);
    registerField("d_materialNS", _materialNSEdit);
    registerField("d_materialKReflex", _materialKReflexEdit);
    registerField("d_centerX", _centerXEdit);
    registerField("d_centerY", _centerYEdit);
    registerField("d_centerZ", _centerZEdit);
    registerField("d_normalX", _normalXEdit);
    registerField("d_normalY", _normalYEdit);
    registerField("d_normalZ", _normalZEdit);
    registerField("d_width*", _widthEdit);
    registerField("d_height*", _heightEdit);
    registerField("d_colorDR", _colorDREdit);
    registerField("d_colorDG", _colorDGEdit);
    registerField("d_colorDB", _colorDBEdit);
    registerField("d_caseSize", _caseSize);
}

void AddDraughtboardPage::browseDPalette() {
    QColor colorSelected = QColorDialog::getColor(Qt::white, this);

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



AddCylindrePage::AddCylindrePage(QWidget* parent) :
    AddShapePage(parent) {

    setTitle("New Cylindre");
    setSubTitle("Set every field to create a new cylindre.");

    _bottomCenterXEdit = new QLineEdit("0", this);
    _bottomCenterXEdit->setFixedWidth(50);
    _bottomCenterYEdit = new QLineEdit("0", this);
    _bottomCenterYEdit->setFixedWidth(50);
    _bottomCenterZEdit = new QLineEdit("0", this);
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

    _lengthEdit = new QLineEdit("10", this);
    _lengthEdit->setFixedWidth(50);
    QFormLayout* lengthLayout = new QFormLayout;
    lengthLayout->addRow("Value:", _lengthEdit);
    QGroupBox* lengthGroupBox = new QGroupBox("Length", this);
    lengthGroupBox->setLayout(lengthLayout);

    _radiusEdit = new QLineEdit("4", this);
    _radiusEdit->setFixedWidth(50);
    QFormLayout* radiusLayout = new QFormLayout;
    radiusLayout->addRow("Value:", _radiusEdit);
    QGroupBox* radiusGroupBox = new QGroupBox("Radius", this);
    radiusGroupBox->setLayout(radiusLayout);

    _mainLayout->addWidget(bottomCenterGroupBox);
    _mainLayout->addWidget(lengthGroupBox);
    _mainLayout->addWidget(radiusGroupBox);
}

int AddCylindrePage::nextId() const {
    return -1;
}

void AddCylindrePage::initializePage() {
    registerField("c_colorR", _colorREdit);
    registerField("c_colorG", _colorGEdit);
    registerField("c_colorB", _colorBEdit);
    registerField("c_materialKA", _materialKAEdit);
    registerField("c_materialKD", _materialKDEdit);
    registerField("c_materialKS", _materialKSEdit);
    registerField("c_materialNS", _materialNSEdit);
    registerField("c_materialKReflex", _materialKReflexEdit);
    registerField("c_bottomCenterX", _bottomCenterXEdit);
    registerField("c_bottomCenterY", _bottomCenterYEdit);
    registerField("c_bottomCenterZ", _bottomCenterZEdit);
    registerField("c_length", _lengthEdit);
    registerField("c_radius", _radiusEdit);
}



AddSurfacePage::AddSurfacePage(QWidget* parent) :
    AddShapePage(parent) {

    setTitle("New Parametrized Surface");
    setSubTitle("Set every field to create a new parametrized surface.");

    //_equation1Edit = new QLineEdit("x^2-y^2-z^2");
    _equation1Edit = new QLineEdit("xy");
    _equation1Edit->setFixedWidth(400);
    //_equation2Edit = new QLineEdit("2xz");
    _equation2Edit = new QLineEdit("yz");
    _equation2Edit->setFixedWidth(400);
    //_equation3Edit = new QLineEdit("2xy");
    _equation3Edit = new QLineEdit("xz");
    _equation3Edit->setFixedWidth(400);
    _equation4Edit = new QLineEdit("x^2+y^2+z^2");
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

int AddSurfacePage::nextId() const {
    return -1;
}

void AddSurfacePage::initializePage() {
    registerField("su_colorR", _colorREdit);
    registerField("su_colorG", _colorGEdit);
    registerField("su_colorB", _colorBEdit);
    registerField("su_materialKA", _materialKAEdit);
    registerField("su_materialKD", _materialKDEdit);
    registerField("su_materialKS", _materialKSEdit);
    registerField("su_materialNS", _materialNSEdit);
    registerField("su_materialKReflex", _materialKReflexEdit);
    registerField("su_equation1", _equation1Edit);
    registerField("su_equation2", _equation2Edit);
    registerField("su_equation3", _equation3Edit);
    registerField("su_equation4", _equation4Edit);
}



AddQuadricPage::AddQuadricPage(QWidget* parent) :
    AddShapePage(parent) {

    setTitle("New Quadric");
    setSubTitle("Set every field to create a new quadric.");

    _aEdit = new QLineEdit("0");
    _aEdit->setFixedWidth(50);
    _bEdit = new QLineEdit("0");
    _bEdit->setFixedWidth(50);
    _cEdit = new QLineEdit("0");
    _cEdit->setFixedWidth(50);
    _dEdit = new QLineEdit("0");
    _dEdit->setFixedWidth(50);
    _eEdit = new QLineEdit("0");
    _eEdit->setFixedWidth(50);
    _fEdit = new QLineEdit("0");
    _fEdit->setFixedWidth(50);
    _gEdit = new QLineEdit("0");
    _gEdit->setFixedWidth(50);
    _hEdit = new QLineEdit("0");
    _hEdit->setFixedWidth(50);
    _iEdit = new QLineEdit("0");
    _iEdit->setFixedWidth(50);
    _jEdit = new QLineEdit("0");
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

int AddQuadricPage::nextId() const {
    return -1;
}

void AddQuadricPage::initializePage() {
    registerField("q_colorR", _colorREdit);
    registerField("q_colorG", _colorGEdit);
    registerField("q_colorB", _colorBEdit);
    registerField("q_materialKA", _materialKAEdit);
    registerField("q_materialKD", _materialKDEdit);
    registerField("q_materialKS", _materialKSEdit);
    registerField("q_materialNS", _materialNSEdit);
    registerField("q_materialKReflex", _materialKReflexEdit);
    registerField("q_a", _aEdit);
    registerField("q_b", _bEdit);
    registerField("q_c", _cEdit);
    registerField("q_d", _dEdit);
    registerField("q_e", _eEdit);
    registerField("q_f", _fEdit);
    registerField("q_g", _gEdit);
    registerField("q_h", _hEdit);
    registerField("q_i", _iEdit);
    registerField("q_j", _jEdit);
}



AddImplicitPage::AddImplicitPage(QWidget* parent) :
    AddShapePage(parent) {

    setTitle("New Implicit Surface");
    setSubTitle("Set every field to create a new implicit surface.");

    _equationEdit = new QLineEdit("x^2+y^2+z^2");
    _equationEdit->setFixedWidth(400);
    QFormLayout* equationLayout = new QFormLayout;
    equationLayout->addRow("Equation:", _equationEdit);
    QGroupBox* equationsGroupBox = new QGroupBox("Equation", this);
    equationsGroupBox->setFixedWidth(600);
    equationsGroupBox->setLayout(equationLayout);

    _mainLayout->addWidget(equationsGroupBox);
}

int AddImplicitPage::nextId() const {
    return -1;
}

void AddImplicitPage::initializePage() {
    registerField("i_colorR", _colorREdit);
    registerField("i_colorG", _colorGEdit);
    registerField("i_colorB", _colorBEdit);
    registerField("i_materialKA", _materialKAEdit);
    registerField("i_materialKD", _materialKDEdit);
    registerField("i_materialKS", _materialKSEdit);
    registerField("i_materialNS", _materialNSEdit);
    registerField("i_materialKReflex", _materialKReflexEdit);
    registerField("i_equation", _equationEdit);
}



AddBoxPage::AddBoxPage(QWidget* parent) :
    AddShapePage(parent) {

    setTitle("New box");
    setSubTitle("Set every field to create a new box.");

    _x1Edit = new QLineEdit("-1", this);
    _x1Edit->setFixedWidth(50);
    _y1Edit = new QLineEdit("-1", this);
    _y1Edit->setFixedWidth(50);
    _z1Edit = new QLineEdit("-1", this);
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

    _x2Edit = new QLineEdit("1", this);
    _x2Edit->setFixedWidth(50);
    _y2Edit = new QLineEdit("1", this);
    _y2Edit->setFixedWidth(50);
    _z2Edit = new QLineEdit("1", this);
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

int AddBoxPage::nextId() const {
    return -1;
}

void AddBoxPage::initializePage() {
    registerField("b_colorR", _colorREdit);
    registerField("b_colorG", _colorGEdit);
    registerField("b_colorB", _colorBEdit);
    registerField("b_materialKA", _materialKAEdit);
    registerField("b_materialKD", _materialKDEdit);
    registerField("b_materialKS", _materialKSEdit);
    registerField("b_materialNS", _materialNSEdit);
    registerField("b_materialKReflex", _materialKReflexEdit);
    registerField("b_x1", _x1Edit);
    registerField("b_y1", _y1Edit);
    registerField("b_z1", _z1Edit);
    registerField("b_x2", _x2Edit);
    registerField("b_y2", _y2Edit);
    registerField("b_z2", _z2Edit);
}



AddTrianglePage::AddTrianglePage(QWidget* parent) :
    AddShapePage(parent) {

    setTitle("New triangle");
    setSubTitle("Set every field to create a new triangle.");

    _x1Edit = new QLineEdit("0", this);
    _x1Edit->setFixedWidth(50);
    _y1Edit = new QLineEdit("0", this);
    _y1Edit->setFixedWidth(50);
    _z1Edit = new QLineEdit("0", this);
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

    _x2Edit = new QLineEdit("0", this);
    _x2Edit->setFixedWidth(50);
    _y2Edit = new QLineEdit("0", this);
    _y2Edit->setFixedWidth(50);
    _z2Edit = new QLineEdit("1", this);
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

    _x3Edit = new QLineEdit("1", this);
    _x3Edit->setFixedWidth(50);
    _y3Edit = new QLineEdit("0", this);
    _y3Edit->setFixedWidth(50);
    _z3Edit = new QLineEdit("0", this);
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

int AddTrianglePage::nextId() const {
    return -1;
}

void AddTrianglePage::initializePage() {
    registerField("t_colorR", _colorREdit);
    registerField("t_colorG", _colorGEdit);
    registerField("t_colorB", _colorBEdit);
    registerField("t_materialKA", _materialKAEdit);
    registerField("t_materialKD", _materialKDEdit);
    registerField("t_materialKS", _materialKSEdit);
    registerField("t_materialNS", _materialNSEdit);
    registerField("t_materialKReflex", _materialKReflexEdit);
    registerField("t_x1", _x1Edit);
    registerField("t_y1", _y1Edit);
    registerField("t_z1", _z1Edit);
    registerField("t_x2", _x2Edit);
    registerField("t_y2", _y2Edit);
    registerField("t_z2", _z2Edit);
    registerField("t_x3", _x3Edit);
    registerField("t_y3", _y3Edit);
    registerField("t_z3", _z3Edit);
}



AddTorusPage::AddTorusPage(QWidget* parent) :
    AddShapePage(parent) {

    setTitle("New torus");
    setSubTitle("Set every field to create a new torus.");

    _ringRadiusEdit = new QLineEdit("10", this);
    _ringRadiusEdit->setFixedWidth(50);
    QFormLayout* ringRadiusLayout = new QFormLayout;
    ringRadiusLayout->addRow("Value:", _ringRadiusEdit);
    QGroupBox* ringRadiusGroupBox = new QGroupBox("Ring radius", this);
    ringRadiusGroupBox->setLayout(ringRadiusLayout);

    _crossRadiusEdit = new QLineEdit("4", this);
    _crossRadiusEdit->setFixedWidth(50);
    QFormLayout* crossRadiusLayout = new QFormLayout;
    crossRadiusLayout->addRow("Value:", _crossRadiusEdit);
    QGroupBox* crossRadiusGroupBox = new QGroupBox("Cross radius", this);
    crossRadiusGroupBox->setLayout(crossRadiusLayout);

    _mainLayout->addWidget(ringRadiusGroupBox);
    _mainLayout->addWidget(crossRadiusGroupBox);
}

int AddTorusPage::nextId() const {
    return -1;
}

void AddTorusPage::initializePage() {
    registerField("to_colorR", _colorREdit);
    registerField("to_colorG", _colorGEdit);
    registerField("to_colorB", _colorBEdit);
    registerField("to_materialKA", _materialKAEdit);
    registerField("to_materialKD", _materialKDEdit);
    registerField("to_materialKS", _materialKSEdit);
    registerField("to_materialNS", _materialNSEdit);
    registerField("to_materialKReflex", _materialKReflexEdit);
    registerField("to_ringRadius", _ringRadiusEdit);
    registerField("to_crossRadius", _crossRadiusEdit);
}



AddDiskPage::AddDiskPage(QWidget* parent) :
    AddPlanePage(parent) {

    setTitle("New disk");
    setSubTitle("Set every field to create a new disk.");

    _radiusEdit = new QLineEdit;
    _radiusEdit->setFixedWidth(50);
    QFormLayout* radiusLayout = new QFormLayout;
    radiusLayout->addRow("Value:", _radiusEdit);
    QGroupBox* radiusGroupBox = new QGroupBox("Radius", this);
    radiusGroupBox->setFixedWidth(250);
    radiusGroupBox->setLayout(radiusLayout);

    _mainLayout->addWidget(radiusGroupBox);
}

int AddDiskPage::nextId() const {
    return -1;
}

void AddDiskPage::initializePage() {
    registerField("di_colorR", _colorREdit);
    registerField("di_colorG", _colorGEdit);
    registerField("di_colorB", _colorBEdit);
    registerField("di_materialKA", _materialKAEdit);
    registerField("di_materialKD", _materialKDEdit);
    registerField("di_materialKS", _materialKSEdit);
    registerField("di_materialNS", _materialNSEdit);
    registerField("di_materialKReflex", _materialKReflexEdit);
    registerField("di_centerX", _centerXEdit);
    registerField("di_centerY", _centerYEdit);
    registerField("di_centerZ", _centerZEdit);
    registerField("di_normalX", _normalXEdit);
    registerField("di_normalY", _normalYEdit);
    registerField("di_normalZ", _normalZEdit);
    registerField("di_radius*", _radiusEdit);
}
