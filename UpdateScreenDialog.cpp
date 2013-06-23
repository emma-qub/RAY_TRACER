#include "UpdateScreenDialog.h"

UpdateScreenDialog::UpdateScreenDialog(QVector<double> screen, RayTracer::Resolution resolution, QWidget *parent) :
    QDialog(parent) {

    _widthEdit = new QLineEdit(QString::number(screen[0]), this);
    _widthEdit->setFixedWidth(50);
    QFormLayout* widthLayout = new QFormLayout;
    widthLayout->addRow("Value:", _widthEdit);
    QGroupBox* widthGroupBox = new QGroupBox("width", this);
    widthGroupBox->setLayout(widthLayout);

    _heightEdit = new QLineEdit(QString::number(screen[1]), this);
    _heightEdit->setFixedWidth(50);
    QFormLayout* heightLayout = new QFormLayout;
    heightLayout->addRow("Value:", _heightEdit);
    QGroupBox* heightGroupBox = new QGroupBox("height", this);
    heightGroupBox->setLayout(heightLayout);

    _resolutionComboBox = new QComboBox;
    _resolutionComboBox->addItem("Low");
    _resolutionComboBox->addItem("Medium");
    _resolutionComboBox->addItem("High");
    _resolutionComboBox->setCurrentIndex(resolution);
    QFormLayout* resolutionLayout = new QFormLayout;
    resolutionLayout->addRow("Value:", _resolutionComboBox);
    QGroupBox* resolutionGroupBox = new QGroupBox("resolution", this);
    resolutionGroupBox->setLayout(resolutionLayout);

    _okButton = new QPushButton("Update", this);
    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    _cancelButton = new QPushButton("Cancel", this);
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->addWidget(_okButton);
    buttonsLayout->addWidget(_cancelButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(widthGroupBox);
    mainLayout->addWidget(heightGroupBox);
    mainLayout->addWidget(resolutionGroupBox);

    QHBoxLayout* globalLayout = new QHBoxLayout;
    globalLayout->addLayout(mainLayout);
    globalLayout->addLayout(buttonsLayout);

    setLayout(globalLayout);
}

int UpdateScreenDialog::getWidth() const {
    return _widthEdit->text().toInt();
}

int UpdateScreenDialog::getHeight() const {
    return _heightEdit->text().toInt();
}

RayTracer::Resolution UpdateScreenDialog::getResolution() const {
    switch (_resolutionComboBox->currentIndex()) {
    case 0:
        return RayTracer::low;
    case 1:
        return RayTracer::medium;
    case 2:
        return RayTracer::high;
    }
}

void UpdateScreenDialog::checkFields() {
    if (_widthEdit->text() != ""
     && _heightEdit->text() != ""
    ) {
        accept();
    } else {
        QMessageBox::warning(this, "Fields empty", "Please fill every field in the form");
    }
}

