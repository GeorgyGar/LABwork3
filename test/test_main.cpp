#include <gtest.h>
#include <arithmetic.h>



int main(int argc, char **argv) {

    setlocale(LC_ALL, "Russian");

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
