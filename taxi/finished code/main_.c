#include"TDManager.h"

int main(){
  cout<<"Hello world!"<<endl;
  const char data[50] ="/home/jeong/taxidatasample/data";
  TDNode* dataset= new TDNode("/home/jeong/taxidatasample/data/000000.DAT");
double id = 180000715;

map<double,size_t> taxiset = dataset->get_taxilist();

cout<<taxiset.size()<<endl;
  bool test = dataset->checkID(id);

for (map<double,size_t>::iterator ntaxi= taxiset.begin(); ntaxi!=taxiset.end();ntaxi++){
  //cout<<*ntaxi<<endl;
  double tempid = (*ntaxi).first;
  dataset->putoff(ntaxi);

}

/*  if (test){
cout<<"true"<<endl;
TData* trip = dataset->puton(id);
if(trip== NULL) cout<<"??"<<endl;
}
else{
cout<<"what the"<<endl;

}
  */
  return 0;
}
