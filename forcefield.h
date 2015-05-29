#ifndef FORCEFIELD_H
#define FORCEFIELD_H
#include "particle.h"
#include "ParticleSystem.h"
class ForceField
{
private :
    Vector3 center;
    float radius,MaxForce;
    unsigned char count;
    ParticleSystem *pars;
public:
    ForceField(const Vector3 &c,const float &r,const float &mf,const ParticleSystem *ps,const unsigned char &c);
    void applyforceonparticle(Particle *p)const;
    void applyforceonsystems()const;
};

#endif // FORCEFIELD_H
