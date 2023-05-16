#define __STDC_FORMAT_MACROS //for MinGW
#include <cinttypes>

#include "stest.h"
#include "ucrc_t.h"





struct CRC_Spec_Info
{
    const char *name;
    uint8_t     bits;
    uint64_t    poly;
    uint64_t    init;
    bool        ref_in;
    bool        ref_out;
    uint64_t    xor_out;
    uint64_t    check;
};




// Catalogue of parametrised CRC algorithms
// more see http://reveng.sourceforge.net/crc-catalogue/
const CRC_Spec_Info  CRC_List[] =
{
    // CRC-3
    { "CRC-3/GSM",  3, 0x3, 0,   false, false, 0x7, 0x4 },
    { "CRC-3/ROHC", 3, 0x3, 0x7, true,  true,  0x0, 0x6 },

    // CRC-4
    { "CRC-4/G-704",      4, 0x3, 0x0, true,  true,  0x0, 0x7 },
    { "CRC-4/INTERLAKEN", 4, 0x3, 0xF, false, false, 0xF, 0xB },

    // CRC-5
    { "CRC-5/EPC-C1G2", 5, 0x09, 0x09, false, false, 0x00, 0x00 },
    { "CRC-5/G-704",    5, 0x15, 0x00, true,  true,  0x00, 0x07 },
    { "CRC-5/USB",      5, 0x05, 0x1F, true,  true,  0x1F, 0x19 },

    // CRC-6
    { "CRC-6/CDMA2000-A", 6, 0x27, 0x3F, false, false, 0x0,  0x0D },
    { "CRC-6/CDMA2000-B", 6, 0x07, 0x3F, false, false, 0x0,  0x3B },
    { "CRC-6/DARC",       6, 0x19, 0x00, true,  true,  0x0,  0x26 },
    { "CRC-6/G-704",      6, 0x03, 0x00, true,  true,  0x0,  0x06 },
    { "CRC-6/GSM",        6, 0x2F, 0x00, false, false, 0x3F, 0x13 },

    // CRC-7
    { "CRC-7/MMC",  7, 0x9,  0x0,  false, false, 0x0, 0x75 },
    { "CRC-7/ROHC", 7, 0x4F, 0x7F, true,  true,  0x0, 0x53 },
    { "CRC-7/UMTS", 7, 0x45, 0x0,  false, false, 0x0, 0x61 },

    // CRC-8
    { "CRC-8/AUTOSAR",    8, 0x2F, 0xFF, false, false, 0xFF, 0xDF },
    { "CRC-8/BLUETOOTH",  8, 0xA7, 0x0,  true,  true,  0x0,  0x26 },
    { "CRC-8/CDMA2000",   8, 0x9B, 0xFF, false, false, 0x0,  0xDA },
    { "CRC-8/DARC",       8, 0x39, 0x0,  true,  true,  0x0,  0x15 },
    { "CRC-8/DVB-S2",     8, 0xD5, 0x0,  false, false, 0x0,  0xBC },
    { "CRC-8/GSM-A",      8, 0x1D, 0x0,  false, false, 0x0,  0x37 },
    { "CRC-8/GSM-B",      8, 0x49, 0x0,  false, false, 0xFF, 0x94 },
    { "CRC-8/HITAG",      8, 0x1D, 0xFF, false, false, 0x0,  0xB4 },
    { "CRC-8/I-432-1",    8, 0x7,  0x0,  false, false, 0x55, 0xA1 },
    { "CRC-8/I-CODE",     8, 0x1D, 0xFD, false, false, 0x0,  0x7E },
    { "CRC-8/LTE",        8, 0x9B, 0x0,  false, false, 0x0,  0xEA },
    { "CRC-8/MAXIM-DOW",  8, 0x31, 0x0,  true,  true,  0x0,  0xA1 },
    { "CRC-8/MIFARE-MAD", 8, 0x1D, 0xC7, false, false, 0x0,  0x99 },
    { "CRC-8/NRSC-5",     8, 0x31, 0xFF, false, false, 0x0,  0xF7 },
    { "CRC-8/OPENSAFETY", 8, 0x2F, 0x0,  false, false, 0x0,  0x3E },
    { "CRC-8/ROHC",       8, 0x7,  0xFF, true,  true,  0x0,  0xD0 },
    { "CRC-8/SAE-J1850",  8, 0x1D, 0xFF, false, false, 0xFF, 0x4B },
    { "CRC-8/SMBUS",      8, 0x7,  0x0,  false, false, 0x0,  0xF4 },
    { "CRC-8/TECH-3250",  8, 0x1D, 0xFF, true,  true,  0x0,  0x97 },
    { "CRC-8/WCDMA",      8, 0x9B, 0x0,  true,  true,  0x0,  0x25 },

    // CRC-10
    { "CRC-10/ATM",      10, 0x233, 0x0,   false, false, 0x0,   0x199 },
    { "CRC-10/CDMA2000", 10, 0x3D9, 0x3FF, false, false, 0x0,   0x233 },
    { "CRC-10/GSM",      10, 0x175, 0x0,   false, false, 0x3FF, 0x12A },

    // CRC-11
    { "CRC-11/FLEXRAY",  11, 0x385, 0x1A, false, false, 0x0, 0x5A3 },
    { "CRC-11/UMTS",     11, 0x307, 0x0,  false, false, 0x0, 0x061 },

    // CRC-12
    { "CRC-12/CDMA2000", 12, 0xF13, 0xFFF, false, false, 0x0,   0xD4D },
    { "CRC-12/DECT",     12, 0x80F, 0x0,   false, false, 0x0,   0xF5B },
    { "CRC-12/GSM",      12, 0xD31, 0x0,   false, false, 0xFFF, 0xB34 },
    { "CRC-12/UMTS",     12, 0x80F, 0x0,   false, true,  0x0,   0xDAF },

    // CRC-13
    { "CRC-13/BBC", 13, 0x1CF5, 0x0, false, false, 0x0, 0x4FA },

    // CRC-14
    { "CRC-14/DARC", 14, 0x805,  0x0, true,  true,  0x0,    0x82D  },
    { "CRC-14/GSM",  14, 0x202D, 0x0, false, false, 0x3FFF, 0x30AE },

    // CRC-15
    { "CRC-15/CAN",     15, 0x4599, 0x0, false, false, 0x0, 0x59E  },
    { "CRC-15/MPT1327", 15, 0x6815, 0x0, false, false, 0x1, 0x2566 },

    // CRC-16
    { "CRC-16/ARC",              16, 0x8005, 0x0,    true,  true,  0x0,    0xBB3D },
    { "CRC-16/CDMA2000",         16, 0xC867, 0xFFFF, false, false, 0x0,    0x4C06 },
    { "CRC-16/CMS",              16, 0x8005, 0xFFFF, false, false, 0x0,    0xAEE7 },
    { "CRC-16/DDS-110",          16, 0x8005, 0x800D, false, false, 0x0,    0x9ECF },
    { "CRC-16/DECT-R",           16, 0x589,  0x0,    false, false, 0x1,    0x7E   },
    { "CRC-16/DECT-X",           16, 0x589,  0x0,    false, false, 0x0,    0x7F   },
    { "CRC-16/DNP",              16, 0x3D65, 0x0,    true,  true,  0xFFFF, 0xEA82 },
    { "CRC-16/EN-13757",         16, 0x3D65, 0x0,    false, false, 0xFFFF, 0xC2B7 },
    { "CRC-16/GENIBUS",          16, 0x1021, 0xFFFF, false, false, 0xFFFF, 0xD64E },
    { "CRC-16/GSM",              16, 0x1021, 0x0,    false, false, 0xFFFF, 0xCE3C },
    { "CRC-16/IBM-3740",         16, 0x1021, 0xFFFF, false, false, 0x0,    0x29B1 },
    { "CRC-16/IBM-SDLC",         16, 0x1021, 0xFFFF, true,  true,  0xFFFF, 0x906E },
    { "CRC-16/ISO-IEC-14443-3-A",16, 0x1021, 0xC6C6, true,  true,  0x0,    0xBF05 },
    { "CRC-16/KERMIT",           16, 0x1021, 0x0,    true,  true,  0x0,    0x2189 },
    { "CRC-16/LJ1200",           16, 0x6F63, 0x0,    false, false, 0x0,    0xBDF4 },
    { "CRC-16//M17",             16, 0x5935, 0xFFFF, false, false, 0x0,    0x772B },
    { "CRC-16/MAXIM-DOW",        16, 0x8005, 0x0,    true,  true,  0xFFFF, 0x44C2 },
    { "CRC-16/MCRF4XX",          16, 0x1021, 0xFFFF, true,  true,  0x0,    0x6F91 },
    { "CRC-16/MODBUS",           16, 0x8005, 0xFFFF, true,  true,  0x0,    0x4B37 },
    { "CRC-16/NRSC-5",           16, 0x080B, 0xFFFF, true,  true,  0x0,    0xA066 },
    { "CRC-16/OPENSAFETY-A",     16, 0x5935, 0x0,    false, false, 0x0,    0x5D38 },
    { "CRC-16/OPENSAFETY-B",     16, 0x755B, 0x0,    false, false, 0x0,    0x20FE },
    { "CRC-16/PROFIBUS",         16, 0x1DCF, 0xFFFF, false, false, 0xFFFF, 0xA819 },
    { "CRC-16/RIELLO",           16, 0x1021, 0xB2AA, true,  true,  0x0,    0x63D0 },
    { "CRC-16/SPI-FUJITSU",      16, 0x1021, 0x1D0F, false, false, 0x0,    0xE5CC },
    { "CRC-16/T10-DIF",          16, 0x8BB7, 0x0,    false, false, 0x0,    0xD0DB },
    { "CRC-16/TELEDISK",         16, 0xA097, 0x0,    false, false, 0x0,    0xFB3  },
    { "CRC-16/TMS37157",         16, 0x1021, 0x89EC, true,  true,  0x0,    0x26B1 },
    { "CRC-16/UMTS",             16, 0x8005, 0x0,    false, false, 0x0,    0xFEE8 },
    { "CRC-16/USB",              16, 0x8005, 0xFFFF, true,  true,  0xFFFF, 0xB4C8 },
    { "CRC-16/XMODEM",           16, 0x1021, 0x0,    false, false, 0x0,    0x31C3 },

    // CRC-17
    { "CRC-17/CAN-FD",     17, 0x1685B, 0x0, false, false, 0x0,  0x4F03 },

    // CRC-21
    { "CRC-21/CAN-FD",     21, 0x102899, 0x0,false, false, 0x0,  0xED841 },

    // CRC-24
    { "CRC-24/BLE",        24, 0x65B,    0x555555, true,  true,  0x0,      0xC25A56 },
    { "CRC-24/FLEXRAY-A",  24, 0x5D6DCB, 0xFEDCBA, false, false, 0x0,      0x7979BD },
    { "CRC-24/FLEXRAY-B",  24, 0x5D6DCB, 0xABCDEF, false, false, 0x0,      0x1F23B8 },
    { "CRC-24/INTERLAKEN", 24, 0x328B63, 0xFFFFFF, false, false, 0xFFFFFF, 0xB4F3E6 },
    { "CRC-24/LTE-A",      24, 0x864CFB, 0x0,      false, false, 0x0,      0xCDE703 },
    { "CRC-24/LTE-B",      24, 0x800063, 0x0,      false, false, 0x0,      0x23EF52 },
    { "CRC-24/OPENPGP",    24, 0x864CFB, 0xB704CE, false, false, 0x0,      0x21CF02 },
    { "CRC-24/OS-9",       24, 0x800063, 0xFFFFFF, false, false, 0xFFFFFF, 0x200FA5 },

    // CRC-30
    { "CRC-30/CDMA", 30, 0x2030B9C7, 0x3FFFFFFF, false, false, 0x3FFFFFFF, 0x4C34ABF },

    // CRC-31
    { "CRC-31/PHILIPS", 31, 0x4C11DB7, 0x7FFFFFFF, false, false, 0x7FFFFFFF, 0xCE9E46C },

    // CRC-32
    { "CRC-32/AIXM",       32, 0x814141AB, 0x0,        false, false, 0x0,        0x3010BF7F },
    { "CRC-32/AUTOSAR",    32, 0xF4ACFB13, 0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0x1697D06A },
    { "CRC-32/BASE91-D",   32, 0xA833982B, 0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0x87315576 },
    { "CRC-32/BZIP2",      32, 0x4C11DB7,  0xFFFFFFFF, false, false, 0xFFFFFFFF, 0xFC891918 },
    { "CRC-32/CD-ROM-EDC", 32, 0x8001801B, 0x0,        true,  true,  0x0,        0x6EC2EDC4 },
    { "CRC-32/CKSUM",      32, 0x4C11DB7,  0x0,        false, false, 0xFFFFFFFF, 0x765E7680 },
    { "CRC-32/ISCSI",      32, 0x1EDC6F41, 0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0xE3069283 },
    { "CRC-32/ISO-HDLC",   32, 0x4C11DB7,  0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0xCBF43926 },
    { "CRC-32/JAMCRC",     32, 0x4C11DB7,  0xFFFFFFFF, true,  true,  0x0,        0x340BC6D9 },
    { "CRC-32/MEF",        32, 0X741B8CD7, 0xFFFFFFFF, true,  true,  0x0,        0xD2C22F51 },
    { "CRC-32/MPEG-2",     32, 0x4C11DB7,  0xFFFFFFFF, false, false, 0x0,        0x376E6E7  },
    { "CRC-32/XFER",       32, 0xAF,       0x0,        false, false, 0x0,        0xBD0BE338 },

    // CRC-40
    { "CRC-40/GSM", 40, 0x4820009, 0x0, false, false, 0xFFFFFFFFFF, 0xD4164FC646 },

    // CRC-64
    { "CRC-64/ECMA-182", 64, 0x42F0E1EBA9EA3693, 0x0,                false, false, 0x0,                0x6C40DF5F0B497347 },
    { "CRC-64/GO-ISO",   64, 0x1B,               0xFFFFFFFFFFFFFFFF, true,  true,  0xFFFFFFFFFFFFFFFF, 0xB90956C775A41001 },
    { "CRC-64/MS",       64, 0x259C84CBA6426349, 0xFFFFFFFFFFFFFFFF, true,  true,  0x0,                0x75D4B74F024ECEEA },
    { "CRC-64/REDIS",    64, 0xAD93D23594C935A9, 0x0,                true,  true,  0x0,                0xE9C6D914C4B8D9CA },
    { "CRC-64/WE",       64, 0x42F0E1EBA9EA3693, 0xFFFFFFFFFFFFFFFF, false, false, 0xFFFFFFFFFFFFFFFF, 0x62EC59E3F1A4F00A },
    { "CRC-64/XZ",       64, 0x42F0E1EBA9EA3693, 0xFFFFFFFFFFFFFFFF, true,  true,  0xFFFFFFFFFFFFFFFF, 0x995DC9BBDF1939FA },

    { 0, 0, 0, 0, 0, 0, 0, 0 } // End Marker
};



const uint8_t std_check_data[] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};



//------------- tests for CRC_t methods -------------


TEST(test_crc_t_name)
{
    uCRC_t  crc;

    TEST_ASSERT( crc.name == "CRC-32" );

    TEST_PASS(nullptr);
}



TEST(test_crc_t_name_2)
{
    const char* name = "some_name";

    uCRC_t crc(name);

    TEST_ASSERT( crc.name == name );

    TEST_PASS(nullptr);
}



TEST(test_crc_t_get_bits)
{
    auto spec = CRC_List;


    while( spec->name )
    {
        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);

        TEST_ASSERT( ucrc.get_bits() == spec->bits);

        spec++;
    }

    TEST_PASS(nullptr);
}



TEST(test_crc_t_get_poly)
{
    auto spec = CRC_List;


    while( spec->name )
    {
        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);

        TEST_ASSERTF(ucrc.get_poly() == spec->poly,
                     "For CRC: %s poly must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     spec->name,
                     spec->poly,
                     ucrc.get_poly());
        spec++;
    }

    TEST_PASS(nullptr);
}



TEST(test_crc_t_get_init)
{
    auto spec = CRC_List;


    while( spec->name )
    {
        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);

        TEST_ASSERTF(ucrc.get_init() == spec->init,
                     "For CRC: %s init must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     spec->name,
                     spec->init,
                     ucrc.get_init());

        spec++;
    }

    TEST_PASS(nullptr);
}



TEST(test_crc_t_get_xor_out)
{
    auto spec = CRC_List;


    while( spec->name )
    {
        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);

        TEST_ASSERTF(ucrc.get_xor_out() == spec->xor_out,
                     "For CRC: %s xor_out must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     spec->name,
                     spec->xor_out,
                     ucrc.get_xor_out());

        spec++;
    }

    TEST_PASS(nullptr);
}



TEST(test_crc_t_get_ref_in)
{
    auto spec = CRC_List;


    while( spec->name )
    {
        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);

        TEST_ASSERT( ucrc.get_ref_in() == spec->ref_in );

        spec++;
    }

    TEST_PASS(nullptr);
}



TEST(test_crc_t_get_ref_out)
{
    auto spec = CRC_List;


    while( spec->name )
    {
        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);

        TEST_ASSERT( ucrc.get_ref_out() == spec->ref_out );

        spec++;
    }

    TEST_PASS(nullptr);
}



TEST(test_crc_t_set_bits)
{
    uCRC_t crc(1, 0, 0, true, true, 0);

    TEST_ASSERT( crc.get_bits()  == 1  );
    TEST_ASSERT( crc.set_bits(0) == -1 );

    // 1..64
    for(int i = 1; i <= 64; ++i)
    {
        TEST_ASSERT( crc.set_bits(i) == 0 );
        TEST_ASSERT( crc.get_bits() == i );
    }


    //more 64
    for(int i = 65; i <= 256; ++i)
    {
        TEST_ASSERT( crc.set_bits(i) == -1 );
    }

    TEST_PASS(nullptr);
}



//------------- tests for Calculate CRC  -------------



// uses parameters constructor by class uCRC_t
TEST(test_crc_std_check_constructor)
{
    uint64_t crc;

    auto spec = CRC_List;


    while( spec->name )
    {
        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);

        crc = ucrc.get_crc(std_check_data, sizeof(std_check_data));

        TEST_ASSERTF(crc == spec->check,
                     "For CRC: %s check must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     spec->name,
                     spec->check,
                     crc);


        TEST_ASSERTF(ucrc.get_check() == spec->check,
                     "For CRC: %s std check must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     spec->name,
                     spec->check,
                     ucrc.get_check());

        spec++;
    }

    TEST_PASS(nullptr);
}



// uses set_xxx methods
TEST(test_crc_std_check_set_xxx)
{
    uint64_t crc;

    auto spec = CRC_List;
    uCRC_t ucrc;


    while( spec->name )
    {
        ucrc.set_bits(spec->bits);
        ucrc.set_poly(spec->poly);
        ucrc.set_init(spec->init);
        ucrc.set_ref_in(spec->ref_in);
        ucrc.set_ref_out(spec->ref_out);
        ucrc.set_xor_out(spec->xor_out);

        crc = ucrc.get_crc(std_check_data, sizeof(std_check_data));
        TEST_ASSERTF(crc == spec->check,
                     "For CRC: %s std check must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     spec->name,
                     spec->check,
                     crc);


        TEST_ASSERTF(ucrc.get_check() == spec->check,
                     "For CRC: %s std check must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     spec->name,
                     spec->check,
                     ucrc.get_check());

        spec++;
    }

    TEST_PASS(nullptr);
}



//------------- tests for Calculate CRC for file -------------



// uses parameters constructor by class uCRC_t
TEST(test_crc_std_check_file)
{
    uint64_t crc;

    auto spec = CRC_List;


    while( spec->name )
    {
        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);

        int res = ucrc.get_crc(crc, "std_file_to_test_crc");

        TEST_ASSERTF((res == 0) && (crc == spec->check),
                     "For CRC: %s std check must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     spec->name,
                     spec->check,
                     crc);

        spec++;
    }

    TEST_PASS(nullptr);
}



TEST(test_crc_no_file)
{
    uint64_t crc;

    auto spec = CRC_List;


    while( spec->name )
    {
        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);

        int res = ucrc.get_crc(crc, "");
        TEST_ASSERTF(res == -1,
                     "For CRC: %s no file but get_crc() ret: %d",
                     spec->name,
                     res);

        spec++;
    }

    TEST_PASS(nullptr);
}



//------------- tests for Calculate CRC for cunks -------------



TEST(test_crc_for_cunks)
{
    uint64_t crc;

    auto spec = CRC_List;


    while( spec->name )
    {
        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);


        crc = ucrc.get_crc_init();
        crc = ucrc.get_raw_crc(&std_check_data[0], 4, crc);
        crc = ucrc.get_raw_crc(&std_check_data[4], 5, crc);
        crc = ucrc.get_end_crc(crc);

        TEST_ASSERTF(crc == spec->check,
                     "For CRC: %s std check must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     spec->name,
                     spec->check,
                     crc);

        spec++;
    }

    TEST_PASS(nullptr);
}



TEST(test_crc_for_cunks2) //test with get_raw_crc for first chunk
{
    uint64_t crc;

    auto spec = CRC_List;


    while( spec->name )
    {
        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);

        crc = ucrc.get_raw_crc(&std_check_data[0], 4);
        crc = ucrc.get_raw_crc(&std_check_data[4], 5, crc);
        crc = ucrc.get_end_crc(crc);

        TEST_ASSERTF(crc == spec->check,
                     "For CRC: %s std check must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     spec->name,
                     spec->check,
                     crc);

        spec++;
    }

    TEST_PASS(nullptr);
}



stest_func tests[] =
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
    test_crc_std_check_constructor,
    test_crc_std_check_set_xxx,


    test_crc_std_check_file,
    test_crc_no_file,

    test_crc_for_cunks,
    test_crc_for_cunks2,
};



MAIN_TESTS(tests)
