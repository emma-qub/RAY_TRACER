#include "MakeFilmWindow.h"

using namespace std;
#include <iostream>

MakeFilmWindow::MakeFilmWindow(QWidget* parent) :
    QDialog(parent) {

    // Normal
    _normalXEdit = new QLineEdit("0");
    _normalXEdit->setFixedWidth(50);
    QFormLayout* normalXLayout = new QFormLayout;
    normalXLayout->addRow("X:", _normalXEdit);
    _normalYEdit = new QLineEdit("1");
    _normalYEdit->setFixedWidth(50);
    QFormLayout* normalYLayout = new QFormLayout;
    normalYLayout->addRow("Y:", _normalYEdit);
    _normalZEdit = new QLineEdit("0");
    _normalZEdit->setFixedWidth(50);
    QFormLayout* normalZLayout = new QFormLayout;
    normalZLayout->addRow("Z:", _normalZEdit);
    QHBoxLayout* normalLayout = new QHBoxLayout;
    normalLayout->addLayout(normalXLayout);
    normalLayout->addLayout(normalYLayout);
    normalLayout->addLayout(normalZLayout);
    QGroupBox* normalGroupBox = new QGroupBox("Normal to plane", this);
    normalGroupBox->setFixedWidth(250);
    normalGroupBox->setLayout(normalLayout);

    // Center
    _circleCenterXEdit = new QLineEdit("0");
    _circleCenterXEdit->setFixedWidth(50);
    QFormLayout* centerXLayout = new QFormLayout;
    centerXLayout->addRow("X:", _circleCenterXEdit);
    _circleCenterYEdit = new QLineEdit("20");
    _circleCenterYEdit->setFixedWidth(50);
    QFormLayout* centerYLayout = new QFormLayout;
    centerYLayout->addRow("Y:", _circleCenterYEdit);
    _circleCenterZEdit = new QLineEdit("0");
    _circleCenterZEdit->setFixedWidth(50);
    QFormLayout* centerZLayout = new QFormLayout;
    centerZLayout->addRow("Z:", _circleCenterZEdit);
    QHBoxLayout* centerLayout = new QHBoxLayout;
    centerLayout->addLayout(centerXLayout);
    centerLayout->addLayout(centerYLayout);
    centerLayout->addLayout(centerZLayout);
    QGroupBox* centerGroupBox = new QGroupBox("Circle center", this);
    centerGroupBox->setFixedWidth(250);
    centerGroupBox->setLayout(centerLayout);

    // Aimed Point
    _aimedPointXEdit = new QLineEdit("0");
    _aimedPointXEdit->setFixedWidth(50);
    QFormLayout* aimedPointXLayout = new QFormLayout;
    aimedPointXLayout->addRow("X:", _aimedPointXEdit);
    _aimedPointYEdit = new QLineEdit("0");
    _aimedPointYEdit->setFixedWidth(50);
    QFormLayout* aimedPointYLayout = new QFormLayout;
    aimedPointYLayout->addRow("Y:", _aimedPointYEdit);
    _aimedPointZEdit = new QLineEdit("0");
    _aimedPointZEdit->setFixedWidth(50);
    QFormLayout* aimedPointZLayout = new QFormLayout;
    aimedPointZLayout->addRow("Z:", _aimedPointZEdit);
    QHBoxLayout* aimedPointLayout = new QHBoxLayout;
    aimedPointLayout->addLayout(aimedPointXLayout);
    aimedPointLayout->addLayout(aimedPointYLayout);
    aimedPointLayout->addLayout(aimedPointZLayout);
    QGroupBox* aimedPointGroupBox = new QGroupBox("Aimed point", this);
    aimedPointGroupBox->setFixedWidth(250);
    aimedPointGroupBox->setLayout(aimedPointLayout);

    // Nb Points
    _nbPointsEdit = new QLineEdit("50");
    _nbPointsEdit->setFixedWidth(50);
    QFormLayout* nbPointsLayout = new QFormLayout;
    nbPointsLayout->addRow("Value:", _nbPointsEdit);
    QGroupBox* nbPointsGroupBox = new QGroupBox("Number of screenshots", this);
    nbPointsGroupBox->setFixedWidth(250);
    nbPointsGroupBox->setLayout(nbPointsLayout);

    // Rayon
    _radiusEdit = new QLineEdit("40");
    _radiusEdit->setFixedWidth(50);
    QFormLayout* radiusLayout = new QFormLayout;
    radiusLayout->addRow("Value:", _radiusEdit);
    QGroupBox* radiusGroupBox = new QGroupBox("Circle radius", this);
    radiusGroupBox->setFixedWidth(250);
    radiusGroupBox->setLayout(radiusLayout);

    // File Name
    _filmNameEdit = new QLineEdit("Film");
    _filmNameEdit->setFixedWidth(200);
    QFormLayout* filmNameLayout = new QFormLayout;
    filmNameLayout->addRow("Value:", _filmNameEdit);
    QGroupBox* filmNameGroupBox = new QGroupBox("Film name", this);
    filmNameGroupBox->setFixedWidth(250);
    filmNameGroupBox->setLayout(filmNameLayout);

    // Buttons
    _okButton = new QPushButton("Ok");
    connect(_okButton, SIGNAL(clicked()), this, SLOT(checkFields()));
    _okButton->setDefault(true);
    _cancelButton = new QPushButton("Cancel");
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(_okButton);
    buttonsLayout->addWidget(_cancelButton);

    // Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(normalGroupBox);
    mainLayout->addWidget(centerGroupBox);
    mainLayout->addWidget(aimedPointGroupBox);
    mainLayout->addWidget(nbPointsGroupBox);
    mainLayout->addWidget(radiusGroupBox);
    mainLayout->addWidget(filmNameGroupBox);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}

double MakeFilmWindow::getNormalX() const {
    return _normalXEdit->text().toDouble();
}

double MakeFilmWindow::getNormalY() const {
    return _normalYEdit->text().toDouble();
}

double MakeFilmWindow::getNormalZ() const {
    return _normalZEdit->text().toDouble();
}

double MakeFilmWindow::getCircleCenterX() const {
    return _circleCenterXEdit->text().toDouble();
}

double MakeFilmWindow::getCircleCenterY() const {
    return _circleCenterYEdit->text().toDouble();
}

double MakeFilmWindow::getCircleCenterZ() const {
    return _circleCenterZEdit->text().toDouble();
}

double MakeFilmWindow::getAimedPointX() const {
    return _aimedPointXEdit->text().toDouble();
}

double MakeFilmWindow::getAimedPointY() const {
    return _aimedPointYEdit->text().toDouble();
}

double MakeFilmWindow::getAimedPointZ() const {
    return _aimedPointZEdit->text().toDouble();
}

int MakeFilmWindow::getNbPoints() const {
    return _nbPointsEdit->text().toInt();
}

double MakeFilmWindow::getRadius() const {
    return _radiusEdit->text().toDouble();
}

QString MakeFilmWindow::getFilmName() const {
    return _filmNameEdit->text();
}

void MakeFilmWindow::checkFields() {
    if (_normalXEdit->text() != ""
     && _normalYEdit->text() != ""
     && _normalZEdit->text() != ""
     && _circleCenterXEdit->text() != ""
     && _circleCenterYEdit->text() != ""
     && _circleCenterZEdit->text() != ""
     && _aimedPointXEdit->text() != ""
     && _aimedPointYEdit->text() != ""
     && _aimedPointZEdit->text() != ""
     && _nbPointsEdit->text() != ""
     && _radiusEdit->text() != ""
     && _filmNameEdit->text() != ""
    ) {
        accept();
    } else {
        QMessageBox::warning(this, "Empty fields", "Please fill every field in the form");
    }
}
