#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QtGui>
#include <QApplication>
#include "ParserXML.h"
#include "Image.h"
#include "RenderingThread.h"

class ImageWindow : public QWidget {
    Q_OBJECT

public:
    ImageWindow();
    ImageWindow(QString fileName);
    ImageWindow(QString fileName, QVector<int> screen,
                RayTracer::Resolution resolution, const Camera& camera);
    virtual ~ImageWindow();

    void init();

    QStringList getShapesList() const;
    QStringList getLightsList() const;
    QStringList getCameraList() const;
    QStringList getScreenList() const;
    QString getWindowTitle() const;
    QString getFileName() const;
    bool getSaved() const;
    bool getNeverSavedBefore() const;
    QVector<ParserXML> getPreviousInfoImage() const;
    QAction* getUndoAction();
    QAction* getRedoAction();

    void setParser(const ParserXML& parser);

    void save();
    void saveAs();
    void exportImage();
    void exportImage(const QString& fileName);
    void writeXML();
    QThread& generate();
    void addShape();
    void addLight();
    void updateShape(int idShape);
    void removeShape(int idShape);
    void updateLight(int idLight);
    void removeLight(int idLight);
    void setCamera();
    void setCamera(const Vector3& observer, const Vector3& aimedPoint);
    void setScreen();

    void mousePressEvent(QMouseEvent* event);

public:
    RenderingThread _renderThread;
    QString _fileName;
    QString _windowTitle;
    bool _neverSavedBefore;
    bool _saved;
    ParserXML _parser;
    QLabel* _imageLabel;
    QString _xmlPath;
    QVector<ParserXML> _previousInfoImage;
    QUndoStack* _undoStack;
    QAction* _undoAction;
    QAction* _redoAction;

public slots:
    void setSaved(bool b);
    void updateImage(const QImage& image);

};

#endif // IMAGEWINDOW_H
