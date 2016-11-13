//
// Created by mikecranwill on 11/12/2016.
//

#include "LinkedList.h"
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


std::vector<relationship> GraphActors::bfs(std::string actorStart, std::string actorGoal){
    
    std::set<std::string> visitedActors;
    visitedActors.insert(actorStart);

    std::vector<relationship> initial_path;
    initial_path.push_back(ActorMap[actorStart].getFirstRelationship());
    
    std::queue<vector<relationship>> pathQueue;
    pathQueue.push(initial_path);


    while(!pathQueue.empty()){

        std::vector<relationship> path = pathQueue.front();
        if (path.size() >= 6){
            std::cout << "Degrees of Seperation more than 6 !! Search Abandoned" << std::endl;
            std::vector<relationship> empty_path;
            return empty_path;
        }
        pathQueue.pop();

        std::vector<relationship> connections = ActorMap[path.back().actorKey].getAllConnections();
        for(relationship connection : connections){
            // Ignore actors who have already been visited
            if (visitedActors.count(connection.actorKey) == 0){
                visitedActors.insert(connection.actorKey);  
                std::vector<relationship> new_path(path);  
                new_path.push_back(connection);   // Add new person/movie to path
                pathQueue.push(new_path);         // Add extended path to queue
                if (connection.actorKey == actorGoal)
                    return new_path; // Success!
            }
        }

    }
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