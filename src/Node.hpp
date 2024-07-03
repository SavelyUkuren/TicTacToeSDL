//
//  Node.hpp
//  TicTacToe
//
//  Created by Савелий Никулин on 02.07.2024.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

class Node {
    
    float x, y, w, h;
    string name;
    Node *parent;
    
    vector<Node> nodes;
    
public:
    Node();
    
    void setPosition(const float x, const float y);
    void setSize(const float w, const float h);
    void setName(const string name);
    
    void addNode(Node *node);
    bool isInteract(Node *node);
    bool isInteract(int x, int y);
    
    bool operator==(const Node &r);
    
    float getX();
    float getY();
    float getW();
    float getH();
    string getName();
    vector<Node> &getNodes();
    Node &getNodeByName(string name);
};

#endif /* Node_hpp */
