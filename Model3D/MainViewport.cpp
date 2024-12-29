#include "MainViewport.h"
//#include <cuda_runtime.h>

//QVulkanWindowRenderer* VulkanWindow::createRenderer() { return new VulkanRenderer(this); };

void VulkanWindow::GetDeviceInfo()
{

    QVulkanInstance* inst = this->vulkanInstance();

    QString info;
    info += "\n********************\n";
    info += " Physical Devices: " + QString::number(this->availablePhysicalDevices().count()) + "\n";

    QVulkanFunctions* f = inst->functions();
    VkPhysicalDeviceProperties props;
    f->vkGetPhysicalDeviceProperties(this->physicalDevice(), &props);
    info += " Device: " + QString::fromUtf8(props.deviceName) + "\n";
    info += " API version: " + QString::number(VK_VERSION_MAJOR(props.apiVersion)) + "."
        + QString::number(VK_VERSION_MINOR(props.apiVersion)) + "."
        + QString::number(VK_VERSION_PATCH(props.apiVersion)) + "\n";

    info += " Color format: " + QString::number(this->colorFormat()) + "\n";
    info += " Depth-stencil format: " + QString::number(this->depthStencilFormat()) + "\n";

    info += " Supported sample counts: ";
    for (int count : this->supportedSampleCounts())
        info += QString::number(count) + " ";
    info += "\n********************";
    nmainUI::statuslogs::getinstance().logNotify(info.toStdString());
}

void VulkanWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        isRightMouseButtonPressed = true;
        lastMousePosition = event->pos();
    }
    if (event->button() == Qt::MiddleButton) {
        isMidMouseButtonPressed = true;
        lastMousePosition = event->pos(); 
    }

}
void VulkanWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        isRightMouseButtonPressed = false;
    }
    if (event->button() == Qt::MiddleButton) {
        isMidMouseButtonPressed = false;
        lastMousePosition = event->pos();
    }

}
void VulkanWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (isRightMouseButtonPressed) {
        QPoint currentPosition = event->pos();
        QPoint delta = currentPosition - lastMousePosition;
        lastMousePosition = currentPosition;

        if (m_renderer) {
            transform->m_rotation[0] = delta.x() * 0.5f;
            transform->m_rotation[1] = delta.y() * 0.5f;
        }
    }
    if (isMidMouseButtonPressed) {
        QPoint delta = event->pos() - lastMousePosition; 
        lastMousePosition = event->pos(); 
        if (m_renderer) {
            transform->m_panx += delta.x() * 10.0f;
			transform->m_pany -= delta.y() * 10.0f;
        }
    }


}
void VulkanWindow::wheelEvent(QWheelEvent* event)
{
    // if (m_zoomLevel = -1.0f){ m_zoomLevel = transform->wheel_zoom_factor;    }
    int delta = event->angleDelta().y();

    float zoomSpeed = 1.0f; 
    if (delta > 0) {
        m_zoomLevel = -zoomSpeed;
    }
    else if (delta < 0) {
        m_zoomLevel = zoomSpeed;
    }

    // m_zoomLevel = std::clamp(m_zoomLevel, 0.1f, 500.0f);

    if (m_renderer) {
        transform->wheel_zoom_factor = m_zoomLevel;
    }

}

