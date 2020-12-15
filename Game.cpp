#include"game.h"

Game::Game(std::string filePath)
{
    room.shortestPathsInRoom(filePath);
    drone.createTree(room.getPossiblePaths());
}

std::string Game::findCommand(int numOfLeaf)
{
    if(numOfLeaf < room.getPossiblePaths().size())
    {
        return room.getPossiblePaths()[numOfLeaf];
    }
    else
    {
        throw std::runtime_error("Invalid numOfLeaf");
    }   
}

int Game::findLength(int numOfLeaf)
{
    if(numOfLeaf < room.getPossiblePaths().size())
    {
        return Room::sizeWithoutPaintSpill(room.getPossiblePaths()[numOfLeaf]);
    }
    else
    {
        throw std::runtime_error("Invalid numOfLeaf");
    } 
}

int Game::findQuantityPaintSpill(int numOfLeaf)
{
    if(numOfLeaf < room.getPossiblePaths().size())
    {
        int sum = 0;
        for(int i=0;i<room.getPossiblePaths()[numOfLeaf].size();i++)
        {
            if(room.getPossiblePaths()[numOfLeaf][i] == 'P')
            {
                sum++;
            }
        }
        return sum;
    }
    else
    {
        throw std::runtime_error("Invalid numOfLeaf");
    }    
}

int Game::findCountTurns(int numOfLeaf)
{   
    if(numOfLeaf < room.getPossiblePaths().size())
    {
        int turns = 0;
        std::string helper = Room::findPathWithoutPaintSpill(room.getPossiblePaths()[numOfLeaf]);
        for(int i=0;i<helper.size()-1;i++)
        {
            if(helper[i] != helper[i+1])
            {
                turns++;
            }
        }
        return turns;
    }
    else
    {
        throw std::runtime_error("Invalid numOfLeaf");
    }  
}

void Game::print(int numLeaf)
{
    std::cout<<"Commands: "<<findCommand(numLeaf)<<'\n';
    std::cout<<"Length: "<<findLength(numLeaf)<<'\n';
    std::cout<<"Quantity Paint Spill: " << findQuantityPaintSpill(numLeaf)<<'\n';
    std::cout<<"Count turns: "<<findCountTurns(numLeaf)<<"\n\n";
    
    std::ofstream output ("PartPathsTree.gv");
    drone.toGv(output);

}



