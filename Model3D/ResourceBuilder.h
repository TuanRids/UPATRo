#ifndef RESOURCE_BUILDER_H
#define RESOURCE_BUILDER_H

#include "..\pch.h"

#include <QVulkanFunctions>
#include <stdexcept>
#include <vector>
#include <string>
#include <QWidget>
#include <cmath>
#include <QVulkanWindow>
#include "vulkan/vulkan.h"
#include "CMesh.h"

class ResourceBuilder {
public:
    ResourceBuilder(QVulkanWindow* gm_VulWindow):m_deviFunc(nullptr){
        m_VulWindow = gm_VulWindow;        }
    void createResources(Mesh& gmesh);
    void releaseResources(Mesh& gmesh);
    inline VkDeviceSize aligned(VkDeviceSize v, VkDeviceSize byteAlign);
private:

    void createBuffer(Mesh& gmesh);
    void allocateMemory(Mesh& gmesh);
    void createDescriptor(Mesh& gmesh);
    void createPipeLine(Mesh& gmesh);

    VkShaderModule createShader(const QString& name);
    QVulkanDeviceFunctions* m_deviFunc;
    VkDevice m_device;
    QVulkanWindow* m_VulWindow;

    static int concurrentFrameCount;
    VkResult result;
};

#endif // RESOURCE_BUILDER_H
