#pragma once

#include <cstring>
#include "lyostl_base.h"

/* BITSET.H: 
   A custom implementation of std::bitset. */

LYOSTL_BEGIN
template <size_t size, typename storage_type = unsigned char> class bitset {
public:

    /* Constexpr functions */
    static constexpr storage_type SHIFTED_ONE  (size_t pos) { return static_cast<storage_type>(1) << (pos % (sizeof(storage_type) * 8)); }
    static constexpr size_t       STORAGE_INDEX(size_t pos) { return static_cast<size_t>(pos / (sizeof(storage_type) * 8)); }
    
    bitset() : storage{}
    {
        std::memset(storage, 0, sizeof(storage));

        #ifdef LYOSTL_DEBUG
        std::cout << "Bitset bit amount: " << size << '\n';
        std::cout << "Bitset array size: " << sizeof(storage) / sizeof(storage[0]) << " (bits available: " << sizeof(storage) * 8 << ")\n";
        #endif
    }

    void set(size_t pos)
    {
         storage[STORAGE_INDEX(pos)] |= SHIFTED_ONE(pos);
    }

    void reset(size_t pos)
    {
        storage[STORAGE_INDEX(pos)] &= ~SHIFTED_ONE(pos);
    }

    void flip(size_t pos)
    {
        storage[STORAGE_INDEX(pos)] ^= SHIFTED_ONE(pos);
    }

    void clear()
    {
        for (storage_type& unit : storage) unit = 0;
    }

    bool operator[](size_t pos) const
    {
        return static_cast<bool>((storage[STORAGE_INDEX(pos)] >> (pos % (sizeof(storage_type) * 8))) & static_cast<storage_type>(1));
    }

private:
    storage_type storage[CEIL_INT(static_cast<double>(size) / (sizeof(storage_type) * 8))]; // Not exactly eye candy, but it works, so...
};
LYOSTL_END
