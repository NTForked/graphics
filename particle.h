#ifndef PARTICLE_H
#define PARTICLE_H
#include "vector3.h"
#include "force.h"
class Particle
{
public :
    Vector3 velocity,position;
    const float mass;
    float *deltatime;
    float lifebegin;
    Particle(const Vector3 &pos,const float &m,float *dt,const float &life)
        :velocity(Vector3()),position(pos),mass(m),deltatime(dt),lifebegin(life)
    {

    }

    void applyforce(const Force &f)
    {
        Vector3 force=f.getOrentation()*f.getStrength();
        Vector3 accleration=force/mass;
        velocity+=accleration*(*deltatime);
        proceedintime();
    }
    void proceedintime()
    {
        position+=velocity*(*deltatime);
        /*thetarotate+=rotationalvelocity*deltatime;
        while(thetarotate<0)
            thetarotate += TWOPI;
        while(thetarotate>TWOPI)
            thetarotate -= TWOPI;*/
    }
    virtual void draw()const=0;
    virtual bool collide(Particle *p)const=0;
    virtual ~Particle()
    {

    }
};

#endif // PARTICLE_H
