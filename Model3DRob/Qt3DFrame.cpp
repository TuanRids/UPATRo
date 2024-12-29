#include "Qt3DFrame.hpp"

#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMaterial>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DRender/QPointLight>
#include <Qt3DExtras/QPhongAlphaMaterial>
#include <QVBoxLayout>

// Constructor
Qt3DFrame::Qt3DFrame(QWidget* parent)
    : QWidget(parent),
    m_view(new Qt3DExtras::Qt3DWindow()),
    m_container(QWidget::createWindowContainer(m_view, this)),
    m_rootEntity(new Qt3DCore::QEntity()),
    m_camera(m_view->camera()),
    m_cameraController(new Qt3DExtras::QOrbitCameraController(m_rootEntity)),
    m_lightEntity(new Qt3DCore::QEntity(m_rootEntity)),
    m_updateThread(new QThread(this))
{
    // Setup layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_container);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // Configure camera
    m_camera->lens()->setPerspectiveProjection(45.0f, float(width()) / height(), 0.1f, 1000.0f);
    m_camera->setPosition(QVector3D(0, 0, 20.0f));
    m_camera->setViewCenter(QVector3D(0, 0, 0));

    // Configure camera controller
    m_cameraController->setCamera(m_camera);

    // Initialize the 3D scene
    initScene();

    // Set the root entity for the view
    m_view->setRootEntity(m_rootEntity);

    // Move data update operations to a separate thread
    // Connect signals and slots for thread-safe operations
    connect(this, &Qt3DFrame::updateRobotPosition, this, &Qt3DFrame::handleUpdateRobotPosition);
    this->moveToThread(m_updateThread);
    m_updateThread->start();
}

// Destructor
Qt3DFrame::~Qt3DFrame()
{
    m_updateThread->quit();
    m_updateThread->wait();
}

// Initialize the 3D scene with lighting and a sample object
void Qt3DFrame::initScene()
{
    // Setup directional light
    auto* light = new Qt3DRender::QDirectionalLight(m_lightEntity);
    light->setColor("white");
    light->setIntensity(1.0f);
    light->setWorldDirection(QVector3D(-1, -1, -1));

    auto* lightTransform = new Qt3DCore::QTransform();
    lightTransform->setTranslation(QVector3D(10, 10, 10));
    lightTransform->setRotation(QQuaternion::fromEulerAngles(-45.0f, 0.0f, 0.0f));

    m_lightEntity->addComponent(light);
    m_lightEntity->addComponent(lightTransform);

    // Add a sample sphere entity
    Qt3DCore::QEntity* sphereEntity = new Qt3DCore::QEntity(m_rootEntity);

    auto* sphereMesh = new Qt3DExtras::QSphereMesh();
    sphereMesh->setRadius(1.0f);

    auto* sphereMaterial = new Qt3DExtras::QPhongMaterial();
    sphereMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));

    auto* sphereTransform = new Qt3DCore::QTransform();
    sphereTransform->setTranslation(QVector3D(0, 0, 0));

    sphereEntity->addComponent(sphereMesh);
    sphereEntity->addComponent(sphereMaterial);
    sphereEntity->addComponent(sphereTransform);
}

// Setup predefined animations (to be implemented)
void Qt3DFrame::setupPredefinedAnimation()
{
    // TODO: Implement predefined animations using Qt3DAnimation module
    // Example: Create animation clips, mixers, and bind them to entities
}

// Slot to handle real-time robot position updates
void Qt3DFrame::handleUpdateRobotPosition(const QVector<QVector3D>& keypoints)
{
    QMutexLocker locker(&m_mutex);
    // TODO: Update the transforms of robot parts based on keypoints
    // Example: Iterate through keypoints and update corresponding entities
}

// Public method to update robot position (emits signal to separate thread)
void Qt3DFrame::updateRobotPosition(const QVector<QVector3D>& keypoints)
{
    emit updateRobotPosition(keypoints);
}

// Draw a line between two points with a specified color
int Qt3DFrame::drawLine(const QVector3D& start, const QVector3D& end, const QColor& color)
{
    QMutexLocker locker(&m_mutex);

    // Create geometry for the line
    Qt3DCore::QGeometry* geometry = new Qt3DCore::QGeometry();

    // Define the positions of the line endpoints
    QVector<QVector3D> positions = { start, end };
    QByteArray bufferBytes;
    bufferBytes.resize(positions.size() * sizeof(QVector3D));
    memcpy(bufferBytes.data(), positions.constData(), bufferBytes.size());

    // Create a buffer and set its data
    Qt3DCore::QBuffer* vertexBuffer = new Qt3DCore::QBuffer(geometry);
    vertexBuffer->setData(bufferBytes);

    // Define the position attribute
    Qt3DCore::QAttribute* positionAttribute = new Qt3DCore::QAttribute(geometry);
    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(vertexBuffer);
    positionAttribute->setByteOffset(0);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(positions.size());

    geometry->addAttribute(positionAttribute);

    // Create a geometry renderer for the line
    Qt3DRender::QGeometryRenderer* renderer = new Qt3DRender::QGeometryRenderer();
    renderer->setGeometry(geometry);
    renderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    renderer->setVertexCount(positions.size());

    // Create an entity for the line
    Qt3DCore::QEntity* lineEntity = new Qt3DCore::QEntity(m_rootEntity);

    // Create a material for the line
    Qt3DExtras::QPhongMaterial* material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(color);

    lineEntity->addComponent(renderer);
    lineEntity->addComponent(material);

    // Store the line information for future adjustments
    Line line;
    line.entity = lineEntity;
    line.renderer = renderer;
    m_lines.append(line);

    return m_lines.size() - 1; // Return the ID of the new line
}

// Adjust an existing line by updating its start and end points
void Qt3DFrame::adjustLine(int lineId, const QVector3D& newStart, const QVector3D& newEnd)
{
    QMutexLocker locker(&m_mutex);

    if (lineId < 0 || lineId >= m_lines.size())
        return;

    Line& line = m_lines[lineId];

    // Retrieve the geometry from the renderer
    Qt3DCore::QGeometry* geometry = line.renderer->geometry();
    if (!geometry)
        return;

    // Get the position attribute
    Qt3DCore::QAttribute* positionAttribute = geometry->attributes().at(0);
    Qt3DCore::QBuffer* vertexBuffer = positionAttribute->buffer();

    // Update the buffer data with new positions
    QVector<QVector3D> positions = { newStart, newEnd };
    QByteArray bufferBytes;
    bufferBytes.resize(positions.size() * sizeof(QVector3D));
    memcpy(bufferBytes.data(), positions.constData(), bufferBytes.size());
    vertexBuffer->setData(bufferBytes);
}

// Draw a curve (line strip) through multiple points with a specified color
int Qt3DFrame::drawCurve(const QVector<QVector3D>& points, const QColor& color)
{
    QMutexLocker locker(&m_mutex);

    if (points.size() < 2)
        return -1;

    // Create geometry for the curve
    Qt3DCore::QGeometry* geometry = new Qt3DCore::QGeometry();

    // Define the positions of the curve points
    QByteArray bufferBytes;
    bufferBytes.resize(points.size() * sizeof(QVector3D));
    memcpy(bufferBytes.data(), points.constData(), bufferBytes.size());

    // Create a buffer and set its data
    Qt3DCore::QBuffer* vertexBuffer = new Qt3DCore::QBuffer(geometry);
    vertexBuffer->setData(bufferBytes);

    // Define the position attribute
    Qt3DCore::QAttribute* positionAttribute = new Qt3DCore::QAttribute(geometry);
    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(vertexBuffer);
    positionAttribute->setByteOffset(0);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(points.size());

    geometry->addAttribute(positionAttribute);

    // Create a geometry renderer for the curve
    Qt3DRender::QGeometryRenderer* renderer = new Qt3DRender::QGeometryRenderer();
    renderer->setGeometry(geometry);
    renderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::LineStrip);
    renderer->setVertexCount(points.size());

    // Create an entity for the curve
    Qt3DCore::QEntity* curveEntity = new Qt3DCore::QEntity(m_rootEntity);

    // Create a material for the curve
    Qt3DExtras::QPhongMaterial* material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(color);

    curveEntity->addComponent(renderer);
    curveEntity->addComponent(material);

    // Store the curve information for future adjustments
    Curve curve;
    curve.entity = curveEntity;
    curve.renderer = renderer;
    curve.positionAttribute = positionAttribute;
    curve.vertexBuffer = vertexBuffer;
    m_curves.append(curve);

    return m_curves.size() - 1; // Return the ID of the new curve
}
