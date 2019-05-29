#include <math.h>
#include "camera.h"

Camera::Camera()
{

}

Camera::Camera(float x, float y, float speed)
    : x(x), y(y), speed(speed), dirx(0), diry(0)
{

}


void Camera::update(float time,float destx,float desty)
{
    float dx=this->x-destx;
    float dy=this->y-desty;
    float dist=sqrt(dx*dx+dy*dy);
    if(dist<=speed){
        this->x=destx;
        this->y=desty;
    }
    else{
        float angle=dx/dist;
        this->dirx=cos(angle);
        this->diry=sin(angle);
    }
}

