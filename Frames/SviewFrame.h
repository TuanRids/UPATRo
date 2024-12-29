#ifndef SSCANFRAME_H
#define SSCANFRAME_H

#include "../pch.h"
#include "PAUTFileReader/AscanProcessor.h"
#include "MainUI/FacObsFrames/FactoryMgr.h"
#include "MainUI/FacObsFrames/ObserverMgr.h"
#include "MainUI/mainwindow.h"
#include "event/ZoomableGraphicsView.h"
#include "event/XYOverlayGrid.h"

// Graphics Frame
class SviewFrame : public QOpenGLWidget, public QOpenGLFunctions_4_3_Core, public nObserver {
    Q_OBJECT
private:
    // Functions
    void MouseGetPosXY(std::shared_ptr<ZoomableGraphicsView> graphicsView);
    void addPoints(bool Cviewlink, int x, int y);
    std::pair<int, int> calculateOriginalPos(int scaled_y, int scaled_z);
    void renderQuad();
    // View Variables
    std::shared_ptr<XYOverlayGrid> overlay = nullptr;
    std::shared_ptr<QGraphicsScene> scene;
    std::shared_ptr<ZoomableGraphicsView> graphicsView;
    // Offline Variables
    uint64_t ysize, xsize, zsize;
    std::shared_ptr<cv::Mat> orgimage;
    std::shared_ptr<cv::Mat> scaledImage;
    bool isRealTime = true;
    // RealtimeGPU Variables
    QVBoxLayout* layout;
    std::unique_ptr<QOpenGLShaderProgram> shaderProgram = nullptr;
    //QOpenGLVertexArrayObject vao;
   // QOpenGLBuffer vbo;
    QOffscreenSurface* surface;
    int vertexLocation{ 0 };
    int colorLocation{ 0 };

    // Realtime GPU variables for GLTexture
    QOpenGLBuffer ebo;      
    GLuint textureID;          
    GLuint vao, vbo;
    // select region
    bool isSelectingRegion = false;
    bool isDragging = false;
    QPointF selectionStart, selectionEnd;
    QPointF lastMousePos;

    cv::Point startPt, endPt;
	int imgWidth, imgHeight;
public:
    explicit SviewFrame(QWidget* parent = nullptr);
    QWidget* createFrame() override;
    void updateOffLine() override;
    void updateRealTime() override;
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
