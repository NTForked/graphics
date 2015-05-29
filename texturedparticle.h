#ifndef TEXTUREDPARTICLE_H
#define TEXTUREDPARTICLE_H
#include <particle.h>
class TexturedParticle : public Particle
{
protected :
unsigned int textureid;
public:
TexturedParticle(const Vector3 &pos,const float &m,float *dt,const float &life,const unsigned int &tex)
    :Particle(pos,m,dt,life),textureid(tex)
{

}
virtual ~TexturedParticle()
{

}

};

#endif // TEXTUREDPARTICLE_H
