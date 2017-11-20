#include<string.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>
#include<istream>
#include<ostream>
#include<fstream>
#include "Setdist.h"
#include "TDNode.h"
#include "TDList.h"

#ifndef TDM_H
#define TDM_H







class TDManager{
private:
  vector<string> flist;
  TDList* Dlist;
  const char* foldername;
  char logname[100];	
  const char* date;
  bool valid;
  void setup();
  ofstream* logdata;
  

public:
  TDManager();
  TDManager(const char* folder);
  void set_input(const char* folder);
  void datepath(){ std::cout<<this->date<<std::endl;};
  void extTripData();
  //void extRootData();
};








#endif
