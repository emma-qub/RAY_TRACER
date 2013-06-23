#ifndef NEWFILEWINDOW_H
#define NEWFILEWINDOW_H

#include <QWidget>
#include <QApplication>
#include <QtGui>

#include "RayTracer.h"

class NewFileWindow : public QDialog {
    Q_OBJECT

public:
    static int _id;

    NewFileWindow(QWidget* parent = 0);

    QString getFileName() const;
    int getFileWidth() const;
    int getFileHeight() const;
    RayTracer::Resolution getFileResolution() const;
    Vector3 getObserver() const;
    Vector3 getAimedPoint() const;
    double getViewAngle() const;
    double getDistanceScreen() const;

private:
    QLabel* _fileNameLabel;
    QLineEdit* _fileNameEdit;
    QLabel* _fileWidthLabel;
    QLineEdit* _fileWidthEdit;
    QLabel* _fileHeightLabel;
    QLineEdit* _fileHeightEdit;
    QLabel* _fileResolutionLabel;
    QComboBox* _fileResolutionComboBox;

    QLineEdit* _observerXEdit;
    QLineEdit* _observerYEdit;
    QLineEdit* _observerZEdit;
    QLineEdit* _aimedPointXEdit;
    QLineEdit* _aimedPointYEdit;
    QLineEdit* _aimedPointZEdit;
    QLineEdit* _viewAngleEdit;
    QLineEdit* _distanceScreenEdit;

    QPushButton* _okButton;
    QPushButton* _cancelButton;
    QPushButton* _advancedButton;
    QDialogButtonBox* _buttonBox;

    QWidget* _advancedWidget;

public slots:
    void checkFields();
    void showHide(bool b);
};

#endif // NEWFILEWINDOW_H
