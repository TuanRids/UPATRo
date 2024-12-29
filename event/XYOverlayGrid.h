#ifndef XYOVERLAYGRID_H
#define XYOVERLAYGRID_H
#include "../pch.h"


class XYOverlayGrid : public QObject, public QGraphicsItemGroup {
    QGraphicsScene* scene;
    QGraphicsView* graphicsView;
    QTimer* blinkTimer;
    bool isBlinkOn;
public:
    XYOverlayGrid(QGraphicsView* ggraphicview, QGraphicsScene* scene) : graphicsView(ggraphicview), scene(scene), blinkTimer(nullptr), isBlinkOn(true) {
        blinkTimer = new QTimer(this);
        connect(blinkTimer, &QTimer::timeout, this, &XYOverlayGrid::toggleBlink);
        blinkTimer->start(100);
    }
    void updateOverlay(int original_y, int original_z, int imageWidth, int imageHeight) {
        removeItemsByData("VerHorLine");
        auto lineGroup = new QGraphicsItemGroup();
        scene->addItem(lineGroup);


        QGraphicsItem* artwork = nullptr;
        auto pointGroup = new QGraphicsItemGroup();
        scene->addItem(pointGroup);
        for (auto* item : scene->items()) {
            if (item->data(0).toString() == "artwork") {
                artwork = item;
                break;
            }
        }
        double artworkWidth = 0;
        double artworkHeight = 0;
        if (artwork) {
            QRectF artworkRect = artwork->boundingRect();
            artworkWidth = artworkRect.width();
            artworkHeight = artworkRect.height();
        }

        double viewWidth = graphicsView->viewport()->width();
        double viewHeight = graphicsView->viewport()->height();

        double scaleX = artworkWidth / viewWidth;
        double scaleY = artworkHeight / viewHeight;

        double pointSizeInScreen = 0.01 * std::min(viewWidth, viewHeight);
        double pointSizeInScene = pointSizeInScreen * std::max(scaleX, scaleY);

        QPen verticalPen(Qt::darkBlue);
        verticalPen.setWidth(pointSizeInScene * 0.1);
        verticalPen.setStyle(Qt::DashDotLine);
        QPen horizontalPen(Qt::magenta);
        horizontalPen.setWidth(pointSizeInScene * 0.1);
        horizontalPen.setStyle(Qt::DashDotLine);

        auto verticalLine = new QGraphicsLineItem(original_y, 0, original_y, imageHeight);
        verticalLine->setData(0, "VerHorLine");
        verticalLine->setZValue(1);
        verticalLine->setPen(verticalPen);
        lineGroup->addToGroup(verticalLine);

        auto horizontalLine = new QGraphicsLineItem(0, original_z, imageWidth, original_z);
        horizontalLine->setData(0, "VerHorLine");
        horizontalLine->setZValue(1);
        horizontalLine->setPen(horizontalPen);
        lineGroup->addToGroup(horizontalLine);
    }
    void updatePoints(double pixelX, double pixelY, Qt::GlobalColor vcolor, Qt::GlobalColor hcolor) {
        removeItemsByData("MarkLine");

        QGraphicsItem* artwork = nullptr;
        for (auto* item : scene->items()) {
            if (item->data(0).toString() == "artwork") {
                artwork = item;
                break;
            }
        }
        double artworkWidth = 0;
        double artworkHeight = 0;
        if (artwork) {
            QRectF artworkRect = artwork->boundingRect();
            artworkWidth = artworkRect.width();
            artworkHeight = artworkRect.height();
        }

        QPen pen(Qt::red);
        QBrush brush(Qt::red);
        double viewWidth = graphicsView->viewport()->width();
        double viewHeight = graphicsView->viewport()->height();

        double scaleX = artworkWidth / viewWidth;
        double scaleY = artworkHeight / viewHeight;

        double pointSizeInScreen = 0.01 * std::min(viewWidth, viewHeight);
        double pointSizeInScene = pointSizeInScreen * std::max(scaleX, scaleY);

        QPointF scenePoint = graphicsView->mapToScene(QPoint(static_cast<int>(pixelX), static_cast<int>(pixelY)));


        auto MarkLine = new QGraphicsItemGroup();
        scene->addItem(MarkLine);


        double lineSize = 0.001 * std::min(scene->height(), scene->width());

        auto* verticalLine = new QGraphicsLineItem(pixelX, 0, pixelX, artworkHeight);
        verticalLine->setData(0, "MarkLine");
        QPen gpen(vcolor);
        gpen.setWidth(pointSizeInScene * 0.1);
        gpen.setCosmetic(true);
        verticalLine->setPen(gpen);
        MarkLine->addToGroup(verticalLine);
        if (hcolor != Qt::color0)
        {
            QPen gpen(hcolor);
            gpen.setWidth(pointSizeInScene * 0.1);
            gpen.setCosmetic(true);
            auto* HorizontalLine = new QGraphicsLineItem(0, pixelY, artworkWidth, pixelY);
            HorizontalLine->setData(0, "MarkLine");
            HorizontalLine->setPen(gpen);
            MarkLine->addToGroup(HorizontalLine);
        };

    }


    void toggleBlink() {
        static const QVector<QColor> colors = { Qt::red, Qt::darkGreen, Qt::darkMagenta, Qt::yellow, Qt::cyan };
        static int currentColorIndex = 0;

        static int lineGroupBlinkCounter = 0;
        static bool isDashLine = false;

        isBlinkOn = !isBlinkOn;

        auto items = scene->items();
        for (auto* item : items) {
            if (item->data(0).toString() == "Point") {
                if (isBlinkOn) {
                    if (auto ellipse = dynamic_cast<QGraphicsEllipseItem*>(item)) {
                        QPen pen = ellipse->pen();
                        pen.setColor(colors[currentColorIndex]);
                        ellipse->setPen(pen);

                        QBrush brush = ellipse->brush();
                        brush.setColor(colors[currentColorIndex]);
                        ellipse->setBrush(brush);

                        currentColorIndex = (currentColorIndex + 1) % colors.size();
                    }
                    item->show();
                }
                else {
                    item->hide();
                }
            }
        }
        lineGroupBlinkCounter++;
        if (lineGroupBlinkCounter >= 5) {
            lineGroupBlinkCounter = 0;
            isDashLine = !isDashLine;

            for (auto* item : items) {
                if (item->data(0).toString() == "VerHorLine") {
                    if (auto lineItem = dynamic_cast<QGraphicsLineItem*>(item)) {
                        QPen pen = lineItem->pen();
                        if (isDashLine) {
                            pen.setStyle(Qt::DashLine);
                        }
                        else {
                            pen.setStyle(Qt::DashDotLine);
                        }
                        lineItem->setPen(pen);
                    }
                    item->show();
                }
            }
        }
        scene->update();
    }

    void ClearLineGroup() {
        for (auto item : scene->items()) {
            if (item->data(0).toString() == "VerHorLine") {
                scene->removeItem(item);
                delete item;
                break;
            }
        }
    }
    void removeItemsByData(const QString& dataName) {
        auto items = scene->items();
        for (auto* item : items) {
            if (item->data(0).toString() == dataName) {
                scene->removeItem(item);
                delete item;
            }
        }
    }
};

#endif // XYOVERLAYGRID_H