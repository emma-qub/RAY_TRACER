#ifndef MAKEFILMWINDOW_H
#define MAKEFILMWINDOW_H

#include <QApplication>
#include <QtGui>

class MakeFilmWindow : public QDialog {
    Q_OBJECT

public:
    explicit MakeFilmWindow(QWidget* parent = 0);

    double getNormalX() const;
    double getNormalY() const;
    double getNormalZ() const;
    double getCircleCenterX() const;
    double getCircleCenterY() const;
    double getCircleCenterZ() const;
    double getAimedPointX() const;
    double getAimedPointY() const;
    double getAimedPointZ() const;
    int getNbPoints() const;
    double getRadius() const;
    QString getFilmName() const;

private:
    QLineEdit* _normalXEdit;
    QLineEdit* _normalYEdit;
    QLineEdit* _normalZEdit;
    QLineEdit* _circleCenterXEdit;
    QLineEdit* _circleCenterYEdit;
    QLineEdit* _circleCenterZEdit;
    QLineEdit* _aimedPointXEdit;
    QLineEdit* _aimedPointYEdit;
    QLineEdit* _aimedPointZEdit;
    QLineEdit* _nbPointsEdit;
    QLineEdit* _radiusEdit;
    QLineEdit* _filmNameEdit;

    QPushButton* _okButton;
    QPushButton* _cancelButton;

public slots:
    void checkFields();
};

#endif // MAKEFILMWINDOW_H
