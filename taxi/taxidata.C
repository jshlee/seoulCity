#include<string.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>
#include<istream>
#include<ostream>
#include<fstream>
#include "Setdist.C"
using namespace std;

class TaxiData{
private:
  int listnum=0;
  string fname[100];
  string folder = "/classified";
  ofstream logdata;
  
  int classify(double taxi_x, double taxi_y);//classify the taxi`s local destrict by GPS location
  
public:
  TaxiData();
  void set_input(ifstream &taxilist);
  void generate();
  
};

TaxiData::TaxiData(){
  logdata = ofstream("Taxidata.log",ios_base::app);
  
}

void TaxiData::set_input(ifstream &taxilist){
 
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

void TaxiData::generate(){
  Setdist();
  int checknum=0;
  if(listnum == 0){
    logdata<<"Generating error : no files!"<<endl;
    return;
  }
  while(checknum!=listnum){
    
    logdata<< "Processing......("<<checknum+1<<"/"<<listnum<<")"<<"    ";
    
    ifstream taxidata(fname[checknum],ios_base::in);
    size_t dot = fname[checknum].find("-")-4;
    fname[checknum] = fname[checknum].substr(dot);
    fname[checknum].insert(0,"/home/jeonghun/classified/");
    ofstream newdata(fname[checknum],ios_base::out);
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
       logdata<<"done."<<endl;
       
    }
   checknum++;
   
  }
 logdata<< "Classification finished" << endl;
}


int TaxiData::classify(double taxi_x, double taxi_y){
  	
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
      if ( crosses % 2>0 ){
	
	dist = district[disnum][0].x;
	goto end;
      }
    }
  }
 end:
  return dist;
}

    
	
 




//void taxiclassification(){
int main(){
  TaxiData* taxi = new TaxiData();
  ifstream list("filelist");
  taxi->set_input(list);
  taxi->generate();
  
  cout<< "Classification finished. check the taxidata.log." << endl;
  return 0;
}
