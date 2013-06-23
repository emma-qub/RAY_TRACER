#include "NewFileWindow.h"

NewFileWindow::NewFileWindow(QWidget* parent) :
    QDialog(parent) {

    _id++;

    // Preset
    _fileNameEdit = new QLineEdit("Untitled-"+QString::number(_id));
    QFormLayout* fileNameLayout = new QFormLayout;
    fileNameLayout->addRow("Name:", _fileNameEdit);

    _fileWidthEdit = new QLineEdit("800");
    QFormLayout* fileWidthLayout = new QFormLayout;
    fileWidthLayout->addRow("Width:", _fileWidthEdit);

    _fileHeightEdit = new QLineEdit("600");
    QFormLayout* fileHeightLayout = new QFormLayout;
    fileHeightLayout->addRow("Height:", _fileHeightEdit);

    _fileResolutionComboBox = new QComboBox;
    _fileResolutionComboBox->addItem("Low");
    _fileResolutionComboBox->addItem("Medium");
    _fileResolutionComboBox->addItem("High");
    _fileResolutionComboBox->setCurrentIndex(RayTracer::high);
    QFormLayout* fileResolutionLayout = new QFormLayout;
    fileResolutionLayout->addRow("Resolution:", _fileResolutionComboBox);


    // Buttons
    _okButton = new QPushButton("Ok");
    connect(_okButton, SIGNAL(clicked()), this, SLOT(checkFields()));
    _okButton->setDefault(true);
    _cancelButton = new QPushButton("Cancel");
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    _buttonBox = new QDialogButtonBox(Qt::Vertical);
    _buttonBox->addButton(_okButton, QDialogButtonBox::ActionRole);
    _buttonBox->addButton(_cancelButton, QDialogButtonBox::ActionRole);


    // Advanced
    _advancedWidget = new QWidget;

    _advancedButton = new QPushButton("Advanced >>", this);
    _advancedButton->setCheckable(true);
    _advancedButton->setAutoDefault(false);
    connect(_advancedButton, SIGNAL(toggled(bool)), this, SLOT(showHide(bool)));

    _advancedButton->setFixedWidth(100);

    _observerXEdit = new QLineEdit("-40", this);
    _observerXEdit->setFixedWidth(50);
    _observerYEdit = new QLineEdit("40", this);
    _observerYEdit->setFixedWidth(50);
    _observerZEdit = new QLineEdit("-40", this);
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

    _aimedPointXEdit = new QLineEdit("0", this);
    _aimedPointXEdit->setFixedWidth(50);
    _aimedPointYEdit = new QLineEdit("0", this);
    _aimedPointYEdit->setFixedWidth(50);
    _aimedPointZEdit = new QLineEdit("0", this);
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

    _viewAngleEdit = new QLineEdit("0.4", this);
    _viewAngleEdit->setFixedWidth(50);
    QFormLayout* viewAngleLayout = new QFormLayout;
    viewAngleLayout->addRow("Value:", _viewAngleEdit);
    QGroupBox* viewAngleGroupBox = new QGroupBox("View angle", this);
    viewAngleGroupBox->setLayout(viewAngleLayout);

    _distanceScreenEdit = new QLineEdit("0.5", this);
    _distanceScreenEdit->setFixedWidth(50);
    QFormLayout* distanceScreenLayout = new QFormLayout;
    distanceScreenLayout->addRow("Value:", _distanceScreenEdit);
    QGroupBox* distanceScreenGroupBox = new QGroupBox("Distance to screen", this);
    distanceScreenGroupBox->setLayout(distanceScreenLayout);

    QVBoxLayout* advancedLayout = new QVBoxLayout;
    advancedLayout->setMargin(0);
    advancedLayout->addWidget(observerGroupBox);
    advancedLayout->addWidget(aimedPointGroupBox);
    advancedLayout->addWidget(viewAngleGroupBox);
    advancedLayout->addWidget(distanceScreenGroupBox);
    _advancedWidget->setLayout(advancedLayout);


    // Layouts
    QVBoxLayout* presetLayout = new QVBoxLayout;
    presetLayout->addLayout(fileWidthLayout);
    presetLayout->addLayout(fileHeightLayout);
    presetLayout->addLayout(fileResolutionLayout);

    QGroupBox* presetGroupBox = new QGroupBox("Preset", this);
    presetGroupBox->setLayout(presetLayout);

    QVBoxLayout* fieldsLayout = new QVBoxLayout;
    fieldsLayout->addLayout(fileNameLayout);
    fieldsLayout->addWidget(presetGroupBox);
    fieldsLayout->addWidget(_advancedButton);
    fieldsLayout->addWidget(_advancedWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(fieldsLayout);
    mainLayout->addWidget(_buttonBox);

    setWindowTitle("New file");
    setLayout(mainLayout);

    _advancedWidget->hide();
    //*/
}

int NewFileWindow::_id;

QString NewFileWindow::getFileName() const {
    return _fileNameEdit->text();
}

int NewFileWindow::getFileWidth() const {
    return _fileWidthEdit->text().toInt();
}

int NewFileWindow::getFileHeight() const {
    return _fileHeightEdit->text().toInt();
}

RayTracer::Resolution NewFileWindow::getFileResolution() const {
    switch (_fileResolutionComboBox->currentIndex()) {
    case 0:
        return RayTracer::low;
    case 1:
        return RayTracer::medium;
    case 2:
        return RayTracer::high;
    }
}

Vector3 NewFileWindow::getObserver() const {
    return Vector3(_observerXEdit->text().toDouble(),
                   _observerYEdit->text().toDouble(),
                   _observerZEdit->text().toDouble()
           );
}

Vector3 NewFileWindow::getAimedPoint() const {
    return Vector3(_aimedPointXEdit->text().toDouble(),
                   _aimedPointYEdit->text().toDouble(),
                   _aimedPointZEdit->text().toDouble()
           );
}

double NewFileWindow::getViewAngle() const {
    return _viewAngleEdit->text().toDouble();
}

double NewFileWindow::getDistanceScreen() const {
    return _distanceScreenEdit->text().toDouble();
}

void NewFileWindow::checkFields() {
    if (_fileNameEdit->text() != ""
     && _fileWidthEdit->text() != ""
     && _fileHeightEdit->text() != ""
     && _observerXEdit->text() != ""
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
        QMessageBox::warning(this, "Empty fields", "Please fill every field in the form");
    }
}

void NewFileWindow::showHide(bool b) {
    _advancedWidget->setVisible(b);
    if (b)
        _advancedButton->setText("Advanced <<");
    else
        _advancedButton->setText("Advanced >>");
}
