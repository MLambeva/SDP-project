#ifndef GAME_H
#define GAME_H
#include"Room.h"
#include"Tree.h"
#include"Position.h"
#include<iostream>

class Game
{///Obhojdaniq da ne sa s takuv for
    private:
    Room room;
    Tree droneWithAllPaths;
    Tree droneWithShortestPaths;   
     
    void visualizeDroneWithAllPaths(std::string outPath);
    void visualizeDroneWithShortestPaths(std::string outPath);

    int lengthOfChosenPath(std::string path) const;
    int quantityPaintSpill(std::string path) const;
    std::string findPathWithoutPaintSpill(std::string path) const;
    int countTurns(std::string path) const;

    int maxPaintSpill() const;
    std::vector<std::string> pathsWithMostPaintSpill() const;
    int minTurns(std::vector<std::string> other) const; 

    public:
    Game(std::string filePath);
    
    std::vector<std::string> pathsWithMaxPaintSpillAndLeastTurns() const;

    void start();
};

#endif
