#include "transformation.h"
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // for time()


float TransForm::m_rotation[3] {0.0f, 0.0f, 0.0f};
float TransForm::wheel_zoom_factor = 0.0f;
float TransForm::m_panx = 0.0f;
float TransForm::m_pany = 0.0f;
Camera TransForm::gcam{};
void TransForm::rotate(QMatrix4x4& matrix) {
    static float rx = m_rotation[0];
    static float ry = m_rotation[1];
    rx += m_rotation[0];
    ry += m_rotation[1];
    matrix.rotate(rx, 0.0f, 1.0f, 0.0f);  // Rotate along X-axis
    matrix.rotate(ry, 1.0f, 0.0f, 0.0f);  // Rotate along Y-axis
    m_rotation[0] = 0.0f; 
	m_rotation[1] = 0.0f;

}

void TransForm::scale(QMatrix4x4& matrix, float factor) {
    matrix.scale(factor);  // Scale uniformly in all directions
}

void TransForm::translate(QMatrix4x4& matrix, float x, float y, float z) {
    matrix.translate(x, y, z);  // Translate in 3D space
}
static int rol = 0;

void TransForm::viz_rotate(QMatrix4x4& matrix, float& rot_ang)
{
    if (abs(static_cast<int>(rot_ang)) == 360) {
        rol = 1;
    }
    else if (abs(static_cast<int>(rot_ang)) == 720) {
        rol = 2; 
    }
    else if (abs(static_cast<int>(rot_ang)) == 360*3) {
        rol = 3; 
    }
    else if (abs(static_cast<int>(rot_ang)) == 360 * 4) {
        rol = 0; rot_ang = 0;
    }

    if (rol == 0) {
        matrix.rotate(rot_ang, 0, 1, 1); 
    }
    if (rol == 1) {
        matrix.rotate(rot_ang, 1, 0, 1); 
    }
    if (rol == 2) {
        matrix.rotate(rot_ang, 1, 1, 0); 
    }
    if (rol == 3) {
        matrix.rotate(rot_ang, 0, 1, 0); 
    }
    

}

void TransForm::translate_pan( QMatrix4x4* viewMatrix)
{

    gcam.yaw -= m_panx * gcam.sensitivity*0.01f;
    gcam.pitch += m_pany * gcam.sensitivity * 0.01f;


    if (gcam.pitch > 89.0f) gcam.pitch = 89.0f;
    if (gcam.pitch < -89.0f) gcam.pitch = -89.0f;

    gcam.updateCameraVectors();
    m_panx = 0.0f;
	m_pany = 0.0f;
}
void TransForm::rotate_cam( QMatrix4x4* viewMatrix)
{
    *viewMatrix = gcam.getViewMatrix();
    float sensitive = 0.01f;
    static float rx = m_rotation[0] * sensitive;
	static float ry = m_rotation[1] * sensitive;
    rx += m_rotation[0] * sensitive;
	ry += m_rotation[1] * sensitive;
    viewMatrix->rotate(rx, 0.0f, 1.0f, 0.0f);  // Rotate along X-axis
	viewMatrix->rotate(ry, -1.0f, 0.0f, 0.0f);  // Rotate along Y-axis

    return;
    gcam.yaw += m_rotation[0] * gcam.sensitivity;
    gcam.pitch += m_rotation[1] * gcam.sensitivity;
    gcam.roll += m_rotation[2] * gcam.sensitivity;

    if (gcam.pitch > 89.0f) gcam.pitch = 89.0f;
    if (gcam.pitch < -89.0f) gcam.pitch = -89.0f;

    gcam.updateCameraVectors();

    *viewMatrix = gcam.getViewMatrix();

    /*m_rotation[0] = 0.0f;
    m_rotation[1] = 0.0f;
    m_rotation[2] = 0.0f;*/

}