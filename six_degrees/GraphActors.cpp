//
// Created by mikecranwill on 11/12/2016.
//

#include "GraphActors.h"
#include <iostream>

using namespace std;

// Constructor
GraphActors::GraphActors(){

}
// Deconstructor
GraphActors::~GraphActors(){
    this->ActorMap.clear();
}

//  Inserts a vertex for each element in the actorsCollection representing the
//  connection along the edge that is denoted by movieTitle
//  @param: actorsCollection denotes all potential vertices related by the movieTitle
//  @param: string element that provides additional information about the connection along the edge
void GraphActors::addActorConnection(std::vector<std::string>& actorsCollection, std::string movieTitle ){
    //Outer Loop inserts or updates each element of actorsCollection
    for (unsigned i=0; i<actorsCollection.size(); i++){
        //  Checking whether we insert new key into the map
        if (!doesKeyExist(actorsCollection.at(i))){
            LinkedList *tempList = new LinkedList();
            //  Create a temporary linked list that contains all the elements from actorsCollection except the current
            for (unsigned j=0; j<actorsCollection.size(); j++){
                if (j != i){
                    tempList->insertEnd(actorsCollection.at(j),movieTitle);
                }
            }
            //  Building the key-pair and inserting
            ActorMap.insert(std::pair<std::string,LinkedList> (actorsCollection.at(i),*tempList));
            delete tempList;
        } else {    //  Key already exists in the map so we append all the new connections
            LinkedList existingList = ActorMap.find(actorsCollection.at(i))->second;
            for (unsigned j=0; j<actorsCollection.size(); j++){
                if (j != i){
                    existingList.insertEnd(actorsCollection.at(j),movieTitle);
                }
            }
            ActorMap[actorsCollection.at(i)] = existingList;
        }
    }
}


std::string GraphActors::bfs(std::string actorOne, std::string actorTwo){
    std::queue<visitedPair> visitedQueue;
    std::map<std::string, bool> visitedMap;
    for (std::map<std::string,LinkedList>::iterator it=ActorMap.begin(); it!=ActorMap.end(); ++it){
        //visitedPair vp(it->first,false);
        visitedMap.insert(std::pair<std::string,bool>(it->first,false));
        //visitedQueue.push(vp);
    }

    visitedMap[actorOne] = true;
    visitedPair vp(actorOne,0);
    visitedQueue.push(vp);

    while(visitedQueue.empty()){
        visitedPair tempPair = visitedQueue.front();
        visitedQueue.pop();
        ActorMap.at(tempPair.key).getFirstConnection();
    }

    return "";
}

//  Utility function to get the number of elements in GraphActors elements
int GraphActors::getLength(){
    return ActorMap.size();
}

//  Utility display function that iterates through a select number of keys and prints their connections
void GraphActors::printXNumOfKeys(int NumToPrint){
    int count = 0;
    for (std::map<std::string,LinkedList>::iterator it=ActorMap.begin(); it!=ActorMap.end(); ++it){
        if (count < NumToPrint){
            std::cout << it->first << " => " << it->second.getFirstConnection() << '\n';
            ++count;
        } else{
            return;
        }
    }
}

//  Utility function to detect whether the key has been inserted already
bool GraphActors::doesKeyExist(std::string key){
    if(this->ActorMap.count(key) > 0){
        return true;
    }else{
        return false;
    }
}