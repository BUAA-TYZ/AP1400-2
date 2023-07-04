#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
        BST::Node node1(5);
        BST::Node node2(3, &node1);
        BST::Node node3(7, nullptr, &node1);
        cout << node2 << endl << node1 << endl << node3 << endl;
        assert(node1 == 5);
        assert(node1 != 6);
        assert(node1 < 6);
        assert(node1 > 4);
        assert(node1 <= 5);
        assert(node1 >= 5);

    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}