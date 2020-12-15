#include"position.h"
#include"room.h"
#include"tree.h"
#include"Game.h"

int main()
{   
    std::string filePath;
    std::cout<<"Please, enter filePath: ";
    std::cin>>filePath; 

    int numOfLeaf;
    std::cout<<"Please, enter numOfLeaf: ";
    std::cin>>numOfLeaf;

    Game game(filePath);
    game.print(numOfLeaf);
  
    return 0;
}
