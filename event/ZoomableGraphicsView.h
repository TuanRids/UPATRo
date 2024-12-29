#ifndef ZOOMABLEGRAPHICSVIEW_H
#define ZOOMABLEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPointF>
#include <QScrollBar>


class ZoomableGraphicsView : public QGraphicsView {
    Q_OBJECT
public:
    explicit ZoomableGraphicsView(QWidget* parent = nullptr);
    void setNavigator(QGraphicsView* navigatorView);

signals:
    void mouseLeftView();
    void mouseClicked(int x, int y);
    void mouseMoved(int x, int y);
    void nKeyPressedEvent();
protected:
    void wheelEvent(QWheelEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    
private:
    const double zoomFactor;
    bool isPanning;
    bool isLDragging;
    QPoint panStartPoint;
    QGraphicsView* navigatorView;
    void updateNavigator() {};
    QGraphicsRectItem* rubberBandRect = nullptr;
    QPointF startPoint;
    QPointF scenePos;
};

#endif // ZOOMABLEGRAPHICSVIEW_H
