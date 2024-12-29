#include "ResourceBuilder.h"
static const int UNIFORM_DATA_SIZE = 16 * sizeof(float);
int ResourceBuilder::concurrentFrameCount = 0;

#include <vulkan/vulkan.h>

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

void setupDebugMessenger(QVulkanInstance& vulkanInstance) {
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;

    VkDebugUtilsMessengerEXT debugMessenger;
    PFN_vkCreateDebugUtilsMessengerEXT func =
        (PFN_vkCreateDebugUtilsMessengerEXT)vulkanInstance.getInstanceProcAddr("vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(vulkanInstance.vkInstance(), &createInfo, nullptr, &debugMessenger);
    }
}


void ResourceBuilder::createResources(Mesh& gmesh)
{
    
    m_deviFunc = m_VulWindow->vulkanInstance()->deviceFunctions(m_VulWindow->device());
    m_device = m_VulWindow->device();

    try
    {
        createBuffer(gmesh);
        allocateMemory(gmesh);
        createDescriptor(gmesh);
        createPipeLine(gmesh);
    }
    catch (std::exception& e) {
        qFatal("%s", e.what());
    }
}

void ResourceBuilder::releaseResources(Mesh& mesh)
{
    if (mesh.buffer) {
        m_deviFunc->vkDestroyBuffer(m_device, mesh.buffer, nullptr);
        mesh.buffer = VK_NULL_HANDLE;
    }
    if (mesh.memory) {
        m_deviFunc->vkFreeMemory(m_device, mesh.memory, nullptr);
        mesh.memory = VK_NULL_HANDLE;
    }
    if (mesh.pipeline) {
        m_deviFunc->vkDestroyPipeline(m_device, mesh.pipeline, nullptr);
        mesh.pipeline = VK_NULL_HANDLE;
    }

    if (mesh.pipelineLayout) {
        m_deviFunc->vkDestroyPipelineLayout(m_device, mesh.pipelineLayout, nullptr);
        mesh.pipelineLayout = VK_NULL_HANDLE;
    }

    if (mesh.pipelineCache) {
        m_deviFunc->vkDestroyPipelineCache(m_device, mesh.pipelineCache, nullptr);
        mesh.pipelineCache = VK_NULL_HANDLE;
    }

    if (mesh.descSetLayout) {
        m_deviFunc->vkDestroyDescriptorSetLayout(m_device, mesh.descSetLayout, nullptr);
        mesh.descSetLayout = VK_NULL_HANDLE;
    }

    if (mesh.descPool) {
        m_deviFunc->vkDestroyDescriptorPool(m_device, mesh.descPool, nullptr);
        mesh.descPool = VK_NULL_HANDLE;
    }

}

inline VkDeviceSize ResourceBuilder::aligned(VkDeviceSize v, VkDeviceSize byteAlign)
{
    return (v + byteAlign - 1) & ~(byteAlign - 1);
}

void ResourceBuilder::createBuffer( Mesh& gmesh)
{
    concurrentFrameCount = m_VulWindow->concurrentFrameCount();
    VkBufferCreateInfo bufInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };

    const VkDeviceSize uniAlign = m_VulWindow->physicalDeviceProperties()->limits.minUniformBufferOffsetAlignment;
    gmesh.vertexAllocSize = aligned(gmesh.vertices.size() * sizeof(Vertex), uniAlign);
    gmesh.indexAllocSize = aligned(gmesh.indices.size() * sizeof(uint32_t), uniAlign);
    gmesh.uniformAllocSize = aligned(UNIFORM_DATA_SIZE, uniAlign);

    bufInfo.size = gmesh.vertexAllocSize + gmesh.indexAllocSize + concurrentFrameCount * gmesh.uniformAllocSize;
    bufInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    bufInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    VkResult result = m_deviFunc->vkCreateBuffer(m_device, &bufInfo, nullptr, &gmesh.buffer);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create buffer.");
    }
}

void ResourceBuilder::allocateMemory( Mesh& gmesh)
{

    // Allocate bind vertex buffer memory
    VkMemoryRequirements memReq = {};
    m_deviFunc->vkGetBufferMemoryRequirements(m_device, gmesh.buffer, &memReq);

    VkMemoryAllocateInfo memAllocInfo = {};
    memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memAllocInfo.allocationSize = memReq.size;
    memAllocInfo.memoryTypeIndex = m_VulWindow->hostVisibleMemoryIndex();


    VkResult result = m_deviFunc->vkAllocateMemory(m_device, &memAllocInfo, nullptr, &gmesh.memory);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate memory.");
    }

    result = m_deviFunc->vkBindBufferMemory(m_device, gmesh.buffer, gmesh.memory, 0);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to bind buffer memory.");
    }


    // Map and copy vertex data
    quint8* p = nullptr;
    result = m_deviFunc->vkMapMemory(m_device, gmesh.memory, 0, gmesh.vertexAllocSize, 0, reinterpret_cast<void**>(&p));
    //result = m_deviFunc->vkMapMemory(m_device, gmesh.memory, 0, gmesh.vertexAllocSize + gmesh.indexAllocSize, 0, reinterpret_cast<void**>(&p));
    if (result != VK_SUCCESS) { throw std::runtime_error("Failed to map vertex memory."); }
    memcpy(p, gmesh.vertices.data(), gmesh.vertices.size() * sizeof(Vertex));
    m_deviFunc->vkUnmapMemory(m_device, gmesh.memory);
    if (gmesh.indices.size() > 0) 
    {
        // Map and copy index data (right after vertex data)
        result = m_deviFunc->vkMapMemory(m_device, gmesh.memory, gmesh.vertexAllocSize, gmesh.indexAllocSize, 0, reinterpret_cast<void**>(&p));
        if (result != VK_SUCCESS) { throw std::runtime_error("Failed to map index memory."); }
        memcpy(p, gmesh.indices.data(), gmesh.indices.size() * sizeof(uint32_t));
        m_deviFunc->vkUnmapMemory(m_device, gmesh.memory);
    }


    // Map and copy uniform buffer data for each frame

    result = m_deviFunc->vkMapMemory(m_device, gmesh.memory, gmesh.vertexAllocSize + gmesh.indexAllocSize, concurrentFrameCount * gmesh.uniformAllocSize, 0, reinterpret_cast<void**>(&p));
    if (result != VK_SUCCESS) { throw std::runtime_error("Failed to map uniform memory."); }

    // Set up uniform buffer info based on vertex data
    // HAVE_TODO_CUSTOMIZE: Optimize by staging buffer instead of mapping
    QMatrix4x4 ident;
    ident.setToIdentity();
    memset(gmesh.uniformBufferInfo, 0, sizeof(gmesh.uniformBufferInfo));
    for (int i = 0; i < concurrentFrameCount; ++i) {
        const VkDeviceSize offset = gmesh.vertexAllocSize + gmesh.indexAllocSize + i * gmesh.uniformAllocSize;
        memcpy(p , ident.constData(), 16 * sizeof(float));
        gmesh.uniformBufferInfo[i].buffer = gmesh.buffer;
        gmesh.uniformBufferInfo[i].offset = offset;
        gmesh.uniformBufferInfo[i].range = gmesh.uniformAllocSize;
    }
    m_deviFunc->vkUnmapMemory(m_device, gmesh.memory);

}

void ResourceBuilder::createDescriptor(Mesh& gmesh)
{

    // Set up and create descriptor pool
    VkDescriptorPoolSize descPoolSizes = { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, uint32_t(concurrentFrameCount) };
    VkDescriptorPoolCreateInfo descPoolInfo;
    memset(&descPoolInfo, 0, sizeof(descPoolInfo));
    descPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    descPoolInfo.maxSets = concurrentFrameCount;
    descPoolInfo.poolSizeCount = 1;
    descPoolInfo.pPoolSizes = &descPoolSizes;
    result = m_deviFunc->vkCreateDescriptorPool(m_device, &descPoolInfo, nullptr, &gmesh.descPool);
    if (result != VK_SUCCESS) { throw std::runtime_error("Failed to create descriptor pool."); }

    // Set up and create descriptor layout
    VkDescriptorSetLayoutBinding layoutBinding = { 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT, nullptr };
    VkDescriptorSetLayoutCreateInfo descLayoutInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,nullptr,0,1,&layoutBinding };
    result = m_deviFunc->vkCreateDescriptorSetLayout(m_device, &descLayoutInfo, nullptr, &gmesh.descSetLayout);
	if (result != VK_SUCCESS) { throw std::runtime_error("Failed to create descriptor set layout."); }

    // Set up and create descriptor set
    for (int i = 0; i < concurrentFrameCount; ++i) {
        VkDescriptorSetAllocateInfo descSetAllocInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO, nullptr, gmesh.descPool, 1, &gmesh.descSetLayout };
        result = m_deviFunc->vkAllocateDescriptorSets(m_device, &descSetAllocInfo, &gmesh.descSet[i]);
		if (result != VK_SUCCESS) { throw std::runtime_error("Failed to allocate descriptor set."); }
        VkWriteDescriptorSet descWrite;
        memset(&descWrite, 0, sizeof(descWrite));
        descWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descWrite.dstSet = gmesh.descSet[i];
        descWrite.descriptorCount = 1;
        descWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descWrite.pBufferInfo = &gmesh.uniformBufferInfo[i];
        m_deviFunc->vkUpdateDescriptorSets(m_device, 1, &descWrite, 0, nullptr);
    }
}

void ResourceBuilder::createPipeLine( Mesh& gmesh)
{
    VkPipelineCacheCreateInfo pipelineCacheInfo;
    memset(&pipelineCacheInfo, 0, sizeof(pipelineCacheInfo));
    pipelineCacheInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    result = m_deviFunc->vkCreatePipelineCache(m_device, &pipelineCacheInfo, nullptr, &gmesh.pipelineCache);
    if (result != VK_SUCCESS) { throw std::runtime_error("Failed to create pipeline cache."); }
    // Pipeline layout
    VkPipelineLayoutCreateInfo pipelineLayoutInfo;
    memset(&pipelineLayoutInfo, 0, sizeof(pipelineLayoutInfo));
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &gmesh.descSetLayout;
    result = m_deviFunc->vkCreatePipelineLayout(m_device, &pipelineLayoutInfo, nullptr, &gmesh.pipelineLayout);
    if (result != VK_SUCCESS) { throw std::runtime_error("Failed to create pipeline layout."); }
    // Shaders
    VkShaderModule vertShaderModule = createShader(QStringLiteral(":/color_vert.spv"));
    VkShaderModule fragShaderModule = createShader(QStringLiteral(":/color_frag.spv"));

    // Graphics pipeline
    VkGraphicsPipelineCreateInfo pipelineInfo;
    memset(&pipelineInfo, 0, sizeof(pipelineInfo));
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

    VkPipelineShaderStageCreateInfo shaderStages[2] = { { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, nullptr, 0, VK_SHADER_STAGE_VERTEX_BIT, vertShaderModule, "main", nullptr },
                { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, nullptr, 0, VK_SHADER_STAGE_FRAGMENT_BIT, fragShaderModule, "main", nullptr } };
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;


    VkVertexInputBindingDescription vertexBindingDesc = { 0,sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX };
    VkVertexInputAttributeDescription vertexAttrDesc[] = {
        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, position) },   // Position
        { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, normal) } // ,     // Normal
        //{ 2, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, texCoord) },      // Texture coordinates
        //{ 3, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color) }       // Color
    };
    VkPipelineVertexInputStateCreateInfo vertexInputInfo;

    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.pNext = nullptr;
    vertexInputInfo.flags = 0;
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.pVertexBindingDescriptions = &vertexBindingDesc;
    vertexInputInfo.vertexAttributeDescriptionCount = 2;
    vertexInputInfo.pVertexAttributeDescriptions = vertexAttrDesc;

    pipelineInfo.pVertexInputState = &vertexInputInfo;

    VkPipelineInputAssemblyStateCreateInfo ia;
    memset(&ia, 0, sizeof(ia));
    ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    if (gmesh.name.find("axisGizmo") != std::string::npos) {
        ia.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    }
    else if (gmesh.name.find("Paut Object") != std::string::npos)
    {
        ia.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST; // VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    }
    else 
    {
        ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    }


    ia.primitiveRestartEnable = VK_FALSE;  // Disable primitive restart for now
    pipelineInfo.pInputAssemblyState = &ia;

    VkPipelineViewportStateCreateInfo vp;
    memset(&vp, 0, sizeof(vp));
    vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    vp.viewportCount = 1;
    vp.scissorCount = 1;
    pipelineInfo.pViewportState = &vp;

    VkPipelineRasterizationStateCreateInfo rs;
    memset(&rs, 0, sizeof(rs));
    rs.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rs.polygonMode = VK_POLYGON_MODE_FILL;
    rs.cullMode = VK_CULL_MODE_NONE; // we want the back face as well
    rs.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rs.lineWidth = 2.0f;
    pipelineInfo.pRasterizationState = &rs;

    VkPipelineMultisampleStateCreateInfo ms;
    memset(&ms, 0, sizeof(ms));
    ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    // Enable multisampling.
    ms.rasterizationSamples = m_VulWindow->sampleCountFlagBits();
    pipelineInfo.pMultisampleState = &ms;

    VkPipelineDepthStencilStateCreateInfo ds;
    memset(&ds, 0, sizeof(ds));
    ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;    
    ds.depthTestEnable = VK_TRUE;
    ds.depthWriteEnable = VK_TRUE;
    if (gmesh.name.find("axisGizmo") != std::string::npos) {
        ds.depthTestEnable = VK_FALSE;
		ds.depthWriteEnable = VK_FALSE;
    }
    ds.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    pipelineInfo.pDepthStencilState = &ds;

    VkPipelineColorBlendStateCreateInfo cb;
    memset(&cb, 0, sizeof(cb));
    cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    // no blend, write out all of rgba
    VkPipelineColorBlendAttachmentState att;
    memset(&att, 0, sizeof(att));
    att.colorWriteMask = 0xF;
    cb.attachmentCount = 1;
    cb.pAttachments = &att;
    pipelineInfo.pColorBlendState = &cb;

    VkDynamicState dynEnable[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
    VkPipelineDynamicStateCreateInfo dyn;
    memset(&dyn, 0, sizeof(dyn));
    dyn.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dyn.dynamicStateCount = sizeof(dynEnable) / sizeof(VkDynamicState);
    dyn.pDynamicStates = dynEnable;
    pipelineInfo.pDynamicState = &dyn;

    pipelineInfo.layout = gmesh.pipelineLayout;
    pipelineInfo.renderPass = m_VulWindow->defaultRenderPass();

    result = m_deviFunc->vkCreateGraphicsPipelines(m_device, gmesh.pipelineCache, 1, &pipelineInfo, nullptr, &gmesh.pipeline);
    if (result != VK_SUCCESS) { throw std::runtime_error("Failed to create graphics pipeline."); }
    if (vertShaderModule)
        m_deviFunc->vkDestroyShaderModule(m_device, vertShaderModule, nullptr);
    if (fragShaderModule)
        m_deviFunc->vkDestroyShaderModule(m_device, fragShaderModule, nullptr);
}

VkShaderModule ResourceBuilder::createShader(const QString& name)
{
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Failed to read shader %s", qPrintable(name));
        return VK_NULL_HANDLE;
    }
    QByteArray blob = file.readAll();
    file.close();

    VkShaderModuleCreateInfo shaderInfo;
    memset(&shaderInfo, 0, sizeof(shaderInfo));
    shaderInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderInfo.codeSize = blob.size();
    shaderInfo.pCode = reinterpret_cast<const uint32_t*>(blob.constData());
    VkShaderModule shaderModule;
    VkResult err = m_deviFunc->vkCreateShaderModule(m_device, &shaderInfo, nullptr, &shaderModule);
    if (err != VK_SUCCESS) {
        qWarning("Failed to create shader module: %d", err);
        return VK_NULL_HANDLE;
    }

    return shaderModule;
}

