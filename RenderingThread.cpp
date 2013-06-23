#include "RenderingThread.h"

#include "RayTracer.h"
#include "Scene.h"

#include <QColor>
#include <QImage>

RenderingThread::RenderingThread(QObject* parent) :
    QThread(parent) {

    _abort = false;
}

RenderingThread::~RenderingThread() {
    _mutex.lock();
    _abort = true;
    _condition.wakeOne();
    _mutex.unlock();

    wait();
}

void RenderingThread::render(ParserXML parser) {
    QMutexLocker locker(&_mutex);

    _parser = parser;

    if (!isRunning()) {
        start(HighPriority);
    } else {
        _condition.wakeOne();
    }
}

void RenderingThread::run() {
    _mutex.lock();
    ParserXML parser = _parser;
    _mutex.unlock();

    Camera camera = parser.createCamera();
    vector<Shape*> shapes;
    for (int k = 0; k < parser.nbShapes(); k++) {
        shapes.push_back(parser.createShape(k));
    }
    vector<LightSource*> lights;
    for (int k = 0; k < parser.nbLights(); k++) {
        lights.push_back(parser.createLight(k));
    }

    Scene scene = Scene(shapes, lights);

    RayTracer rt(scene, camera);

    QVector<double> screenSetup = parser.createScreenSetup();
    int width = screenSetup[0];
    int height = screenSetup[1];
    RayTracer::Resolution resolution = parser.createScreenResolution();

    _image = QImage(width, height, QImage::Format_RGB32);
    _image.fill(Qt::black);

    rt.raytrace(this, resolution);

    emit renderedImage(_image);
}

void RenderingThread::setPixel(unsigned int x, unsigned int y, const Color& color) {
    QColor rgb(color[0]*255,color[1]*255,color[2]*255);
    *((QRgb*)_image.scanLine(y)+x) = rgb.rgb();
    if(x == 0) {
        emit renderedImage(_image);
    }
}
