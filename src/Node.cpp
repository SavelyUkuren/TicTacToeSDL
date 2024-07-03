//
//  Node.cpp
//  TicTacToe
//
//  Created by Савелий Никулин on 02.07.2024.
//

#include "Node.hpp"

Node::Node() {
    parent = nullptr;
}

void Node::setPosition(const float x, const float y) {
    this->x = x;
    this->y = y;
}

void Node::setSize(const float w, const float h) {
    this->w = w;
    this->h = h;
}

void Node::setName(const string name) {
    this->name = name;
}

void Node::addNode(Node *node) {
    node->parent = this;
    nodes.push_back(*node);
}

bool Node::isInteract(Node *node) {
    if (node->getX() > x && node->getX() < x + w &&
        node->getY() > y && node->getY() < y + h) {
        return true;
    }
}

bool Node::isInteract(int x, int y) {
    if (x > this->x && x < this->x + w &&
        y > this->y && y < this->y + h) {
        return true;
    }
}

bool Node::operator==(const Node &r) {
    if (this->name == r.name &&
        this->x == r.x &&
        this->y == r.y &&
        this->w == r.w &&
        this->h == r.h) {
        return true;
    }
    return false;
}

float Node::getX() {
    return x;
}

float Node::getY() {
    return y;
}

float Node::getW() {
    return w;
}

float Node::getH() {
    return h;
}

string Node::getName() {
    return name;
}

vector<Node> &Node::getNodes() {
    return nodes;
}

Node &Node::getNodeByName(string name) {
    for (Node &node : nodes) {
        if (node.name == name)
            return node;
    }
}
