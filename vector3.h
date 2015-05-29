#ifndef VECTOR3_H
#define VECTOR3_H
#include <cmath>
#include <iostream>
#include <exception>
#define PI 3.141592653589
#define TWOPI  2*PI
#define gravity 9.7973
#define PIdiv180 (PI/180.0)


using namespace std;
class Vector3
{
private:
    float x,y,z;
public:   
    Vector3(float coordx=0,float coordy=0,float coordz=0):x(coordx),y(coordy),z(coordz)
    {

    }
    Vector3(const Vector3 &v):x(v.x),y(v.y),z(v.z)
    {
    }
    float length()const
    {
        return sqrt(x*x+y*y+z*z);
    }
    float X()const
    {
        return x;
    }
    float Y()const
    {
        return y;
    }
    float Z()const
    {
        return z;
    }
    void Normalize()
    {
        float len=length();
        if(len!=1)
        {
            x/=len;
            y/=len;
            z/=len;
        }
    }
    Vector3 operator +(const Vector3 &other)const
    {
        return Vector3(x+other.x,y+other.y,z+other.z);
    }
    Vector3 operator -(const Vector3 &other)const
    {
        return Vector3(x-other.x,y-other.y,z-other.z);
    }
    Vector3 operator -()const
    {
        return Vector3(-x,-y,-z);
    }
    Vector3 operator *(const float &scale)const
    {
        return Vector3(x*scale,y*scale,z*scale);
    }
    float operator *(const Vector3 &v)const
    {
        return x*v.x+y*v.y+z*v.z;
    }
    Vector3 operator /(const float &scale)const
    {
        try
        {
            return Vector3(x/scale,y/scale,z/scale);
        }
        catch(exception e)
        {
            cerr<<e.what()<<'\n';
        }
    }
    Vector3 &operator =(const Vector3& other)
    {
        x=other.x;
        y=other.y;
        z=other.z;
        return *this;
    }

    Vector3 &operator +=(const Vector3& other)
    {
        x+=other.x;
        y+=other.y;
        z+=other.z;
        return *this;
    }
    const float *toArray()const
    {
        float *a=new float[3];
        a[0]=x;
        a[1]=y;
        a[2]=z;
        return a;
    }
};
#endif // VECTOR3_H
