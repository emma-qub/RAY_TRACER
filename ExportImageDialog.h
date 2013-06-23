#ifndef EXPORTIMAGEDIALOG_H
#define EXPORTIMAGEDIALOG_H

#include <QWidget>
#include <QApplication>
#include <QtGui>

class ExportImageDialog : public QDialog {
    Q_OBJECT

public:
    ExportImageDialog(const QPixmap* pixmap,
                      QString fileName,
                      QWidget* parent = 0);

private:
    QFrame* _imageFrame;
    QLabel* _renderedImage;
    QString _fileName;
    QComboBox* _formatsList;
    QComboBox* _qualityList;
    QPushButton* _saveButton;
    QPushButton* _cancelButton;

public slots:
    void saveImage();
};

#endif // EXPORTIMAGEDIALOG_H
