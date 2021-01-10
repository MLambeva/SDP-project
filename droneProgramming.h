#ifndef GAME_H
#define GAME_H
#include"Room.h"
#include"Tree.h"
#include<iostream>
#include<string>
#include<vector>
#include<limits>

class DroneProgramming
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
    int maxPaintSpill(std::vector<std::string> paths) const;
    //Returns all paths with maximum amount of spilled paint
    std::vector<std::string> pathsWithMostPaintSpill() const;
    //Returns the number of least turns
    int minTurns(std::vector<std::string> other) const; 
    //Returns all paths with maximum amount of spilled paint and minimum turns Tom should make to reach Jerry
    std::vector<std::string> pathsWithMaxPaintSpillAndLeastTurns() const;
    //Returns all fastest paths with maximum amount of spilled paint Tom should make to reach Jerry
    std::vector<std::string> fastestPathWithMostPaintSpill() const;

    //print string with '->' between chars
    void print(std::string path) const;

    //Helper functions for presenting functionalities
    void createRoomAndDrone();
    void visualize();
    void mainFunctionalities();
    void firstAdditionallyFunctionalities() const;
    void secondAdditionallyFunctionalities() const;
    
    public:
    //main function demonstrating all functionalities
    void start();
};

#endif
