#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include <particle.h>
#include <deque>
using namespace std;

class Emmiter;
class ForceField;

class ParticleSystem
{
    friend class Emmiter;
    friend class ForceField;
private :
    deque<Particle*> particles;
    float elapsedtime;
    float *deltatime;
    float LifeOfParticles;
    unsigned short particlesperframe;
public :
    ParticleSystem(const float &life,float *dt)
        :elapsedtime(0),deltatime(dt),LifeOfParticles(life)
    {

    }
   
    void deleteparticles()
    {
        deque<Particle*>::iterator begin=particles.begin();
        deque<Particle*>::iterator end=particles.end();
        for(deque<Particle*>::iterator it=begin;it!=end;)
        {
            if(elapsedtime>=(*it)->lifebegin+LifeOfParticles)
            {
                delete (*it);
                it=particles.erase(it);
            }
            else
                it++;
        }
    }
    void drawparticl1es()
    {
        deque<Particle*>::const_iterator begin=particles.begin();
        deque<Particle*>::const_iterator end=particles.end();
        for(deque<Particle*>::const_iterator it=begin;it!=end;it++)
        {
            (*it)->proceedintime();
            (*it)->draw();
        }
        elapsedtime+=(*deltatime);      
    }
};
class Emmiter
{
public :
    unsigned short ParticlesPerSecond;    
    Vector3 position;
    ParticleSystem *ps;
    unsigned char count;
    float *deltatime;
    Particle *(*emitfunc)(const Emmiter &em);
    Emmiter(const unsigned short &parpersec,const Vector3 &pos,ParticleSystem *p,const unsigned char &c)
        :ParticlesPerSecond(parpersec),position(pos),ps(p),count(c)
    {

    }
    unsigned short particlesperframe()const
    {
        return ParticlesPerSecond*(*deltatime);
    }
    void emitparticles()const
    {
        unsigned short numpars=particlesperframe();
        Particle *p=0;
        for(unsigned char i=0;i<count;i++)
        {
            for(unsigned short j=0;j<numpars;j++)
            {
                p=emitfunc(*this);
                p->lifebegin=ps->elapsedtime;
                ps[i].particles.push_back(p);
            }
        }
    }
};
class ForceField
{
private :
    Vector3 center;
    float radius,MaxAcceleration;
    unsigned char count;
    ParticleSystem *pars;
public:
    ForceField(const Vector3 &cen,const float &r,const float &mf,ParticleSystem *ps,const unsigned char &c);
    void applyforceonparticle(Particle *p)const;
    void applyforceonsystems()const;
};


ForceField::ForceField(const Vector3 &cen,const float &r,const float &mf,ParticleSystem *ps,const unsigned char &c)
    :center(cen),radius(r),MaxAcceleration(mf),count(c),pars(ps)
{

}

void ForceField::applyforceonsystems() const
{
    for(unsigned char i=0;i<count;i++)
    {
        ParticleSystem p=pars[i];
        for(deque<Particle*>::const_iterator it=p.particles.begin();it!=p.particles.end();it++)
        {
            applyforceonparticle(*it);
        }
    }
}

void ForceField::applyforceonparticle(Particle *p) const
{
    Vector3 orentation=center-p->position;
    float strength=1-orentation.length()/radius;
    if(strength<=0)
        return;
    p->applyforce(Force(orentation,strength*MaxAcceleration*p->mass));
}

#endif // PARTICLESYSTEM_H
