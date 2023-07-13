#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
        FLAGS_log_dir = "../log";
        google::InitGoogleLogging(argv[0]);
        Matrix t = algebra::random(5, 5, 1, 10);

        algebra::show(t);
        google::ShutdownGoogleLogging();
    }
    else
    {
        FLAGS_log_dir = "../log";
        google::InitGoogleLogging(argv[0]);
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
        google::ShutdownGoogleLogging();
    }
    return 0;
}
