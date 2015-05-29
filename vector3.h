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
    static float anglebetweeninradian(const Vector3 &v1,const Vector3 &v2)
    {
        return acos((v1.x*v2.x+v1.y*v2.y+v1.z*v2.z)/(v1.length()*v2.length()));
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
    bool operator ==(const Vector3 &v)const
    {
        return (x==v.x)&&(y==v.y)&&(z==v.z);
    }
    bool operator !=(const Vector3 &v)const
    {
        return !operator==(v);
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
    Vector3 &operator -=(const Vector3& other)
    {
        x-=other.x;
        y-=other.y;
        z-=other.z;
        return *this;
    }
    Vector3 &operator *=(const float& scale)
    {
        x*=scale;
        y*=scale;
        z*=scale;
        return *this;
    }
    static bool isperpendicular(const Vector3 &u,const Vector3 &v)
    {
        return (u*v)==0;
    }
    static bool isparallel(const Vector3 &u,const Vector3 &v)
    {
        Vector3 zero;
        if((v==zero)||(u==zero))
            return true;
        return ((u.x/v.x)==(u.y/v.y))&&((u.y/v.y)==(u.z/v.z));
    }
    Vector3 &operator /=(const float& scale)
    {
        try
        {
            x/=scale;
            y/=scale;
            z/=scale;
            return *this;
        }
        catch(exception e)
        {
            cerr<<e.what()<<'\n';
        }
    }
    void Translate(const Vector3 &v)
    {
        x+=v.x;
        y+=v.y;
        z+=v.z;
    }
    void RotateX(const float &angle)
    {
        float y0=y;
        float z0=z;
        float theta=angle*PIdiv180;
        float cost=(float)cos(theta);
        float sint=(float)sin(theta);

        z=y0*sint+z0*cost;
        y=y0*cost-z0*sint;
    }
    void RotateY(const float &angle)
    {
        float x0=x;
        float z0=z;
        float theta=angle*PIdiv180;
        float cost=(float)cos(theta);
        float sint=(float)sin(theta);

        z=x0*sint+z0*cost;
        x=x0*cost-z0*sint;

    }
    void RotateZ(const float &angle)
    {
        float x0=x;
        float y0=y;
        float theta=angle*PIdiv180;
        float cost=(float)cos(theta);
        float sint=(float)sin(theta);

        y=x0*sint+y0*cost;
        x=x0*cost-y0*sint;
    }

    void Rotate(const Vector3 &v,const float &theta1)
    {
        float a=x,b=y,c=z;

        float theta=theta1*PIdiv180;

        x=(cos(theta)+(v.x*v.x)*(1-cos(theta)))*a;
        x+=(v.x*v.y*(1-cos(theta))-v.z*sin(theta))*b;
        x+=(v.x*v.z*(1-cos(theta))+v.y*sin(theta))*c;

        y=(v.y*v.x*(1-cos(theta))+v.z*sin(theta))*a;
        y+=(cos(theta)+v.y*v.y*(1-cos(theta)))*b;
        y+=(v.y*v.z*(1-cos(theta))-v.x*sin(theta))*c;

        z=(v.z*v.x*(1-cos(theta))-v.y*sin(theta))*a;
        z+=(v.z*v.y*(1-cos(theta))+v.x*sin(theta))*b;
        z+=(cos(theta)+v.z*v.z*(1-cos(theta)))*c;
    }
    void Scale(const float &c)
    {
        x*=c;
        y*=c;
        z*=c;
    }

    const float *toArray()const
    {
        float *a=new float[3];
        a[0]=x;
        a[1]=y;
        a[2]=z;
        return a;
    }
    static Vector3 crossproduct(const Vector3 &v,const Vector3 &u)
    {
        Vector3 resVector;
        resVector.x = u.y*v.z - u.z*v.y;
        resVector.y = u.z*v.x - u.x*v.z;
        resVector.z = u.x*v.y - u.y*v.x;

        return resVector;
    }
};
#endif // VECTOR3_H
