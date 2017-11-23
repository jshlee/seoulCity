#include<string.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>
#include<istream>
#include<ostream>
#include<fstream>

#ifndef TDL_H
#define TDL_H

class TDNode;




class TDList{
private:
  class TDL{
  public:
    TDL* nextNode;
    TDNode* data;
  };
  
  TDL* head = new TDL;
  int Count;
  void valid(int count);
public:
  TDList();
  TDNode* get(int index);//return data
  int size();
  void set(int index, TDNode* Data);//replace data
  void remove(int index);
  void add(TDNode* Data);//push_data
  void add(int index, TDNode* Data);//insert data
  bool isEmpty();
  
};

#endif
