#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QListWidget>

class AnimationWidget : public QListWidget {
    Q_OBJECT

public:
    AnimationWidget(QWidget* parent = 0);

    void addThumb(QPixmap pixmap, QPoint location);

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dropEvent(QDropEvent* event);
    void startDrag(Qt::DropActions supportedActions);

private:

signals:

public slots:

};

#endif // ANIMATIONWIDGET_H
