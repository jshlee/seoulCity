#include<string.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>
#include<istream>
#include<ostream>
#include<set>
#include<fstream>
#include "Setdist.h"

#ifndef TAXI_H
#define TAXI_H
using namespace std;

class TDNode{
private:
  set<double> tlist;
  string fname;
  ofstream* logdata;
  bool classified = false;
  bool valid = false;
  ifstream* data;
  char* date;
  //classify the taxi`s local destrict by GPS location
  int classify(double taxi_x, double taxi_y);
  
  //return data line to Tdata
  TData convert(const char* dataline);
  
  //remember last info
  double lastId, lasttime;
  size_t last;
  int tNumber=0;

public:
  //constructor
  TDNode();
  TDNode(const char* name);
  TDNode(const char* name,const char* date);
  TData* getbyID(double ID);
  bool checkID(double ID);
  //TData* getbyTime();
  TData* puton(double ID);
  TData* putoff(double ID);
  void setup();
  //void set_input(ifstream &taxilist);
  void generate();
  int number(){ return tNumber;};
  bool is_valid(){ return valid;};
  
};


 
#endif



//void taxiclassification(){
/*int main(){
  TDNode* taxi = new TDNode();
  ifstream list("filelist");
  taxi->set_input(list);
  taxi->generate();
  
  cout<< "Classification finished. check the taxidata.log." << endl;
  return 0;
}
*/
