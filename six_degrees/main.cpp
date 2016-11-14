#include <iostream>
#include <fstream>
#include "GraphActors.h"

using namespace std;

const int DEBUG = 0;

string trim(string input);
int processLineForVertexEdge (GraphActors*&, string);
std::string acceptUserInputOfActor(GraphActors*&, std::string);

void printSearchResult(string actorOne,string actorGoal,
                       std::vector<relationship> full_path);

int main() {

    string line, fileName = "";
    GraphActors *ga = new GraphActors();

    ifstream myFile;
    if (fileName == ""){
        //myFile.open("MovieDataUnitTests.txt");
        //myFile.open("C:\\Users\\mikej\\Documents\\CMUGradSchool\\2016_FALL_DATA_STRUCTS\\A5\\cs_cmu\\six_degrees\\data\\MovieData.txt");
        myFile.open("data/MovieData.txt");
        //myFile.open("data/MovieData_JimCarreyJenniferAnistonBenStiller.txt");
    }else {
        myFile.open(fileName);
    }

    // Loading Vertices and Edges into the application
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            //(edge, vertex) = processLine(line);
            processLineForVertexEdge (ga, line);
        }
    } else {
        if (fileName == ""){
            cout << "The file data/MovieData.txt was not found in the current working directory." << endl;
        }else {
            cout << "The file " << fileName << " was not found in the current working directory." << endl;
        }
        return 0;
    }

    //  cout << "The graph of connections has been loaded successfully." << endl;
    //  cout << "What is the length of graph? It is " << (*ga).getLength() << endl;
    //  (*ga).printXNumOfKeys((*ga).getLength());


/*
    // For testing only, find connections between Jim Carrey and Ben Stiller
    // (through Jennifer Aniston)
    cout << endl << endl;
    string actorOne = "Owen Wilson", actorTwo = "Justin Cooper";
    //string actorOne = "Ben Stiller", actorTwo = "Jim Carrey";

    std::vector<relationship> full_path = (*ga).bfs(actorOne, actorTwo);

    if(full_path.size() > 0)
        printSearchResult(actorOne, actorTwo, full_path);
*/

    // Interact with user to find degrees of separation between two actors
    bool userWillContinue = true;
    string shouldExit = "";
    while (userWillContinue){
        cout << "If you would like to exit, please type 'exit'. Otherwise, press enter to continue." << endl;
        getline (cin, shouldExit);
        if (!shouldExit.compare("exit")){
            userWillContinue = false;
        }else {
            cout << "You will be prompted for two actors to find their degrees of separation, enjoy" << endl;
            string actorOne = acceptUserInputOfActor(ga, "first");
            string actorTwo = acceptUserInputOfActor(ga, "second");
            std::vector<relationship> full_path = (*ga).bfs(actorOne, actorTwo);
            if(full_path.size() > 0)
                printSearchResult(actorOne, actorTwo, full_path);
        }
    }

    return 0;
}

void printSearchResult(string actorOne,string actorGoal,
                       std::vector<relationship> full_path){
    cout << endl << actorOne << " -> " << actorGoal << ": " <<
            full_path.size() - 1 << " Degrees of Separation" << endl;

    std::string last_actor = actorOne; 
    for (relationship rel : full_path){
        cout << rel.movieTitle << " : "  << last_actor << "; " << rel.actorKey  << endl;
        last_actor = rel.actorKey;
    }
}

std::string acceptUserInputOfActor(GraphActors*& ga, std::string firstOrSecond){
    string tempActor = "";
    while (tempActor == ""){
        cout << "What's the " << firstOrSecond << " actor's name?" << endl;
        getline (cin, tempActor);
        if (tempActor == ""){
            cout << "Please don't leave the " << firstOrSecond << " actor's name empty" << endl;
        }
        else if (!(*ga).doesKeyExist(tempActor)){
            cout << "The actor with name " << tempActor << " does not exist in this data set" << endl;
            tempActor = "";
        }
    }
    return tempActor;
}


int processLineForVertexEdge (GraphActors*& ga, string line){
    string title = "", actors = "";
    std::vector<std::string> actorsToAdd;
    int indexOfRating = line.find('('), indexOfActors = line.rfind('(');
    int indexOfActorsClosingParen = line.rfind(')');

    if (indexOfActors != std::string::npos && indexOfRating != std::string::npos){
        actors = line.substr(indexOfActors+1, indexOfActorsClosingParen-indexOfActors-1);
        title = line.substr(0, indexOfRating);
        title = trim(title);
        if (DEBUG){
            cout << "Whole contents of line is " << line << endl;
            cout << "Value of title is " << title << endl;
            cout << "Value of actors is " << actors << endl;
        }

        string actorVertex = "";
        int indexOfActorVertex =actors.find(',');
        while (actors != ""){                            // (below) Handle case of missing first actor
            if ( indexOfActorVertex != std::string::npos && indexOfActorVertex > 0){
                if (DEBUG){cout << "Index of Actor Vertex " << indexOfActorVertex << endl;}
                actorVertex = actors.substr(0,indexOfActorVertex);
                actorVertex = trim(actorVertex);
                if (DEBUG){cout << "current value of actor vertex is " << actorVertex << endl;}
                actors = actors.substr(indexOfActorVertex+1, actors.length()-1);
            } else if (actors.length() > 0) {
                actorVertex = actors.substr(0,actors.length());
                actorVertex = trim(actorVertex);
                if (DEBUG){cout << "current value of actor vertex is " << actorVertex << endl;}
                actors = "";
            } else {
                actors = "";
            }
            if (actorVertex != "Jr.")  // Avoid problematic 'Someone, Jr.' name
                actorsToAdd.push_back(actorVertex);
            indexOfActorVertex =actors.find(',');
        }
        if (actorsToAdd.size() > 0){
            ga->addActorConnection(actorsToAdd,title);
        }   else{
            cout << "No actors were parsed from " << actors << " with original line being " << line<< endl;
        }
    } else {
        cout << "No title or actors processed from line with contents = " << line << endl;
    }

    return 0;
}

// Utility function to trim leading and trailing whitespace
string trim(string input){
    int newStartIndex = input.find_first_not_of(" \r\t\n"),newEndIndex = input.find_last_not_of(" )\r\t\n");

    return input.substr(newStartIndex,newEndIndex-newStartIndex+1);
}