#include<string.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>
#include<istream>
#include<ostream>
#include<fstream>
#include "TDList.h"
#include "TDNode.h"

TDList::TDList(){
  TDList::Count = 0;
  TDList::head->nextNode = NULL;
  
}

void TDList::valid(int count){
  if(count>TDList::Count){
    throw "Error : TDList::valid error";
  }
}

TDNode *TDList::get(int index){
  try{
    valid(index);
  }
  catch(const char* msg){
    std::cout<<msg<<std::endl;
    return NULL;//adding TDNode error
  }

  TDL* temp = head;
  for (int j =0; j<=index; j++){
    temp = temp->nextNode;
  }
  return temp->data;
    
}

int TDList::size(){
  return TDList::Count;
}
void TDList::remove(int index){
  try
    {
      valid(index);
    }
  catch(const char* msg)
    {
      std::cout<<msg<<std::endl;
      return;
    }
   
  TDL* temp = head;
  TDL* remove = head;
  for(int i = 0; i<index; i++){
    temp = temp->nextNode;
    remove = remove->nextNode;
  }
  remove = remove->nextNode;
  temp->nextNode =remove->nextNode;
  remove->nextNode = NULL;
  delete remove;
  
 
  TDList::Count--;
}

void TDList::set(int index, TDNode* Data){
   try
    {
      valid(index);
    }
  catch(const char* msg)
    {
      std::cout<<msg<<std::endl;
      return;
    }
   TDL* temp = head;
   for (int i = 0; i<=index; i++){
     temp = temp->nextNode;
   }
   temp->data = Data;
}
void TDList::add(TDNode* Data){
  TDL* NewNode = new TDL;
  NewNode->data = Data;
  NewNode->nextNode=NULL;
  
  if(this->head->nextNode == NULL){
    
    TDList::head->nextNode = NewNode;
  }
  else{
    
    TDL* temp = TDList::head;
    while(temp->nextNode != NULL)
      {
	temp = temp->nextNode;
      }
    temp->nextNode = NewNode;
  }
  TDList::Count++;
  
}
void TDList::add(int index, TDNode* Data){
  try
    {
      valid(index);
    }
  catch(const char* msg)
    {
      std::cout<<msg<<std::endl;
      return;
    }
  TDL* NewNode = new TDL;
  NewNode->data = Data;
  NewNode->nextNode=NULL;
  if(head->nextNode == NULL)
    {
      head->nextNode = NewNode;
    }
  
  else
    {
      TDL* temp = head;
      for(int i = 0; i<index; i++){
	temp = temp->nextNode;
      }
      NewNode->nextNode =temp->nextNode;
      temp->nextNode = NewNode;
    }
  TDList::Count++;
}
bool TDList::isEmpty(){
  if(head->nextNode == NULL) return true;
  else return false;
}
