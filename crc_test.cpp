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

};



int main(void)
{

    RUN_TESTS(tests);

    return 0;
}
