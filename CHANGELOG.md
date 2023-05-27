# Change Log


[**uCRC_t**](https://github.com/KoynovStas/uCRC_t) - is C++ class for calculation CRC any sizes 1-64 bits

License: BSD 3-Clause

Copyright (c) 2015, Koynov Stas - skojnov@yandex.ru



---
## [v2.0](https://github.com/KoynovStas/uCRC_t/tree/v2.0) (2023-05-27)
[Full Changelog](https://github.com/KoynovStas/uCRC_t/compare/v1.4...v2.0)


### New
 - New: Since version 2.0 required `C++11`




## [v1.4](https://github.com/KoynovStas/uCRC_t/tree/v1.4) (2023-05-14)
[Full Changelog](https://github.com/KoynovStas/uCRC_t/compare/v1.3...v1.4)


### New
 - Pro: use cmake for build tests
 - add method `get_raw_crc` for first chunk of data


### Refactoring
 - add prefix `static` for `reflect` method
 - rename `get_final_crc` -> `get_end_crc`
 - update `STest` to ver 2.1


### Tests
 - add to CRC list `CRC-64/MS`
 - add to CRC list `CRC-64/REDIS`
 - add to CRC list `CRC-32/MEF`
 - add to CRC list `CRC-24/OS-9`
 - add to CRC list `CRC-21/CAN-FD`
 - add to CRC list `CRC-17/CAN-FD`
 - add to CRC list `CRC-16/M17`
 - add to CRC list `CRC-16/NRSC-5`
 - add to CRC list `CRC-8/HITAG`
 - add to CRC list `CRC-8/BLUETOOTH`
 - add to CRC list `CRC-8/NRSC-5`
 - add to CRC list `CRC-8/LTE`




## [v1.3](https://github.com/KoynovStas/uCRC_t/tree/v1.3) (2017-05-03)
[Full Changelog](https://github.com/KoynovStas/uCRC_t/compare/v1.2...v1.3)


### Added
- add method `get_check` - crc for ASCII string '123456789'


### Refactoring
 - Replacement `(const char *)` to `(const void *)` - for ease use methods: `get_crc` and `get_raw_crc`


### Tests
 - add to CRC list `CRC-64/GO-ISO`
 - add to CRC list `CRC-32/AUTOSAR`
 - add to CRC list `CRC-30/CDMA`
 - add to CRC list `CRC-24/LTE-B`
 - add to CRC list `CRC-24/LTE-A`
 - add to CRC list `CRC-24/INTERLAKEN`
 - add to CRC list `CRC-24/BLE`
 - add to CRC list `CRC-16/PROFIBUS`
 - add to CRC list `CRC-16/OPENSAFETY-B`
 - add to CRC list `CRC-16/OPENSAFETY-A`
 - add to CRC list `CRC-16/LJ1200`
 - add to CRC list `CRC-16/GSM`
 - add to CRC list `CRC-16/CMS`
 - add to CRC list `CRC-14/GSM`
 - add to CRC list `CRC-12/GSM`
 - add to CRC list `CRC-11/UMTS`
 - add to CRC list `CRC-10/GSM`
 - add to CRC list `CRC-8/SAE-J1850`
 - add to CRC list `CRC-8/OPENSAFETY`
 - add to CRC list `CRC-8/GSM-B`
 - add to CRC list `CRC-8/GSM-A`
 - add to CRC list `CRC-8/AUTOSAR`
 - add to CRC list `CRC-7/UMTS`
 - add to CRC list `CRC-6/GSM`
 - add to CRC list `CRC-4/INTERLAKEN`
 - add to CRC list `CRC-3/GSM`




## [v1.2](https://github.com/KoynovStas/uCRC_t/tree/v1.2) (2016-02-02)
[Full Changelog](https://github.com/KoynovStas/uCRC_t/compare/v1.1...v1.2)


### BugFix
 - In `get_crc()` for files must use `crc_init` NOT `init` [(fdcbe8d)](https://github.com/KoynovStas/uCRC_t/commit/fdcbe8dee781e01b6cc950900731c4fa725031bb)


### Tests
 - Add `test_crc_for_cunks`
 - Add `test_crc_no_file` for ALL CRC




## [v1.1](https://github.com/KoynovStas/uCRC_t/tree/v1.1) (2016-01-29)
[Full Changelog](https://github.com/KoynovStas/uCRC_t/compare/v1.0...v1.1)


### BugFix
 - BugFix: for Big Data **SEGFAULT** for `Bits` <= 8 [(ebc8f2c)](https://github.com/KoynovStas/uCRC_t/commit/ebc8f2c76ac4ff9a6e50b02c1203890ee3053c99)




## [v1.0](https://github.com/KoynovStas/uCRC_t/tree/v1.0) (2016-01-25)
