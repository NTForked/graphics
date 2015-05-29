#include "camera.h"


Vector3 Camera::getView() const
{
    return View;
}

Vector3 Camera::getPosition() const
{
    return Position;
}



Camera::Camera(const Vector3 &pos, const float &lookatx,const float &lookaty)
    :Position(pos), View(Vector3(lookatx,lookaty,pos.Z()-1))
    , Up(Vector3::crossproduct(lineofsight,Vector3(1,0,0))),lineofsight(View-pos)
    ,uprotation(0)
{

}

void Camera::flip(const GLfloat &angle)
{
    uprotation+=angle;
    while(uprotation>360)
        uprotation-=360;
    while(uprotation<0)
        uprotation+=360;
    Up.Rotate(lineofsight,uprotation);
}



void Camera::SetView(const float &x, const float &y)
{
    View=Vector3(x,y,Position.Z()-1);
    lineofsight=View-Position;
    Up=Vector3::crossproduct(lineofsight,Vector3(1,0,0));
    Up.Rotate(lineofsight,uprotation);
}

void Camera::MoveLeft(const GLfloat &distance)
{
    Vector3 a(-distance);
    Position.Translate(a);
    View.Translate(a);
}

void Camera::MoveRight(const GLfloat &distance)
{
    Vector3 a(distance);
    Position.Translate(a);
    View.Translate(a);
}

void Camera::MoveForward(const GLfloat &distance)
{
    Vector3 a=View-Position;
    a.Normalize();
    Position+=a*distance;
}

void Camera::MoveBackward(const GLfloat &distance)
{
    Vector3 a=View-Position;
    a.Normalize();
    Position+=a*(-distance);
}

void Camera::LookAt() const
{      
    gluLookAt(Position.X(),Position.Y(),Position.Z(),View.X(),View.Y(),View.Z(),Up.X(),Up.Y(),Up.Z());
}

