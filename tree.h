#ifndef TREE_H
#define TREE_H
#include<string>
#include<vector>
#include<exception>
#include<iostream>
#include<algorithm>
#include"room.h"

class Tree
{
    private:
    struct Node
    {
        std::string data;
        //char data;
        Node* north;
        Node* east;
        Node* south;
        Node* west;
        Node* paint;
    };
    Node* start;

    static Node*& findNextPosition(char x, Node*& curr);
    static void helper(std::string x, Node*& curr);

    void createTailTree(std::string& path);
    void toGvHelp (std::ostream& out, Node *curr);
    void add(std::string path);

    public:
    Tree();
    
    void createTree(std::vector<std::string> paths);

    void toGv(std::ostream& out); 
};

#endif
