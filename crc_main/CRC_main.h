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

static const  uint8_t reverse_table[16]{
0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE,
0x1, 0x9, 0x5, 0xD, 0x3, 0xB, 0x7, 0xF};

class CRC_main {

   /* static inline uint32_t crc_32_bit_base(std::istream input_inf, uint32_t poly_,uint32_t init,
                                               uint32_t doXor,bool refIn,bool refOut){
        uint32_t crc_=init;

        while (input_inf.eof()){

            if(refIn){
                crc_=crc_^(static_cast<int32_t>(
                        reverse_bits_32()(
                                static_cast<int8_t>(input_inf.get())
                                )
                                )<<8);
            } else
            {
                crc_=crc_^ (static_cast<int32_t>((input_inf.get()))<<8);
            }

            for (int i = 0; i < 8; ++i) {
                if(crc_ & 0x8000){
                    crc_=(crc_<<1)^poly_;
                } else{
                    crc_=crc_<<1;
                }
            }
        }

        if(refOut){
            crc_= reverse_bits_32()(crc_);
        }

        return (crc_ ^ doXor);
    }

    static inline uint32_t crc_64_bit_base(std::istream input_inf, uint64_t poly_,uint64_t init,
                                           uint64_t doXor,bool refIn,bool refOut){
        uint64_t crc_=init;

        while (input_inf.eof()){

            if(refIn){
                crc_=crc_^(static_cast<int64_t>(
                        reverse_bits_64()(
                                static_cast<int8_t>(input_inf.get())
                        )
                )<<8);
            } else
            {
                crc_=crc_^ (static_cast<int64_t>((input_inf.get()))<<8);
            }

            for (int i = 0; i < 8; ++i) {
                if(crc_ & 0x80000000){
                    crc_=(crc_<<1)^poly_;
                } else{
                    crc_=crc_<<1;
                }
            }
        }

        if(refOut){
            crc_= reverse_bits_64()(crc_);
        }

        return (crc_ ^ doXor);
    }
*/

    template<typename int_t>
    static inline int_t crc_base(std::istream &input_inf, int_t poly_,int_t init,
                                 int_t doXor,bool refIn,bool refOut,std::function<int_t(int_t)> revers_bits){
        int_t crc_=init;

        while (input_inf.eof()){

            if(refIn){
                crc_=crc_^(static_cast<int_t>(
                        revers_bits(
                                static_cast<int8_t>(input_inf.get())
                        )
                )<<8);
            } else
            {
                crc_=crc_^ (static_cast<int_t>((input_inf.get()))<<8);
            }

            for (int i = 0; i < 8; ++i) {
                if(crc_ & static_cast<int_t>(0x8)<<(sizeof(int_t)-4)){
                    crc_=(crc_<<1)^poly_;
                } else{
                    crc_=crc_<<1;
                }
            }
        }

        if(refOut){
            crc_= revers_bits(crc_);
        }

        return (crc_ ^ doXor);
    }

    template<int N>
    static inline std::bitset<N> crc_base_2(std::istream &input_inf,
                                            std::bitset<N> &poly_,
                                            std::bitset<N> &init,
                                            std::bitset<N> &doXor,
                                            bool refIn,bool refOut,
                                 std::function<std::bitset<N>(std::bitset<N>)> revers_bits){
        std::bitset<N> crc_=init;

        while (input_inf.eof()){

            if(refIn){
                crc_=crc_^(revers_bits(std::bitset<N>(input_inf.get()))<<8);
            } else
            {
                crc_=crc_^(std::bitset<N>(input_inf.get())<<8);
            }

            for (int i = 0; i < 8; ++i) {
                if(crc_[0].operator~()){
                    crc_=(crc_.operator<<(1))^poly_;
                } else{
                    crc_=crc_.operator<<(1);
                }
            }
        }

        if(refOut){
            crc_= revers_bits(crc_);
        }

        return (crc_ ^ doXor);
    }

    static inline uint8_t crc_8_bit(std::istream &input_inf, uint8_t poly_,uint8_t init,
                                      uint8_t doXor,bool refIn,bool refOut){
        return crc_base<uint8_t>(input_inf,poly_,init,doXor,refIn,refOut,reverse_bits_8());
    }

    static inline uint16_t crc_16_bit(std::istream &input_inf, uint16_t poly_,uint16_t init,
                              uint16_t doXor,bool refIn,bool refOut){
        return crc_base<uint16_t>(input_inf,poly_,init,doXor,refIn,refOut,reverse_bits_16());
    }

    static inline uint32_t crc_32_bit(std::istream &input_inf, uint32_t poly_,uint32_t init,
                                      uint32_t doXor,bool refIn,bool refOut){
        return crc_base<uint32_t>(input_inf,poly_,init,doXor,refIn,refOut,reverse_bits_32());
    }

    static inline uint64_t crc_64_bit(std::istream &input_inf, uint64_t poly_,uint64_t init,
                                      uint64_t doXor,bool refIn,bool refOut){
        return crc_base<uint64_t>(input_inf,poly_,init,doXor,refIn,refOut,reverse_bits_64());
    }

private:

class reverse_bits_8: std::unary_function<uint8_t,uint8_t>{
public:
        reverse_bits_8()=default;
        ~reverse_bits_8()=default;

        uint8_t operator()(uint8_t k){
            return static_cast<uint8_t>((reverse_table[k & 0xF]<<4)| reverse_table[k >> 4]);
        }
};

    template<int N>
    class reverse_bits: std::unary_function<std::bitset<N>,std::bitset<N>>{
    public:
        reverse_bits()=default;
        ~reverse_bits()=default;

        std::bitset<N> operator()(std::bitset<N> &k){
           auto res=std::bitset<N>(0);
            for (int i = 0; i < N; ++i) {
                res.set(i,k[N-1-i].operator~());
            }
        }
    };

/*    template<typename int_t>
    class reverse_bits: std::unary_function<int_t,int_t>{
    public:
        reverse_bits()=default;
        ~reverse_bits()=default;

        int_t operator()(int_t k){
            for (int i = 0; i < sizeof(int_t); ++i) {

            }
            return static_cast<int8_t>((reverse_table[k & 0xF]<<4)| reverse_table[k >> 4]);
        }
    };*/

    class reverse_bits_16: std::unary_function<uint16_t,uint16_t>{
    public:
        reverse_bits_16()=default;
        ~reverse_bits_16()=default;

        uint16_t operator()(uint16_t k){
            return static_cast<int16_t>(reverse_bits_8()(static_cast<uint8_t>(k & 0xFF)))<<8|
                   reverse_bits_8()(static_cast<uint8_t>(k >>8));
        }
    };

    class reverse_bits_32: std::unary_function<uint32_t,uint32_t>{
    public:
        reverse_bits_32()=default;
        ~reverse_bits_32()=default;

        uint32_t operator()(uint32_t k){
            return static_cast<int32_t>(reverse_bits_16()(static_cast<uint16_t>(k & 0xFFFF)))<<16|
                   reverse_bits_16()(static_cast<uint16_t>(k >>16));
        }
    };

    class reverse_bits_64: std::unary_function<uint64_t,uint64_t>{
    public:
        reverse_bits_64()=default;
        ~reverse_bits_64()=default;

        uint8_t operator()(uint64_t k){
            return static_cast<int64_t>(reverse_bits_32()(static_cast<uint32_t>(k & 0xFFFFFFFF)))<<32 |
                   reverse_bits_32()(static_cast<uint32_t>(k >>32));
        }
    };


/*    static uint8_t  reverse_bits_8(uint8_t k){
        return static_cast<int8_t>((reverse_table[k & 0xF]<<4)| reverse_table[k >> 4]);
    }*/

    /*static uint16_t reverse_bits_16(uint16_t k){
        return static_cast<int16_t>(reverse_bits_8(static_cast<uint8_t>(k & 0xFF)))<<8|
        reverse_bits_8(static_cast<uint8_t>(k >>8));
    }*/

    /*static uint32_t reverse_bits_32(uint32_t k){
        return static_cast<int32_t>(reverse_bits_16(static_cast<uint16_t>(k & 0xFFFF)))<<16|
        reverse_bits_16(static_cast<uint16_t>(k >>16));
    }*/
/*
    static uint64_t reverse_bits_64(uint64_t k){
        return static_cast<int64_t>(reverse_bits_32(static_cast<uint32_t>(k & 0xFFFFFFFF)))<<32 |
                                    reverse_bits_32(static_cast<uint32_t>(k >>32));
    }*/

};


#endif //CRC_CRC_MAIN_H
