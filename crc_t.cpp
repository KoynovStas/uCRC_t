/*
 * crc_t.cpp
 *
 *
 * Copyright (c) 2015, Koynov Stas - skojnov@yandex.ru
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1 Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  2 Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  3 Neither the name of the <organization> nor the
 *    names of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

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


    init_class();
}



CRC_t::CRC_t(uint8_t Bits, uint64_t Poly, uint64_t Init, bool RefIn, bool RefOut, uint64_t XorOut)
{
    bits    = Bits;
    poly    = Poly;
    init    = Init;
    ref_in  = RefIn;
    ref_out = RefOut;
    xor_out = XorOut;


    init_class();
}



int CRC_t::set_bits(uint8_t new_bits)
{
    if( (new_bits < 1) || (new_bits > 64) )
        return -1; //error


    bits = new_bits;
    init_class();


    return 0; //good job
}



uint64_t CRC_t::get_crc(const char *buf, size_t len) const
{
    uint64_t crc = get_raw_crc(crc_init, buf, len);

    return get_final_crc(crc);
}



int CRC_t::get_crc(uint64_t *crc, const char *file_name) const
{
    if( !file_name || !crc )
        return -1; //Bad param

    *crc = crc_init;

    char buf[4096];


    FILE *stream = fopen(file_name, "rb");
    if( stream == NULL )
        return -1; //Cant open file


    while( !feof(stream) )
    {
       size_t len = fread(buf, 1, sizeof(buf), stream);
       *crc = get_raw_crc(*crc, buf, len);
    }


    fclose(stream);


    *crc = get_final_crc(*crc);


    return 0; //good  job
}



uint64_t CRC_t::get_raw_crc(uint64_t crc, const char *buf, size_t len) const
{
    if(bits > 8)
    {
        if(ref_in)
            while (len--)
                crc = (crc >> 8) ^ crc_table[ (crc ^ *buf++) & 0xff ];
        else
            while (len--)
                crc = (crc << 8) ^ crc_table[ ((crc >> shift) & 0xff) ^ *buf++ ];
    }
    else
    {
        if (ref_in)
            while (len--)
                crc = crc_table[ crc ^ *buf++ ];
        else
            while (len--)
                crc = crc_table[ (crc << shift) ^ *buf++ ];
    }


    return crc;
}



uint64_t CRC_t::get_final_crc(uint64_t raw_crc) const
{
    if(ref_out^ref_in) raw_crc = reflect(raw_crc, bits);

    raw_crc ^= xor_out;
    raw_crc &= crc_mask; //for CRC not power 2

    return raw_crc;
}



uint64_t CRC_t::reflect(uint64_t data, uint8_t num_bits) const
{
    uint64_t reflection = 0;
    uint64_t one = 1;

    for ( size_t i = 0; i < num_bits; ++i, data >>= 1 )
    {
        if ( data & one )
        {
            reflection |= ( one << (num_bits - one - i) );
        }
    }

    return reflection;
}



void CRC_t::init_crc_table()
{
    int i;
    uint64_t crc;


    for(i = 0; i < 256; i++)
    {

        crc = 0;

        for(uint8_t mask = 0x80; mask; mask >>= 1)
        {

            if ( i & mask )
                crc ^= top_bit;


            if (crc & top_bit)
            {
                crc <<= 1;
                crc ^= poly;
            }
            else
                crc <<= 1;
        }

        crc &= crc_mask; //for CRC not power 2

        if(ref_in)
            crc_table[reflect(i, 8)] = reflect(crc, bits);
        else
            crc_table[i] = crc;
    }
}



void CRC_t::init_class()
{
    top_bit  = (uint64_t)1 << (bits - 1);
    crc_mask = ( (top_bit - 1) << 1) | 1;


    if(bits > 8)
        shift = (bits - 8);
    else
        shift = (8 - bits);


    if(ref_in)
        crc_init = reflect(init, bits);
    else
        crc_init = init;


    init_crc_table();
}
