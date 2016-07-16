// Copyright Jeroen Habraken 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0298r1.pdf

#ifndef VEXOCIDE_CSTDDEF_HPP
#define VEXOCIDE_CSTDDEF_HPP

#include <type_traits>
#include <utility>

namespace vexocide {

enum class byte : unsigned char {};

template <class IntegerType,
          typename = std::enable_if_t<std::is_integral<IntegerType>::value>>
constexpr byte &operator<<=(byte &b, IntegerType shift) noexcept {
  return b = byte(static_cast<unsigned char>(b) << shift);
}

template <class IntegerType,
          typename = std::enable_if_t<std::is_integral<IntegerType>::value>>
constexpr byte operator<<(byte b, IntegerType shift) noexcept {
  return byte(static_cast<unsigned char>(b) << shift);
}

template <class IntegerType,
          typename = std::enable_if_t<std::is_integral<IntegerType>::value>>
constexpr byte &operator>>=(byte &b, IntegerType shift) noexcept {
  return b = byte(static_cast<unsigned char>(b) >> shift);
}

template <class IntegerType,
          typename = std::enable_if_t<std::is_integral<IntegerType>::value>>
constexpr byte operator>>(byte b, IntegerType shift) noexcept {
  return byte(static_cast<unsigned char>(b) >> shift);
}

constexpr byte &operator|=(byte &l, byte r) noexcept {
  return l = byte(static_cast<unsigned char>(l) |
                  static_cast<unsigned char>(r));
}

constexpr byte operator|(byte l, byte r) noexcept {
  return byte(static_cast<unsigned char>(l) | static_cast<unsigned char>(r));
}

constexpr byte &operator&=(byte &l, byte r) noexcept {
  return l = byte(static_cast<unsigned char>(l) &
                  static_cast<unsigned char>(r));
}

constexpr byte operator&(byte l, byte r) noexcept {
  return byte(static_cast<unsigned char>(l) & static_cast<unsigned char>(r));
}

constexpr byte &operator^=(byte &l, byte r) noexcept {
  return l = byte(static_cast<unsigned char>(l) ^
                  static_cast<unsigned char>(r));
}

constexpr byte operator^(byte l, byte r) noexcept {
  return byte(static_cast<unsigned char>(l) ^ static_cast<unsigned char>(r));
}

constexpr byte operator~(byte b) noexcept {
  return byte(~static_cast<unsigned char>(b));
}

template <class IntegerType,
          typename = std::enable_if_t<std::is_integral<IntegerType>::value>>
constexpr IntegerType to_integer(byte b) noexcept {
  return IntegerType(b);
}

}

#endif
