#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#define CAMERA_SPEED_DEFAULT 0.01

struct Camera
{
    float x,y;
    float dirx,diry;
    float speed;

    Camera();
    Camera(float x,float y,float speed);
    void update(float time,float destx,float desty);
};

#endif // CAMERA_H_INCLUDED
