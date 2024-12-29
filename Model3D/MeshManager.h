#ifndef MODELDATATYPE_H
#define MODELDATATYPE_H

#include "..\pch.h"
#include <vector>
#include <cmath>
#include <QWidget>
#include <QVulkanWindow>
#include "ResourceBuilder.h"
#include "Transformation.h"

class MeshRenderer : public QVulkanWindowRenderer
{
public:
    // ========= Constructor =========
    MeshRenderer(QVulkanWindow* w, bool msaa = false);
    // ========= Mesh Manager =========
    void MeshInit(Mesh& mesh);
    void MeshRelease();
  

private:
    std::vector<std::shared_ptr<Mesh>> omesh;

    void initResources() override;

    // ========= Main Rendering Methods =========
    void setupRenderEnvironment(VkCommandBuffer cb, const QSize& sz);
    void renderMesh(VkCommandBuffer cb);

    // ========= Adjust for next frame =========
    void initSwapChainResources() override;
    void releaseSwapChainResources() override {};
    void releaseResources() override;
    void startNextFrame() override;

    void test_object();
    void InitAxisGizmo();
    void InitMSAA();


    std::unique_ptr<TransForm> transform;
    QVulkanWindow* m_VulWindow;
    QVulkanDeviceFunctions* m_deviFunc;
    QMatrix4x4 m_proj; // m_swapchain
    std::unique_ptr<ResourceBuilder> upResBuilder;

};

#endif
