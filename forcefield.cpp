#include "forcefield.h"




ForceField::ForceField(const Vector3 &c,const float &r,const float &mf,const ParticleSystem *ps,const unsigned char &c)
    :center(c),radius(r),MaxForce(mf),count(c),pars(ps)
{

}

void ForceField::applyforceonsystems() const
{
    for(unsigned char i=0;i<count;i++)
    {
        int n=pars[i].particles.size();
    }
}

void ForceField::applyforce(Particle *p) const
{
    Vector3 orentation=center-p->position;
    float strength=1-orentation.length()/radius;
    if(strength<=0)
        return;
    p->applyforce(Force(orentation,strength*MaxForce));
}
