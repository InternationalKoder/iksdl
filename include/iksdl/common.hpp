/*
 * IKSDL - C++ wrapper for SDL
 * Copyright (C) 2021 InternationalKoder
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#ifndef IKSDL_COMMON_HPP
#define IKSDL_COMMON_HPP

#include <type_traits>
#include <utility>

namespace iksdl
{

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

/////////////////////////////////////////////////
/// \brief Compares two instances of \a std::pair where the first component behaves like a primary key
///
/// The default implementation for the comparison of two instances \c a and \c b of \a std::pair
/// is something like:
/// \code{.cpp}
/// return a.first < b.first || (a.first == b.first && a.second < b.second);
/// \endcode
///
/// However, if we are sure that first element is a primary key,
/// then \c a.first and \c b.first cannot be equal.
/// Therefore, in this case the default implementation may lead
/// to useless comparisons.
///
/// This function can be used to avoid useless computations in
/// the case described above.
///
/// \param p1 First pair to compare
/// \param p2 Second pair to compare
///
/// \return True if the key of \a p1 is lower than the key of \a p2
/////////////////////////////////////////////////
template<typename K, typename V>
inline bool comparePairKeys(const std::pair<K, V>& p1, const std::pair<K, V>& p2)
{
    return p1.first < p2.first;
}

}

#endif // IKSDL_COMMON_HPP
