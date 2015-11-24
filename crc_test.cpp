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


};



int main(void)
{

    RUN_TESTS(tests);

    return 0;
}
