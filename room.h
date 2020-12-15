#ifndef ROOM_H
#define ROOM_H
#include"position.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<exception>

class Room
{
   private:
    std::vector<std::vector<char>> room;
    Position Jerry;
    Position Tom;
    std::vector<std::string> possiblePaths{};

    void resizeRoom(std::ifstream& input);
    void putJerryPosition(std::ifstream& input);
    void putTomPosition(std::ifstream& input);
    void putFurniture(int K, std::ifstream& input);
    void placesForPaintSpill(int L, std::ifstream& input);
    bool canStepOn(const Position& other);
    void createPossiblePathsHelper(const Position& curr, std::string& path);
    void createPossiblePaths(const Position& curr);

    public:
    Room();
    
    std::vector<std::vector<char>> getRoom() const;
    Position getJerry() const;
    Position getTom() const; 
    std::vector<std::string> getPossiblePaths() const;
   
    void createRoom(std::string filePath);     

    void printRoom();    
    static int sizeWithoutPaintSpill(std::string path);
    static int minLengthPaths(std::vector<std::string> paths);
    static std::string findPathWithoutPaintSpill(std::string path);

    std::vector<std::string> allPossPathsInRoom(std::string filePath);
    std::vector<std::string> shortestPathsInRoom(std::string filePath);
     
};

#endif
