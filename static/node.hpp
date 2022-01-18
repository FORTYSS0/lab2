//
// Created by login on 20.11.2021.
//

#ifndef REV_2_STATIC__RIGHT_NODE_HPP
#define REV_2_STATIC__RIGHT_NODE_HPP
enum  Node_color {RED = 0, BLACK = 1};

struct Node{
    explicit Node(int data_){
        data = data_;
    }
    Node* pRight = nullptr;
    Node* pLeft = nullptr;
    Node* pMother = nullptr;
    Node_color color = RED;
    int data;
};
#endif //REV_2_STATIC__RIGHT_NODE_HPP
