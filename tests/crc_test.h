//
// Created by kirill_kazarin on 19.05.22.
//

#ifndef CRC_CRC_TEST_H
#define CRC_CRC_TEST_H

#include "../crc_main/CRC_main.h"
#include <gtest/gtest.h>
#include <random>

class Testing_main_CRC : public ::testing::Test {
protected:
    void SetUp() override {
        str << "123456789";
    }
    void TearDown() override {
        str.clear();
    }

// объекты тестового окружения, доступные в каждом тесте
    std::stringstream str{};
};


#endif //CRC_CRC_TEST_H
