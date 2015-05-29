#include <iostream>
#ifdef __linux__
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SOIL/SOIL.h>
#else
#endif
#include "texturedparticle.h"
#include "ParticleSystem.h"
#include "camera.h"
#include <stdlib.h>
#include <cmath>
class BallParticle:public TexturedParticle
{
public :
    float radius;
    BallParticle(const Vector3 &pos,const float &r,const float &m,float *dt,const float &life,const unsigned int &tex)
        :TexturedParticle(pos,m,dt,life,tex),radius(r)
    {

    }
    void draw() const
    {        
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,textureid);
        glTranslatef(position.X(), position.Y(), position.Z());
        glutSolidSphere(radius,10,10);
        glPopMatrix();
    }
    bool collide(Particle *p) const
    {
        BallParticle *b=dynamic_cast<BallParticle*>(p);
        return (b);
    }
};
using namespace std;

float deltatime;
float oldtime;
float newtime;
GLuint texture;
ParticleSystem pars(1,&deltatime);
Emmiter emmiter(200,Vector3(0,0,0),&pars,1);
ForceField f(Vector3(0,3,0),3,4,&pars,1);

Camera camera(Vector3(20,20,20),0,0);
float myrand(const float &min,const float &max)
{
    return min+(max-min)*(float(rand())/float(RAND_MAX));
}

Particle *emitfunction(const Emmiter &em)
{
    float x=em.position.X(),y=em.position.Y();
    BallParticle *b=new BallParticle(Vector3(myrand(x-1,x+1),myrand(y-1,y+1),em.position.Z()),0.2f,2,&deltatime,0.0f,texture);
    b->velocity=Vector3(0,1,0);
    return b;
}

GLuint GetTextId(const char *texture_name)
{
    return(SOIL_load_OGL_texture(
               texture_name,
               SOIL_LOAD_AUTO,
               SOIL_CREATE_NEW_ID,
               SOIL_FLAG_POWER_OF_TWO
               ));

}

/* GLUT callback Handlers */
void resize(int width, int height)
{    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,(float)width/(float)height,0.1f,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 0, 0, 10, 0, 0, 0, 0, 1, 0 );
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    newtime=glutGet(GLUT_ELAPSED_TIME)/1000;
    deltatime=newtime-oldtime;
    oldtime=newtime;    
    pars.drawparticl1es();    
    glutSwapBuffers();    
}
void idle()
{
    emmiter.emitparticles();
    f.applyforceonsystems();
    pars.deleteparticles();
    glutPostRedisplay();
}

void init()
{
    const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    const GLfloat light_diffuse[] = { 1, 0.5f, 0.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };
    const GLfloat mat_emissive[]={1,0.5f,0,1};

    glClearColor(0, 0, 0, 0);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT,GL_EMISSION,mat_emissive);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);    
    glutInitWindowSize(640,480);
    glutInitWindowPosition(300,200);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Fire");
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    init();
    oldtime=glutGet(GLUT_ELAPSED_TIME)/1000;
    emmiter.emitfunc=&emitfunction;
    emmiter.deltatime=&deltatime;
    texture=GetTextId("/home/abd/graphics/fire2.jpg");
    glutMainLoop();
    return EXIT_SUCCESS;
}

