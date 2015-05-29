#ifndef PLANE_H
#define PLANE_H
#include "vector3.h"
#include "ball.h"
struct Plane
{
private:
    Vector3 normal;
    Vector3 referencepoint;    
    float d;
public:
    Plane(const Vector3 &n,const Vector3 &r)
        :normal(n),referencepoint(r),d(-(normal*referencepoint))
    {

    }
    Plane(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3)
        :normal(Vector3::crossproduct(p1-p2,p3-p2)),referencepoint(p2),d(-(normal*referencepoint))
    {

    }
    Vector3 getNormal()const
    {
        return normal;
    }
    float distancefrom(const Vector3 &v)const
    {
        float a=normal.X();
        float b=normal.Y();
        float c=normal.Z();
        return fabs((normal*v)+getD())/sqrt(a*a+b*b+c*c);
    }
    bool collidewithball(const Ball &b)const
    {
        return distancefrom(b.getcenterofmass())<=b.getRadius();
    }
    float getD() const
    {
        return d;
    }
    void Translate(const Vector3 &v)
    {
        referencepoint.Translate(v);
        d=(-normal*referencepoint);
    }
    void Rotate(const Vector3 &p,const float &theta)
    {
        referencepoint.Rotate(p,theta);
        normal.Rotate(p,theta);
        d=(-normal*referencepoint);
    }
    bool ispointin(const Vector3 &p)const
    {
        return ((p*normal)+d)==0;
    }
    bool ispointupper(const Vector3 &p)const
    {
        return ((p*normal)+d)>0;
    }
    bool ispointlower(const Vector3 &p)const
    {
        return ((p*normal)+d)<0;
    }
};

#endif // PLANE_H

