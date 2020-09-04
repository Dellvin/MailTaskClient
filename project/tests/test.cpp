//
// Created by Dellvin on 06.03.2020.
//
#include "gtest/gtest.h"

extern "C++"{
#include "../UI/ui.h"
}

TEST(test, Test1) {
    UI cli("jdjrfdjjghiukhvvbukhjchcvy", 2000);
    EXPECT_EQ(cli.start(), 1);
}

TEST(test, Test2) {
    UI cli("192.168.0.1", 0);
    EXPECT_EQ(cli.start(), 3);
}
