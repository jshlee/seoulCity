#include "Setdist.h"
#include "string.h"

std::vector<position> district[25];

void Setdist(){
  
  std::ifstream fin("district.txt");
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
      std::string line;
      getline(fin,line);
      std::stringstream ss(line);
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
       
       
    }
    
 
    
  }

  return;
}

