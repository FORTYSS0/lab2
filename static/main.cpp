#include <iostream>
#include "node.hpp"

using std::cout;
using std::endl;

Node* insert_case5(Node* current,Node** tree){
    Node* mother = current->pMother;
    Node* granny = mother->pMother;
    Node* result = current;
    mother->color =BLACK;
    granny->color = RED;
    if(current != current->pMother->pLeft ||
    (mother != granny->pLeft)){
        result = granny;
        Node* right_g = result->pRight;
        if(result->pMother){
            if(result == result->pMother->pLeft)
                result->pMother->pLeft = right_g;
            else
                result->pMother->pRight = right_g;
        } else{
            *tree = right_g;
        }
        if(right_g)
            right_g->pMother = result->pMother;
        result->pRight = right_g->pLeft;
        if(right_g->pLeft)
            right_g->pLeft->pMother = result;
        right_g->pLeft = result;
        result->pMother = right_g;
    } else{
        result = granny->pLeft;
        if(granny->pMother){
            if(granny == granny->pMother->pLeft)
                granny->pMother->pLeft = result;
            else
                granny->pMother->pRight = result;
        } else{
            *tree = result;
        }
        if(result)
            result->pMother = granny->pMother;
        granny->pLeft = result->pRight;
        if(result->pRight)
            result->pRight->pMother = granny;
        result->pRight = granny;
        granny->pMother = result;
    }
    return result;
}

Node* insert_cases3_4(Node** tree, Node* new_node){
    Node* current = new_node;
    Node* mother = new_node->pMother;
    Node* granny = current->pMother->pMother;
    Node* uncle = mother == granny->pLeft ? granny->pRight : granny->pLeft;
    //insert_case3
    while(true){
        if(!uncle || uncle->color)
            break;
        mother->color = BLACK;
        uncle->color = BLACK;
        granny->color = RED;
        current = current->pMother->pMother;
        if(!current->pMother){
            current->color = BLACK;
            return current;
        }
        if(current->pMother->color == BLACK)
            return current;
    }
    //insert_case4
    if(current != mother->pRight
    || mother != granny->pLeft){
        if(current == mother->pLeft
        && mother == granny->pRight){
            Node* left_m = mother->pLeft;
            if(granny){
                if(mother == granny->pLeft)
                    granny->pLeft = left_m;
                else
                    granny->pRight =  left_m;
            } else{
                *tree = left_m;
            }
            if(left_m)
                left_m->pMother = granny;
            mother->pLeft = left_m->pRight;
            if(left_m->pRight)
                left_m->pRight->pMother = mother;
            left_m->pRight = mother;
            granny = left_m;
        }
        current = insert_case5(current, tree);
    } else{
        Node* right_m = mother->pRight;
        if(granny){
            if(mother == granny->pLeft)
                granny->pLeft = right_m;
            else
                granny->pRight = right_m;
        } else{
            *tree = right_m;
        }
        if(right_m){
            right_m->pMother = granny;
        }
        mother->pRight = right_m->pLeft;
        if(right_m->pLeft)
            right_m->pLeft->pMother = mother;
        right_m->pLeft = mother;
        granny = right_m;
        current = insert_case5(current->pLeft, tree);
    }
    return current;
}

void inserting(Node** tree, int input_data){
    Node* new_node = new Node(input_data);
    Node* pRoot = *tree;
    if(*tree){
        while(true){
            while (input_data < pRoot->data){
                if(!pRoot->pLeft){
                    pRoot->pLeft = new_node;
                    goto LABEL_13;
                }
                pRoot = pRoot->pLeft;
            }
            if(input_data <= pRoot->data){
                delete new_node;
                return;
            }
            if(!pRoot->pRight)
                break;
            pRoot = pRoot->pRight;
        }
        pRoot->pRight = new_node;
LABEL_13:
        new_node->pMother = pRoot;
    } else{
        *tree = new_node;
    }
    if(new_node->pMother){
        if(new_node->pMother->color != BLACK){
            insert_cases3_4(tree, new_node);
        }
    } else
        new_node->color = BLACK;
}

void show(Node* pRoot, int indent = 0){
    if(pRoot){
        while(true){
            if(pRoot->pRight){
                show(pRoot->pRight, indent + 4);
            }
            if(indent > 0){
                int indent_count = indent;
                do{
                    cout << " ";
                    --indent_count;
                } while (indent_count);
            }
            pRoot->color == BLACK ? cout << pRoot->data << "\n" : cout << "<" << pRoot->data << ">" << "\n";
            pRoot = pRoot->pLeft;
            if(!pRoot)
                break;
            indent += 4;
        }
    } else{
        cout << "<Is Empty>\n";
    }
}

int compare(int input_data, int root_data){
    int result;
    if(input_data >= root_data)
        result = input_data > root_data;
    else
        result = -1;
    return result;
}

Node* delete_cases(Node** tree, Node* pRoot);

Node* rotate_left(Node** tree, Node* pRoot){
    Node* mother = pRoot->pMother;
    Node* result = pRoot->pRight;
    Node* grandchild;
    if ( mother )
    {
        if ( pRoot == mother->pLeft )
            mother->pLeft = result;
        else
            mother->pRight = result;
    }
    else
    {
        *tree = result;
    }
    if ( result )
        result->pMother = pRoot->pMother;
    pRoot->pRight = result->pLeft;
    grandchild = result->pLeft;
    if ( grandchild )
        grandchild->pMother = pRoot;
    result->pLeft = pRoot;
    pRoot->pMother = result;
    return result;
}

Node* rotate_right(Node** tree, Node* pRoot){
    Node *mother = pRoot->pMother;
    Node * result = pRoot->pLeft;
    Node *grandchild;
    if ( mother )
    {
        if ( pRoot == mother->pLeft )
            mother->pLeft = result;
        else
            mother->pRight = result;
    }
    else
    {
        *tree = result;
    }
    if ( result )
        result->pMother = pRoot->pMother;
    pRoot->pLeft = result->pRight;
    grandchild = result->pRight;
    if ( grandchild )
        grandchild->pMother = pRoot;
    result->pRight = pRoot;
    pRoot->pMother = result;
    return result;
}

Node* delete_case6(Node* pRoot, Node** tree){
    Node* mother = pRoot->pMother;
    Node* sibling, *result,* granny;
    Node_color color = BLACK;
    if(mother)
        color = mother->color;
    if(pRoot == mother->pLeft)
        sibling = mother->pRight;
    else
        sibling = mother->pLeft;
    sibling->color = color;
    pRoot->pMother->color = BLACK;
    Node* current_child = mother->pLeft;
    if(pRoot == mother->pLeft){
        if(pRoot == current_child)
            current_child = mother->pRight;
        current_child->pRight->color = BLACK;
        result = pRoot->pMother;
        granny = result->pMother;
        sibling = result->pRight;
        if(granny){
            if(result == granny->pLeft)
                granny->pLeft = sibling;
            else
                granny->pRight = sibling;
        } else{
            *tree = sibling;
        }
        if(sibling)
            sibling->pMother = result->pMother;
        result->pRight = sibling->pLeft;
        Node* nephew_l = sibling->pLeft;
        if(nephew_l)
            nephew_l->pMother = result;
        sibling->pLeft = result;
        result->pMother = sibling;
    } else{
        if(pRoot == current_child)
            current_child = mother->pRight;
        current_child->pRight->color = BLACK;
        result = pRoot->pMother;
        granny = result->pMother;
        sibling = result->pLeft;
        if(granny){
            if(result == granny->pLeft)
                granny->pLeft = sibling;
            else
                granny->pRight = sibling;
        } else{
            *tree = sibling;
        }
        if(sibling)
            sibling->pMother = result->pMother;
        result->pLeft = sibling->pRight;
        Node* nephew_r = sibling->pRight;
        if(nephew_r)
            nephew_r->pMother = result;
        sibling->pRight = result;
        result->pMother = sibling;
    }
    return result;
}

Node* delete_case5(Node* pRoot, Node** tree){
    Node* mother = pRoot->pMother;
    Node* left_m = mother->pLeft;
    Node* right_m,* right_m_l_leaf,* right_m_r_leaf,* result;
    if(pRoot != left_m
    || (right_m = mother->pRight) != nullptr && right_m->color != BLACK
    || (right_m_l_leaf = right_m->pLeft) == nullptr
    || right_m_l_leaf->color
    || (right_m_r_leaf = right_m->pRight) != nullptr && right_m_r_leaf->color != BLACK
    ){
        Node* current_child = mother->pRight;
        if(pRoot == current_child){
            Node* sibling = mother->pRight;
            if(pRoot != left_m)
                sibling = mother->pLeft;
            if(!sibling || sibling->color == BLACK){
                Node* sibling_sibling = mother->pRight;
                if(pRoot != left_m)
                    sibling_sibling = mother->pLeft;
                Node* child_r = sibling_sibling->pRight;
                if(child_r && child_r->color == RED){
                    Node* current_child_ = mother->pRight;
                    if(pRoot != left_m)
                        current_child_ = mother->pLeft;
                    if(!current_child_->pLeft || current_child_->pLeft->color == BLACK){
                        if(pRoot != left_m)
                            current_child = mother->pLeft;
                        current_child->color = RED;
                        sibling->pRight->color = BLACK;
                        rotate_left(tree, pRoot);
                    }
                }
            }
        }
        result = delete_case6(pRoot, tree);
    } else {
        right_m->color = RED;
        Node* sibling;
        if(pRoot == mother->pLeft)
            sibling = mother->pRight;
        else
            sibling = mother->pLeft;
        sibling->pLeft->color = BLACK;
        rotate_right(tree, pRoot);
        result = delete_case6(pRoot, tree);
    }
    return result;
}

Node* delete_case4(Node* pRoot, Node** tree){
    Node* mother = pRoot->pMother;
    Node* left_m,* result,* sibling,* sibling_,* sibling_2,* nephew_l,* nephew_r;
    if(!mother
    || mother->color
    || ((left_m = mother->pLeft, pRoot != left_m) ? (sibling = mother->pLeft) : (sibling = mother->pRight),
            sibling && sibling->color != BLACK
            || (pRoot!= left_m ? (sibling_ = mother->pLeft) : (sibling_ = mother->pRight),
                    (nephew_l = sibling_->pLeft) != nullptr && nephew_l->color != BLACK
                    || (pRoot != left_m ? (sibling_2 = mother->pLeft) : (sibling_2 = mother->pRight),
                            (nephew_r = sibling_2->pRight) != nullptr && nephew_r->color != BLACK)))
                            )
        result = delete_case5(pRoot, tree);
    else{
        if(pRoot == left_m)
            sibling = mother->pRight;
        else
            sibling = mother->pLeft;
        sibling->color = RED;
        result = pRoot->pMother;
        result->color = BLACK;
    }
    return result;
}

Node* delete_case3(Node** tree, Node* pRoot){
    Node* mother;
    Node* left_m;
    Node* sibling;
    Node* sibling_;
    Node* nephew_l;
    Node* sibling_2;
    Node* nephew_r;

    mother = pRoot->pMother;
    if ( mother && mother->color != 1
         || ((left_m = mother->pLeft, pRoot != left_m) ? (sibling = mother->pLeft) : (sibling = mother->pRight),
            sibling && sibling->color != 1
            || (pRoot != left_m ? (sibling_ = mother->pLeft) : (sibling_ = mother->pRight),
                    (nephew_l = sibling_->pLeft) != nullptr && nephew_l->color != 1
                    || (pRoot != left_m ? (sibling_2 = mother->pLeft) : (sibling_2 = mother->pRight), (nephew_r = sibling_2->pRight) != nullptr && nephew_r->color != 1)))) {
        delete_case4(pRoot, tree);
    } else {
        if ( pRoot == left_m ) {
            left_m = mother->pRight;
        }
        left_m->color = RED;
        if ( mother->pMother ) {
            delete_cases(tree, mother);
        }
    }
    return pRoot;
}

Node* delete_cases(Node** tree, Node* pRoot){
    Node* mother = pRoot->pMother;
    Node* sibling;
    Node* nephew;
    if(pRoot == mother->pLeft)
        sibling = mother->pRight;
    else
        sibling = mother->pLeft;
    if(!sibling || sibling->color)
        return delete_case3(tree, pRoot);
    mother->color = RED;
    if(pRoot == mother->pLeft)
        sibling = mother->pRight;
    else
        sibling = mother->pLeft;
    sibling->color = BLACK;
    Node* granny = mother->pMother;
    if(pRoot != mother->pLeft){
        sibling = mother->pLeft;
        if(granny){
            if(mother == granny->pLeft)
                granny->pLeft = sibling;
            else
                granny->pRight = sibling;
        } else
            *tree = sibling;
        if(sibling)
            sibling->pMother = mother->pMother;
        mother->pLeft = sibling->pRight;
        nephew = sibling->pRight;
        if(nephew)
            nephew->pMother = mother;
        sibling->pRight = mother;
        mother->pMother = sibling;
        return delete_case3(tree, pRoot);
    }
    sibling = mother->pRight;
    if(granny){
        if(mother == granny->pLeft)
            granny->pLeft = sibling;
        else
            granny->pRight = sibling;
    } else
        *tree = sibling;
    if(sibling)
        sibling->pMother = mother->pMother;
    mother->pRight = sibling->pLeft;
    nephew = sibling->pLeft;
    if(nephew)
        nephew->pMother = mother;
    sibling->pLeft = mother;
    mother->pMother = sibling;
    return delete_case3(tree, pRoot);
}

void deleting(int input_data, Node** tree){
    Node* pRoot = *tree;
    if(*tree){
        do{
            int compare_result = compare(input_data, pRoot->data);
            if(!compare_result)
                break;
            pRoot = compare_result >= 0 ? pRoot->pRight : pRoot->pLeft;
        } while (pRoot);
        if(pRoot){
            Node* left = pRoot->pLeft;
            if(left && pRoot->pRight){
                for(Node* i = left->pRight; i; i = i->pRight)
                    left = i;
                pRoot->data = left->data;
                pRoot = left;
            }
            Node* right = pRoot->pRight;
            if(!right)
                right = pRoot->pLeft;
            if(pRoot->color == BLACK){
                Node_color color = BLACK;
                if(right)
                    color = right->color;
                pRoot->color = color;
                if(pRoot->pMother != nullptr)
                    delete_cases(tree, pRoot);
            }
            Node* mother = pRoot->pMother;
            if(mother){
                if(pRoot == mother->pLeft)
                    mother->pLeft = right;
                else
                    mother->pRight = right;
            } else{
                *tree = right;
            }
            if(right)
                right->pMother = pRoot->pMother;
            if(!pRoot->pMother){
                if(right)
                    right->color = BLACK;
            }
            delete(pRoot);
        }
    }
}

void in_order(Node* pRoot){
    for(Node* i = pRoot; i ; i = i->pRight){
        in_order(i->pLeft);
            printf("%d -> ", i->data);
        }
}

void pre_order(Node* pRoot){
    if(pRoot){
        for(Node* i = pRoot; i ; i = i->pRight){
            printf("%d -> ", i->data);
            pre_order(i->pLeft);
        }
    } else
        printf("Is empty");
}

void half_post_order(Node* pRoot){
    if (pRoot) {
        if (pRoot->pLeft || pRoot->pRight) {
            half_post_order(pRoot->pLeft);
            half_post_order(pRoot->pRight);
            printf("%d -> ", pRoot->data);
        } else {
            printf("Is empty%d -> ", pRoot->data);
        }
    }
}

int main() {
    Node** tree = new Node*;
    Node* pRoot;
    int input_data = 0;
    int prev_data;
    *tree = nullptr;
    show(*tree);
    do{
        prev_data = input_data;
        cout << "\nWhat do you want to do?" << endl;
        cout << "1.Insert" << endl;
        cout << "2.Delete" << endl;
        cout << "3.Show" << endl;
        cout << "4.Inorder" << endl;
        cout << "5.Preorder" << endl;
        cout << "6.Postorder" << endl;
        cout << "7.Exit" << endl;
        cout << "Enter your choice:";
        std::cin >> input_data;
        switch (input_data) {
            case 1:
                cout << "\nEnter The Data for Inserting:";
                std::cin >> input_data;
                cout << "\nInserting!\n\n" << endl;
                inserting(tree, input_data);
                break;
            case 2:
                cout << "\nEnter The Data for Deleting:";
                std::cin >> input_data;
                deleting(input_data, tree);
                break;
            case 3:
                cout << "\n";
                show(*tree);
                break;
            case 4:
                cout << "\n";
                in_order(*tree);
                cout << "\n";
                break;
            case 5:
                cout << "\n";
                pre_order(*tree);
                cout << "\n";
                break;
            case 6:
                cout << "\n";
                pRoot = *tree;
                if(prev_data){
                    if(pRoot){
                        half_post_order(pRoot->pLeft);
                        half_post_order(pRoot->pRight);
                        printf("%d -> ", pRoot->data);
                    }
                } else{
                    printf("Is empty");
                }
                cout << "\n";
                break;
            case 7:
                cout << "\nExiting......" << endl;
                exit(1);
            default:
                cout << "Please Enter a valid number!!\n" << endl;
                break;
        }
    } while (true);
}
