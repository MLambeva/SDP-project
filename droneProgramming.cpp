#include"droneProgramming.h"

void DroneProgramming::visualizeDroneWithAllPaths(std::string outPath) 
{
    std::ofstream output (outPath);
    droneWithAllPaths.toGv(output);
}

void DroneProgramming::visualizeDroneWithShortestPaths(std::string outPath) 
{
    std::ofstream output (outPath);
    droneWithShortestPaths.toGv(output);
}

//Returns the length of a string that represents a path in the tree by a given identifier
int DroneProgramming::lengthOfChosenPath(std::string path) const
{
    int length = 0;
    for(char elem : path)
    {
        if(elem != 'P')
        {
            length++;
        }
    }
    return length;
}

//Returns the quantity of paint spill of a string that represents a path in the tree by a given identifier
int DroneProgramming::quantityPaintSpill(std::string path) const
{
    int quantity = 0;
    for(char elem : path)
    {
        if(elem == 'P')
        {
            quantity++;
        }
    }
    return quantity;
}

//Returns a string of path in which there is no paint spill
std::string DroneProgramming::findPathWithoutPaintSpill(std::string path) const
{
    std::string saver;
    for(char elem : path)
    {
        if(elem != 'P')
        {
            saver.push_back(elem);
        }
    }
    return saver;
}

//Returns the number of turns Tom should make to reach Jerry of a string that represents a path in the tree by a given identifier
int DroneProgramming::countTurns(std::string path) const
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

//Returns the maximum amount of spilled paint
int DroneProgramming::maxPaintSpill(std::vector<std::string> paths) const
{
    int max = 0;
    if(!paths.empty())
    {
        max = quantityPaintSpill(paths[0]);
        for(std::string posPath : paths)
        {
            if(quantityPaintSpill(posPath) > max)
            {
                max = quantityPaintSpill(posPath);
            }
        }
    }
    return max;
}

//Returns all paths with maximum amount of spilled paint
std::vector<std::string> DroneProgramming::pathsWithMostPaintSpill() const
{
    std::vector<std::string> saver;
    int max = maxPaintSpill(room.getPossiblePaths());
    if(max)
    {
        for(std::string posPath : room.getPossiblePaths())
        {
            if(quantityPaintSpill(posPath) == max)
            {
                saver.push_back(posPath);
            }
        }
    }    
    return saver;
}

//Returns the number of least turns
int DroneProgramming::minTurns(std::vector<std::string> other) const
{
    int min = 0;
    if(!other.empty())
    {
        min = countTurns(other[0]);
        for(std::string elem : other)
        {
            if(countTurns(elem) < min)
            {
                min = countTurns(elem);
            }
        }
    }
    return min;
}

//Returns all paths with maximum amount of spilled paint and minimum turns Tom should make to reach Jerry
std::vector<std::string> DroneProgramming::pathsWithMaxPaintSpillAndLeastTurns() const
{
    std::vector<std::string> result;
    std::vector<std::string> curr = pathsWithMostPaintSpill();
    if(!curr.empty())
    {
        int min = minTurns(curr);
        for(std::string elem : curr)
        {
            if(countTurns(elem) == min)
            {
                result.push_back(elem);
            }
        }
    }
    return result;
}

//Returns all fastest paths with maximum amount of spilled paint Tom should make to reach Jerry
std::vector<std::string> DroneProgramming::fastestPathWithMostPaintSpill() const
{
    std::vector<std::string> result;
    std::vector<std::string> curr = room.createShortestPossiblePaths();
    if(!curr.empty())
    {
        int max = maxPaintSpill(curr);
        for(std::string elem : curr)
        {
            if(quantityPaintSpill(elem) == max)
            {
                result.push_back(elem);
            }
        }
    }
    return result;
}

void DroneProgramming::print(std::string path) const
{
    for(int i = 0; i < path.size() - 1; i++)
    {
        std::cout << path[i] << "->";
    }
    std::cout << path[path.size() - 1];
}

void DroneProgramming::createRoomAndDrone()
{
    bool flag = true;
    std::string filePath;   
    do
    {
        try
        {
            std::cout << "Please, enter file name: ";
            std::cin >> filePath;
            room.createRoom(filePath + ".txt");
            flag = false;
        }
        catch(const std::runtime_error& e)
        {
            std::cout << e.what() << '\n';
        }
    } while (flag);  

    droneWithAllPaths.addAllPaths(room.createAllPossiblePaths());
    droneWithShortestPaths.addAllPaths(room.createShortestPossiblePaths());   
    droneWithAllPaths.createIdToLeaves();
    droneWithShortestPaths.createIdToLeaves();
}

void DroneProgramming::visualize() 
{
    std::string visAllPaths;
    std::cout<<"Please, type a file name to visualize tree with all possible paths in: ";
    std::cin>>visAllPaths;
    visualizeDroneWithAllPaths(visAllPaths + ".gv");
    std::string visShortestPaths;
    std::cout<<"Please, type a file name to visualize tree with the shortest possible paths in: ";
    std::cin>>visShortestPaths;
    visualizeDroneWithShortestPaths(visShortestPaths + ".gv");  
}

void DroneProgramming::mainFunctionalities()
{
    int id;   
    do
    {
        while (std::cout << "Please, enter number of leaf: " && !(std::cin >> id))
        {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
            std::cout << "Invalid input, please re-enter!\n";
        }
    } while (id < 0 || id >= droneWithShortestPaths.countLeaves());    
    
    std::cout << "\nCommands which have to be entered in the drone: ";
    print(droneWithShortestPaths.findPathOnLeafWithId(id));
    std::cout<<'\n';
    std::cout << "Length of path: " << lengthOfChosenPath(droneWithShortestPaths.findPathOnLeafWithId(id)) << '\n';
    std::cout << "Amount of paint spilled: " << quantityPaintSpill(droneWithShortestPaths.findPathOnLeafWithId(id)) << '\n';
    std::cout << "Number of turns: " << countTurns(droneWithShortestPaths.findPathOnLeafWithId(id)) << "\n\n";
}

void DroneProgramming::firstAdditionallyFunctionalities() const
{
    std::vector<std::string> maxPaintMinTurns = pathsWithMaxPaintSpillAndLeastTurns();
    if(!maxPaintMinTurns.empty())
    {
        std::cout<<"Paths with the most paint spill and the least turns: ";
        for(std::string maxElem : maxPaintMinTurns)
        {
            print(maxElem);
            std::cout<< "    ";
        }
        std::cout << '\n';
    }
    else
    {
        std::cout << "There are no roads in which there is paint spill!\n";
    }       
}

void DroneProgramming::secondAdditionallyFunctionalities() const
{
    std::vector<std::string> maxPaintShortestPath = fastestPathWithMostPaintSpill();
    if(!maxPaintShortestPath.empty())
    {
        std::cout<<"The shortest path with the most paint spill: ";
        for(std::string elem : maxPaintShortestPath)
        {
            print(elem);
            std::cout<< "    ";
        }
        std::cout << '\n';
    }
    else
    {
        std::cout << "There are no roads in which there is paint spill!\n";
    }       
}

//main function demonstrating all functionalities
void DroneProgramming::start()
{
    createRoomAndDrone();    
    if(droneWithAllPaths.countLeaves())
    {
        visualize();
        mainFunctionalities();
        firstAdditionallyFunctionalities();    
        secondAdditionallyFunctionalities();
    } 
    else
    {
        std::cout<< "No paths from Tom to Jerry!\n";
    }       
}
