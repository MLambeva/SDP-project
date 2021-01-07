#ifndef ROOM_H
#define ROOM_H
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include "Position.h"

class Room
{
    private:
    std::vector<std::vector<char>> room;
    Position Jerry;
    Position Tom;
    std::vector<std::string> possiblePaths;

    //Function that checks if we can place Tom, Jerry or furniture in the position set by the text file 
    bool canBeLocated(const Position& other) const;
    
    void resizeRoom(std::ifstream& input);

    //Function for putting position of Tom and Jerry
    void putCharactersPosition(Position& other, char x, const std::string& error, std::ifstream& input);
    void putJerryPosition(std::ifstream& input);
    void putTomPosition(std::ifstream& input);

    void putFurniture(int K, std::ifstream& input);
    void placesForPaintSpill(int L, std::ifstream& input);
    //function for removing repeats
    void actionAfterCanStepOn(const Position& curr, char x, std::string path);
    void createPossiblePathsHelper(const Position& curr, std::string& path);

    //Places 'x' in the room on position 'curr'
    void setElemInCurrPosition(const Position& curr, char x);
    //Checks if element 'x' is on position 'curr' in the room
    bool isCorrectSymbol(const Position& curr, char x) const;
    bool canStepOn(const Position& other) const;

    //Returns length of set path
    int lengthPath(std::string path) const;
    //Finds length of shortest path
    int lengthShortestPath() const;

    public:
    std::vector<std::string> getPossiblePaths() const;

    //Creates the room with information from a text file 
    void createRoom(std::string filePath); 
    
    //Returns all possible paths for Tom to reach Jerry 
    std::vector<std::string> createAllPossiblePaths();
    //Returns the shortest possible paths for Tom to reach Jerry 
    std::vector<std::string> createShortestPossiblePaths() const;
          
    //Prints room
    void printRoom() const;    
};

#endif
