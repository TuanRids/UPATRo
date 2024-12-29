#ifndef BVIEWFRAME_H
#define BVIEWFRAME_H

#include "..\pch.h"
#include "PAUTFileReader/AscanProcessor.h"
#include "MainUI/FacObsFrames/FactoryMgr.h"
#include "MainUI/FacObsFrames/ObserverMgr.h"
#include "MainUI/mainwindow.h"
#include "event/ZoomableGraphicsView.h"
#include "event/XYOverlayGrid.h"


// Graphics Frame
class BviewFrame : public QOpenGLWidget, public QOpenGLFunctions_4_3_Core, public nObserver {
private:
    void CreateArtFrame();
    void MouseGetPosXY(std::shared_ptr<ZoomableGraphicsView> graphicsView);
    void addPoints(bool Cviewlink, int x, int y);

    std::shared_ptr<QGraphicsScene> scene;
    std::shared_ptr<ZoomableGraphicsView> graphicsView;
    uint64_t ysize, xsize, zsize;
    std::pair<int, int> calculateOriginalPos(int scaled_y, int scaled_z);

    std::shared_ptr<XYOverlayGrid> overlay;
    std::shared_ptr<cv::Mat> orgimage;
    std::shared_ptr<cv::Mat> scaledImage;
    bool isRealTime = true;

    // RealtimeGPU Variables
    QVBoxLayout* layout;
    std::unique_ptr<QOpenGLShaderProgram> shaderProgram = nullptr;
    QOffscreenSurface* surface;

    // Realtime GPU variables for GLTexture
    GLuint textureID;
    GLuint vao, vbo, ebo;

    // select region
    bool isSelectingRegion = false;
    bool isDragging = false;
    QPointF selectionStart, selectionEnd;
    QPointF lastMousePos;
public:    
    explicit BviewFrame(QWidget* parent = nullptr);
    QWidget* createFrame() override;
    void updateOffLine() override;
    void updateRealTime() override;
    void renderQuad();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void Wait3DScreen();
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    QVector2D zoomCenter;
    float zoomRatio = 1.0f;
};

#endif
