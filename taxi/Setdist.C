#include<list>
#include<iostream>
#include<sstream>
#include<fstream>
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

struct position{
  double x, y;
};

vector<position> district[25];


int Setdist(){
  
  ifstream fin("district.txt");
  //  struct position{
  //  double x, y;
  //};
  //vector<vector<position>>city;
  
  for(int j=0 ; j<25;j++){
    char buf[100];
    char *error;
  reset:
    
    if (!fin.eof()){
      position ID;
      fin.getline(buf,100);
      char *pt=buf;
      //cout<<buf<<endl;
      ID.x=strtod(pt,&error);
      fin.getline(buf,100);
      pt=buf;
      //cout<<buf<<endl;
      ID.y=strtod(pt,&error);
      district[j].push_back(ID);
      string line;
      getline(fin,line);
      stringstream ss(line);
      int entry = 0 ;
      while(!fin.eof()){

	position point;
	
	ss.getline(buf,100,' ');
	if (strlen(buf)==0)
	  {
	    break;
	  }
	pt=buf;
	point.y=(double) (atof(buf)) *10000000;
	ss.getline(buf,100,' ');
	pt=buf;
	point.x=(double) (atof(buf)) *10000000;
	district[j].push_back(point);
	entry++;
      
      
      
      }
     
       fin.getline(buf,100);
       //cout<<buf<<endl;
       
    }
    //cout<<district[j][0].x<<endl;
 
    // city.push_back(district);
  }
 for(int i = 0; i< district[24].size(); ++i)
	 {
	   //   cout<< district[24][i].x<<"," << district[24][i].y  <<endl;
	 }
  return 0;
}
