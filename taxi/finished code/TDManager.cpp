#include<string.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>
#include<istream>
#include<ostream>
#include<fstream>
#include<set>
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
  this->date = folder.c_str();
  char logname[100];
  sprintf(logname,"%sTaxidata.log",date);
      
  TDManager::logdata = new ofstream(logname, ios_base::out);
  bool dvalid = true;
  for(vector<string>::iterator i = flist.begin(); i!=flist.end();i++){
    
    TDNode* data = new TDNode((*i).c_str(),date);
   
    Dlist->add(data);
    if(!data->is_valid()){
      // dvalid = false; //all data must exist!
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


void TDManager::extTripData(){
  //check the validity
  
  if (!this->valid) {
    std::cout<<"not valid Manager"<<std::endl;
    *(this->logdata)<<"TDManager validity is false. extraction failed."<<std::endl;
    return;
  }
  char trippath[100];
  sprintf(trippath,"%sTripdata.DAT",date);
  //set up file
  
  ofstream tripdata(trippath,ios_base::out);
  map<double,size_t> taxilist;
  map<double,size_t> templist;
  TData* tripo ,* tripd;
  tripo = NULL;
  tripd = NULL;
  int index = 1;
  tripdata<<fixed;
  tripdata.precision(0);
  std::cout<<fixed;
  std::cout.precision(0);
  
  for (int inteval = 0; inteval<this->flist.size();inteval++ ){
   

    if(TDManager::Dlist->get(inteval)==NULL) continue;
    //call the all taxi ID list for one node    
    taxilist = TDManager::Dlist->get(inteval)->get_taxilist();
    
    //for all ID in that time, check the taxi get psg.
    //##additionally the taxi on the putoff map. continue the process.
    //it will do better performance.
    for (map<double,size_t>::iterator ntaxi= taxilist.begin(); ntaxi!=taxilist.end();ntaxi++){
      
      tripo = TDManager::Dlist->get(inteval)->puton(ntaxi);
      
      //when the taxi get the psg, then
      if(tripo!=NULL){
	if(tripo->x==5) continue;
	if(tripo->y==5) continue;
	//std::cout<<*ntaxi;
	//std::cout<<this->flist[inteval]<<":"<<tripo->x<<","<<tripo->y<<","<<tripo->v<<","<<tripo->z<<","<<tripo->psg<<","<<tripo->angle<<","<<tripo->id<<","<<tripo->time<<std::endl;
	//for all time inteval, check the when the psg put off
	for(int chindex = inteval; chindex <this->flist.size();chindex++ ){
	  if(TDManager::Dlist->get(chindex)==NULL) continue;
	  templist = TDManager::Dlist->get(chindex)->get_taxilist();
	  map<double,size_t>::iterator tmpit = templist.find((*ntaxi).first);
	  if(tmpit == templist.end()) continue;
	  tripd = TDManager::Dlist->get(chindex)->putoff(tmpit);
	  if(tripd!= NULL) break;
	}
	
	//check sucess data recoded and it will be recoded on map.
	if(tripd!= NULL){
	  //tripo , tripd;
	  
	  tripdata<<index<<","<<tripo->id<<","<<tripo->time<<","<<tripo->x<<","<<tripo->y<<","<<tripd->id<<","<<tripd->time<<","<<tripd->x<<","<<tripd->y<<std::endl;
	  tripo = NULL;
	  tripd = NULL;
	  index++;
	}
	//check fail recoded fail message on log
	else{
	  //log;
	  *(this->logdata)<<"fail to find tripdata for :"<<tripo->id<<","<<tripo->time<<std::endl;
	}
      }
      
    }



  }
  //extract finished







}
