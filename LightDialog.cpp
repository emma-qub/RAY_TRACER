#include "LightDialog.h"

LightDialog::LightDialog(QWidget *parent, LightSource* light) :
    QDialog(parent) {

    if (light == 0) {
        _colorREdit = new QLineEdit(QString::number(1.0));
        _colorGEdit = new QLineEdit(QString::number(1.0));
        _colorBEdit = new QLineEdit(QString::number(1.0));
    } else {
        Color lightColor = light->_color;
        _colorREdit = new QLineEdit(QString::number(lightColor[0]));
        _colorGEdit = new QLineEdit(QString::number(lightColor[1]));
        _colorBEdit = new QLineEdit(QString::number(lightColor[2]));
    }
    _colorREdit->setVisible(false);
    _colorGEdit->setVisible(false);
    _colorBEdit->setVisible(false);

    _colorRender = new QLabel;
    _colorRender->setFixedSize(50, 20);
    QPixmap colorPixmap(50, 20);
    if (light == 0) {
        colorPixmap.fill(Qt::white);
    } else {
        colorPixmap.fill(QColor(_colorREdit->text().toDouble()*255, _colorGEdit->text().toDouble()*255, _colorBEdit->text().toDouble()*255));
    }
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

    if (light == 0) {
        _positonXEdit = new QLineEdit(QString::number(20.0), this);
        _positonYEdit = new QLineEdit(QString::number(20.0), this);
        _positonZEdit = new QLineEdit(QString::number(-20.0), this);
    } else {
        _positonXEdit = new QLineEdit(QString::number(light->_position[0]), this);
        _positonYEdit = new QLineEdit(QString::number(light->_position[1]), this);
        _positonZEdit = new QLineEdit(QString::number(light->_position[2]), this);
    }
    _positonXEdit->setFixedWidth(50);
    _positonYEdit->setFixedWidth(50);
    _positonZEdit->setFixedWidth(50);
    QFormLayout* positionXLayout = new QFormLayout;
    positionXLayout->addRow("X:", _positonXEdit);
    QFormLayout* positionYLayout = new QFormLayout;
    positionYLayout->addRow("Y:", _positonYEdit);
    QFormLayout* positionZLayout = new QFormLayout;
    positionZLayout->addRow("Z:", _positonZEdit);
    QHBoxLayout* positionLayout = new QHBoxLayout;
    positionLayout->addLayout(positionXLayout);
    positionLayout->addLayout(positionYLayout);
    positionLayout->addLayout(positionZLayout);
    QGroupBox* positionGroupBox = new QGroupBox("Position", this);
    positionGroupBox->setFixedWidth(250);
    positionGroupBox->setLayout(positionLayout);

    if (light == 0) {
        _intensityEdit = new QLineEdit(QString::number(3.0), this);
    } else {
        _intensityEdit = new QLineEdit(QString::number(light->_intensity), this);
    }
    _intensityEdit->setFixedWidth(50);
    QFormLayout* intensityLayout = new QFormLayout;
    intensityLayout->addRow("Value:", _intensityEdit);
    QGroupBox* intensityGroupBox = new QGroupBox("Intensity", this);
    intensityGroupBox->setLayout(intensityLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(colorGroupBox);
    mainLayout->addWidget(positionGroupBox);
    mainLayout->addWidget(intensityGroupBox);


    if (light == 0) {
        _okButton = new QPushButton("Add", this);
    } else {
        _okButton = new QPushButton("Update", this);
    }
    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    _cancelButton = new QPushButton("Cancel", this);
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->addWidget(_okButton);
    buttonsLayout->addWidget(_cancelButton);


    QHBoxLayout* globalLayout = new QHBoxLayout;
    globalLayout->addLayout(mainLayout);
    globalLayout->addLayout(buttonsLayout);

    setLayout(globalLayout);
}

void LightDialog::browsePalette() {
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

Color LightDialog::getColor() const {
    return Color(_colorREdit->text().toDouble(),
                 _colorGEdit->text().toDouble(),
                 _colorBEdit->text().toDouble()
           );
}

Vector3 LightDialog::getPosition() const {
    return Vector3(_positonXEdit->text().toDouble(),
                   _positonYEdit->text().toDouble(),
                   _positonZEdit->text().toDouble()
           );
}

double LightDialog::getIntensity() const {
    return _intensityEdit->text().toDouble();
}

