//***************************************************************************
//  Camera based on Vectors
//***************************************************************************
#ifndef CAMERA_H
#define CAMERA_H
#include "vector3.h"
#include <cmath>
#ifdef __linux__
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#else
#include <windows.h>
#include <gl\glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#endif

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

class Camera
{
private:
    Vector3 Position;
    Vector3 View;    
    Vector3 Up;
    Vector3 lineofsight;
    float uprotation;
public:
    Camera(const Vector3 &pos, const float &lookatx, const float &lookaty);
    void flip (const GLfloat &angle );
    void SetView(const float &x,const float &y);

    void MoveLeft(const GLfloat &distance);
    void MoveRight (const GLfloat &distance );
    void MoveForward(const GLfloat &distance);
    void MoveBackward(const GLfloat &distance );    


    void LookAt()const;
    Vector3 getView() const;
    Vector3 getPosition() const;
};
#endif
