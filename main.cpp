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
    tree.InsertNode(300);
    //tree.InsertNode(400);
    tree.InsertNode(150);
    tree.InsertNode(20);
    tree.InsertNode(200);
    tree.InsertNode(2);
    tree.InsertNode(0);
    tree.InsertNode(3);
    tree.InsertNode(10);

    std::cout<<tree<<std::endl;
    std::cout<<"height: "<<tree.height()<<std::endl;
    //tree.PrintTree();
    return 0;
}
