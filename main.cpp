#include <iostream>
#include <bitset>
#include "crc_main/CRC_main.h"

int main() {

    std::cout << std::bitset<8>(0b01111111).operator>>(8) << std::endl;
    return 0;
}
