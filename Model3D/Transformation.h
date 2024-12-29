#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "..\pch.h"
#include "CCamera.h"

class ITransForm {
public:
    virtual ~ITransForm() = default;

    
    static float m_rotation[3];
    static float wheel_zoom_factor;
    static float m_panx, m_pany;
    static Camera gcam;
};



class TransForm {
public:
    TransForm() {};

    void rotate(QMatrix4x4& matrix) ;
    void scale(QMatrix4x4& matrix, float factor) ;
    void translate(QMatrix4x4& matrix, float x, float y, float z) ;
    void viz_rotate(QMatrix4x4& matrix, float& rot_ang) ;
    void translate_pan( QMatrix4x4* viewMatrix);
    void rotate_cam( QMatrix4x4* viewMatrix) ;
    static float m_rotation[3];
    static float wheel_zoom_factor;
    static float m_panx, m_pany;
    static Camera gcam;
};


#endif // TRANSFORMATION_H