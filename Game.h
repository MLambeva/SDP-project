#ifndef GAME_H
#define GAME_H
#include"Room.h"
#include"Tree.h"
#include"Position.h"
#include<iostream>
#include<limits>

class Game
{
    private:
    Room room;
    Tree droneWithAllPaths;
    Tree droneWithShortestPaths;   
     
    void visualizeDroneWithAllPaths(std::string outPath);
    void visualizeDroneWithShortestPaths(std::string outPath);

    //Returns the length of a string that represents a path in the tree by a given identifier
    int lengthOfChosenPath(std::string path) const;
    //Returns the quantity of paint spill of a string that represents a path in the tree by a given identifier
    int quantityPaintSpill(std::string path) const;
    //Returns a string of path in which there is no paint spill
    std::string findPathWithoutPaintSpill(std::string path) const;
    //Returns the number of turns Tom should make to reach Jerry of a string that represents a path in the tree by a given identifier
    int countTurns(std::string path) const;
    //Returns the maximum amount of spilled paint
    int maxPaintSpill() const;
    //Returns all paths with maximum amount of spilled paint
    std::vector<std::string> pathsWithMostPaintSpill() const;
    //Returns the number of least turns
    int minTurns(std::vector<std::string> other) const; 
    //Returns all paths with maximum amount of spilled paint and minimum turns Tom should make to reach Jerry
    std::vector<std::string> pathsWithMaxPaintSpillAndLeastTurns() const;

    //Helper functions for presenting functionalities
    void createRoomAndDrone();
    void visualize();
    void mainFunctionalities();
    void additionallyFunctionalities();
    
    public:
    Game() = default;   

    //main function demonstrating all functionalities
    void start();
};

#endif
