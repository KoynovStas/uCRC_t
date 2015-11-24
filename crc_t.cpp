#include "crc_t.h"
#include <cstdio>




CRC_t::CRC_t(const std::string Name, uint8_t Bits, uint64_t Poly, uint64_t Init, bool RefIn, bool RefOut, uint64_t XorOut)
{
    name    = Name;
    bits    = Bits;
    poly    = Poly;
    init    = Init;
    ref_in  = RefIn;
    ref_out = RefOut;
    xor_out = XorOut;
}



CRC_t::CRC_t(uint8_t Bits, uint64_t Poly, uint64_t Init, bool RefIn, bool RefOut, uint64_t XorOut)
{
    bits    = Bits;
    poly    = Poly;
    init    = Init;
    ref_in  = RefIn;
    ref_out = RefOut;
    xor_out = XorOut;
}
