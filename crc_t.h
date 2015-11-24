/*
 * crc_t.h
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

#ifndef CRC_T_H
#define CRC_T_H

#include <stdint.h>
#include <string>





class CRC_t
{

    public:

        explicit CRC_t(const std::string Name = "CRC-32",
                       uint8_t  Bits   = 32,
                       uint64_t Poly   = 0x04c11db7,
                       uint64_t Init   = 0xffffffff,
                       bool     RefIn  = true,
                       bool     RefOut = true,
                       uint64_t XorOut = 0xffffffff);


        explicit CRC_t(uint8_t  Bits,
                       uint64_t Poly,
                       uint64_t Init,
                       bool     RefIn,
                       bool     RefOut,
                       uint64_t XorOut);


        std::string name;


        // get param CRC
        uint8_t  get_bits()    const { return bits;   }
        uint64_t get_poly()    const { return poly;   }
        uint64_t get_init()    const { return init;   }
        uint64_t get_xor_out() const { return xor_out;}
        bool     get_ref_in()  const { return ref_in; }
        bool     get_ref_out() const { return ref_out;}

        uint64_t get_crc_init()const { return crc_init;} //crc_init = reflect(init, bits) if RefIn, else = init



    private:

        uint8_t  bits;
        uint64_t poly;
        uint64_t init;
        bool     ref_in;
        bool     ref_out;
        uint64_t xor_out;

        uint8_t  shift;
        uint64_t crc_init;
        uint64_t top_bit;
        uint64_t crc_mask;
        uint64_t crc_table[256];


        uint64_t reflect(uint64_t data, uint8_t num_bits);
        void     init_crc_table();
        void     init_class();
};





#endif // CRC_T_H
