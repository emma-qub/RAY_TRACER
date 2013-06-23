#include "UpdateCameraDialog.h"

UpdateCameraDialog::UpdateCameraDialog(const Camera& camera, QWidget *parent) :
    QDialog(parent) {

    _observerXEdit = new QLineEdit(QString::number(camera._observer[0]), this);
    _observerXEdit->setFixedWidth(50);
    _observerYEdit = new QLineEdit(QString::number(camera._observer[1]), this);
    _observerYEdit->setFixedWidth(50);
    _observerZEdit = new QLineEdit(QString::number(camera._observer[2]), this);
    _observerZEdit->setFixedWidth(50);
    QFormLayout* observerXLayout = new QFormLayout;
    observerXLayout->addRow("X:", _observerXEdit);
    QFormLayout* observerYLayout = new QFormLayout;
    observerYLayout->addRow("Y:", _observerYEdit);
    QFormLayout* observerZLayout = new QFormLayout;
    observerZLayout->addRow("Z:", _observerZEdit);
    QHBoxLayout* observerLayout = new QHBoxLayout;
    observerLayout->addLayout(observerXLayout);
    observerLayout->addLayout(observerYLayout);
    observerLayout->addLayout(observerZLayout);
    QGroupBox* observerGroupBox = new QGroupBox("observer", this);
    observerGroupBox->setFixedWidth(250);
    observerGroupBox->setLayout(observerLayout);

    _aimedPointXEdit = new QLineEdit(QString::number(camera._aimedPoint[0]), this);
    _aimedPointXEdit->setFixedWidth(50);
    _aimedPointYEdit = new QLineEdit(QString::number(camera._aimedPoint[1]), this);
    _aimedPointYEdit->setFixedWidth(50);
    _aimedPointZEdit = new QLineEdit(QString::number(camera._aimedPoint[2]), this);
    _aimedPointZEdit->setFixedWidth(50);
    QFormLayout* aimedPointXLayout = new QFormLayout;
    aimedPointXLayout->addRow("X:", _aimedPointXEdit);
    QFormLayout* aimedPointYLayout = new QFormLayout;
    aimedPointYLayout->addRow("Y:", _aimedPointYEdit);
    QFormLayout* aimedPointZLayout = new QFormLayout;
    aimedPointZLayout->addRow("Z:", _aimedPointZEdit);
    QHBoxLayout* aimedPointLayout = new QHBoxLayout;
    aimedPointLayout->addLayout(aimedPointXLayout);
    aimedPointLayout->addLayout(aimedPointYLayout);
    aimedPointLayout->addLayout(aimedPointZLayout);
    QGroupBox* aimedPointGroupBox = new QGroupBox("aimedPoint", this);
    aimedPointGroupBox->setFixedWidth(250);
    aimedPointGroupBox->setLayout(aimedPointLayout);

    _viewAngleEdit = new QLineEdit(QString::number(camera._viewAngle), this);
    _viewAngleEdit->setFixedWidth(50);
    QFormLayout* viewAngleLayout = new QFormLayout;
    viewAngleLayout->addRow("Value:", _viewAngleEdit);
    QGroupBox* viewAngleGroupBox = new QGroupBox("View angle", this);
    viewAngleGroupBox->setLayout(viewAngleLayout);

    _distanceScreenEdit = new QLineEdit(QString::number(camera._distScreen), this);
    _distanceScreenEdit->setFixedWidth(50);
    QFormLayout* distanceScreenLayout = new QFormLayout;
    distanceScreenLayout->addRow("Value:", _distanceScreenEdit);
    QGroupBox* distanceScreenGroupBox = new QGroupBox("Distance to screen", this);
    distanceScreenGroupBox->setLayout(distanceScreenLayout);

    QVBoxLayout* fieldsLayout = new QVBoxLayout;
    fieldsLayout->setAlignment(Qt::AlignTop);
    fieldsLayout->addWidget(observerGroupBox);
    fieldsLayout->addWidget(aimedPointGroupBox);
    fieldsLayout->addWidget(viewAngleGroupBox);
    fieldsLayout->addWidget(distanceScreenGroupBox);


    _okButton = new QPushButton("Update");
    connect(_okButton, SIGNAL(clicked()), this, SLOT(checkFields()));
    _cancelButton = new QPushButton("Cancel");
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->addWidget(_okButton);
    buttonsLayout->addWidget(_cancelButton);


    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(fieldsLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}

Vector3 UpdateCameraDialog::getObserver() const {
    return Vector3(_observerXEdit->text().toDouble(),
                   _observerYEdit->text().toDouble(),
                   _observerZEdit->text().toDouble()
           );
}

Vector3 UpdateCameraDialog::getAimedPoint() const {
    return Vector3(_aimedPointXEdit->text().toDouble(),
                   _aimedPointYEdit->text().toDouble(),
                   _aimedPointZEdit->text().toDouble()
           );
}

double UpdateCameraDialog::getViewAngle() const {
    return _viewAngleEdit->text().toDouble();
}

double UpdateCameraDialog::getDistanceScreen() const {
    return _distanceScreenEdit->text().toDouble();
}

void UpdateCameraDialog::checkFields() {
    if (_observerXEdit->text() != ""
     && _observerYEdit->text() != ""
     && _observerZEdit->text() != ""
     && _aimedPointXEdit->text() != ""
     && _aimedPointYEdit->text() != ""
     && _aimedPointZEdit->text() != ""
     && _viewAngleEdit->text() != ""
     && _distanceScreenEdit->text() != ""
    ) {
        accept();
    } else {
        QMessageBox::warning(this, "Fields empty", "Please fill every field in the form");
    }
}
