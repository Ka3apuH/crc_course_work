//
// Created by kirill_kazarin on 28.04.22.
//

#ifndef CRC_CRC_MAIN_H
#define CRC_CRC_MAIN_H

#include <vector>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <bitset>
#include <bit>

#define INVERT_BYTE(a)  \
((a&1)<<7) | ((a&2)<<5) | ((a&4)<<3) | \
((a&8)<<1) | ((a&16)>>1) | ((a&32)>>3) | \
((a&64)>>5) | ((a&128)>>7)

class CRC_main {
private:

    /*считываем с потока 256 бит и XOR с регистром в котором созранился остаток*/
    template<int N>
    inline static uint_fast16_t
    fill_reg(std::bitset<256+N> &reg,std::istream &input_inf,bool refIn){

        uint_fast16_t size_of_reg=0;

        auto help_reg=std::bitset<256+N>(0);

        for (int i = 0; i < 32; ++i) {
            char ch=0;
            size_t k=input_inf.readsome(&ch,1);
            if(k==0)break;

            help_reg.operator<<=(8).
                    operator^=(static_cast<uint8_t>(refIn? INVERT_BYTE(ch):ch));

            size_of_reg++;

        }
        reg.operator<<=(size_of_reg*8).operator^=(help_reg);
        return size_of_reg;
    }

    template<int N>
    inline static std::bitset<N> crc_base(std::istream &input_inf,
                                          std::bitset<N> poly_,
                                          std::bitset<N> init,
                                          bool refIn,
                                          bool refOut,
                                          std::bitset<N> xorOut){

        std::bitset<(N)> crc_=init;

        std::bitset<256+N> reg(0x00);

        size_t remainder_of_bits=0;

        while (true){

            //читаем данные из файла и запоминаем кол-во символов
            size_t n_read_byte = fill_reg<N>(reg, input_inf,refIn);

            reg<<=(256-n_read_byte*8+N-remainder_of_bits);

            //находим полную длину регистра в битах
            size_t cout_of_bits=n_read_byte * 8 + remainder_of_bits;

            //находим новое значение остатка бит
            remainder_of_bits=cout_of_bits%N;

            for (size_t j = 0; j < cout_of_bits/N; ++j) {
                std::bitset<N> reg_N= std::bitset<N>(reg.to_string());

                crc_.operator^=(reg_N);

                reg.operator<<=(N);

                for (size_t i=0; i < N; ++i){

                    bool set_main_bit=crc_.test(N - 1);

                    crc_.operator<<=(1);

                    if(set_main_bit)crc_.operator^=(poly_);
                }
            }

            if(n_read_byte <32){
               std::bitset<N> reg_N= std::bitset<N>(reg.to_string());

                crc_.operator^=(reg_N);

                for (size_t i=0; i <(remainder_of_bits); ++i){

                    bool set_main_bit=crc_.test(N - 1);

                    crc_.operator<<=(1);

                    if(set_main_bit)
                        crc_.operator^=(poly_);
                }
                break;
            }

            reg.operator>>=(256+N-remainder_of_bits);
        }

        if(refOut){
            crc_= reverse_bits<N>()(crc_);
        }

        crc_.operator^=(xorOut);

        return crc_;
    }

public:

    static std::bitset<64> crc_64(std::istream &input_inf){
        return crc_base<64>(input_inf,
                            std::bitset<64>(0x42F0E1EBA9EA3693UL),
                            std::bitset<64>(0x0),
                            false,
                            false,
                            std::bitset<64>(0x0));
    }

    static std::bitset<4> crc_4(std::istream &input_inf){
        return crc_base<4>(input_inf,
                            std::bitset<4>(0b1001),
                            std::bitset<4>(0x0),
                            false,
                            false,
                            std::bitset<4>(0x0));
    }

    static std::bitset<8> crc_8(std::istream &input_inf){
        return crc_base<8>(input_inf,
                            std::bitset<8>(0x7),
                            std::bitset<8>(0x0),
                            false,
                            false,
                            std::bitset<8>(0x0));
    }

    static std::bitset<64> crc_64_WE(std::istream &input_inf){
        return crc_base<64>(input_inf,
                                  std::bitset<64>(0x42F0E1EBA9EA3693UL),
                                  std::bitset<64>(0xFFFFFFFFFFFFFFFF),
                                  false,
                                  false,
                                  std::bitset<64>(0xFFFFFFFFFFFFFFFF));
    }

    static std::bitset<32> crc_32_BZIP2(std::istream &input_inf){
        return crc_base<32>(input_inf,
                            std::bitset<32>(0x4C11DB7),
                            std::bitset<32>(0xFFFFFFFF),
                            false,
                            false,
                            std::bitset<32>(0xFFFFFFFF));
    }

    static std::bitset<64> crc_64_XZ(std::istream &input_inf){
        return crc_base<64>(input_inf,
                            std::bitset<64>(0x42F0E1EBA9EA3693),
                            std::bitset<64>(0xFFFFFFFFFFFFFFFF),
                            true,
                            true,
                            std::bitset<64>(0xFFFFFFFFFFFFFFFF));
    }

    static std::bitset<40> crc_40_GSM(std::istream &input_inf){
        return crc_base<40>(input_inf,
                            std::bitset<40>(0x4820009),
                            std::bitset<40>(0x0),
                            false,
                            false,
                            std::bitset<40>(0xFFFFFFFFFF));
    }

    static std::bitset<32> crc_32_XFER(std::istream &input_inf){
        return crc_base<32>(input_inf,
                            std::bitset<32>(0xAF),
                            std::bitset<32>(0x0),
                            false,
                            false,
                            std::bitset<32>(0x0));
    }

    static std::bitset<32> crc_32_JAMCRC(std::istream &input_inf){
        return crc_base<32>(input_inf,
                            std::bitset<32>(0x4C11DB7),
                            std::bitset<32>(0xFFFFFFFF),
                            true,
                            true,
                            std::bitset<32>(0x0));
    }

    static std::bitset<32> crc_32_Q(std::istream &input_inf){
        return crc_base<32>(input_inf,
                            std::bitset<32>(0x814141AB),
                            std::bitset<32>(0x0),
                            true,
                            true,
                            std::bitset<32>(0x0));
    }

    static std::bitset<32> crc_32_POSIX(std::istream &input_inf){
        return crc_base<32>(input_inf,
                            std::bitset<32>(0x4C11DB7),
                            std::bitset<32>(0x0),
                            false,
                            false,
                            std::bitset<32>(0xFFFFFFFF));
    }

    static std::bitset<32> crc_32_MPEG_2(std::istream &input_inf){
        return crc_base<32>(input_inf,
                            std::bitset<32>(0x4C11DB7),
                            std::bitset<32>(0xFFFFFFFF),
                            false,
                            false,
                            std::bitset<32>(0x0));
    }

    static std::bitset<32> crc_32_D(std::istream &input_inf){
        return crc_base<32>(input_inf,
                            std::bitset<32>(0xA833982B),
                            std::bitset<32>(0xFFFFFFFF),
                            true,
                            true,
                            std::bitset<32>(0xFFFFFFFF));
    }

    static std::bitset<32> crc_32_C(std::istream &input_inf){
        return crc_base<32>(input_inf,
                            std::bitset<32>(0x1EDC6F41),
                            std::bitset<32>(0xFFFFFFFF),
                            true,
                            true,
                            std::bitset<32>(0xFFFFFFFF));
    }

    static std::bitset<32> crc_32_ZLIB(std::istream &input_inf){
        return crc_base<32>(input_inf,
                            std::bitset<32>(0x4C11DB7),
                            std::bitset<32>(0xFFFFFFFF),
                            true,
                            true,
                            std::bitset<32>(0xFFFFFFFF));
    }

    static std::bitset<31> crc_31_PHILIPS(std::istream &input_inf){
        return crc_base<31>(input_inf,
                            std::bitset<31>(0x4C11DB7),
                            std::bitset<31>(0x7FFFFFFF),
                            false,
                            false,
                            std::bitset<31>(0x7FFFFFFF));
    }

    static std::bitset<24> crc_24_FLEXRAY_B(std::istream &input_inf){
        return crc_base<24>(input_inf,
                            std::bitset<24>(0x5D6DCB),
                            std::bitset<24>(0xFEDCBA),
                            false,
                            false,
                            std::bitset<24>(0x0));
    }

    static std::bitset<24> crc_24(std::istream &input_inf){
        return crc_base<24>(input_inf,
                            std::bitset<24>(0x864CFB),
                            std::bitset<24>(0xB704CE),
                            false,
                            false,
                            std::bitset<24>(0x0));
    }

    static std::bitset<16> crc_16_XMODEM(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x1021),
                            std::bitset<16>(0x0),
                            false,
                            false,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_X_25(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x1021),
                            std::bitset<16>(0xFFFF),
                            true,
                            true,
                            std::bitset<16>(0xFFFF));
    }

    static std::bitset<16> crc_16_MODBUS(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x8005),
                            std::bitset<16>(0xFFFF),
                            true,
                            true,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_KERMIT(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x1021),
                            std::bitset<16>(0x0),
                            true,
                            true,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_A(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x1021),
                            std::bitset<16>(0xC6C6),
                            true,
                            true,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_USB(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x8005),
                            std::bitset<16>(0xFFFF),
                            true,
                            true,
                            std::bitset<16>(0xFFFF));
    }

    static std::bitset<16> crc_16_TMS37157(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x1021),
                            std::bitset<16>(0x89EC),
                            true,
                            true,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_TELEDISK(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0xA097),
                            std::bitset<16>(0x0),
                            false,
                            false,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_T_10_DIF(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x8BB7),
                            std::bitset<16>(0x0),
                            false,
                            false,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_RIELLO(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x1021),
                            std::bitset<16>(0xB2AA),
                            true,
                            true,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_MCRF4XX(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x1021),
                            std::bitset<16>(0xFFFF),
                            true,
                            true,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_MAXIM(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x8005),
                            std::bitset<16>(0x0),
                            true,
                            true,
                            std::bitset<16>(0xFFFF));
    }

    static std::bitset<16> crc_16_GENIBUS(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x1021),
                            std::bitset<16>(0xFFFF),
                            false,
                            false,
                            std::bitset<16>(0xFFFF));
    }

    static std::bitset<16> crc_16_EN_13757(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x3D65),
                            std::bitset<16>(0x0),
                            false,
                            false,
                            std::bitset<16>(0xFFFF));
    }

    static std::bitset<16> crc_16_DNP(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x3D65),
                            std::bitset<16>(0x0),
                            true,
                            true,
                            std::bitset<16>(0xFFFF));
    }

    static std::bitset<16> crc_16_DECT_X(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x589),
                            std::bitset<16>(0x0),
                            false,
                            false,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_DECT_R(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x589),
                            std::bitset<16>(0x0),
                            false,
                            false,
                            std::bitset<16>(0x1));
    }

    static std::bitset<16> crc_16_DDS_110(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x8005),
                            std::bitset<16>(0x800D),
                            false,
                            false,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_CDMA2000(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0xC867),
                            std::bitset<16>(0xFFFF),
                            false,
                            false,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_CCITT_FALSE(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x1021),
                            std::bitset<16>(0xFFFF),
                            false,
                            false,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_BUYPASS(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x8005),
                            std::bitset<16>(0x0),
                            false,
                            false,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_AUG_CCITT(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x1021),
                            std::bitset<16>(0x1D0F),
                            false,
                            false,
                            std::bitset<16>(0x0));
    }

    static std::bitset<16> crc_16_ARC(std::istream &input_inf){
        return crc_base<16>(input_inf,
                            std::bitset<16>(0x8005),
                            std::bitset<16>(0x0),
                            true,
                            true,
                            std::bitset<16>(0x0));
    }

    static std::bitset<15> crc_15_MPT1327(std::istream &input_inf){
        return crc_base<15>(input_inf,
                            std::bitset<15>(0x6815),
                            std::bitset<15>(0x0),
                            false,
                            false,
                            std::bitset<15>(0x1));
    }

    static std::bitset<15> crc_15(std::istream &input_inf){
        return crc_base<15>(input_inf,
                            std::bitset<15>(0x4599),
                            std::bitset<15>(0x0),
                            false,
                            false,
                            std::bitset<15>(0x0));
    }

    static std::bitset<14> crc_14_DARC(std::istream &input_inf){
        return crc_base<14>(input_inf,
                            std::bitset<14>(0x805),
                            std::bitset<14>(0x0),
                            true,
                            true,
                            std::bitset<14>(0x0));
    }

    static std::bitset<13> crc_13_BBC(std::istream &input_inf){
        return crc_base<13>(input_inf,
                            std::bitset<13>(0x1CF5),
                            std::bitset<13>(0x0),
                            false,
                            false,
                            std::bitset<13>(0x0));
    }

    static std::bitset<12> crc_12_DECT(std::istream &input_inf){
        return crc_base<12>(input_inf,
                            std::bitset<12>(0x80F),
                            std::bitset<12>(0x0),
                            false,
                            false,
                            std::bitset<12>(0x0));
    }

    static std::bitset<12> crc_12_CDMA2000(std::istream &input_inf){
        return crc_base<12>(input_inf,
                            std::bitset<12>(0xF13),
                            std::bitset<12>(0xFFF),
                            false,
                            false,
                            std::bitset<12>(0x0));
    }

    static std::bitset<12> crc_12_3GPP(std::istream &input_inf){
        return crc_base<12>(input_inf,
                            std::bitset<12>(0x80F),
                            std::bitset<12>(0x0),
                            false,
                            true,
                            std::bitset<12>(0x0));
    }

    static std::bitset<11> crc_11(std::istream &input_inf){
        return crc_base<11>(input_inf,
                            std::bitset<11>(0x385),
                            std::bitset<11>(0x1A),
                            false,
                            false,
                            std::bitset<11>(0x0));
    }

    static std::bitset<10> crc_10_CDMA2000(std::istream &input_inf){
        return crc_base<10>(input_inf,
                            std::bitset<10>(0x3D9),
                            std::bitset<10>(0x3FF),
                            false,
                            false,
                            std::bitset<10>(0x0));
    }

    static std::bitset<10> crc_10(std::istream &input_inf){
        return crc_base<10>(input_inf,
                            std::bitset<10>(0x233),
                            std::bitset<10>(0x0),
                            false,
                            false,
                            std::bitset<10>(0x0));
    }

    static std::bitset<8> crc_8_WCDMA(std::istream &input_inf){
        return crc_base<8>(input_inf,
                           std::bitset<8>(0x9B),
                           std::bitset<8>(0x0),
                           true,
                           true,
                           std::bitset<8>(0x0));
    }

    static std::bitset<8> crc_8_ROHC(std::istream &input_inf){
        return crc_base<8>(input_inf,
                           std::bitset<8>(0x7),
                           std::bitset<8>(0xFF),
                           true,
                           true,
                           std::bitset<8>(0x0));
    }

    static std::bitset<8> crc_8_MAXIM(std::istream &input_inf){
        return crc_base<8>(input_inf,
                           std::bitset<8>(0x31),
                           std::bitset<8>(0x0),
                           true,
                           true,
                           std::bitset<8>(0x0));
    }

    static std::bitset<8> crc_8_ITU(std::istream &input_inf){
        return crc_base<8>(input_inf,
                           std::bitset<8>(0x7),
                           std::bitset<8>(0x0),
                           false,
                           false,
                           std::bitset<8>(0x55));
    }

    static std::bitset<8> crc_8_I_CODE(std::istream &input_inf){
        return crc_base<8>(input_inf,
                           std::bitset<8>(0x1D),
                           std::bitset<8>(0xFD),
                           false,
                           false,
                           std::bitset<8>(0x0));
    }

    static std::bitset<8> crc_8_EBU(std::istream &input_inf){
        return crc_base<8>(input_inf,
                           std::bitset<8>(0x1D),
                           std::bitset<8>(0xFF),
                           true,
                           true,
                           std::bitset<8>(0x0));
    }

    static std::bitset<8> crc_8_DVB_S2(std::istream &input_inf){
        return crc_base<8>(input_inf,
                           std::bitset<8>(0xD5),
                           std::bitset<8>(0x0),
                           false,
                           false,
                           std::bitset<8>(0x0));
    }

    static std::bitset<8> crc_8_DARC(std::istream &input_inf){
        return crc_base<8>(input_inf,
                           std::bitset<8>(0x39),
                           std::bitset<8>(0x0),
                           true,
                           true,
                           std::bitset<8>(0x0));
    }

    static std::bitset<8> crc_8_CDMA2000(std::istream &input_inf){
        return crc_base<8>(input_inf,
                           std::bitset<8>(0x9B),
                           std::bitset<8>(0xFF),
                           false,
                           false,
                           std::bitset<8>(0x0));
    }

    static std::bitset<7> crc_7_ROHC(std::istream &input_inf){
        return crc_base<7>(input_inf,
                           std::bitset<7>(0x4F),
                           std::bitset<7>(0x7F),
                           true,
                           true,
                           std::bitset<7>(0x0));
    }

    static std::bitset<7> crc_7(std::istream &input_inf){
        return crc_base<7>(input_inf,
                           std::bitset<7>(0x9),
                           std::bitset<7>(0x0),
                           false,
                           false,
                           std::bitset<7>(0x0));
    }

    static std::bitset<6> crc_6_ITU(std::istream &input_inf){
        return crc_base<6>(input_inf,
                           std::bitset<6>(0x3),
                           std::bitset<6>(0x0),
                           true,
                           true,
                           std::bitset<6>(0x0));
    }

    static std::bitset<6> crc_6_DARC(std::istream &input_inf){
        return crc_base<6>(input_inf,
                           std::bitset<6>(0x19),
                           std::bitset<6>(0x0),
                           true,
                           true,
                           std::bitset<6>(0x0));
    }

    static std::bitset<6> crc_6_CDMA2000_B(std::istream &input_inf){
        return crc_base<6>(input_inf,
                           std::bitset<6>(0x7),
                           std::bitset<6>(0x3F),
                           false,
                           false,
                           std::bitset<6>(0x0));
    }

    static std::bitset<6> crc_6_CDMA2000_A(std::istream &input_inf){
        return crc_base<6>(input_inf,
                           std::bitset<6>(0x27),
                           std::bitset<6>(0x3F),
                           false,
                           false,
                           std::bitset<6>(0x0));
    }

    static std::bitset<5> crc_5_USB(std::istream &input_inf){
        return crc_base<5>(input_inf,
                           std::bitset<5>(0x5),
                           std::bitset<5>(0x1F),
                           true,
                           true,
                           std::bitset<5>(0x1F));
    }

    static std::bitset<5> crc_5_ITU(std::istream &input_inf){
        return crc_base<5>(input_inf,
                           std::bitset<5>(0x15),
                           std::bitset<5>(0x0),
                           true,
                           true,
                           std::bitset<5>(0x0));
    }

    static std::bitset<5> crc_5_EPC(std::istream &input_inf){
        return crc_base<5>(input_inf,
                           std::bitset<5>(0x9),
                           std::bitset<5>(0x9),
                           false,
                           false,
                           std::bitset<5>(0x0));
    }

    static std::bitset<4> crc_4_ITU(std::istream &input_inf){
        return crc_base<4>(input_inf,
                           std::bitset<4>(0x3),
                           std::bitset<4>(0x0),
                           true,
                           true,
                           std::bitset<4>(0x0));
    }

    static std::bitset<3> crc_3_ROHC(std::istream &input_inf){
        return crc_base<3>(input_inf,
                           std::bitset<3>(0x3),
                           std::bitset<3>(0x7),
                           true,
                           true,
                           std::bitset<3>(0x0));
    }
private:

    template<int N>
    class reverse_bits: std::unary_function<std::bitset<N>,std::bitset<N>>{
    public:
        reverse_bits()=default;
        ~reverse_bits()=default;

        std::bitset<N> operator()(std::bitset<N> k){
           auto res=std::bitset<N>(0x0);
               for (size_t i = 0; i < N; ++i) {
                   res.set(i, k.test(N - 1 - i));
               }
            return res;
        }
    };

};
#endif //CRC_CRC_MAIN_H
