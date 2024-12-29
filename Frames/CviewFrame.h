#ifndef CVIEWFRAME_H
#define CVIEWFRAME_H

#include "..\pch.h"
#include "PAUTFileReader/AscanProcessor.h"
#include "MainUI/FacObsFrames/FactoryMgr.h"
#include "MainUI/FacObsFrames/ObserverMgr.h"
#include "MainUI/mainwindow.h"
#include "event/ZoomableGraphicsView.h"
#include "event/XYOverlayGrid.h"


// Graphics Frame
class CviewFrame : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core, public nObserver {
private:
    // Functions
    void renderQuad();
    void CreateXYview();
    void MouseGetPosXY();
    void addPoints(bool Cviewlink, int x, int y);
    std::pair<int, int> calculateOriginalPos(int scaled_y, int scaled_z);
    // View Variables
    std::shared_ptr<QGraphicsScene> scene;
    std::shared_ptr<ZoomableGraphicsView> graphicsView;
    std::shared_ptr<XYOverlayGrid> overlay = nullptr;
    bool isRealTime = true;
    // Offline Variables
    uint64_t ysize, xsize, zsize;
    std::shared_ptr<cv::Mat> orgimage;
    std::shared_ptr<cv::Mat> scaledImage;
    // RealtimeGPU Variables
    QVBoxLayout* layout;
    std::unique_ptr<QOpenGLShaderProgram> shaderProgram = nullptr;
    
    QOffscreenSurface* surface;
    GLuint vao, vbo, ebo;

    // Realtime GPU variables for GLTexture
    GLuint textureID;
        // select region
    bool isSelectingRegion = false;
    bool isDragging = false;
    QPointF selectionStart, selectionEnd;
    QPointF lastMousePos;
public:
    explicit CviewFrame(QWidget* parent = nullptr);
    QWidget* createFrame() override;
    void updateOffLine() override;
    void updateRealTime() override;
    void setter_Curpt(int x, int y, int z) { curpt[0] = x; curpt[1] = y; curpt[2] = z; }
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
