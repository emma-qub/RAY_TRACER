#ifndef LIGHTDIALOG_H
#define LIGHTDIALOG_H


#include <QWidget>
#include <QApplication>
#include <QtGui>

#include "LightSource.h"

class LightDialog : public QDialog {
    Q_OBJECT

public:
    LightDialog(QWidget* parent = 0, LightSource* light = 0);

    Color getColor() const;
    double getIntensity() const;
    Vector3 getPosition() const;

private:
    QLineEdit* _intensityEdit;
    QLineEdit* _positonXEdit;
    QLineEdit* _positonYEdit;
    QLineEdit* _positonZEdit;
    QLabel* _colorRender;
    QLineEdit* _colorREdit;
    QLineEdit* _colorGEdit;
    QLineEdit* _colorBEdit;

    QPushButton* _paletteButton;

    QPushButton* _okButton;
    QPushButton* _cancelButton;

public slots:
    void browsePalette();
};

#endif // ADDLIGHTDIALOG_H
