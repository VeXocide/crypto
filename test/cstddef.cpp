// Copyright Jeroen Habraken 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <vexocide/cstddef.hpp>

TEST(cstddef, constructor) {
  {
    [[maybe_unused]] vexocide::byte b{23};
  }

  {
    [[maybe_unused]] vexocide::byte b = vexocide::byte{23};
  }
}

TEST(cstddef, operators) {
  {
    vexocide::byte b{23};
    b <<= 2;
    ASSERT_EQ(b, vexocide::byte{92});
  }

  {
    vexocide::byte b{23};
    ASSERT_EQ(b << 2, vexocide::byte{92});
  }

  {
    vexocide::byte b{23};
    b >>= 2;
    ASSERT_EQ(b, vexocide::byte{5});
  }

  {
    vexocide::byte b{23};
    ASSERT_EQ(b >> 2, vexocide::byte{5});
  }

  {
    vexocide::byte b{23};
    b |= vexocide::byte{42};
    ASSERT_EQ(b, vexocide::byte{63});
  }

  {
    vexocide::byte b{23};
    ASSERT_EQ(b | vexocide::byte{42}, vexocide::byte{63});
  }

  {
    vexocide::byte b{23};
    b &= vexocide::byte{42};
    ASSERT_EQ(b, vexocide::byte{2});
  }

  {
    vexocide::byte b{23};
    ASSERT_EQ(b & vexocide::byte{42}, vexocide::byte{2});
  }

  {
    vexocide::byte b{23};
    b ^= vexocide::byte{42};
    ASSERT_EQ(b, vexocide::byte{61});
  }

  {
    vexocide::byte b{23};
    ASSERT_EQ(b ^ vexocide::byte{42}, vexocide::byte{61});
  }

  {
    vexocide::byte b{23};
    ASSERT_EQ(~b, vexocide::byte{232});
  }
}

TEST(cstddef, to_integer) {
  {
    vexocide::byte b{23};
    ASSERT_EQ(vexocide::to_integer<int>(b), 23);
  }
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
