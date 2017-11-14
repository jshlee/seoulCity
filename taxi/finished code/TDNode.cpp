#include<string.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>
#include<istream>
#include<ostream>
#include<fstream>
#include"datastruct.h"
#include "Setdist.h"
#include "TDNode.h"

using namespace std;

TDNode::TDNode(){
  TDNode::logdata = new ofstream("Taxidata.log",ios_base::app);
  
}

TDNode::TDNode(const char* name){
  TDNode::logdata = new ofstream("Taxidata.log",ios_base::app);
  TDNode::fname  = name;
  TDNode::setup();
}

TDNode::TDNode(const char* name,const char* date){
  char log[50];
  sprintf(log,"%sTaxidata.log",date);
  TDNode::logdata = new ofstream(log,ios_base::app);
  TDNode::fname  = name;
  TDNode::setup();
}

void TDNode::setup(){
  

  ifstream* chfile = new ifstream(TDNode::fname,ifstream::in);
    
  if (chfile->is_open()){
    TDNode::data = chfile;
    string line;
    int index=0;
    
    double tempid;
    while(!TDNode::data->eof()){
	
      getline(*TDNode::data,line);
      if(line.size()==0) continue;
      size_t site = line.find_first_of(",");
      string cutoff = line.substr(0,site);

      //if (cutoff.size()!=0){
      tempid = stod(cutoff);
      //}
      if (tempid != index){
      index = tempid;
      TDNode::tlist.insert(index);
      }
	
	
      }
    TDNode::tNumber = TDNode::tlist.size();
    *TDNode::logdata<< TDNode::fname <<" : on loaded" <<endl;
    TDNode::valid = true;
  }
  else{
    if (TDNode::fname.length()!=0){
      *TDNode::logdata<< TDNode::fname << " : loading fail" << endl;
    }
  }
      
    
  
}

void TDNode::generate(){
  if (TDNode::classified){return;}
  //Setdist();
  int checknum=0;
  if(!TDNode::valid){
    //TDNode::logdata<<TDNode::fname<<": Generating error : need setup!"<<endl;
    return;
  } 
  ifstream taxidata(TDNode::fname,ios_base::in);
  size_t dot = TDNode::fname.find("-")-4;
  string cname = TDNode::fname;
  cname = cname.substr(dot);
  cname.insert(0,"/home/jeonghun/classified/");
  ofstream newdata(cname,ios_base::out);
  char buf[100];
  if (taxidata.is_open()){
    string line;
      
    while(getline(taxidata,line))
      {
	double id, tx,ty,tz,time,angle,tv,vali,pass;
	stringstream ss(line);
	ss.getline(buf,100,',');
	id = (double) (atoi(buf));
	ss.getline(buf,100,',');
	tx = (double) (atoi(buf));
	ss.getline(buf,100,',');
	ty = (double) (atoi(buf));
	ss.getline(buf,100,',');
	tz = (double) (atoi(buf));
	ss.getline(buf,100,',');
	time = (double) (atof(buf));
	ss.getline(buf,100,',');
	angle = (double) (atoi(buf));
	ss.getline(buf,100,',');
	tv = (double) (atoi(buf));
	ss.getline(buf,100,',');
	vali = (double) (atoi(buf));
	ss.getline(buf,100);
	pass = (double) (atoi(buf));
	int dist = classify(tx,ty);
	newdata.precision(0);
	newdata <<fixed << id << "," << tx<< "," <<ty<< "," <<tz<< "," <<time<< "," <<angle<< "," <<tv<< "," <<vali<< "," <<pass<< "," <<dist<<endl;
	  
	//logdata.precision(0);
	//logdata <<fixed << id << "," << tx<< "," <<ty<< "," <<tz<< "," <<time<< "," <<angle<< "," <<tv<< "," <<vali<< "," <<pass<< "," <<dist<<endl;
      }
   *TDNode::logdata<<fname<<": classified"<<endl;
       
  }
   
  
 *TDNode::logdata<< "Classification finished" << endl;
 TDNode::classified = true;
}


int TDNode::classify(double taxi_x, double taxi_y){
  	
  int dist = 0 ;
  for (int disnum = 0; disnum< 25; disnum++){
    
    int entry = district[disnum].size();
    int crosses = 0;
    for (int ch = 1; ch < entry; ch ++){
      int nch = ch +1;
      if (ch+1 == entry){
	nch = 1;
      }
      
      if( (district[disnum][ch].y > taxi_y) != (district[disnum][nch].y>taxi_y)){

	double atX = (district[disnum][nch].x - district[disnum][ch].x)*(taxi_y - district[disnum][ch].y)/(district[disnum][nch].y - district[disnum][ch].y) +district[disnum][ch].x;
	if (taxi_x< atX){
	    crosses++;
	    
	}
      }
      if ( crosses % 2 ){
	
	dist = district[disnum][0].x;
	goto end;
      }
    }
  }
 end:
  return dist;
}

    
TData* TDNode::getbyID(double ID){
  if (TDNode::valid){
    this->data->clear();
    this->data->seekg(0, ios_base::beg);
    string line;
    int index  =  0;
    TData* result = new TData[15];
    while(!TDNode::data->eof()){
      getline(*TDNode::data,line);
      if(line.size()==0) continue;
      size_t site = line.find_first_of(",");
      double tempid = stod(line.substr(0,site));
      if (tempid == ID){
	result[index++] = TDNode::convert(line.c_str());
      }
      if(index>14){
	return result;
      }
    }
    
   
    
  }
  else {
    return NULL;
  }
}

bool TDNode::checkID(double ID){
  if (TDNode::valid){
    if(tlist.find(ID) != tlist.end()){
      return true;
    }
    else{
      return false;
    }
  }
    /*
    this->data->clear();
    this->data->seekg(0, ios_base::beg);


    
    bool founded = false;
    string line;
    while(!TDNode::data->eof()){
      getline(*TDNode::data,line);
      if(line.size()==0) continue;
      size_t site = line.find_first_of(",");
      double tempid = stod(line.substr(0,site));
      if (tempid == ID){
	founded = true;
	return founded;
      }
    }
    return founded;
  }*/
}

TData* TDNode::puton(double ID){
  if (TDNode::valid){
    this->data->clear();
    this->data->seekg(0, ios_base::beg);
    bool founded = false;
    int psg = -1;
    string line;
    TData* result = new TData;
    while(!TDNode::data->eof()){
      getline(*TDNode::data,line);
      if(line.size()==0) continue;
      size_t site = line.find_first_of(",");
      double tempid = stod(line.substr(0,site));
      if (tempid == ID){
	founded = true;
	*result = TDNode::convert(line.c_str());
      }
      if(psg != -1){
	if (!psg){
	  if (result->psg){
	    return result;
	  }
	}
      }
      psg = result->psg;
    }
  }
  else {
    return NULL;
  }      
}


TData* TDNode::putoff(double ID){
  if (TDNode::valid){
    this->data->clear();
    this->data->seekg(0, ios_base::beg);
    bool founded = false;
    int psg = -1;
    string line;
    TData* result = new TData;
    while(!TDNode::data->eof()){
      getline(*TDNode::data,line);
      if(line.size()==0) continue;
      size_t site = line.find_first_of(",");
      double tempid = stod(line.substr(0,site));
      if (tempid == ID){
	founded = true;
	*result = TDNode::convert(line.c_str());
      }
      if(psg != -1){
	if (psg){
	  if (!result->psg){
	    return result;
	  }
	}
      }
      psg = result->psg;
    }
  }
  else {
    return NULL;
  }      
}




TData TDNode::convert(const char* dataline){
  TData temp;
  string line = dataline;
  
  size_t site = line.find_first_of(",");
  double tempdata = stod(line.substr(0,site));
  line = line.substr(0,site+1);
  temp.id = tempdata;
  	
  site = line.find_first_of(",");
  tempdata = stod(line.substr(0,site));
  line = line.substr(0,site+1);
  temp.x = tempdata;
	
  site = line.find_first_of(",");
  tempdata = stod(line.substr(0,site));
  line = line.substr(0,site+1);
  temp.y = tempdata;

  site = line.find_first_of(",");
  tempdata = stoi(line.substr(0,site));
  line = line.substr(0,site+1);
  temp.z = tempdata;

  site = line.find_first_of(",");
  tempdata = stod(line.substr(0,site));
  line = line.substr(0,site+1);
  temp.time = tempdata;

  site = line.find_first_of(",");
  tempdata = stoi(line.substr(0,site));
  line = line.substr(0,site+1);
  temp.angle = tempdata;

  site = line.find_first_of(",");
  tempdata = stoi(line.substr(0,site));
  line = line.substr(0,site+1);
  temp.v = tempdata;

  site = line.find_first_of(",");
  tempdata = stoi(line.substr(0,site));
  line = line.substr(0,site+1);
  temp.valid = tempdata;
  if (TDNode::classified){
    site = line.find_first_of(",");
    tempdata = stoi(line.substr(0,site));
    line = line.substr(0,site+1);
    temp.psg = tempdata;
	  
    site = line.find_first_of(",");
    tempdata = stoi(line);
    temp.dist = tempdata;
  }
  else{
    site = line.find_first_of(",");
    tempdata = stoi(line);
    temp.psg = tempdata;
  }
  return temp;
}
