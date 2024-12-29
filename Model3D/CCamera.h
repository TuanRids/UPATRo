#ifndef CCAMERA_H
#define CCAMERA_H
#include "..\pch.h"
#include <QVector3D>
#include <QMatrix4x4>

struct Camera {
    QVector3D position = QVector3D(0.0f, 0.0f, 3.0f);
    QVector3D front = QVector3D(0.0f, 0.0f, -1.0f);
    QVector3D up = QVector3D(0.0f, 1.0f, 0.0f);
    QVector3D right = QVector3D(1.0f, 0.0f, 0.0f);
    QVector3D worldUp = QVector3D(0.0f, 1.0f, 0.0f); // Static up direction for the world

    float yaw = -90.0f;     // Y
    float pitch = 0.0f;      // X
    float roll = 0.0f;      // Z
    float speed = 2.5f;     // Movement speed
    float sensitivity = 0.1f; // Sensitivity for mouse movement
    float zoom = 45.0f;     // Zoom level

    Camera() { updateCameraVectors(); }

    // Generates and returns the view matrix using the camera's position, front, and up vectors
    QMatrix4x4 getViewMatrix() const {
        QMatrix4x4 viewMatrix;
        viewMatrix.lookAt(position, position + front, up);
        return viewMatrix;
    }

    void updateCameraVectors() {
        QVector3D newFront;
        newFront.setX(cos(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
        newFront.setY(sin(qDegreesToRadians(pitch)));
        newFront.setZ(sin(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
        front = newFront.normalized();

        QMatrix4x4 rollMatrix;
        rollMatrix.setToIdentity();
        rollMatrix.rotate(roll, front);  
        right = QVector3D::crossProduct(front, worldUp).normalized();
        right = rollMatrix.map(right);

        up = QVector3D::crossProduct(right, front).normalized();
    }
    void czoom(float& wheel_zoom_factor) {
        position += front * wheel_zoom_factor * speed;
        wheel_zoom_factor = 0.0f;
        updateCameraVectors();
    }
};

#endif // !CCAMERA_H
