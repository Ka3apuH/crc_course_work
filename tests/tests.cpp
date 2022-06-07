//
// Created by kirill_kazarin on 19.05.22.
//

#include "CRC_main.h"
#include "crc_test.h"

TEST_F(Testing_main_CRC,crc_64){

    auto res=CRC_main::crc_64(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x6C40DF5F0B497347));
}

TEST_F(Testing_main_CRC,crc64_WE){
    auto res=CRC_main::crc_64_WE(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x62EC59E3F1A4F00AUL));
}

TEST_F(Testing_main_CRC,crc32){
    auto res=CRC_main::crc_32_BZIP2(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xFC891918));
}

TEST_F(Testing_main_CRC,crc4){
    auto res=CRC_main::crc_4(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0b0110));
}

TEST_F(Testing_main_CRC,crc_3_ROHC){
    auto res=CRC_main::crc_3_ROHC(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x6));
}

TEST_F(Testing_main_CRC,crc_32_ZLIB){
    auto res=CRC_main::crc_32_ZLIB(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xCBF43926));
}

TEST_F(Testing_main_CRC,crc_32_BZIP2){
    auto res=CRC_main::crc_32_BZIP2(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xFC891918));
}

TEST_F(Testing_main_CRC,crc_11){
    auto res=CRC_main::crc_11(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x5A3));
}

TEST_F(Testing_main_CRC,crc_12_3GPP){
    auto res=CRC_main::crc_12_3GPP(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xDAF));
}

TEST_F(Testing_main_CRC,crc_16_CCITT_FALSE){
    auto res=CRC_main::crc_16_CCITT_FALSE(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x29B1));
}

TEST_F(Testing_main_CRC,crc_4_ITU){
    auto res=CRC_main::crc_4_ITU(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x7));
}

TEST_F(Testing_main_CRC,crc_5_EPC){
    auto res=CRC_main::crc_5_EPC(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x0));
}

TEST_F(Testing_main_CRC,crc_5_ITU){
    auto res=CRC_main::crc_5_ITU(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x7));
}

TEST_F(Testing_main_CRC,crc_5_USB){
    auto res=CRC_main::crc_5_USB(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x19));
}

TEST_F(Testing_main_CRC,crc_6_CDMA2000_A){
    auto res=CRC_main::crc_6_CDMA2000_A(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xD));
}

TEST_F(Testing_main_CRC,crc_6_CDMA2000_B){
    auto res=CRC_main::crc_6_CDMA2000_B(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x3B));
}

TEST_F(Testing_main_CRC,crc_6_DARC){
    auto res=CRC_main::crc_6_DARC(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x26));
}

TEST_F(Testing_main_CRC,crc_6_ITU){
    auto res=CRC_main::crc_6_ITU(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x6));
}

TEST_F(Testing_main_CRC,crc_7){
    auto res=CRC_main::crc_7(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x75));
}

TEST_F(Testing_main_CRC,crc_7_ROHC){
    auto res=CRC_main::crc_7_ROHC(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x53));
}

TEST_F(Testing_main_CRC,crc_8){
    auto res=CRC_main::crc_8(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xF4));
}

TEST_F(Testing_main_CRC,crc_8_CDMA2000){
    auto res=CRC_main::crc_8_CDMA2000(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xDA));
}

TEST_F(Testing_main_CRC,crc_8_DARC){
    auto res=CRC_main::crc_8_DARC(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x15));
}

TEST_F(Testing_main_CRC,crc_8_DVB_S2){
    auto res=CRC_main::crc_8_DVB_S2(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xBC));
}

TEST_F(Testing_main_CRC,crc_8_EBU){
    auto res= CRC_main::crc_8_EBU(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x97));
}

TEST_F(Testing_main_CRC,crc_8_I_CODE){
    auto res=CRC_main::crc_8_I_CODE(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x7E));
}

TEST_F(Testing_main_CRC,crc_8_ITU){
    auto res=CRC_main::crc_8_ITU(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xA1));
}

TEST_F(Testing_main_CRC,crc_8_MAXIM){
    auto res= CRC_main::crc_8_MAXIM(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xA1));
}

TEST_F(Testing_main_CRC,crc_8_ROHC){
    auto res=CRC_main::crc_8_ROHC(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xD0));
}

TEST_F(Testing_main_CRC,crc_64_XZ){
    auto res=CRC_main::crc_64_XZ(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0x995DC9BBDF1939FA));
}

TEST_F(Testing_main_CRC,crc_40_GSM){
    auto res= CRC_main::crc_40_GSM(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xD4164FC646));
}

TEST_F(Testing_main_CRC,crc_32_XFER){
    auto res=CRC_main::crc_32_XFER(str);
    ASSERT_EQ(res.to_ulong(),static_cast<ulong>(0xBD0BE338));
}



