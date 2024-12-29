#ifndef CMesh_h
#define CMesh_h

#include "..\pch.h"
#include <QWidget>
#include <QVulkanWindow>
#include <QVulkanFunctions>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
};
struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    glm::mat4 transform;
    std::string name;
    bool systemMesh = false;

    VkDescriptorSet descSet[QVulkanWindow::MAX_CONCURRENT_FRAME_COUNT];
    VkDescriptorBufferInfo uniformBufferInfo[QVulkanWindow::MAX_CONCURRENT_FRAME_COUNT];
    VkDeviceSize vertexAllocSize;
    VkDeviceSize indexAllocSize;
    VkDeviceSize uniformAllocSize;

    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    VkDescriptorPool descPool = VK_NULL_HANDLE;
    VkDescriptorSetLayout descSetLayout = VK_NULL_HANDLE;

    VkPipelineCache pipelineCache = VK_NULL_HANDLE;
    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
    VkPipeline pipeline = VK_NULL_HANDLE;

};


#endif // CMesh_h