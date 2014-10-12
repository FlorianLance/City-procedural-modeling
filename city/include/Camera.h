#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "vector.h"

enum Camera_FlyTrackball { CAMERA_FLY=0, CAMERA_TRACKBALL=1 };

//! A camera is defined by a position and 2 angles of rotations (defining the orientation)
struct Camera
{
    Vector pos;
    float rotLeft;
    float rotUp;
    int mode;       // 0=neutral, 1=rotation mode, 2=translation mode
    Camera_FlyTrackball flyOrTrackball;
    int mx,my;      // mouse position
};


inline void camInit(Camera& cam, const Camera_FlyTrackball ft=CAMERA_FLY)
{
	cam.pos = Vector(0,0,0);
    cam.rotUp = 0;
    cam.rotLeft = 0;
    cam.mode = 0;
    cam.flyOrTrackball = ft;
}


inline void camComputeDirFront( const Camera& cam, Vector& dir)
{
    if (cam.flyOrTrackball==CAMERA_FLY)
    {
        float a = (cam.rotUp * 2.0f*M_PI)/360.f;
        float b = (cam.rotLeft * 2.0f*M_PI)/360.f;
        int signz=(cam.pos[2]>0)?1:-1;
        int signy=(cam.pos[1]>0)?1:-1;
		dir = Vector(sin(b), -signz*signy*sin(a)*cos(b), -cos(a)*cos(b));
    }
    else
    {
		dir = Vector(-cam.pos[0], -cam.pos[1], -cam.pos[2]);
		dir = Normalized(dir);
    }

}

inline void camSetFlyTrackballMode(Camera& cam, const Camera_FlyTrackball m)
{
//    cam.flyOrTrackball = m;
    camInit( cam, m);
}

inline void camSetGL(const Camera& cam)
{

//Vec3f dir;
//camComputeDirFront(cam, dir);
//vecPrint(dir);
//printf("%f %f\n\n", cam.rotUp, cam.rotLeft);

    glMatrixMode( GL_MODELVIEW);

    if (cam.flyOrTrackball==CAMERA_FLY)
    {
        glRotatef( cam.rotUp, 1.0f, 0, 0);
        glRotatef( cam.rotLeft, 0, 1.0f, 0);
        glTranslatef( -cam.pos[0], -cam.pos[1], -cam.pos[2]);
    }
    else
    {
        glTranslatef(cam.pos[0], -cam.pos[1], -cam.pos[2]);
        glRotatef( cam.rotUp, 1.0f, 0, 0);
        glRotatef( cam.rotLeft, 0, 1.0f, 0);
    }
}

inline void camTurnUpDown(Camera& cam, const float stepR=2.f)
{
    cam.rotUp += stepR;
}
inline void camTurnLeftRight(Camera& cam, const float stepR=2.f)
{
    cam.rotLeft += stepR;
}


enum DIR { FRONT, BACK, LEFT, RIGHT, UP, DOWN };
inline void camTranslate(Camera& cam, const DIR where, const float c=1.f)
{
    Vector dir, up, right;

    camComputeDirFront( cam, dir);

    //vecInit( dir, a, b);
    if (dir[1]>=1.f)
        up = Vector(1, 0, 0);
    else
        up = Vector(0, 1, 0);
    
	right = dir/up;

    Vector tr(0,0,0);

    switch (where)
    {
    case UP:
        tr = c *up;
        break;

    case DOWN:
        tr = -c *up;
        break;

    case FRONT:
        tr = c * dir;
        break;

    case BACK:
        tr = -c * dir;
        break;

    case LEFT:
        tr = -c * right;
        break;

    case RIGHT:
        tr = c * right;
        break;
    }

	cam.pos += tr ;
}

enum CAMERA_MODE { CAMERA_STOP, CAMERA_ROTATION, CAMERA_TRANSLATION };
inline void camStartMove( Camera& cam, const CAMERA_MODE mode, const int x, const int y)
{
    cam.mode = mode;
    cam.mx = x;
    cam.my = y;
}

inline void camMove( Camera& cam, const int x, const int y)
{
    if (cam.mode==CAMERA_TRANSLATION)
    {
        if (y>cam.my) camTranslate( cam, BACK);
        else camTranslate( cam, FRONT);
    }
    else if (cam.mode==CAMERA_ROTATION)
    {
//        if (abs(y-cam.my)>3)
        camTurnUpDown( cam, 0.5f*(y-cam.my));
//        if (abs(x-cam.mx)>3)
        camTurnLeftRight( cam, 0.5f*(x-cam.mx));
    }
    cam.mx = x;
    cam.my = y;
}


#endif // CAMERA_H_INCLUDED
