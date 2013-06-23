#ifndef RENDERINGTHREAD_H
#define RENDERINGTHREAD_H

#include <QThread>
#include <QImage>

#include "ParserXML.h"
#include "Image.h"
#include "RayTracer.h"

class RenderingThread : public QThread, public SetPixelFunction {
    Q_OBJECT

public:
    RenderingThread(QObject* parent = 0);
    virtual ~RenderingThread();

    void render(ParserXML parser);
    void setPixel(unsigned int x, unsigned int y, const Color& color);

signals:
    void renderedImage(const QImage& image);

protected:
    void run();

private:
    ParserXML _parser;
    QMutex _mutex;
    QWaitCondition _condition;
    bool _abort;
    QImage _image;

};

#endif // RENDERINGTHREAD_H
