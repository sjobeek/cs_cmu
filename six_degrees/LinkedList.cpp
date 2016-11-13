//  LinkedList class implementation file implementing singly Linked List with pointers
//  Created by Mike Cranwill on 10/17/16.
//

#include "LinkedList.h"

//  Initialize the Linked List
LinkedList::LinkedList(){
    head = NULL;
    tail = NULL;
}

//  Tear down the Linked List
LinkedList::~LinkedList(){
    LLNode *cur = head;
    //LLNode *toDelete = head;
    while (cur != NULL){
        //toDelete = cur;
        cur = cur->next;
        //delete toDelete;
    }
    head = NULL;
    tail = NULL;
}

//  Append input person to end of Linked List
void LinkedList::insertEnd(std::string actorKey, std::string movieTitle){
    LLNode *temp = new LLNode;
    temp->actorKey = actorKey;
    temp->movieTitle = movieTitle;
    temp->next = nullptr;
    if (head== nullptr){
        head = temp;
    }else{
        tail->next = temp;
    }
    tail = temp;
}

std::string LinkedList::getFirstConnection(){
    LLNode *cur = head;
    std::string output = "";
    while (cur != nullptr){
        output = output + cur->actorKey + " appeared in " + cur->movieTitle + "  \t";
        cur=cur->next;
    }
    return output;
}

std::vector<relationship> LinkedList::getAllConnections(){
    std::vector<relationship> connections;
    LLNode *cur = head;
    while (cur != nullptr){
        relationship r(cur->actorKey,cur->movieTitle);
        connections.push_back(r);
    }

    return connections;
}

//
////  Find insertion point for the input person within the Linked List
//void LinkedList::insertSorted(Person input){
//    LLNode *cur = head, *last = head, *temp = new LLNode;
//    temp->p = input;
//    temp->next = NULL;
//
//    if (head== NULL){   //  list was empty
//        head = temp;
//        tail = temp;
//    }else if(temp->p.name < head->p.name){  //  temp fits at the beginning of the list
//        temp->next = head;
//        head = temp;
//    }else if(temp->p.name > tail->p.name){  //  temp fits at the end of the list
//        tail->next = temp;
//        tail = temp;
//    }else{              //  temp fits somewhere in the middle
//        cur = cur->next;    //  separate cur pointer from last by incrementing it one place
//        while ( temp->p.name > cur->p.name){    //  trying to find insertion point by incrementing cur and last
//            cur = cur->next;
//            last = last->next;
//        }
//        //  Found the place we need to insert temp between last and cur
//        last->next = temp;
//        temp->next = cur;
//    }
//}
//
////  Display all contents of the Linked List
//void LinkedList::displayList(){
//    LLNode *temp = head;
//
//    while (temp != NULL){
//        temp->p.print();
//        temp = temp->next;
//    }
//}
//
////  Base case of recursive quicksort
//void LinkedList::quickSort(){
//    head = quickSort_LinkedList(head).head;
//    LLNode *temp = head;
//    while (temp->next != NULL){ //  Find proper place for tail after sorting
//        temp = temp->next;
//    }
//    tail = temp;
//}
//
////  Recursive step to sort smaller list each time before re-assembling the list.
//LinkedList LinkedList::quickSort_LinkedList(LLNode *&tempNode){
//
//    if (tempNode == nullptr){   //  If the input node is empty, return empty list
//        return LinkedList();
//    }
//
//    LLNode *pivot = tempNode, *tempCleanup;     //  Select the pivot to be first element
//    LinkedList lessThanList = LinkedList(), greaterThanList = LinkedList();
//
//    tempNode = tempNode->next;      //  Get the second element in the list for the first comparison
//    pivot->next = nullptr;          //  Disconnect the pivot element from the list
//
//    //  If list only had one element, this while loop is skipped
//    //  If list had two elements, this while loop executes once then pieces the two nodes back together.
//    while (tempNode != NULL){       //  Iterate until tempNode has visited all elements
//        if (tempNode->p.name < pivot->p.name){      //  Should tempNode be added to lessThanList?
//            lessThanList.insertEnd(tempNode->p);    //  Append the element to new lessThanList
//        } else {
//            greaterThanList.insertEnd(tempNode->p); //  Append to the greater than list if >= is the case
//        }
//        tempCleanup = tempNode;     //  Prepare to cleanup the node we just recreated in a new list
//        tempNode = tempNode->next;  //  iterate the tempNode pointer
//        delete tempCleanup;         //  Cleanup old node
//    }
//
//    if (lessThanList.head != NULL){
//        lessThanList = quickSort_LinkedList(lessThanList.head);     //  recursive step for the lessThanList
//    }
//    if (greaterThanList.head != NULL){
//        greaterThanList = quickSort_LinkedList(greaterThanList.head);   //  recursive step for greaterThanList
//    }
//
//    //  Piecing list back together starts by appending the pivot in its proper place at end of lessThanList
//    lessThanList.insertEnd(pivot->p);
//
//    //  Prepare to append all items from greater than list to the end of lessThanList
//    LLNode *temp = greaterThanList.head;
//    while (temp != NULL){
//        lessThanList.insertEnd(temp->p);
//        tempCleanup = temp;
//        temp = temp->next;
//        delete tempCleanup;     //  Cleanup unnecessary nodes after they've been recreated
//    }
//
//    return lessThanList;
//}