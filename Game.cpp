#include"Game.h"

Game::Game(std::string filePath)
{
    room.createRoom(filePath);
    //droneWithAllPaths.addAllPaths(room.createAllPossiblePaths());
    //droneWithShortestPaths.addAllPaths(room.createShortestPossiblePaths());   
    //droneWithShortestPaths.createIdToLeaves();
}

void Game::visualizeDroneWithAllPaths(std::string outPath)
{
    std::ofstream output (outPath);
    droneWithAllPaths.toGv(output);
}

void Game::visualizeDroneWithShortestPaths(std::string outPath)
{
    std::ofstream output1 (outPath);
    droneWithShortestPaths.toGv(output1);
}

int Game::lengthOfChosenPath(std::string path) const
{
    int length = 0;
    for(int i=0;i<path.size();i++)
    {
        if(path[i] != 'P')
        {
            length++;
        }
    }
    return length;
}

int Game::quantityPaintSpill(std::string path) const
{
    int quantity = 0;
    for(int i=0;i<path.size();i++)
    {
        if(path[i] == 'P')
        {
            quantity++;
        }
    }
    return quantity;
}

std::string Game::findPathWithoutPaintSpill(std::string path) const
{
    std::string saver;
    for(int i =0; i < path.size(); i++)
    {
        if(path[i] != 'P')
        {
            saver.push_back(path[i]);
        }
    }
    return saver;
}

int Game::countTurns(std::string path) const
{
    int turns = 0;
    std::string helper = findPathWithoutPaintSpill(path);
    for(int i = 0; i < helper.size() - 1; i++)
    {
        if(helper[i] != helper[i+1])
        {
            turns++;
        }
    }
    return turns;
}

int Game::maxPaintSpill() const
{
    int max = 0;
    if(!room.getPossiblePaths().empty())
    {
        max = quantityPaintSpill(room.getPossiblePaths()[0]);
        for(int i=0;i<room.getPossiblePaths().size();i++)
        {
            if(quantityPaintSpill(room.getPossiblePaths()[i]) > max)
            {
                max = quantityPaintSpill(room.getPossiblePaths()[i]);
            }
        }
    }
    return max;
}

std::vector<std::string> Game::pathsWithMostPaintSpill() const
{
    std::vector<std::string> saver;
    int max = maxPaintSpill();
    for(int i = 0;i< room.getPossiblePaths().size();i++)
    {
        if(quantityPaintSpill(room.getPossiblePaths()[i]) == max)
        {
            saver.push_back(room.getPossiblePaths()[i]);
        }
    }
    return saver;
}

int Game::minTurns(std::vector<std::string> other) const
{
    int min = 0;
    if(!other.empty())
    {
        min = countTurns(other[0]);
        for(int i=0;i<other.size();i++)
        {
            if(countTurns(other[i]) < min)
            {
                min = countTurns(other[i]);
            }
        }
    }
    return min;
}

std::vector<std::string> Game::pathsWithMaxPaintSpillAndLeastTurns() const
{
    std::vector<std::string> result;
    std::vector<std::string> curr = pathsWithMostPaintSpill();
    if(!curr.empty())
    {
        int min = minTurns(curr);
        for(int i=0;i<curr.size();i++)
        {
            if(countTurns(curr[i]) == min)
            {
                result.push_back(curr[i]);
            }
        }
    }
    return result;
}

void Game::start()
{
    droneWithAllPaths.addAllPaths(room.createAllPossiblePaths());
    droneWithShortestPaths.addAllPaths(room.createShortestPossiblePaths());   
    droneWithAllPaths.createIdToLeaves();
    droneWithShortestPaths.createIdToLeaves();

    std::string visAllPaths;
    std::cout<<"Please, type a file name with extension 'gv' to visualize tree with all possible paths in: ";
    std::cin>>visAllPaths;
    visualizeDroneWithAllPaths(visAllPaths);

    std::string visShortestPaths;
    std::cout<<"Please, type a file name with extension 'gv' to visualize tree with the shortest possible paths in: ";
    std::cin>>visShortestPaths;
    visualizeDroneWithShortestPaths(visShortestPaths);

    std::vector<std::string> maxPaintMinTurns = pathsWithMaxPaintSpillAndLeastTurns();
    
    try
    {
        int id;
        std::cout<<"Please, enter number of leaf: ";
        std::cin>>id;
        std::cout<<"Commands which have to be entered in the drone: "<< droneWithShortestPaths.findPathOnLeafWithId(id) << '\n';
        std::cout<<"Length of path: " << lengthOfChosenPath(droneWithShortestPaths.findPathOnLeafWithId(id)) << '\n';
        std::cout<<"Amount of paint spilled: " << quantityPaintSpill(droneWithShortestPaths.findPathOnLeafWithId(id)) << '\n';
        std::cout<<"Number of turns: " << countTurns(droneWithShortestPaths.findPathOnLeafWithId(id)) << "\n\n";

        std::cout<<"Paths with the most paint spill and the least turns: ";
        for(int i=0;i<maxPaintMinTurns.size();i++)
        {
            std::cout<<maxPaintMinTurns[i]<<"   ";
        }
        std::cout<<'\n';
    }
    catch(const std::runtime_error& e)
    {
        std::cout << e.what() << '\n';
    }   
}
