#include "unit_tests.h"
#include "crc_t.h"





//------------- tests for CRC_t methods -------------


int test_crc_t_name(struct test_info_t  *test_info)
{

    TEST_INIT;


    CRC_t  crc;


    if( crc.name != "CRC-32" )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc_t_name_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    const char* name = "some_name";

    CRC_t crc(name);


    if( crc.name != name )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc_t_get_bits(struct test_info_t  *test_info)
{

    TEST_INIT;


    CRC_t crc(1, 0, 0, true, true, 0);


    if( crc.get_bits() != 1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc_t_get_poly(struct test_info_t  *test_info)
{

    TEST_INIT;


    CRC_t crc(1, 123, 0, true, true, 0);


    if( crc.get_poly() != 123 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc_t_get_init(struct test_info_t  *test_info)
{

    TEST_INIT;


    CRC_t crc(1, 0, 1234, true, true, 0);


    if( crc.get_init() != 1234 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc_t_get_xor_out(struct test_info_t  *test_info)
{

    TEST_INIT;


    CRC_t crc(1, 0, 0, true, true, 1000);


    if( crc.get_xor_out() != 1000 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc_t_get_ref_in(struct test_info_t  *test_info)
{

    TEST_INIT;


    CRC_t crc(1, 0, 0, true, true, 0);


    if( crc.get_ref_in() != true )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc_t_get_ref_out(struct test_info_t  *test_info)
{

    TEST_INIT;


    CRC_t crc(1, 0, 0, true, true, 0);


    if( crc.get_ref_out() != true )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc_t_set_bits(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i, res;

    CRC_t crc(1, 0, 0, true, true, 0);


    if( crc.get_bits() != 1 )
        return TEST_BROKEN;


    if( crc.set_bits(0) != -1 )
         return TEST_BROKEN;

    // 1..64
    for( i = 1; i <= 64; ++i)
    {
        res = crc.set_bits(i);
        if( res != 0 )
             return TEST_BROKEN;

        if( crc.get_bits() != i )
            return TEST_BROKEN;
    }


    //more 64
    for( i = 65; i <= 256; ++i)
    {
        if( crc.set_bits(i) != -1 )
             return TEST_BROKEN;
    }



    return TEST_PASSED;
}



//------------- tests for Calculate CRC  -------------



//width=3 poly=0x3 init=0x7 refin=true refout=true xorout=0x0 check=0x6 name="CRC-3/ROHC"
int test_crc3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(3, 0x3, 0x7, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x6 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc4(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(4, 0x3, 0x0, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xE )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=4 poly=0x3 init=0x0 refin=true refout=true xorout=0x0 check=0x7 name="CRC-4/ITU"
int test_crc4_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(4, 0x3, 0x0, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x7 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=5 poly=0x09 init=0x09 refin=false refout=false xorout=0x00 check=0x00 name="CRC-5/EPC"
int test_crc5(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(5, 0x09, 0x09, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x0 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=5 poly=0x15 init=0x00 refin=true refout=true xorout=0x00 check=0x07 name="CRC-5/ITU"
int test_crc5_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(5, 0x15, 0x00, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x07 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=5 poly=0x05 init=0x1f refin=true refout=true xorout=0x1f check=0x19 name="CRC-5/USB"
int test_crc5_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(5, 0x05, 0x1f, true, true, 0x1f);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x19 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=6 poly=0x27 init=0x3f refin=false refout=false xorout=0x00 check=0x0d name="CRC-6/CDMA2000-A"
int test_crc6(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(6, 0x27, 0x3f, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x0d )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=6 poly=0x07 init=0x3f refin=false refout=false xorout=0x00 check=0x3b name="CRC-6/CDMA2000-B"
int test_crc6_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(6, 0x07, 0x3f, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x3b )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=6 poly=0x19 init=0x00 refin=true refout=true xorout=0x00 check=0x26 name="CRC-6/DARC"
int test_crc6_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(6, 0x19, 0x0, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x26 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=6 poly=0x03 init=0x00 refin=true refout=true xorout=0x00 check=0x06 name="CRC-6/ITU"
int test_crc6_4(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(6, 0x03, 0x0, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x06 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=7 poly=0x09 init=0x00 refin=false refout=false xorout=0x00 check=0x75 name="CRC-7"
int test_crc7(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(7, 0x09, 0x0, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x75 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=7 poly=0x4f init=0x7f refin=true refout=true xorout=0x00 check=0x53 name="CRC-7/ROHC"
int test_crc7_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(7, 0x4f, 0x7f, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x53 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc8(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(8, 0x31, 0xFF, false, false, 0x00);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xF7 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x07 init=0x00 refin=false refout=false xorout=0x00 check=0xf4 name="CRC-8"
int test_crc8_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(8, 0x07, 0x0, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xF4 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x9b init=0xff refin=false refout=false xorout=0x00 check=0xda name="CRC-8/CDMA2000"
int test_crc8_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(8, 0x9b, 0xff, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xDA )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x39 init=0x00 refin=true refout=true xorout=0x00 check=0x15 name="CRC-8/DARC"
int test_crc8_4(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(8, 0x39, 0x0, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x15 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0xd5 init=0x00 refin=false refout=false xorout=0x00 check=0xbc name="CRC-8/DVB-S2"
int test_crc8_5(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(8, 0xd5, 0x0, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xBC )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x1d init=0xff refin=true refout=true xorout=0x00 check=0x97 name="CRC-8/EBU"
int test_crc8_6(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(8, 0x1d, 0xff, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x97 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x1d init=0xfd refin=false refout=false xorout=0x00 check=0x7e name="CRC-8/I-CODE"
int test_crc8_7(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(8, 0x1d, 0xfd, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x7E )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x07 init=0x00 refin=false refout=false xorout=0x55 check=0xa1 name="CRC-8/ITU"
int test_crc8_8(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(8, 0x07, 0x00, false, false, 0x55);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xA1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x31 init=0x00 refin=true refout=true xorout=0x00 check=0xa1 name="CRC-8/MAXIM"
int test_crc8_9(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(8, 0x31, 0x00, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xA1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x07 init=0xff refin=true refout=true xorout=0x00 check=0xd0 name="CRC-8/ROHC"
int test_crc8_10(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(8, 0x07, 0xff, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xD0 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x9b init=0x00 refin=true refout=true xorout=0x00 check=0x25 name="CRC-8/WCDMA"
int test_crc8_11(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t ucrc(8, 0x9b, 0x00, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x25 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=10 poly=0x233 init=0x000 refin=false refout=false xorout=0x000 check=0x199 name="CRC-10"
int test_crc10(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(10, 0x233, 0x0, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x199 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=10 poly=0x3d9 init=0x3ff refin=false refout=false xorout=0x000 check=0x233 name="CRC-10/CDMA2000"
int test_crc10_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(10, 0x3d9, 0x3ff, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x233 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=11 poly=0x385 init=0x01a refin=false refout=false xorout=0x000 check=0x5a3 name="CRC-11"
int test_crc11(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(11, 0x385, 0x01a, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x5A3 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=12 poly=0x80f init=0x000 refin=false refout=true xorout=0x000 check=0xdaf name="CRC-12/3GPP"
int test_crc12(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(12, 0x80f, 0x0, false, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xDAF )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=12 poly=0xf13 init=0xfff refin=false refout=false xorout=0x000 check=0xd4d name="CRC-12/CDMA2000"
int test_crc12_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(12, 0xf13, 0xfff, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xD4D )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=12 poly=0x80f init=0x000 refin=false refout=false xorout=0x000 check=0xf5b name="CRC-12/DECT"
int test_crc12_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(12, 0x80f, 0x0, false, false, 0x0);


    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xF5B )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=13 poly=0x1cf5 init=0x0000 refin=false refout=false xorout=0x0000 check=0x04fa name="CRC-13/BBC"
int test_crc13(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(13, 0x1cf5, 0x0, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x04FA )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=14 poly=0x0805 init=0x0000 refin=true refout=true xorout=0x0000 check=0x082d name="CRC-14/DARC"
int test_crc14(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(14, 0x0805, 0x0, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x082D )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=15 poly=0x4599 init=0x0000 refin=false refout=false xorout=0x0000 check=0x059e name="CRC-15"
int test_crc15(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(15, 0x4599, 0x0, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x059E )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=15 poly=0x6815 init=0x0000 refin=false refout=false xorout=0x0001 check=0x2566 name="CRC-15/MPT1327"
int test_crc15_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(15, 0x6815, 0x0, false, false, 0x1);


    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x2566 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8005  init=0x0000  refin=true  refout=true  xorout=0x0000  check=0xbb3d  name="CRC-16/ARC"
int test_crc16(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x8005, 0x0, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xbb3d )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0x1d0f  refin=false  refout=false  xorout=0x0000  check=0xe5cc  name="CRC-16/AUG-CCITT"
int test_crc16_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x1021, 0x1d0f, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xe5cc )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8005  init=0x0000  refin=false  refout=false  xorout=0x0000  check=0xfee8  name="CRC-16/BUYPASS"
int test_crc16_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x8005, 0x0, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xfee8 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0xffff  refin=false  refout=false  xorout=0x0000  check=0x29b1  name="CRC-16/CCITT-FALSE"
int test_crc16_4(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x1021, 0xffff, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x29b1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0xc867  init=0xffff  refin=false  refout=false  xorout=0x0000  check=0x4c06  name="CRC-16/CDMA2000"
int test_crc16_5(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0xc867, 0xffff, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x4c06 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8005  init=0x800d  refin=false  refout=false  xorout=0x0000  check=0x9ecf  name="CRC-16/DDS-110"
int test_crc16_6(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x8005, 0x800d, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x9ecf )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x0589  init=0x0000  refin=false  refout=false  xorout=0x0001  check=0x007e  name="CRC-16/DECT-R"
int test_crc16_7(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x0589, 0x0, false, false, 0x0001);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x007e )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x0589  init=0x0000  refin=false  refout=false  xorout=0x0000  check=0x007f  name="CRC-16/DECT-X"
int test_crc16_8(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x0589, 0x0, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x007f )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x3d65  init=0x0000  refin=true  refout=true  xorout=0xffff  check=0xea82  name="CRC-16/DNP"
int test_crc16_9(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x3d65, 0x0, true, true, 0xffff);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xea82 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x3d65  init=0x0000  refin=false  refout=false  xorout=0xffff  check=0xc2b7  name="CRC-16/EN-13757"
int test_crc16_10(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x3d65, 0x0, false, false, 0xffff);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xc2b7 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0xffff  refin=false  refout=false  xorout=0xffff  check=0xd64e  name="CRC-16/GENIBUS"
int test_crc16_11(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x1021, 0xffff, false, false, 0xffff);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xd64e )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8005  init=0x0000  refin=true  refout=true  xorout=0xffff  check=0x44c2  name="CRC-16/MAXIM"
int test_crc16_12(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x8005, 0x0, true, true, 0xffff);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x44c2 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0xffff  refin=true  refout=true  xorout=0x0000  check=0x6f91  name="CRC-16/MCRF4XX"
int test_crc16_13(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x1021, 0xffff, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x6f91 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0xb2aa  refin=true  refout=true  xorout=0x0000  check=0x63d0  name="CRC-16/RIELLO"
int test_crc16_14(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x1021, 0xb2aa, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x63d0 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8bb7  init=0x0000  refin=false  refout=false  xorout=0x0000  check=0xd0db  name="CRC-16/T10-DIF"
int test_crc16_15(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x8bb7, 0x0, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xd0db )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0xa097  init=0x0000  refin=false  refout=false  xorout=0x0000  check=0x0fb3  name="CRC-16/TELEDISK"
int test_crc16_16(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0xa097, 0x0, false, false, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x0fb3 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0x89ec  refin=true  refout=true  xorout=0x0000  check=0x26b1  name="CRC-16/TMS37157"
int test_crc16_17(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x1021, 0x89ec, true, true, 0x0);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x26b1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8005  init=0xffff  refin=true  refout=true  xorout=0xffff  check=0xb4c8  name="CRC-16/USB"
int test_crc16_18(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t ucrc(16, 0x8005, 0xffff, true, true, 0xffff);

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xb4c8 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



ptest_func tests[] =
{

    //CRC_t methods
    test_crc_t_name,
    test_crc_t_name_2,

    test_crc_t_get_bits,
    test_crc_t_get_poly,
    test_crc_t_get_init,
    test_crc_t_get_xor_out,
    test_crc_t_get_ref_in,
    test_crc_t_get_ref_out,

    test_crc_t_set_bits,


    //CRC
    test_crc3,

    test_crc4,
    test_crc4_2,

    test_crc5,
    test_crc5_2,
    test_crc5_3,

    test_crc6,
    test_crc6_2,
    test_crc6_3,
    test_crc6_4,

    test_crc7,
    test_crc7_2,

    test_crc8,
    test_crc8_2,
    test_crc8_3,
    test_crc8_4,
    test_crc8_5,
    test_crc8_6,
    test_crc8_7,
    test_crc8_8,
    test_crc8_9,
    test_crc8_10,
    test_crc8_11,

    test_crc10,
    test_crc10_2,

    test_crc11,

    test_crc12,
    test_crc12_2,
    test_crc12_3,

    test_crc13,

    test_crc14,

    test_crc15,
    test_crc15_2,

    test_crc16,
    test_crc16_2,
    test_crc16_3,
    test_crc16_4,
    test_crc16_5,
    test_crc16_6,
    test_crc16_7,
    test_crc16_8,
    test_crc16_9,
    test_crc16_10,
    test_crc16_11,
    test_crc16_12,
    test_crc16_13,
    test_crc16_14,
    test_crc16_15,
    test_crc16_16,
    test_crc16_17,
    test_crc16_18,

};



int main(void)
{

    RUN_TESTS(tests);

    return 0;
}
