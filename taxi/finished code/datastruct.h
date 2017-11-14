#include<stdio.h>


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
