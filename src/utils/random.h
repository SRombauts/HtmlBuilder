/**
 * @file    random.h
 * @ingroup Utils
 * @brief   Generating random data.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <cstddef>  // size_t

namespace Utils {

/**
 * @brief   Generating random data.
 * @ingroup Utils
 *
 * Getting various type of random data.
 */
class Random {
public:
    /**
     * @brief Generate an integer between 0 and aMax (<= RAND_MAX).
     *
     * @param[in] aMax  Maximum value to generate (using modulo aMax+1)
     *
     * @return A random printable character.
     */
    static unsigned long gen(unsigned long aMax);

    /**
     * @brief Generate an integer between aMin and aMax (<= RAND_MAX).
     *
     * @param[in] aMin  Minimum value to generate
     * @param[in] aMax  Maximum value to generate
     *
     * @return A random printable character.
     */
    static unsigned long gen(unsigned long aMin, unsigned long aMax);

    /**
     * @brief Generate a printable alphanumeric character.
     *
     * @return A random printable character.
     */
    static char genChar();

    /**
     * @brief Generate a printable alphanumeric string.
     *
     * @param[out]  str Buffer for the generated string
     * @param[in]   len Size of the buffer (including the null terminator)
     *
     * @return A random printable string.
     */
    static void genString(char* str, size_t len);

    /**
     * @brief Initializer of the random generator
     */
    class Init {
    public:
        /**
         * @brief Initialize the random generator with the current time
         */
        Init();
    };
};

// static Random::Init _mInit;


} // namespace Utils

