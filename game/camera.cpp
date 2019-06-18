#include <iostream>
#include <math.h>
#include "camera.h"

using namespace std;

Camera::Camera()
    : x(0), y(0), dirx(0), diry(0)
{

}

Camera::Camera(float x, float y, float speed)
    : x(x), y(y), speed(speed), dirx(0), diry(0)
{

}


//void Camera::update(float time,float destx,float desty)
//{
//    if(destx!=this->x || desty!=this->y){
//        float dx=this->x-destx;
//        float dy=this->y-desty;
//        float dist=sqrt(dx*dx+dy*dy);
//        if(dist<=speed){
//            this->x=destx;
//            this->y=desty;
//            this->dirx=0;
//            this->diry=0;
//        }
//        else{
//            this->dirx=dx/speed;
//            this->diry=dy/speed;
//        }
//        this->x+=this->dirx*time;
//        this->y+=this->diry*time;
//        cout<<"camera update dest\n";
//        cout<<"camera x:"<<(int)this->x<<" y:"<<(int)this->y<<" w:"<<this->dirx<<" h:"<<this->dirx<<endl;
//    }
//    else{
//        cout<<"dont update camera\n";
//    }
//}

void Camera::update(float time,float destx,float desty)
{
//..система наследования камеры за игроком (неудачная)
//    if(destx!=this->x || desty!=this->y){
//        float dx=this->x-destx;
//        float dy=this->y-desty;
//        float dist=sqrt(dx*dx+dy*dy);
//        if(int(abs(dist))>this->speed){
//            this->x=destx;
//            this->y=desty;
//        }
//        if(int(destx)==int(this->x)){
//            this->x=int(destx);
//        }
//        if(int(desty)==int(this->y)){
//            this->y=int(desty);
//        }
//        else{
//            this->x+=dx*dist/this->speed*time/1000;
//            this->y+=dy*dist/this->speed*time/1000;
//        }
//    }
    this->x=destx;
    this->y=desty;
}

