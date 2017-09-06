#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<ostream>
using namespace std;

int main(){
  char *folderPath;
  cout<<"Enter the path of folder that include data file :";
  cin>>folderPath;
  //char zero = '0';
  FILE *file;
  file = fopen("filelist","w");
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
    char filename[500];
    sprintf(filename,"%s%02d%02d%02d.DAT",folderPath,h,m,s);
    cout<<filename<<endl;
    fprintf(file,"%s\n",filename);
    count = count + 2.5;
  }
  fclose(file);
  return 0;
}
    
  
  
