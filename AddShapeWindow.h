#ifndef ADDSHAPEWINDOW_H
#define ADDSHAPEWINDOW_H

#include <QWidget>
#include <QApplication>
#include <QtGui>

class AddShapeWindow : public QWizard {
    Q_OBJECT

public:
    enum {
        chooseShapeTypePage,
        addShapePage,
        addSpherePage,
        addPlanePage,
        addRectanglePage,
        addDraughtboardPage,
        addCylindrePage,
        addSurfacePage,
        addQuadricPage,
        addImplicitPage,
        addBoxPage,
        addTrianglePage,
        addTorusPage,
        addDiskPage
    };

    AddShapeWindow(QWidget* parent = 0);
};



class ChooseShapeTypePage : public QWizardPage {
    Q_OBJECT

public:
    ChooseShapeTypePage(QWidget* parent = 0);

    int nextId() const;

private:
    QLabel* _topLabel;
    QComboBox* _shapesTypeList;
};



class AddShapePage : public QWizardPage {
    Q_OBJECT

public:
    AddShapePage(QWidget* parent = 0);

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

public slots:
    void browsePalette();
};



class AddSpherePage : public AddShapePage {
    Q_OBJECT

public:
    AddSpherePage(QWidget* parent = 0);

    int nextId() const;
    virtual void initializePage();

protected:
    QLineEdit* _centerOnlyXEdit;
    QLineEdit* _centerOnlyYEdit;
    QLineEdit* _centerOnlyZEdit;
    QLineEdit* _radiusEdit;
};



class AddPlanePage : public AddShapePage {
    Q_OBJECT

public:
    AddPlanePage(QWidget* parent = 0);

    int nextId() const;
    virtual void initializePage();

protected:
    QLineEdit* _centerXEdit;
    QLineEdit* _centerYEdit;
    QLineEdit* _centerZEdit;
    QLineEdit* _normalXEdit;
    QLineEdit* _normalYEdit;
    QLineEdit* _normalZEdit;
};



class AddRectanglePage : public AddPlanePage {
    Q_OBJECT

public:
    AddRectanglePage(QWidget* parent = 0);

    int nextId() const;
    virtual void initializePage();

protected:
    QLineEdit* _heightEdit;
    QLineEdit* _widthEdit;
};



class AddDraughtboardPage : public AddRectanglePage {
    Q_OBJECT

public:
    AddDraughtboardPage(QWidget* parent = 0);

    int nextId() const;
    virtual void initializePage();

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



class AddCylindrePage : public AddShapePage {
    Q_OBJECT

public:
    AddCylindrePage(QWidget* parent = 0);

    int nextId() const;
    virtual void initializePage();

protected:
    QLineEdit* _bottomCenterXEdit;
    QLineEdit* _bottomCenterYEdit;
    QLineEdit* _bottomCenterZEdit;
    QLineEdit* _lengthEdit;
    QLineEdit* _radiusEdit;
};



class AddSurfacePage : public AddShapePage {
    Q_OBJECT

public:
    AddSurfacePage(QWidget* parent = 0);

    int nextId() const;
    virtual void initializePage();

protected:
    QLineEdit* _equation1Edit;
    QLineEdit* _equation2Edit;
    QLineEdit* _equation3Edit;
    QLineEdit* _equation4Edit;
};



class AddQuadricPage : public AddShapePage {
    Q_OBJECT

public:
    AddQuadricPage(QWidget* parent = 0);

    int nextId() const;
    virtual void initializePage();

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



class AddImplicitPage : public AddShapePage {
    Q_OBJECT

public:
    AddImplicitPage(QWidget* parent = 0);

    int nextId() const;
    virtual void initializePage();

protected:
    QLineEdit* _equationEdit;
};



class AddBoxPage : public AddShapePage {
    Q_OBJECT

public:
    AddBoxPage(QWidget* parent = 0);

    int nextId() const;
    virtual void initializePage();

protected:
    QLineEdit* _x1Edit;
    QLineEdit* _y1Edit;
    QLineEdit* _z1Edit;
    QLineEdit* _x2Edit;
    QLineEdit* _y2Edit;
    QLineEdit* _z2Edit;
};



class AddTrianglePage : public AddShapePage {
    Q_OBJECT

public:
    AddTrianglePage(QWidget* parent = 0);

    int nextId() const;
    virtual void initializePage();

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



class AddTorusPage : public AddShapePage {
    Q_OBJECT

public:
    AddTorusPage(QWidget* parent = 0);

    int nextId() const;
    virtual void initializePage();

protected:
    QLineEdit* _ringRadiusEdit;
    QLineEdit* _crossRadiusEdit;
};



class AddDiskPage : public AddPlanePage {
    Q_OBJECT

public:
    AddDiskPage(QWidget* parent = 0);

    int nextId() const;
    virtual void initializePage();

protected:
    QLineEdit* _radiusEdit;
};

#endif // ADDSHAPEWINDOW_H
