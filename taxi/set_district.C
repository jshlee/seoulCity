#include<list>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include "position.C"
using namespace std;






int set_district(){
  
  ifstream fin("district.txt");
  //  struct position{
  //  double x, y;
  //};
  vector<vector<position>>city;
  
  for(int j=0 ; j<25;j++){
    

    vector<position> district[25];
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
      district->push_back(ID);
      string line;
      getline(fin,line);
      stringstream ss(line);
      int entry = 0 ;
      while(!fin.eof()){

	position point;
	
	ss.getline(buf,100,' ');
	pt=buf;
	point.y=(double) (atof(buf)) *1000000000;
	ss.getline(buf,100,' ');
	pt=buf;
	point.x=(double) (atof(buf)) *1000000000;
	district->push_back(point);
	entry++;
      
      
      if (strlen(buf)==0)
	  {
	    break;
	  }
      }
      for(int i = 0; i< district[0].size(); ++i)
	 {
	   cout<< district[0][i].x<<" " << district[0][i].y  <<endl;
	 }
       fin.getline(buf,100);
       cout<<buf<<endl;
       
    }
    
 
    city.push_back(district);
  }

  return 0;
}
