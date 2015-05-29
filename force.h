#ifndef FORCE_H
#define FORCE_H
struct Force
{
private :
    float strength;
    Vector3 orentation;
public :
    Force(const Vector3 &v,const float &s)
        :strength(s),orentation(v)
    {
        orentation.Normalize();
    }
    Force(const Force &f)
        :strength(f.strength),orentation(f.orentation)
    {

    }
   
    float getStrength() const
    {
        return strength;
    }
    void setStrength(const float &value)
    {
        strength=value;
    }

    Vector3 getOrentation() const
    {
        return orentation;
    }
    void setOrentation(const Vector3 &value)
    {
        orentation=value;
        orentation.Normalize();
    }
};
#endif // FORCE_H
