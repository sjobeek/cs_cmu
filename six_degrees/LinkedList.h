//  LinkedList class header file implementing singly Linked List with pointers
//  Created by Mike Cranwill on 10/17/16.
//

#ifndef A4_RUBEGOLDBERG_LINKEDLIST_H
#define A4_RUBEGOLDBERG_LINKEDLIST_H

//#include "Person.h"
#include <string>
#include <vector>

struct LLNode {
    //Person p;
    std::string actorKey;
    std::string movieTitle;
    LLNode *next;
};

struct relationship {
    relationship(std::string ak, std::string t): actorKey(ak), movieTitle(t){}
    std::string actorKey;
    std::string movieTitle;
};

class LinkedList {
    public:
        LinkedList();       //  Constructor
        ~LinkedList();      //  Deconstructor
        void insertEnd(std::string actorKey, std::string movieTitle);       //  Append input person to end of Linked List
        std::string getFirstConnection();
        relationship getFirstRelationship();
//        void insertSorted(Person input);    //  Find insertion point for the input person within the Linked List
        void displayList();                 //  Display all contents of the Linked List
        void quickSort();                   //  Implement recursive quicksort
        std::vector<relationship> getAllConnections();
    private:
        LLNode *head;
        LLNode *tail;
        LinkedList quickSort_LinkedList(LLNode*& tempNode);     //  Making the quicksort problem smaller
};


#endif //A4_RUBEGOLDBERG_LINKEDLIST_H
