#ifndef ASCANFRAME_H
#define ASCANFRAME_H

#include "..\pch.h"
#include "PAUTFileReader/AscanProcessor.h"
#include "MainUI/FacObsFrames/FactoryMgr.h"
#include "MainUI/FacObsFrames/ObserverMgr.h"
#include "MainUI/mainwindow.h"
#include "Pylon/pylon/PylonIncludes.h"

// Aview Frame
class AviewFrame : public QOpenGLWidget, public QOpenGLFunctions_4_3_Core, public nObserver {
private:
    //************** Method
    void RenderFrame();
    void drawAxesAndGrid(float maxY);
    //************** Properties   
    std::shared_ptr<QGraphicsScene> scene;
    std::shared_ptr<QGraphicsView> graphicsView;

    QValueAxis* axisX;
    QValueAxis* axisY;
    QVector<QPointF> points;

    QChart* chart;
    QSplineSeries* lineSeries = nullptr;
    QChartView* chartView;
    bool isRealTime = true;

    // RealtimeGPU Variables
    QVBoxLayout* layout;
    std::unique_ptr<QOpenGLShaderProgram> shaderProgram = nullptr;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOffscreenSurface* surface;

    // Realtime GPU variables for GLTexture
    QOpenGLBuffer ebo;
    GLuint textureID;

    // Grid
    QOpenGLBuffer gridVbo;
    QOpenGLVertexArrayObject gridVao;
    int gridVertexCount = 0;
public:
    explicit AviewFrame(QWidget* parent = nullptr);
    QWidget* createFrame() override;
    void updateOffLine() override;
    void updateRealTime() override ;
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
};

#endif
