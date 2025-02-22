#include <stl/cstdlib/cstdint.h>
#include <stl/cstdlib/cstring.h>
#include <x86_64/checksum.hpp>

namespace firefly::kernel::checksum {
    /**
     * Random numbers for getting a checksum of string
     */
    unsigned int rndnums[256] = {0x568c, 0x54388, 0xd5c9, 0xbfc1, 
                        0x607cf, 0x439c2, 0x74028, 0x249f, 
                        0xd190, 0x10aec, 0x2eff2, 0x1e907, 
                        0x1885a, 0x32484, 0x5f6a7, 0x28b35, 
                        0x22ed5, 0x324b, 0x69584, 0x62d1b, 
                        0x63e7f, 0x7e460, 0x61174, 0x18eb0,
                        0x48365, 0x47d33, 0x3916a, 0x6e6d4,
                        0x7a194, 0x2c3c3, 0x1d6a7, 0x65d60,
                        0x2e0a3, 0x2e12, 0x335db, 0x428f7,
                        0x4f97, 0x4b521, 0x4a09d, 0x5dff3,
                        0x795c7, 0x3c9a7, 0x64b09, 0x56871, 
                        0x780f2, 0x6a1c0, 0x419ab, 0x5d88e, 
                        0x2ca44, 0x303ae, 0x5d7e, 0x9c3f, 
                        0x38566, 0x1d0f9, 0x2cfe6, 0x4ff70, 
                        0x3bf8b, 0x4489b, 0x68756, 0xa496, 
                        0x7ef26, 0x3860f, 0x4a341, 0x7d2f0,
                        0x6b28, 0x70d96, 0x15fca, 0x35a22,
                        0x354d8, 0x1f182, 0x11457, 0x33c51,
                        0x57bd5, 0x7dc81, 0x36274, 0x3ecb7,
                        0x341ea, 0x30949, 0x1c92e, 0x171de,
                        0x213ca, 0x37b5b, 0x5c6a5, 0x18cde,
                        0x2617f, 0x5295b, 0x9a9a, 0x1e702,
                        0xae4, 0x18a5f, 0xb992, 0x31c4b,
                        0x15931, 0x6e006, 0x58cc2, 0x190f8,
                        0xb873, 0x1cf11, 0x156f5, 0x411d3, 
                        0x414ee, 0x692db, 0x1a8cb, 0x1f0b4, 
                        0x3a11d, 0x3af58, 0x4adf9, 0x625c8, 
                        0x71272, 0x7ec7a, 0x3626f, 0x5680f, 
                        0x45ec7, 0x716da, 0x32de8, 0x5ea24, 
                        0x9033, 0x76ddb, 0x49c3c, 0x66dea, 
                        0x7e0f9, 0x6f65d, 0x605aa, 0x65cdb,
                        0x36dcf, 0x42e8e, 0x387dc, 0x1d394,
                        0x39a0b, 0x62d55, 0x51e26, 0x48c54,
                        0x1ec3, 0x6e2d2, 0x7bca1, 0x7b2b0,
                        0x5a31e, 0x2053f, 0x4f6da, 0x7ecc,
                        0x765da, 0x7b2d2, 0x8bbe, 0xdb06, 
                        0x2b293, 0x45a73, 0x21932, 0x6fb19, 
                        0x1c931, 0x7aa01, 0x24640, 0x805a, 
                        0x46b01, 0x770d1, 0xbff9, 0x70d5e, 
                        0x614b8, 0x6e9be, 0x23b00, 0x43fc1, 
                        0x48d7f, 0x2ee45, 0x19c72, 0x65051, 
                        0xfc9d, 0x2f2b6, 0x6431b, 0x56ea7, 
                        0x3bc89, 0x76bf7, 0x402b5, 0x725b9, 
                        0x6d4a8, 0x58481, 0x641bb, 0x1a07b, 
                        0x69aa5, 0x729ea, 0x72d68, 0x5caa6, 
                        0x14b1d, 0x6ae48, 0x42a77, 0x77267, 
                        0x31f8c, 0x5634a, 0x3655f, 0x597ed, 
                        0x6ed2, 0x22e8f, 0x59d36, 0x68618, 
                        0x6bede, 0x7df03, 0x2e7a6, 0x3ffd7, 
                        0x41691, 0x69649, 0x521d8, 0x68b85, 
                        0x7fea1, 0x626f9, 0x37b88, 0x20371, 
                        0x7adb, 0x3e298, 0x4e16a, 0x7e289, 
                        0x24f96, 0x5bccd, 0xc99a, 0x7493, 
                        0x6aa7, 0x19f62, 0x8288, 0x26d00, 
                        0x7496e, 0x2cc65, 0x7377a, 0x6953, 
                        0x465db, 0x2d478, 0x2d831, 0x6691b, 
                        0xae7, 0x286d6, 0x65e2d, 0x3b10a, 
                        0xe723, 0x31222, 0x524bf, 0x3d60f, 
                        0x54b53, 0x5d17c, 0x30285, 0x5d903,
                        0x4b37b, 0x27bc4, 0x76a44, 0x2a0ca, 
                        0x51427, 0x5985f, 0x46d1, 0x18f8d, 
                        0x6c54e, 0x2df83, 0x3e03c, 0x3db34, 
                        0x2c255, 0x2c8ea, 0x70fc2, 0x2b05d, 
                        0x43f55, 0x96ff1, 0x767c, 0x10e1e};

    /**
     * This function uses char * to get checksum
     * 
     * @param string const char *string
     * 
     * @return Checksum of a string (int) 
     */
    unsigned int checksum(const char *string){
        unsigned int string_size = strnlen(string);
        unsigned int string_pointer = 0;

        uint8_t array_pointer = 0;

        unsigned int result = 0;

        while(string_size > string_pointer){
            result += (rndnums[array_pointer++] + ((unsigned int)string[string_pointer++] << string_pointer));
        }

        return result;
    }
}