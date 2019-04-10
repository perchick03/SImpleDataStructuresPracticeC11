#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SimpleBinaryTree.h"

int main(int argc, char* argv[]) {
    using namespace exercise;
//    testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();

    SimpleBinaryTree<int> tree;
    tree.InsertNode(100);
    tree.InsertNode(200);
<<<<<<< HEAD
    tree.InsertNode(300);
    //tree.InsertNode(400);
    tree.InsertNode(150);
=======
>>>>>>> c77716d9fd4614df96ac5d9662703323c10ce61a
    tree.InsertNode(20);
    tree.InsertNode(200);
    tree.InsertNode(2);
    tree.InsertNode(0);
    tree.InsertNode(3);
    tree.InsertNode(10);
<<<<<<< HEAD

    std::cout<<tree<<std::endl;
    std::cout<<"height: "<<tree.height()<<std::endl;
    //tree.PrintTree();
=======
    tree.PrintTree();
>>>>>>> c77716d9fd4614df96ac5d9662703323c10ce61a
    return 0;
}
