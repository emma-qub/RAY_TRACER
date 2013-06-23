#ifndef UPDATECAMERADIALOG_H
#define UPDATECAMERADIALOG_H

#include <QWidget>
#include <QApplication>
#include <QtGui>

#include "Camera.h"

class UpdateCameraDialog : public QDialog {
    Q_OBJECT

public:
    UpdateCameraDialog(const Camera& camera, QWidget* parent = 0);

    Vector3 getObserver() const;
    Vector3 getAimedPoint() const;
    double getViewAngle() const;
    double getDistanceScreen() const;

private:
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

public slots:
    void checkFields();
};

#endif // UPDATECAMERADIALOG_H
