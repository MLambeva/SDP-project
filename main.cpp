#include "Position.h"
#include "Room.h"
#include "Tree.h"
#include "Game.h"
#include<iostream>

int main()
{
    
    std::string filePath;
    std::cout<<"Please, enter file path: ";
    std::cin>>filePath;
    
    Game game(filePath);
    game.start();   


  
    return 0;
}
