/*
  Justin Weiss, Cole Burkhart, Jacky Shi
  3/29/19
  CSC4510
  BC Version 3 - Recursive Decent Parser
*/

#include "symbolTable.h"
#include "symbolNode.h"
#include "general_ex.h"
#include<cstddef>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>


using namespace std;

Symbol_table::Symbol_table(void) {

  //Symbol_node * head;
  head = new Symbol_node[TABLE_SIZE];


    for (int i = 0; i < TABLE_SIZE; i++) {
       head[i].next = NULL;
    }

   //initialize the table
   //sets everything to null

}

Symbol_table::~Symbol_table(void) {
	//destruct the table
}

Symbol_ptr Symbol_table::insert(char * identifier) {

    //call look up
   //call hash function
   int index = hash(identifier);
   Symbol_node* p = new Symbol_node(identifier);



   //check if location if empty
   //if it is then place node there
   if(head[index].next == NULL){
      head[index].next = p;
      return head[index].next;
   }


   //else go until you find an empty spot and place node there
   else{
      Symbol_node* start = head[index].next;
      while(start-> next != NULL){
         start = start->next;
      }
      start->next = p;
      return start;
   }


}

void Symbol_table::remove(char * identifier) {

   //call lookup to find the location to remove
   int index = hash(identifier);
   Symbol_node* tmp = head[index].next;
   Symbol_node* par = head[index].next;


   //if empty do nothing
    if (tmp == NULL) {

    //else
    } else if (tmp->id == identifier && tmp->next == NULL) {
        tmp->next = NULL;
        delete tmp;
    } else {
        while (tmp->id != identifier && tmp->next != NULL) {
            par = tmp;
            tmp = tmp->next;
        }
        //set the pointer location to null
        if (tmp->id == identifier && tmp->next != NULL) {
            par->next = tmp->next;
            tmp->next = NULL;
            free(tmp);
        } else {
            par->next = NULL;
            tmp->next = NULL;
            free(tmp);
        }
    }
}

Symbol_ptr Symbol_table::lookup(char * identifier) {

    //call the hash function until you find it
    int index = hash(identifier);
    Symbol_node* start = head[index].next;

    //use pointer to get the value
    if(start == NULL)
        return NULL;

    //return val
    while(start != NULL){
        if(start->id = identifier)
            return start;

        start=start->next;
    }


}

void Symbol_table::dump_table(void) {

    for (int i=0; i<TABLE_SIZE; i++) {
        Symbol_node* start = head[i].next;
        //use pointer to get the value
        while(start != NULL){
            cout << start->id << "=" << start->value << " "<< endl;
            start=start->next;
        }
    }
}

//Hash function determines where to put the nodes in the symbol table.
// It's based off of Brian Kernighan and Dennis Ritchie's hash function.
// Using the pattern 131..131..131
int Symbol_table::hash(const char* id) {
  unsigned int seed = 131;
  unsigned int hash = 0;
  unsigned int i = 0;
  for (i = 0; i < MAX_ID_LENGTH; ++id, ++i) {
    hash = (hash * seed) + (*id);
  }
  return (hash % (TABLE_SIZE-1));
}
