#include"TDManager.h"

int main(){
  cout<<"Hello world!"<<endl;
  const char data[50] ="/home/jeong/taxidatasample/data";
  TDManager* dataset= new TDManager("/home/jeong/taxidatasample/data/");
  return 0;
}
