//
// Created by mikecranwill on 11/12/2016.
//

#ifndef SIXDEGREESOFSEPARATION_GRAPHACTORS_H
#define SIXDEGREESOFSEPARATION_GRAPHACTORS_H

#include <map>
#include <string>
#include <vector>
#include <queue>
#include "LinkedList.h"

struct visitedPair {
    visitedPair(std::string k, int d): key(k), distance(d){}
    std::string key;
    int distance;
};

class GraphActors {
public:
    GraphActors();      // Constructor
    ~GraphActors();     //  Deconstuctor
    //  Inserts a vertex for each element in the actorsCollection representing the
    //  connection along the edge that is denoted by movieTitle
    //  @param: actorsCollection denotes all potential vertices related by the movieTitle
    //  @param: string element that provides additional information about the connection along the edge
    void addActorConnection(std::vector<std::string>& actorsCollection, std::string movieTitle );
    //  Utility function to get the number of elements in GraphActors elements
    int getLength();
    //  Utility display function that iterates through a select number of keys and prints their connections
    void printXNumOfKeys(int NumToPrint);
    //  Utility function to detect whether the key has been inserted already
    bool doesKeyExist(std::string key);

    std::string bfs(std::string actorOne, std::string actorTwo);
private:
    std::queue<std::string> visitedQueue;
    std::map<std::string, LinkedList> ActorMap;
};


#endif //SIXDEGREESOFSEPARATION_GRAPHACTORS_H
