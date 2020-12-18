#ifndef TREE_H
#define TREE_H
#include<string>
#include<vector>
#include<exception>
#include<iostream>

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
    
    //Helper functions for adding string to tree
    //According to direction symbol, function returns a pointer to next direction
    static Node*& findNextPosition(char x, Node*& curr);
    //Creates next part of tree
    static void helper(char x, Node*& curr);
    //Creates the tail of tree
    void createTailTree(std::string& path);
    //Creates tree from one string
    void addOnePath(std::string path);

    //Tree visualization
    void toGvHelper (std::ostream& out, Node *curr, bool flag) const; 

    //Checks if the pointer points to leaf
    bool isLeaf(Node* curr) const;
    //Counts the leaves
    int countLeavesHelper(Node *curr) const;
    //Each leaf has an identifier starting from 0 and each node that is not a leaf takes a value -1
    void createIdToLeavesHelper(Node* curr, int& id);
    //We need to know if there is leaf with identifier 'id' in the subtree with root 'curr'
    bool isLeafWithIdInSubtree(Node* curr, const int& id) ;    
    //According to 'id', function create path from root to leaf with this id
    void findPathOnLeafWithIdHelper(Node* curr, const int& id, std::string& path) ;

    public:
    Tree();
    
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
