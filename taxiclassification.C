#include<string.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>
#include<istream>
#include<ostream>
#include "Setdist.C"
using namespace std;

class taxiCl{
private:
  int listnum=0;
  string flist[100];
  string folder = "/classified";
  
public:
  taxiCl();
  void set_input(ifstream &taxilist);
  
  void generate();
  int classify(double taxi_x, double taxi_y);
};

taxiCl::taxiCl(){
  Setdist();
}

void taxiCl::set_input(ifstream &taxilist){
 
  listnum=0;
  char buf[500];
  
  while(!taxilist.eof()){
    taxilist.getline(buf,500);
    flist[listnum] = buf;
    ifstream chfile (flist[listnum],ifstream::in);
    if (chfile.is_open()){
      
      cout<< flist[listnum] <<" : on loaded" <<endl;
      listnum++;
    }
    else{
      if (flist[listnum].length()!=0){
      cout<< flist[listnum] << " : loading fail" << endl;
      }
    }
      
    if (listnum==100)
      {
	cout<< "There is too many file. just 100 files loaded"<<endl;
	break;
      }
  }
  cout << listnum << " file(s) checking finished" <<endl;
  cout<<"Now working"<< endl;
}

void taxiCl::generate(){
  
  int checknum=0;
  while(checknum!=listnum){
    
    cout<< "Processing......("<<checknum+1<<"/"<<listnum<<")"<<"    ";
    
    ifstream taxidata(flist[checknum],ios_base::in);
    size_t dot = flist[checknum].find("-")-4;
    flist[checknum] = flist[checknum].substr(dot);
    flist[checknum].insert(0,"/home/jeonghun/classified/");
    ofstream newdata(flist[checknum],ios_base::out);
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
	  
	  //cout.precision(0);
	  //cout <<fixed << id << "," << tx<< "," <<ty<< "," <<tz<< "," <<time<< "," <<angle<< "," <<tv<< "," <<vali<< "," <<pass<< "," <<dist<<endl;
	}
       cout<<"done."<<endl;

    }
   checknum++;
   
  }
  
}


int taxiCl::classify(double taxi_x, double taxi_y){
  	
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
  taxiCl* taxi = new taxiCl();
  ifstream list("filelist");
  taxi->set_input(list);
  taxi->generate();
  cout<< "Classification finished" << endl;
  return 0;
}
