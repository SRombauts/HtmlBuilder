/**
 * @file    Random.cpp
 * @ingroup Utils
 * @brief   Generating random data.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Utils/Random.h"

#include <stdio.h>

#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()
#include <cassert>  // assert()
#include <cstdint>  // uint32_t

namespace Utils {

// Generate an integer between 0 and aMax (<= RAND_MAX).
uint32_t Random::gen(uint32_t aMax) {
    assert(aMax > 0);
    assert(aMax < RAND_MAX);
    return (std::rand() % (aMax + 1));
}

// Generate an integer between aMin and aMax (<= RAND_MAX).
uint32_t Random::gen(uint32_t aMin, uint32_t aMax) {
    assert(aMax > aMin);
    assert((aMax - aMin) < RAND_MAX);
    return (aMin + (std::rand() % ((aMax - aMin) + 1)));
}

// Generate a printable alphanumeric character.
char Random::genChar() {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    return alphanum[Random::gen(static_cast<uint32_t>(sizeof(alphanum) - 1))];
}

// Generate a printable alphanumeric string.
void Random::genString(char* str, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        str[i] = Random::genChar();
    }

    str[len] = '\0';
}

// Initialize the random generator with the current time
Random::Init::Init() {
    std::srand(static_cast<unsigned int>(std::time(0)));
}

/// Static initialization of the random generator, calling Init() before main()
static Random::Init _mInit;


} // namespace Utils
