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
  
  void extTripData();
  //void extRootData();
};






/*void TDNode::set_input(ifstream &taxilist){
 
  listnum=0;
  char buf[500];
  
  while(!taxilist.eof()){
    taxilist.getline(buf,500);
    fname[listnum] = buf;
    ifstream chfile (fname[listnum],ifstream::in);
    
    if (chfile.is_open()){
      
      logdata<< fname[listnum] <<" : on loaded" <<endl;
      listnum++;
    }
    else{
      if (fname[listnum].length()!=0){
      logdata<< fname[listnum] << " : loading fail" << endl;
      }
    }
      
    if (listnum==100)
      {
	logdata<< "There is too many file. just 100 files loaded"<<endl;
	break;
      }
  }
  logdata << listnum << " file(s) checking finished" <<endl;
  
}
*/


#endif
