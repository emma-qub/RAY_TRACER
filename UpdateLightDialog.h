#ifndef UPDATELIGHTDIALOG_H
#define UPDATELIGHTDIALOG_H

#include <QWidget>
#include <QApplication>
#include <QtGui>

#include "LightSource.h"

class UpdateLightDialog : public QDialog {
    Q_OBJECT

public:
    UpdateLightDialog(LightSource* light, QWidget* parent = 0);

    Color getColor() const;
    double getIntensity() const;

};

#endif // UPDATELIGHTDIALOG_H
