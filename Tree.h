#ifndef TREE_H
#define TREE_H
#include<string>
#include<vector>
#include<exception>
#include<iostream>
#include<queue>

class Tree
{
    private:
    struct Node
    {
        char data;
        Node* north;
        Node* east;
        Node* south;
        Node* west;
        Node* paint;
        int idLeaf = -1;
    };
    Node* start;
    //Helper function for destructor
    void clearHelper(Node* curr);
    
    //According to direction symbol, function returns a pointer to next direction
    Node*& findNextPosition(char x, Node*& curr);
    //Creates next part of tree
    void createNextNode(char x, std::string path, Node*& curr);
    //Check if 'x' is 'N', 'E', 'S', 'W' or 'P'
    bool isCorrectChar(char x) const;
    //Creates the tail of tree
    void createTailTree(std::string& path);
    //Creates tree from one string
    void addOnePath(std::string path);

    void makeLegend(std::ostream& out) const;
    //Remove repeats for visualizing tree
    void removeRepeats (std::ostream& out, Node* pos, Node* direction, std::string color) const;
    //Tree visualization
    void toGvHelper (std::ostream& out, Node *curr) const; 

    //Checks if the pointer points to leaf
    bool isLeaf(Node* curr) const;
    //Counts the leaves
    int countLeavesHelper(Node *curr) const;
    //Each leaf has an identifier starting from 0 and each node that is not a leaf takes a value -1
    void createIdToLeavesHelper(Node* curr, int& id);

    //Helper function to add node to queue
    void addNodeToQueue(Node* direction, std::queue<Node*>& q);
    //We need to know if there is leaf with identifier 'id' in the subtree with root 'curr'
    bool isLeafWithIdInSubtree(Node* curr, const int& id);    
    //According to 'id', function create path from root to leaf with this id
    void findPathOnLeafWithIdHelper(Node* curr, const int& id, std::string& path);

    public:
    Tree();
    ~Tree();
    
    //Creates tree from all paths
    void addAllPaths(std::vector<std::string> paths);

    //Tree visualization
    void toGv(std::ostream& out); 

    //Counts the leaves
    int countLeaves()const;
    //Creates identifier to each leaf
    void createIdToLeaves();
    //According to a given identifier 'id', function returns string that is path from root to a leaf with this 'id'
    std::string findPathOnLeafWithId(const int& id);   
};

#endif
