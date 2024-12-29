#ifndef MAINVIEWPORT_H
#define MAINVIEWPORT_H
#include "..\pch.h"
#include <QVulkanWindow>
#include "MeshManager.h"
#include <QVulkanFunctions>
#include "..\MainUI\statuslogs.h"
#include "Transformation.h"
class MeshRenderer;



#include <QObject>
#include <QVulkanInstance>




class VulkanWindow : public QVulkanWindow // QVulkanWindow 
{
    Q_OBJECT

public:
    VulkanWindow() : m_renderer(nullptr) { transform = std::make_unique<TransForm>(); }

    QVulkanWindowRenderer* createRenderer() override { m_renderer = new MeshRenderer(this, 1); return m_renderer; }
    void PautINIT(Mesh& mesh) {
        GetDeviceInfo();
        //m_renderer->MeshInit(mesh);  
          };
    void GetDeviceInfo();

protected:

private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    //void GetDeviceInfo();
    QPoint lastMousePosition;
    bool isRightMouseButtonPressed = false;
    bool isMidMouseButtonPressed = false;
    MeshRenderer* m_renderer;
    float m_zoomLevel = -1.0f;
    // ========= 
    std::unique_ptr<TransForm> transform;
};

#endif