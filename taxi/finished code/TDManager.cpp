#include<string.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>
#include<istream>
#include<ostream>
#include<fstream>
#include "TDManager.h"
#include "Setdist.h"
#include "TDNode.h"
#include "TDList.h"

using namespace std;

TDManager::TDManager(){
  TDManager::valid = false;
}
TDManager::TDManager(const char * folder){
  Dlist = new TDList();
  TDManager::set_input(folder);
}

void TDManager::set_input(const char* folder){
  TDManager::foldername = folder;
  char filename[500];
  sprintf(filename, "%s000000.DAT",folder);
  ifstream* chfile = new ifstream(filename,ifstream::in);
  if (chfile->is_open()){
    
    TDManager::valid = true;
    int h=0;
    int m=0;
    int s=0;
    float count = 0;
    while(h<24){
      if (count==60){
	count = 0;
	h++;
      }
      m = (int)count;
      s = ((int)(2*count)%2)*30;
      sprintf(filename,"%s%02d%02d%02d.DAT",folder,h,m,s);
      TDManager::flist.push_back(filename);
      
      count += 2.5;
    }
    
    TDManager::setup();
  }
  else{
    cout<<"fail to loads"<<endl;
  }


}

void TDManager::setup(){
  string folder = foldername;
  size_t dot = folder.find("-");
  if (dot==string::npos){
    dot = 0;
  }
  else{
    dot = dot    -4;
  }
  
  folder = folder.substr(dot);
  date = folder.c_str();
  char logname[100];
  sprintf(logname,"%sTaxidata.log",date);
      
  TDManager::logdata = new ofstream(logname, ios_base::out);
  bool dvalid = true;
  for(int i = 0; i<flist.size();i++){
    TDNode* data = new TDNode(flist.at(i).c_str(),date);
    Dlist->add(data);
    for (int j = 0; j <1111111 ; j++){
      if(data->checkID(j))
	{
	  cout<<"wow"<<endl;
	}
    }
    
    if(!data->is_valid()){
      dvalid = false;
    }
  }
 
  if(dvalid){

    TDManager::valid = true;
    *TDManager::logdata<<date<<": TDManager ready."<<endl;
    
  }
  else{
    *TDManager::logdata<<date<<": TDManager loads fail.(lack of data)"<<endl;
  }
}


