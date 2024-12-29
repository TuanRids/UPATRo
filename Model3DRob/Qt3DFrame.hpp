#ifndef QT3DFRAME_HPP
#define QT3DFRAME_HPP

#include <QWidget>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DCore/QAttribute>
#include <Qt3DCore/QBuffer>

#include <QVector3D>
#include <QThread>
#include <QMutex>
#include <QVBoxLayout>
#include <QColor>

class Qt3DFrame : public QWidget
{
    Q_OBJECT

public:
    explicit Qt3DFrame(QWidget* parent = nullptr);
    ~Qt3DFrame() ;

    // Setup predefined animations
    void setupPredefinedAnimation() ;

    // Update robot position in real-time using keypoints
    void updateRobotPosition(const QVector<QVector3D>& keypoints) ;

    // Draw a line and return its ID
    int drawLine(const QVector3D& start, const QVector3D& end, const QColor& color = Qt::white) ;

    // Adjust an existing line by its ID
    void adjustLine(int lineId, const QVector3D& newStart, const QVector3D& newEnd) ;

    // Draw a curve and return its ID
    int drawCurve(const QVector<QVector3D>& points, const QColor& color = Qt::white) ;

private:
    Qt3DExtras::Qt3DWindow* m_view;                // Qt3D window for rendering
    QWidget* m_container;                           // Container widget for the Qt3D window
    Qt3DCore::QEntity* m_rootEntity;                // Root entity of the 3D scene
    Qt3DRender::QCamera* m_camera;                  // Camera for the scene
    Qt3DExtras::QOrbitCameraController* m_cameraController; // Camera controller

    // Light entity
    Qt3DCore::QEntity* m_lightEntity;

    // Structures to manage lines and curves
    struct Line {
        Qt3DCore::QEntity* entity;
        Qt3DRender::QGeometryRenderer* renderer;
    };
    QList<Line> m_lines;

    struct Curve {
        Qt3DCore::QEntity* entity;
        Qt3DRender::QGeometryRenderer* renderer;
        Qt3DCore::QAttribute* positionAttribute;
        Qt3DCore::QBuffer* vertexBuffer;
    };
    QList<Curve> m_curves;

    QMutex m_mutex; // Mutex for thread safety

    // Initialize the 3D scene
    void initScene() ;

    // Thread for handling data updates
    QThread* m_updateThread;

    // Private slots for thread operations
private slots:
    void handleUpdateRobotPosition(const QVector<QVector3D>& keypoints) ;
};

#endif // QT3DFRAME_HPP
