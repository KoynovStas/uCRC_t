# CRC_t - is C++ class for calculation CRC sizes 1-64 bits


## Description

CRC_t is C++ class for calculation CRC sizes 1-64 bits.


#### Features of the implementation:

 -  The code uses only the standard **C++03 not C++11** -> This allows you to use the class in the oldest projects with older compilers.
 - In the code not uses the library boost.
 - The code has no dependencies, and imprisoned in the one file.
 - For **any** bit-depth (width) of CRC will be use the standard table method for calculation. Will be calculated standart table for byte (table size 256 elements)


Class parameters is the standard Specifications algorithms CRC as described in Ross N. Williams [A PAINLESS GUIDE TO CRC ERROR DETECTION ALGORITHMS.](http://www.ross.net/crc/download/crc_v3.txt)


**Ross N. Williams:**

> By putting all these pieces together we end up with the parameters of the algorithm:
>
>   - **NAME:** This is a name given to the algorithm. A string value.
>
>   - **WIDTH:** This is the width of the algorithm expressed in bits.
>   This is one less than the width of the Poly.
>
>   - **POLY:** This parameter is the poly. This is a binary value that
>   should be specified as a hexadecimal number. The top bit of the
>   poly should be omitted. For example, if the poly is 10110, you
>   should specify 06. An important aspect of this parameter is that it
>   represents the unreflected poly; the bottom bit of this parameter
>   is always the LSB of the divisor during the division regardless of
>   whether the algorithm being modelled is reflected.
>
>   - **INIT:** This parameter specifies the initial value of the register
>   when the algorithm starts. This is the value that is to be assigned
>   to the register in the direct table algorithm. In the table
>   algorithm, we may think of the register always commencing with the
>   value zero, and this value being XORed into the register after the
>   N'th bit iteration. This parameter should be specified as a
>   hexadecimal number.
>
>   - **REFIN:** This is a boolean parameter. If it is FALSE, input bytes are
>   processed with bit 7 being treated as the most significant bit
>   (MSB) and bit 0 being treated as the least significant bit. If this
>   parameter is FALSE, each byte is reflected before being processed.>
>
>   - **REFOUT:** This is a boolean parameter. If it is set to FALSE, the
>   final value in the register is fed into the XOROUT stage directly,
>   otherwise, if this parameter is TRUE, the final register value is
>   reflected first.
>
>   - **XOROUT:** This is an W-bit value that should be specified as a
>   hexadecimal number. It is XORed to the final register value (after
>   the REFOUT) stage before the value is returned as the official
>   checksum.
>
>   - **CHECK:** This field is not strictly part of the definition, and, in
>   the event of an inconsistency between this field and the other
>   field, the other fields take precedence. This field is a check
>   value that can be used as a weak validator of implementations of
>   the algorithm. The field contains the checksum obtained when the
>   ASCII string "123456789" is fed through the specified algorithm
>   (i.e. 313233... (hexadecimal)).




**The class has the following public methods:**
```C++
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
uint64_t get_top_bit() const { return top_bit; }
uint64_t get_crc_mask()const { return crc_mask;}


// set param CRC
int  set_bits(uint8_t new_bits);
void set_poly(uint64_t new_poly)       { poly    = new_poly; init_class();}
void set_init(uint64_t new_init)       { init    = new_init; init_class();}
void set_xor_out(uint64_t new_xor_out) { xor_out = new_xor_out;}
void set_ref_in(bool new_ref_in)       { ref_in  = new_ref_in; init_class();}
void set_ref_out(bool new_ref_out)     { ref_out = new_ref_out;}


// Calculate methods
uint64_t get_crc(const char* buf, size_t len);
int      get_crc(uint64_t *crc, const char *file_name);

// Calculate for chunks of data
uint64_t get_raw_crc(uint64_t crc, const char* buf, size_t len); //for first byte crc = crc_init (must be)
uint64_t get_final_crc(uint64_t raw_crc);
```

More details see: **[crc_t.h](./crc_t.h)**


<br/>
## Usage

**To start working, perform the following steps:**

1. You need to include **[crc_t.h](./crc_t.h)** file in your **.cpp** file.
2. And add file **[crc_t.cpp](./crc_t.cpp)** to list of source files to compile.
3. Set parameters in a class (see an examples).


<br/>
## Examples

**Get CRC-32 for file:**

```C++
uint64_t crc;

CRC_t ucrc(32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF);

int res = ucrc.get_crc(&crc, "standard_check_file"); // res == -1 (error); res == 0 (good)

if( res != -1 )
    //uses crc
```


**Get CRC-32 for single buf:**

```C++
char buf[len_of_buf]; //bla bla

uint32_t crc;

CRC_t ucrc(32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF);

crc = ucrc.get_crc(buf, len_of_buf);
//uses crc
```


**Get CRC-32 for buf(s) (chunks):**

**Note:**
when the method is used uint64_t get_raw_crc(uint64_t crc, const char* buf, size_t len)
for the first byte (or chunk of data) **crc** param must be obtained through a method **get_crc_init()** and in the final you need to call the method: **get_final_crc():**

```C++
char buf[len_of_buf];   //bla bla
char buf2[len_of_buf2]; //bla bla

uint32_t crc;

CRC_t ucrc(32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF);

crc = ucrc.get_crc_init();
crc = ucrc.get_raw_crc(crc, buf,  len_of_buf);   //first chunk
crc = ucrc.get_raw_crc(crc, buf2, len_of_buf2);  //second chunk
crc = get_final_crc(crc);
//uses crc
```

More details can be found in the test application: **[crc_test.cpp](./crc_test.cpp)**


<br/>
## License

[BSD](./LICENSE).
