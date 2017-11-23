#include<stdio.h>
#include<iostream>

#ifndef DSTRUCT_H
#define DSTRUCT_H

struct position{
  double x, y;
};

class TData{
public:
  double id;
  double x;
  double y;
  int z;
  double time;
  int angle;
  int v;
  bool valid;
  bool psg;
  int dist;
  bool validity = true;
  void show(){std::cout<<this->id<<","<<this->x<<","<<this->y<<","<<this->z<<","<<this->time<<","<<this->angle<<","<<this->v<<","<<this->psg<<std::endl;};
};
  

class TRData{
public:
  int tripId;
  double taxiId;
  position opos;
  double otime;
  position dpos;
  double dtime;
};




#endif
