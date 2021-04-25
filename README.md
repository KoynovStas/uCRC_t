# uCRC_t - is C++ class for calculation CRC any sizes 1-64 bits


## Description

`uCRC_t` is universal C++ class for calculation CRC any sizes(width) 1-64 bits.


#### Features of the implementation:

 - The code uses only the standard **C++03** -> This allows you to use the class in the oldest projects with older compilers.
 - The code has no dependencies.
 - You can change the parameters of the algorithm CRC in Run-Time, see `set_xxx` methods.
 - For **any** bit-depth (width) of CRC will be use the standard table method for calculation. Will be calculated standart table for byte (table size 256 elements)


#### Limitations of the implementation:

- This class is universal, but it leads to extra work because the data type is `uint64_t`. This is not optimal.


If you don't need such universality, you can use a more optimized template for your algorithm see:[CRC_t C++ Template](https://github.com/KoynovStas/CRC_t)


Class parameters is the standard Specifications algorithms CRC as described in Ross N. Williams [A PAINLESS GUIDE TO CRC ERROR DETECTION ALGORITHMS](./doc/crc_v3.txt)


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
explicit uCRC_t(const std::string& Name = "CRC-32",
                uint8_t  Bits   = 32,
                uint64_t Poly   = 0x04c11db7,
                uint64_t Init   = 0xffffffff,
                bool     RefIn  = true,
                bool     RefOut = true,
                uint64_t XorOut = 0xffffffff);


explicit uCRC_t(uint8_t  Bits,
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
uint64_t get_check()   const;                    //crc for ASCII string "123456789" (i.e. 313233... (hexadecimal)).


// set param CRC
int  set_bits(uint8_t new_value);
void set_poly(uint64_t new_value)    { poly    = new_value; init_class();}
void set_init(uint64_t new_value)    { init    = new_value; init_class();}
void set_ref_in(bool new_value)      { ref_in  = new_value; init_class();}
void set_ref_out(bool new_value)     { ref_out = new_value;}
void set_xor_out(uint64_t new_value) { xor_out = new_value;}


// Calculate methods
uint64_t get_crc(const void* data, size_t len) const;
int      get_crc(uint64_t &crc, const char* file_name) const;
int      get_crc(uint64_t &crc, const char* file_name, void* buf, size_t size_buf) const;


// Calculate for chunks of data
uint64_t get_raw_crc(const void* data, size_t len, uint64_t crc) const; //for first byte crc = crc_init (must be)
uint64_t get_final_crc(uint64_t raw_crc) const;
```

More details see: **[ucrc_t.h](./ucrc_t.h)**



## Usage

**To start working, perform the following steps:**

1. You need to include **[ucrc_t.h](./ucrc_t.h)** file in your **.cpp** file.
2. And add file **[ucrc_t.cpp](./ucrc_t.cpp)** to list of source files to compile.
3. Set parameters to a class (see an examples).

**Note:**
> The parameters for the class correspond to the `Ross N. Williams` specification. A list of CRC algorithms for this specification can be found here: [Catalogue CRC algorithms](http://reveng.sourceforge.net/crc-catalogue/all.htm)





## Examples

**Get CRC-32 for file:**

```C++
uint64_t crc;

uCRC_t ucrc(32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF);

int res = ucrc.get_crc(crc, "std_file_to_test_crc"); // res == -1 (error); res == 0 (good)

if( res == 0 )
    //uses crc
```


**Note:**
>
>  methods for calculate CRC file
>
>  ```C++
>  int get_crc(uint64_t &crc, const char* file_name) const;
>  ```
>  These method are reentrant. He use a buffer on the stack.
>  The buffer size is 4 Kib (4096 bytes) which is optimal for most   systems.
>  If you have a buffer or needs aligned buffer, you can use the following method:
>
>  ```C++
>  int get_crc(uint64_t &crc, const char* file_name, void* buf, size_t size_buf) const;
>  ```

**Get CRC-32 for single buf:**

```C++
char buf[len_of_buf]; //bla bla

uint32_t crc;

uCRC_t ucrc(32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF);

crc = ucrc.get_crc(buf, len_of_buf);
//uses crc
```


**Get CRC-ModBus for single buf:**

```C++
char buf[len_of_buf]; //bla bla

uint16_t crc;

uCRC_t ucrc(16, 0x8005, 0xffff, true, true, 0x0);

crc = ucrc.get_crc(buf, len_of_buf);
//uses crc
```


**Get CRC-8 for buf(s) (chunks):**

**Note:**
> when the method is used `uint64_t get_raw_crc(const void* data, size_t len, uint64_t crc)`
for the first byte (or chunk of data) **crc** param must be obtained through a method `get_crc_init()` and in the final you need to call the method: `get_final_crc()`:

```C++
char buf[len_of_buf];   //bla bla
char buf2[len_of_buf2]; //bla bla

uint8_t crc;

uCRC_t ucrc(8, 0x7,  0x0, false, false, 0x0);

crc = ucrc.get_crc_init();
crc = ucrc.get_raw_crc(buf,  len_of_buf,  crc);  //first chunk
crc = ucrc.get_raw_crc(buf2, len_of_buf2, crc);  //second chunk
crc = ucrc.get_final_crc(crc);

//uses crc
```

More details can be found in the test application: **[crc_test.cpp](./crc_test.cpp)**



## License

[BSD-3-Clause](./LICENSE).
