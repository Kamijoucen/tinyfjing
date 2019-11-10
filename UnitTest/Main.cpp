/*
 * @Author: kamijoucen
 * @Date: 2019-11-10 22:21:25
 * @LastEditTime: 2019-11-10 22:21:52
 * @LastEditors: kamijoucen
 * @Description: 
 * @FilePath: \tinyfjing\UnitTest\Main.cpp
 * @
 */
#include <gtest/gtest.h>
#include "LexicalTest.h"

#define _UNICODE_TINYFJING

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}