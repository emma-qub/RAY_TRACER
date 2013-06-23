#ifndef UPDATESCREENDIALOG_H
#define UPDATESCREENDIALOG_H

#include <QWidget>
#include <QApplication>
#include <QtGui>

#include "RayTracer.h"

class UpdateScreenDialog : public QDialog {
    Q_OBJECT

public:
    UpdateScreenDialog(QVector<double> screen, RayTracer::Resolution resolution, QWidget* parent = 0);

    int getWidth() const;
    int getHeight() const;
    RayTracer::Resolution getResolution() const;

private:
    QLineEdit* _widthEdit;
    QLineEdit* _heightEdit;
    QComboBox* _resolutionComboBox;

    QPushButton* _okButton;
    QPushButton* _cancelButton;

public slots:
    void checkFields();
};

#endif // UPDATESCREENDIALOG_H
