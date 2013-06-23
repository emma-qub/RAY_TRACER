#include "ExportImageDialog.h"
#include <string>

ExportImageDialog::ExportImageDialog(const QPixmap* pixmap, QString fileName, QWidget *parent) :
    QDialog(parent),
    _fileName(fileName) {


    // Rendered Image
    _imageFrame = new QFrame(this);
    _imageFrame->setFrameShape(QFrame::Panel);
    _imageFrame->setFrameShadow(QFrame::Sunken);
    _imageFrame->setLineWidth(3);
    _imageFrame->setFixedSize(1200, 800);

    _renderedImage = new QLabel;
    _renderedImage->setPixmap(*pixmap);
    _renderedImage->setAlignment(Qt::AlignCenter);

    QVBoxLayout* imageLayout = new QVBoxLayout;
    imageLayout->addWidget(_renderedImage);
    imageLayout->setAlignment(Qt::AlignCenter);

    _imageFrame->setLayout(imageLayout);



    // Buttons
    _saveButton = new QPushButton("Save", this);
    _saveButton->setFixedWidth(100);
    connect(_saveButton, SIGNAL(clicked()), this, SLOT(saveImage()));

    _cancelButton = new QPushButton("Cancel", this);
    _cancelButton->setFixedWidth(100);
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->setAlignment(Qt::AlignCenter);
    buttonsLayout->addWidget(_saveButton);
    buttonsLayout->addWidget(_cancelButton);



    // Presets
    _formatsList = new QComboBox(this);
    _formatsList->addItem("PNG");
    _formatsList->addItem("JPG");
    _formatsList->addItem("JPEG");
    _formatsList->addItem("BMP");
    _formatsList->addItem("PPM");
    QFormLayout* formatLayout = new QFormLayout;
    formatLayout->addRow("Format:", _formatsList);

    _qualityList = new QComboBox(this);
    _qualityList->addItem("Auto");
    _qualityList->addItem("Low");
    _qualityList->addItem("Medium");
    _qualityList->addItem("High");
    _qualityList->addItem("Very high");
    _qualityList->addItem("Maximum");
    QFormLayout* qualityLayout = new QFormLayout;
    qualityLayout->addRow("Quality:", _qualityList);

    QVBoxLayout* presetLayout = new QVBoxLayout;
    presetLayout->addLayout(formatLayout);
    presetLayout->addLayout(qualityLayout);

    QGroupBox* presetGroupBox = new QGroupBox("Preset", this);
    presetGroupBox->setLayout(presetLayout);



    // Save fields layout
    QVBoxLayout* saveWidgetLayout = new QVBoxLayout;
    saveWidgetLayout->setAlignment(Qt::AlignCenter);
    saveWidgetLayout->addLayout(buttonsLayout);
    saveWidgetLayout->addWidget(presetGroupBox);



    // Main layout
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(_imageFrame);
    mainLayout->addLayout(saveWidgetLayout);

    setLayout(mainLayout);
    setWindowTitle("Export image");
    setWindowState(Qt::WindowMaximized);
}

void ExportImageDialog::saveImage() {
    QString extension = _formatsList->currentText();
    QString fileName = "../RayTracer/save/"+_fileName+"."+extension.toLower();
    QString saveName = QFileDialog::getSaveFileName(this, "Export", fileName.toStdString().c_str(), "Img (*"+extension+")");
    if (saveName != "") {
        int quality = -1;
        if (_qualityList->currentIndex() != 0) {
            quality = _qualityList->currentIndex() * 20;
        }
        if (_renderedImage->pixmap()->save(saveName, extension.toStdString().c_str()), quality) {
            accept();
        }
    }
}
