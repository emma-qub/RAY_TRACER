#include "AnimationWidget.h"

#include <QtGui>

AnimationWidget::AnimationWidget(QWidget *parent) :
    QListWidget(parent) {

    setViewMode(QListView::IconMode);

    setIconSize(QSize(60, 60));
    setSpacing(10);

    setAcceptDrops(true);
    setMinimumSize(1400, 94);
    setMaximumSize(1400, 94);
}

void AnimationWidget::dragEnterEvent(QDragEnterEvent *event) {
    event->accept();
}

void AnimationWidget::dragMoveEvent(QDragMoveEvent *event) {
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void AnimationWidget::dropEvent(QDropEvent *event) {
    QByteArray pieceData = event->mimeData()->data("image/jpg");
    QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
    QPixmap pixmap;
    QPoint location = event->pos();
    dataStream >> pixmap;

    location.setX(location.x()/80);
    location.setY(location.y()/80);

    addThumb(pixmap, location);

    event->accept();
}

void AnimationWidget::startDrag(Qt::DropActions supportedActions) {
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qVariantValue<QPixmap>(item->data(Qt::UserRole));

    dataStream << pixmap;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("image/jpg", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
        delete takeItem(row(item));
    }
}

void AnimationWidget::addThumb(QPixmap pixmap, QPoint location) {
    QListWidgetItem* pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));

    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, location);

    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}
