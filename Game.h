#ifndef GAME_H
#define GAME_H
#include "room.h"
#include "tree.h"
class Game
{
    private:
    Room room;
    Tree drone;

    public:
    Game(std::string filePath);

    std::string findCommand(int numOfLeaf);
    int findLength(int numOfLeaf);
    int findQuantityPaintSpill(int numOfLeaf);
    int findCountTurns(int numOfLeaf);

    void print(int numLeaf);
    


};







#endif
