#include<stdio.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<list>
using namespace std;

struct position{
  double  x,y;
};
  

list<position> district;
vector<list<position>> city(25);






int reading(){
  string line;
  char text[1000];
  ofstream fout("district.txt");
  FILE *read = fopen("../classification/TL_SCCO_SIG_W.gml","r");
  if ( read == NULL)
    {cout<<"error!"<<endl;}
  else
    {
      while(!feof(read))
	{
	    fgets(text,1000,read);
	    
	    if(strstr(text,"FID")==NULL){}
	    else{
	      ftell(read);
	      char test[20],*pt;
	      fgets(test,3,read);
	      fgets(test,20,read);
	      
	      strtok(test,"<");
	      pt = strstr(test,"1");
	      fout<<pt<<endl;
	    }
	    
	    if(strstr(text,"SIG_CD")==NULL){}
	    else{
	      ftell(read);
	      char test[20],*pt;
	      fgets(test,17,read);
	      fgets(test,15,read);
	      pt = strtok(test,"<");
	      fout<<test<<endl;
	    }
	    if(strstr(text,"<gml:LinearRing>")==NULL){}
	    else{
	      ftell(read);
	      char test[50000],*pt;
	      fgets(test,10,read);
	      fgets(test,50000,read);
	      strtok(test,"<");
	      pt = strchr(test,'3');
	      fout<<pt<<endl<<endl;
	    }
	}
    }
  fout.close();
  return 0;
  
}
