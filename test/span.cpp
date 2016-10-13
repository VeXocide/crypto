// Copyright Jeroen Habraken 2016
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include <vexocide/span.hpp>

#include <array>
#include <string>
#include <vector>

TEST(span, default_constructor) {
  {
    vexocide::span<int> s;
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), nullptr);

    vexocide::span<const int> cs;
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), nullptr);
  }

  {
    vexocide::span<int, 0> s;
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), nullptr);

    vexocide::span<const int, 0> cs;
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), nullptr);
  }

  {
    vexocide::span<int> s{};
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), nullptr);

    vexocide::span<const int> cs{};
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), nullptr);
  }
}

TEST(span, nullptr_constructor) {
  {
    vexocide::span<int> s = nullptr;
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), nullptr);

    vexocide::span<const int> cs = nullptr;
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), nullptr);
  }

  {
    vexocide::span<int, 0> s = nullptr;
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), nullptr);

    vexocide::span<const int, 0> cs = nullptr;
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), nullptr);
  }

  {
    vexocide::span<int> s{nullptr};
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), nullptr);

    vexocide::span<const int> cs{nullptr};
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), nullptr);
  }

  {
    vexocide::span<int *> s{nullptr};
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), nullptr);

    vexocide::span<const int *> cs{nullptr};
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), nullptr);
  }
}

TEST(span, pointer_count_constructor) {
  {
    vexocide::span<int> s{nullptr,
                          static_cast<vexocide::span<int>::index_type>(0)};
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), nullptr);

    vexocide::span<const int> cs{
        nullptr, static_cast<vexocide::span<const int>::index_type>(0)};
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), nullptr);
  }

  {
    vexocide::span<int, 0> s{
        nullptr, static_cast<vexocide::span<int, 0>::index_type>(0)};
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), nullptr);

    vexocide::span<const int, 0> cs{
        nullptr, static_cast<vexocide::span<const int, 0>::index_type>(0)};
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), nullptr);
  }

  {
    vexocide::span<int *> s{nullptr,
                            static_cast<vexocide::span<int *>::index_type>(0)};
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), nullptr);

    vexocide::span<const int *> cs{
        nullptr, static_cast<vexocide::span<const int *>::index_type>(0)};
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), nullptr);
  }

  int a[2] = {1, 2};

  {
    vexocide::span<int> s{&a[0], 2};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), &a[0]);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<const int> cs{&a[0], 2};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), &a[0]);
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }

  {
    vexocide::span<int, 2> s{&a[0], 2};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), &a[0]);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<const int, 2> cs{&a[0], 2};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), &a[0]);
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }
}

TEST(span, pointer_pointer_constructor) {
  {
    vexocide::span<int> s{nullptr, nullptr};
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), nullptr);

    vexocide::span<const int> cs{nullptr, nullptr};
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), nullptr);
  }

  {
    vexocide::span<int, 0> s{nullptr, nullptr};
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), nullptr);

    vexocide::span<const int, 0> cs{nullptr, nullptr};
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), nullptr);
  }

  int a[2] = {1, 2};

  {
    vexocide::span<int> s{&a[0], &a[0]};
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), &a[0]);

    vexocide::span<const int> cs{&a[0], &a[0]};
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), &a[0]);
  }

  {
    vexocide::span<int, 0> s{&a[0], &a[0]};
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.data(), &a[0]);

    vexocide::span<const int, 0> cs{&a[0], &a[0]};
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.data(), &a[0]);
  }

  {
    vexocide::span<int> s{&a[0], &a[2]};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), &a[0]);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<const int> cs{&a[0], &a[2]};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), &a[0]);
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }

  {
    vexocide::span<int, 2> s{&a[0], &a[2]};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), &a[0]);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<const int, 2> cs{&a[0], &a[2]};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), &a[0]);
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }
}

TEST(span, array_constructor) {
  int a[2] = {1, 2};

  {
    vexocide::span<int> s{a};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), &a[0]);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<const int> cs{a};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), &a[0]);
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }

  {
    vexocide::span<int, 2> s{a};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), &a[0]);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<const int, 2> cs{a};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), &a[0]);
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }
}

TEST(span, std_array_constructor) {
  std::array<int, 2> a = {{1, 2}};

  {
    vexocide::span<int> s{a};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), std::addressof(a[0]));
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<const int> cs{a};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), std::addressof(a[0]));
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }

  {
    vexocide::span<int, 2> s{a};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), std::addressof(a[0]));
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<const int, 2> cs{a};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), std::addressof(a[0]));
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }

  const std::array<int, 2> ca = {{1, 2}};

  {
    vexocide::span<const int> cs{ca};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), std::addressof(ca[0]));
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }

  {
    vexocide::span<const int, 2> cs{ca};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), std::addressof(ca[0]));
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }
}

TEST(span, container_constructor) {
  std::vector<int> v = {1, 2};

  {
    vexocide::span<int> s{v};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), std::addressof(v[0]));
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<const int> cs{v};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), std::addressof(v[0]));
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }

  {
    vexocide::span<int, 2> s{v};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), std::addressof(v[0]));
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<const int, 2> cs{v};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), std::addressof(v[0]));
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }

  const std::vector<int> cv = {1, 2};

  {
    vexocide::span<const int> cs{cv};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), std::addressof(cv[0]));
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }

  {
    vexocide::span<const int, 2> cs{cv};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), std::addressof(cv[0]));
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
  }

  std::string t = "ab";

  {
    vexocide::span<char> s{t};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), std::addressof(t[0]));
    ASSERT_EQ(s[0], 'a');
    ASSERT_EQ(s[1], 'b');

    vexocide::span<const char> cs{t};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), std::addressof(t[0]));
    ASSERT_EQ(cs[0], 'a');
    ASSERT_EQ(cs[1], 'b');
  }

  {
    vexocide::span<char, 2> s{t};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), std::addressof(t[0]));
    ASSERT_EQ(s[0], 'a');
    ASSERT_EQ(s[1], 'b');

    vexocide::span<const char, 2> cs{t};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), std::addressof(t[0]));
    ASSERT_EQ(cs[0], 'a');
    ASSERT_EQ(cs[1], 'b');
  }

  const std::string ct = "ab";

  {
    vexocide::span<const char> cs{ct};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), std::addressof(ct[0]));
    ASSERT_EQ(cs[0], 'a');
    ASSERT_EQ(cs[1], 'b');
  }

  {
    vexocide::span<const char, 2> cs{ct};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), std::addressof(ct[0]));
    ASSERT_EQ(cs[0], 'a');
    ASSERT_EQ(cs[1], 'b');
  }
}

TEST(span, span_constructor) {
  int a[2] = {1, 2};

  {
    vexocide::span<int> s{a};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), &a[0]);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<unsigned int> us = s;
    ASSERT_EQ(us.size(), 2);
    ASSERT_EQ(us.data(), reinterpret_cast<const unsigned int *>(&a[0]));
    ASSERT_EQ(us[0], 1u);
    ASSERT_EQ(us[1], 2u);
  }

  {
    vexocide::span<const int> cs{a};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), &a[0]);
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);

    vexocide::span<const unsigned int> cus = cs;
    ASSERT_EQ(cus.size(), 2);
    ASSERT_EQ(cus.data(), reinterpret_cast<const unsigned int *>(&a[0]));
    ASSERT_EQ(cus[0], 1u);
    ASSERT_EQ(cus[1], 2u);
  }

  {
    vexocide::span<int> s{a};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), &a[0]);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<const unsigned int> cus = s;
    ASSERT_EQ(cus.size(), 2);
    ASSERT_EQ(cus.data(), reinterpret_cast<const unsigned int *>(&a[0]));
    ASSERT_EQ(cus[0], 1u);
    ASSERT_EQ(cus[1], 2u);
  }

  {
    vexocide::span<int, 2> s{a};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), &a[0]);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<unsigned int, 2> us = s;
    ASSERT_EQ(us.size(), 2);
    ASSERT_EQ(us.data(), reinterpret_cast<const unsigned int *>(&a[0]));
    ASSERT_EQ(us[0], 1u);
    ASSERT_EQ(us[1], 2u);
  }

  {
    vexocide::span<const int, 2> cs{a};
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.data(), &a[0]);
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);

    vexocide::span<const unsigned int, 2> cus = cs;
    ASSERT_EQ(cus.size(), 2);
    ASSERT_EQ(cus.data(), reinterpret_cast<const unsigned int *>(&a[0]));
    ASSERT_EQ(cus[0], 1u);
    ASSERT_EQ(cus[1], 2u);
  }

  {
    vexocide::span<int, 2> s{a};
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.data(), &a[0]);
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);

    vexocide::span<const unsigned int, 2> cus = s;
    ASSERT_EQ(cus.size(), 2);
    ASSERT_EQ(cus.data(), reinterpret_cast<const unsigned int *>(&a[0]));
    ASSERT_EQ(cus[0], 1u);
    ASSERT_EQ(cus[1], 2u);
  }
}

TEST(span, copy_copy_assignment) {
  int a[2] = {1, 2};

  {
    vexocide::span<int> s{a};
    vexocide::span<int> c{s};
    ASSERT_EQ(s, c);

    vexocide::span<const int> cs{a};
    vexocide::span<const int> cc{cs};
    ASSERT_EQ(cs, cc);
  }

  {
    vexocide::span<int, 2> s{a};
    vexocide::span<int, 2> c{s};
    ASSERT_EQ(s, c);

    vexocide::span<const int, 2> cs{a};
    vexocide::span<const int, 2> cc{cs};
    ASSERT_EQ(cs, cc);
  }

  {
    vexocide::span<int> s{a};
    vexocide::span<int> c = s;
    ASSERT_EQ(s, c);

    vexocide::span<const int> cs{a};
    vexocide::span<const int> cc = cs;
    ASSERT_EQ(cs, cc);
  }

  {
    vexocide::span<int, 2> s{a};
    vexocide::span<int, 2> c = s;
    ASSERT_EQ(s, c);

    vexocide::span<const int, 2> cs{a};
    vexocide::span<const int, 2> cc = cs;
    ASSERT_EQ(cs, cc);
  }
}

TEST(span, first) {
  {
    vexocide::span<int> s;
    vexocide::span<int, 0> f = s.first<0>();
    ASSERT_EQ(f.size(), 0);
    ASSERT_EQ(f.data(), nullptr);

    vexocide::span<const int> cs;
    vexocide::span<const int, 0> cf = cs.first<0>();
    ASSERT_EQ(cf.size(), 0);
    ASSERT_EQ(cf.data(), nullptr);
  }

  {
    vexocide::span<int, 0> s;
    vexocide::span<int, 0> f = s.first<0>();
    ASSERT_EQ(f.size(), 0);
    ASSERT_EQ(f.data(), nullptr);

    vexocide::span<const int, 0> cs;
    vexocide::span<const int, 0> cf = cs.first<0>();
    ASSERT_EQ(cf.size(), 0);
    ASSERT_EQ(cf.data(), nullptr);
  }

  int a[4] = {1, 2, 3, 4};

  {
    vexocide::span<int> s{a};
    vexocide::span<int, 4> f = s.first<4>();
    ASSERT_EQ(f.size(), 4);
    ASSERT_EQ(f.data(), &a[0]);
    ASSERT_EQ(f[0], 1);
    ASSERT_EQ(f[1], 2);
    ASSERT_EQ(f[2], 3);
    ASSERT_EQ(f[3], 4);

    vexocide::span<const int> cs{a};
    vexocide::span<const int, 4> cf = cs.first<4>();
    ASSERT_EQ(cf.size(), 4);
    ASSERT_EQ(cf.data(), &a[0]);
    ASSERT_EQ(cf[0], 1);
    ASSERT_EQ(cf[1], 2);
    ASSERT_EQ(cf[2], 3);
    ASSERT_EQ(cf[3], 4);
  }

  {
    vexocide::span<int, 4> s{a};
    vexocide::span<int, 4> f = s.first<4>();
    ASSERT_EQ(f.size(), 4);
    ASSERT_EQ(f.data(), &a[0]);
    ASSERT_EQ(f[0], 1);
    ASSERT_EQ(f[1], 2);
    ASSERT_EQ(f[2], 3);
    ASSERT_EQ(f[3], 4);

    vexocide::span<const int, 4> cs{a};
    vexocide::span<const int, 4> cf = cs.first<4>();
    ASSERT_EQ(cf.size(), 4);
    ASSERT_EQ(cf.data(), &a[0]);
    ASSERT_EQ(cf[0], 1);
    ASSERT_EQ(cf[1], 2);
    ASSERT_EQ(cf[2], 3);
    ASSERT_EQ(cf[3], 4);
  }

  {
    vexocide::span<int> s{a};
    vexocide::span<int, 2> f = s.first<2>();
    ASSERT_EQ(f.size(), 2);
    ASSERT_EQ(f.data(), &a[0]);
    ASSERT_EQ(f[0], 1);
    ASSERT_EQ(f[1], 2);

    vexocide::span<const int> cs{a};
    vexocide::span<const int, 2> cf = cs.first<2>();
    ASSERT_EQ(cf.size(), 2);
    ASSERT_EQ(cf.data(), &a[0]);
    ASSERT_EQ(cf[0], 1);
    ASSERT_EQ(cf[1], 2);
  }

  {
    vexocide::span<int, 4> s{a};
    vexocide::span<int, 2> f = s.first<2>();
    ASSERT_EQ(f.size(), 2);
    ASSERT_EQ(f.data(), &a[0]);
    ASSERT_EQ(f[0], 1);
    ASSERT_EQ(f[1], 2);

    vexocide::span<const int, 4> cs{a};
    vexocide::span<const int, 2> cf = cs.first<2>();
    ASSERT_EQ(cf.size(), 2);
    ASSERT_EQ(cf.data(), &a[0]);
    ASSERT_EQ(cf[0], 1);
    ASSERT_EQ(cf[1], 2);
  }

  {
    vexocide::span<int> s{a};
    vexocide::span<int, 0> f = s.first<0>();
    ASSERT_EQ(f.size(), 0);
    ASSERT_EQ(f.data(), &a[0]);

    vexocide::span<const int> cs{a};
    vexocide::span<const int, 0> cf = cs.first<0>();
    ASSERT_EQ(cf.size(), 0);
    ASSERT_EQ(cf.data(), &a[0]);
  }

  {
    vexocide::span<int, 4> s{a};
    vexocide::span<int, 0> f = s.first<0>();
    ASSERT_EQ(f.size(), 0);
    ASSERT_EQ(f.data(), &a[0]);

    vexocide::span<const int, 4> cs{a};
    vexocide::span<const int, 0> cf = cs.first<0>();
    ASSERT_EQ(cf.size(), 0);
    ASSERT_EQ(cf.data(), &a[0]);
  }
}

TEST(span, last) {
  {
    vexocide::span<int> s;
    vexocide::span<int, 0> l = s.last<0>();
    ASSERT_EQ(l.size(), 0);
    ASSERT_EQ(l.data(), nullptr);

    vexocide::span<const int> cs;
    vexocide::span<const int, 0> cl = cs.last<0>();
    ASSERT_EQ(cl.size(), 0);
    ASSERT_EQ(cl.data(), nullptr);
  }

  {
    vexocide::span<int, 0> s;
    vexocide::span<int, 0> l = s.last<0>();
    ASSERT_EQ(l.size(), 0);
    ASSERT_EQ(l.data(), nullptr);

    vexocide::span<const int, 0> cs;
    vexocide::span<const int, 0> cl = cs.last<0>();
    ASSERT_EQ(cl.size(), 0);
    ASSERT_EQ(cl.data(), nullptr);
  }

  int a[4] = {1, 2, 3, 4};

  {
    vexocide::span<int> s{a};
    vexocide::span<int, 4> l = s.last<4>();
    ASSERT_EQ(l.size(), 4);
    ASSERT_EQ(l.data(), &a[0]);
    ASSERT_EQ(l[0], 1);
    ASSERT_EQ(l[1], 2);
    ASSERT_EQ(l[2], 3);
    ASSERT_EQ(l[3], 4);

    vexocide::span<const int> cs{a};
    vexocide::span<const int, 4> cl = cs.last<4>();
    ASSERT_EQ(cl.size(), 4);
    ASSERT_EQ(cl.data(), &a[0]);
    ASSERT_EQ(cl[0], 1);
    ASSERT_EQ(cl[1], 2);
    ASSERT_EQ(cl[2], 3);
    ASSERT_EQ(cl[3], 4);
  }

  {
    vexocide::span<int, 4> s{a};
    vexocide::span<int, 4> l = s.last<4>();
    ASSERT_EQ(l.size(), 4);
    ASSERT_EQ(l.data(), &a[0]);
    ASSERT_EQ(l[0], 1);
    ASSERT_EQ(l[1], 2);
    ASSERT_EQ(l[2], 3);
    ASSERT_EQ(l[3], 4);

    vexocide::span<const int, 4> cs{a};
    vexocide::span<const int, 4> cl = cs.last<4>();
    ASSERT_EQ(cl.size(), 4);
    ASSERT_EQ(cl.data(), &a[0]);
    ASSERT_EQ(cl[0], 1);
    ASSERT_EQ(cl[1], 2);
    ASSERT_EQ(cl[2], 3);
    ASSERT_EQ(cl[3], 4);
  }

  {
    vexocide::span<int> s{a};
    vexocide::span<int, 2> l = s.last<2>();
    ASSERT_EQ(l.size(), 2);
    ASSERT_EQ(l.data(), &a[2]);
    ASSERT_EQ(l[0], 3);
    ASSERT_EQ(l[1], 4);

    vexocide::span<const int> cs{a};
    vexocide::span<const int, 2> cl = cs.last<2>();
    ASSERT_EQ(cl.size(), 2);
    ASSERT_EQ(cl.data(), &a[2]);
    ASSERT_EQ(cl[0], 3);
    ASSERT_EQ(cl[1], 4);
  }

  {
    vexocide::span<int, 4> s{a};
    vexocide::span<int, 2> l = s.last<2>();
    ASSERT_EQ(l.size(), 2);
    ASSERT_EQ(l.data(), &a[2]);
    ASSERT_EQ(l[0], 3);
    ASSERT_EQ(l[1], 4);

    vexocide::span<const int, 4> cs{a};
    vexocide::span<const int, 2> cl = cs.last<2>();
    ASSERT_EQ(cl.size(), 2);
    ASSERT_EQ(cl.data(), &a[2]);
    ASSERT_EQ(cl[0], 3);
    ASSERT_EQ(cl[1], 4);
  }

  {
    vexocide::span<int> s{a};
    vexocide::span<int, 0> l = s.last<0>();
    ASSERT_EQ(l.size(), 0);
    ASSERT_EQ(l.data(), &a[4]);

    vexocide::span<const int> cs{a};
    vexocide::span<const int, 0> cl = cs.last<0>();
    ASSERT_EQ(cl.size(), 0);
    ASSERT_EQ(cl.data(), &a[4]);
  }

  {
    vexocide::span<int, 4> s{a};
    vexocide::span<int, 0> l = s.last<0>();
    ASSERT_EQ(l.size(), 0);
    ASSERT_EQ(l.data(), &a[4]);

    vexocide::span<const int, 4> cs{a};
    vexocide::span<const int, 0> cl = cs.last<0>();
    ASSERT_EQ(cl.size(), 0);
    ASSERT_EQ(cl.data(), &a[4]);
  }
}

TEST(span, subspan) {
  {
    vexocide::span<int> s;
    vexocide::span<int, 0> p = s.subspan<0>();
    ASSERT_EQ(p.size(), 0);
    ASSERT_EQ(p.data(), nullptr);

    vexocide::span<const int> cs;
    vexocide::span<const int, 0> cp = cs.subspan<0>();
    ASSERT_EQ(cp.size(), 0);
    ASSERT_EQ(cp.data(), nullptr);
  }

  {
    vexocide::span<int> s;
    vexocide::span<int, 0> p = s.subspan<0, 0>();
    ASSERT_EQ(p.size(), 0);
    ASSERT_EQ(p.data(), nullptr);

    vexocide::span<const int> cs;
    vexocide::span<const int, 0> cp = cs.subspan<0, 0>();
    ASSERT_EQ(cp.size(), 0);
    ASSERT_EQ(cp.data(), nullptr);
  }

  {
    vexocide::span<int> s;
    vexocide::span<int, 0> p = s.subspan(0);
    ASSERT_EQ(p.size(), 0);
    ASSERT_EQ(p.data(), nullptr);

    vexocide::span<const int> cs;
    vexocide::span<const int, 0> cp = cs.subspan(0);
    ASSERT_EQ(cp.size(), 0);
    ASSERT_EQ(cp.data(), nullptr);
  }

  {
    vexocide::span<int> s;
    vexocide::span<int, 0> p = s.subspan(0, 0);
    ASSERT_EQ(p.size(), 0);
    ASSERT_EQ(p.data(), nullptr);

    vexocide::span<const int> cs;
    vexocide::span<const int, 0> cp = cs.subspan(0, 0);
    ASSERT_EQ(cp.size(), 0);
    ASSERT_EQ(cp.data(), nullptr);
  }

  {
    vexocide::span<int, 0> s;
    vexocide::span<int, 0> p = s.subspan<0>();
    ASSERT_EQ(p.size(), 0);
    ASSERT_EQ(p.data(), nullptr);

    vexocide::span<const int, 0> cs;
    vexocide::span<const int, 0> cp = cs.subspan<0>();
    ASSERT_EQ(cp.size(), 0);
    ASSERT_EQ(cp.data(), nullptr);
  }

  {
    vexocide::span<int, 0> s;
    vexocide::span<int, 0> p = s.subspan<0, 0>();
    ASSERT_EQ(p.size(), 0);
    ASSERT_EQ(p.data(), nullptr);

    vexocide::span<const int, 0> cs;
    vexocide::span<const int, 0> cp = cs.subspan<0, 0>();
    ASSERT_EQ(cp.size(), 0);
    ASSERT_EQ(cp.data(), nullptr);
  }

  {
    vexocide::span<int, 0> s;
    vexocide::span<int, 0> p = s.subspan(0);
    ASSERT_EQ(p.size(), 0);
    ASSERT_EQ(p.data(), nullptr);

    vexocide::span<const int, 0> cs;
    vexocide::span<const int, 0> cp = cs.subspan(0);
    ASSERT_EQ(cp.size(), 0);
    ASSERT_EQ(cp.data(), nullptr);
  }

  {
    vexocide::span<int, 0> s;
    vexocide::span<int, 0> p = s.subspan(0, 0);
    ASSERT_EQ(p.size(), 0);
    ASSERT_EQ(p.data(), nullptr);

    vexocide::span<const int, 0> cs;
    vexocide::span<const int, 0> cp = cs.subspan(0, 0);
    ASSERT_EQ(cp.size(), 0);
    ASSERT_EQ(cp.data(), nullptr);
  }

  int a[4] = {1, 2, 3, 4};

  // TODO
}

TEST(span, length_size_length_bytes_size_bytes_empty) {
  {
    vexocide::span<int> s;
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.length_bytes(), 0);
    ASSERT_EQ(s.size_bytes(), 0);
    ASSERT_TRUE(s.empty());

    vexocide::span<const int> cs;
    ASSERT_EQ(cs.length(), 0);
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.length_bytes(), 0);
    ASSERT_EQ(cs.size_bytes(), 0);
    ASSERT_TRUE(cs.empty());
  }

  {
    vexocide::span<int, 0> s;
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.length_bytes(), 0);
    ASSERT_EQ(s.size_bytes(), 0);
    ASSERT_TRUE(s.empty());

    vexocide::span<const int, 0> cs;
    ASSERT_EQ(cs.length(), 0);
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.length_bytes(), 0);
    ASSERT_EQ(cs.size_bytes(), 0);
    ASSERT_TRUE(cs.empty());
  }

  {
    vexocide::span<int> s = nullptr;
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.length_bytes(), 0);
    ASSERT_EQ(s.size_bytes(), 0);
    ASSERT_TRUE(s.empty());

    vexocide::span<const int> cs = nullptr;
    ASSERT_EQ(cs.length(), 0);
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.length_bytes(), 0);
    ASSERT_EQ(cs.size_bytes(), 0);
    ASSERT_TRUE(cs.empty());
  }

  {
    vexocide::span<int, 0> s = nullptr;
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.length_bytes(), 0);
    ASSERT_EQ(s.size_bytes(), 0);
    ASSERT_TRUE(s.empty());

    vexocide::span<const int, 0> cs = nullptr;
    ASSERT_EQ(cs.length(), 0);
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.length_bytes(), 0);
    ASSERT_EQ(cs.size_bytes(), 0);
    ASSERT_TRUE(cs.empty());
  }

  {
    vexocide::span<int> s{nullptr};
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.length_bytes(), 0);
    ASSERT_EQ(s.size_bytes(), 0);
    ASSERT_TRUE(s.empty());

    vexocide::span<const int> cs{nullptr};
    ASSERT_EQ(cs.length(), 0);
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.length_bytes(), 0);
    ASSERT_EQ(cs.size_bytes(), 0);
    ASSERT_TRUE(cs.empty());
  }

  {
    vexocide::span<int, 0> s{nullptr};
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.length_bytes(), 0);
    ASSERT_EQ(s.size_bytes(), 0);
    ASSERT_TRUE(s.empty());

    vexocide::span<const int, 0> cs{nullptr};
    ASSERT_EQ(cs.length(), 0);
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.length_bytes(), 0);
    ASSERT_EQ(cs.size_bytes(), 0);
    ASSERT_TRUE(cs.empty());
  }

  {
    vexocide::span<int> s{nullptr,
                          static_cast<vexocide::span<int>::index_type>(0)};
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.length_bytes(), 0);
    ASSERT_EQ(s.size_bytes(), 0);
    ASSERT_TRUE(s.empty());

    vexocide::span<const int> cs{
        nullptr, static_cast<vexocide::span<const int>::index_type>(0)};
    ASSERT_EQ(cs.length(), 0);
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.length_bytes(), 0);
    ASSERT_EQ(cs.size_bytes(), 0);
    ASSERT_TRUE(cs.empty());
  }

  {
    vexocide::span<int, 0> s{
        nullptr, static_cast<vexocide::span<int, 0>::index_type>(0)};
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.length_bytes(), 0);
    ASSERT_EQ(s.size_bytes(), 0);
    ASSERT_TRUE(s.empty());

    vexocide::span<const int, 0> cs{
        nullptr, static_cast<vexocide::span<const int, 0>::index_type>(0)};
    ASSERT_EQ(cs.length(), 0);
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.length_bytes(), 0);
    ASSERT_EQ(cs.size_bytes(), 0);
    ASSERT_TRUE(cs.empty());
  }

  {
    vexocide::span<int> s{nullptr, nullptr};
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.length_bytes(), 0);
    ASSERT_EQ(s.size_bytes(), 0);
    ASSERT_TRUE(s.empty());

    vexocide::span<const int> cs{nullptr, nullptr};
    ASSERT_EQ(cs.length(), 0);
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.length_bytes(), 0);
    ASSERT_EQ(cs.size_bytes(), 0);
    ASSERT_TRUE(cs.empty());
  }

  {
    vexocide::span<int, 0> s{nullptr, nullptr};
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.length_bytes(), 0);
    ASSERT_EQ(s.size_bytes(), 0);
    ASSERT_TRUE(s.empty());

    vexocide::span<const int, 0> cs{nullptr, nullptr};
    ASSERT_EQ(cs.length(), 0);
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.length_bytes(), 0);
    ASSERT_EQ(cs.size_bytes(), 0);
    ASSERT_TRUE(cs.empty());
  }

  int a[2] = {1, 2};

  {
    vexocide::span<int> s{&a[0], &a[0]};
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.length_bytes(), 0);
    ASSERT_EQ(s.size_bytes(), 0);
    ASSERT_TRUE(s.empty());

    vexocide::span<const int> cs{&a[0], &a[0]};
    ASSERT_EQ(cs.length(), 0);
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.length_bytes(), 0);
    ASSERT_EQ(cs.size_bytes(), 0);
    ASSERT_TRUE(cs.empty());
  }

  {
    vexocide::span<int, 0> s{&a[0], &a[0]};
    ASSERT_EQ(s.length(), 0);
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.length_bytes(), 0);
    ASSERT_EQ(s.size_bytes(), 0);
    ASSERT_TRUE(s.empty());

    vexocide::span<const int, 0> cs{&a[0], &a[0]};
    ASSERT_EQ(cs.length(), 0);
    ASSERT_EQ(cs.size(), 0);
    ASSERT_EQ(cs.length_bytes(), 0);
    ASSERT_EQ(cs.size_bytes(), 0);
    ASSERT_TRUE(cs.empty());
  }

  {
    vexocide::span<int> s{a};
    ASSERT_EQ(s.length(), 2);
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.length_bytes(), static_cast<std::ptrdiff_t>(2 * sizeof(int)));
    ASSERT_EQ(s.size_bytes(), static_cast<std::ptrdiff_t>(2 * sizeof(int)));
    ASSERT_FALSE(s.empty());

    vexocide::span<const int> cs{a};
    ASSERT_EQ(cs.length(), 2);
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.length_bytes(), static_cast<std::ptrdiff_t>(2 * sizeof(int)));
    ASSERT_EQ(cs.size_bytes(), static_cast<std::ptrdiff_t>(2 * sizeof(int)));
    ASSERT_FALSE(cs.empty());
  }

  {
    vexocide::span<int, 2> s{a};
    ASSERT_EQ(s.length(), 2);
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.length_bytes(), static_cast<std::ptrdiff_t>(2 * sizeof(int)));
    ASSERT_EQ(s.size_bytes(), static_cast<std::ptrdiff_t>(2 * sizeof(int)));
    ASSERT_FALSE(s.empty());

    vexocide::span<const int, 2> cs{a};
    ASSERT_EQ(cs.length(), 2);
    ASSERT_EQ(cs.size(), 2);
    ASSERT_EQ(cs.length_bytes(), static_cast<std::ptrdiff_t>(2 * sizeof(int)));
    ASSERT_EQ(cs.size_bytes(), static_cast<std::ptrdiff_t>(2 * sizeof(int)));
    ASSERT_FALSE(cs.empty());
  }
}

TEST(span, array_subscript_operator_function_call_operator) {
  int a[2] = {1, 2};

  {
    vexocide::span<int> s{a};
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);
    ASSERT_EQ(s(0), 1);
    ASSERT_EQ(s(1), 2);

    vexocide::span<const int> cs{a};
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
    ASSERT_EQ(cs(0), 1);
    ASSERT_EQ(cs(1), 2);
  }

  {
    vexocide::span<int, 2> s{a};
    ASSERT_EQ(s[0], 1);
    ASSERT_EQ(s[1], 2);
    ASSERT_EQ(s(0), 1);
    ASSERT_EQ(s(1), 2);

    vexocide::span<const int, 2> cs{a};
    ASSERT_EQ(cs[0], 1);
    ASSERT_EQ(cs[1], 2);
    ASSERT_EQ(cs(0), 1);
    ASSERT_EQ(cs(1), 2);
  }
}

TEST(span, iterator_default_constructor) {
  vexocide::span<int>::iterator il;
  vexocide::span<int>::iterator ir;
  ASSERT_EQ(il, ir);

  vexocide::span<int>::const_iterator cil;
  vexocide::span<int>::const_iterator cir;
  ASSERT_EQ(cil, cir);

  ASSERT_EQ(il, cil);
}

TEST(span, iterator_relational_operators) {
  int a[3] = {1, 2, 3};

  vexocide::span<int> s{a};
  vexocide::span<int>::iterator i = s.begin();
  vexocide::span<int>::iterator j = i + 1;
  vexocide::span<int>::const_iterator ci = s.cbegin();

  ASSERT_EQ(i, i);
  ASSERT_EQ(ci, ci);
  ASSERT_EQ(i, ci);
  ASSERT_EQ(ci, i);
  ASSERT_EQ(i, s.begin());
  ASSERT_EQ(s.begin(), i);
  ASSERT_EQ(ci, s.cbegin());
  ASSERT_EQ(s.cbegin(), ci);
  ASSERT_EQ(i, s.cbegin());
  ASSERT_EQ(s.cbegin(), i);
  ASSERT_EQ(ci, s.begin());
  ASSERT_EQ(s.begin(), ci);

  ASSERT_NE(i, j);
  ASSERT_NE(j, i);
  ASSERT_NE(i, s.end());
  ASSERT_NE(s.end(), i);
  ASSERT_NE(j, s.end());
  ASSERT_NE(s.end(), j);
  ASSERT_NE(j, ci);
  ASSERT_NE(ci, j);

  ASSERT_LT(i, j);
  ASSERT_LE(i, j);
  ASSERT_LT(i, s.end());
  ASSERT_LE(i, s.end());
  ASSERT_LT(j, s.end());
  ASSERT_LE(j, s.end());
  ASSERT_LE(i, ci);
  ASSERT_LE(ci, i);
  ASSERT_LT(ci, j);
  ASSERT_LE(ci, j);
  ASSERT_LT(ci, s.end());
  ASSERT_LE(ci, s.end());

  ASSERT_GT(j, i);
  ASSERT_GE(j, i);
  ASSERT_GT(s.end(), i);
  ASSERT_GE(s.end(), i);
  ASSERT_GT(s.end(), j);
  ASSERT_GE(s.end(), j);
  ASSERT_GE(ci, i);
  ASSERT_GE(i, ci);
  ASSERT_GT(j, ci);
  ASSERT_GE(j, ci);
  ASSERT_GT(s.end(), ci);
  ASSERT_GE(s.end(), ci);
}

TEST(span, begin_end) {
  // TODO
}

TEST(span, cbegin_cend) {
  // TODO
}

TEST(span, rbegin_rend) {
  // TODO
}

TEST(span, crbegin_crend) {
  // TODO
}

TEST(span, relational_operators) {
  {
    vexocide::span<int> sl = nullptr;
    vexocide::span<int> sr = nullptr;

    ASSERT_TRUE(sl == sr);
    ASSERT_FALSE(sl != sr);
    ASSERT_FALSE(sl < sr);
    ASSERT_TRUE(sl <= sr);
    ASSERT_FALSE(sl > sr);
    ASSERT_TRUE(sl >= sr);
    ASSERT_TRUE(sr == sl);
    ASSERT_FALSE(sr != sl);
    ASSERT_FALSE(sr < sl);
    ASSERT_TRUE(sr <= sl);
    ASSERT_FALSE(sr > sl);
    ASSERT_TRUE(sr >= sl);
  }

  {
    int a[2] = {2, 1};

    vexocide::span<int> sl{a};
    vexocide::span<int> sr{a};

    ASSERT_TRUE(sl == sr);
    ASSERT_FALSE(sl != sr);
    ASSERT_FALSE(sl < sr);
    ASSERT_TRUE(sl <= sr);
    ASSERT_FALSE(sl > sr);
    ASSERT_TRUE(sl >= sr);
    ASSERT_TRUE(sr == sl);
    ASSERT_FALSE(sr != sl);
    ASSERT_FALSE(sr < sl);
    ASSERT_TRUE(sr <= sl);
    ASSERT_FALSE(sr > sl);
    ASSERT_TRUE(sr >= sl);
  }

  {
    int a[2] = {2, 1};

    vexocide::span<int> sl = nullptr;
    vexocide::span<int> sr{a};

    ASSERT_TRUE(sl != sr);
    ASSERT_TRUE(sr != sl);
    ASSERT_FALSE(sl == sr);
    ASSERT_FALSE(sr == sl);
    ASSERT_TRUE(sl < sr);
    ASSERT_FALSE(sr < sl);
    ASSERT_TRUE(sl <= sr);
    ASSERT_FALSE(sr <= sl);
    ASSERT_TRUE(sr > sl);
    ASSERT_FALSE(sl > sr);
    ASSERT_TRUE(sr >= sl);
    ASSERT_FALSE(sl >= sr);
  }

  {
    int al[2] = {1, 2};
    int ar[2] = {1, 2};

    vexocide::span<int> sl = al;
    vexocide::span<int> sr = ar;

    ASSERT_TRUE(sl == sr);
    ASSERT_FALSE(sl != sr);
    ASSERT_FALSE(sl < sr);
    ASSERT_TRUE(sl <= sr);
    ASSERT_FALSE(sl > sr);
    ASSERT_TRUE(sl >= sr);
    ASSERT_TRUE(sr == sl);
    ASSERT_FALSE(sr != sl);
    ASSERT_FALSE(sr < sl);
    ASSERT_TRUE(sr <= sl);
    ASSERT_FALSE(sr > sl);
    ASSERT_TRUE(sr >= sl);
  }

  {
    int a[3] = {1, 2, 3};

    vexocide::span<int> sl = {&a[0], 2};
    vexocide::span<int> sr = a;

    ASSERT_TRUE(sl != sr);
    ASSERT_TRUE(sr != sl);
    ASSERT_FALSE(sl == sr);
    ASSERT_FALSE(sr == sl);
    ASSERT_TRUE(sl < sr);
    ASSERT_FALSE(sr < sl);
    ASSERT_TRUE(sl <= sr);
    ASSERT_FALSE(sr <= sl);
    ASSERT_TRUE(sr > sl);
    ASSERT_FALSE(sl > sr);
    ASSERT_TRUE(sr >= sl);
    ASSERT_FALSE(sl >= sr);
  }

  {
    int al[2] = {1, 2};
    int ar[2] = {2, 1};

    vexocide::span<int> sl = al;
    vexocide::span<int> sr = ar;

    ASSERT_TRUE(sl != sr);
    ASSERT_TRUE(sr != sl);
    ASSERT_FALSE(sl == sr);
    ASSERT_FALSE(sr == sl);
    ASSERT_TRUE(sl < sr);
    ASSERT_FALSE(sr < sl);
    ASSERT_TRUE(sl <= sr);
    ASSERT_FALSE(sr <= sl);
    ASSERT_TRUE(sr > sl);
    ASSERT_FALSE(sl > sr);
    ASSERT_TRUE(sr >= sl);
    ASSERT_FALSE(sl >= sr);
  }
}

TEST(span, as_bytes) {
  {
    vexocide::span<int> s;
    vexocide::span<const vexocide::byte> b = vexocide::as_bytes(s);
    ASSERT_EQ(b.size(), 0);
    ASSERT_EQ(b.data(), nullptr);

    vexocide::span<const int> cs;
    vexocide::span<const vexocide::byte> cb = vexocide::as_bytes(cs);
    ASSERT_EQ(cb.size(), 0);
    ASSERT_EQ(cb.data(), nullptr);
  }

  int a[2] = {1, 2};

  {
    vexocide::span<int> s{a};
    vexocide::span<const vexocide::byte> b = vexocide::as_bytes(s);
    ASSERT_EQ(b.size(), s.size_bytes());
    ASSERT_EQ(b.data(), reinterpret_cast<const vexocide::byte *>(s.data()));

    vexocide::span<const int> cs{a};
    vexocide::span<const vexocide::byte> cb = vexocide::as_bytes(cs);
    ASSERT_EQ(cb.size(), s.size_bytes());
    ASSERT_EQ(cb.data(), reinterpret_cast<const vexocide::byte *>(s.data()));
  }

  {
    vexocide::span<int, 2> s{a};
    vexocide::span<const vexocide::byte, static_cast<std::ptrdiff_t>(2 * sizeof(int))> b = vexocide::as_bytes(s);
    ASSERT_EQ(b.size(), s.size_bytes());
    ASSERT_EQ(b.data(), reinterpret_cast<const vexocide::byte *>(s.data()));

    vexocide::span<const int, 2> cs{a};
    vexocide::span<const vexocide::byte, static_cast<std::ptrdiff_t>(2 * sizeof(int))> cb = vexocide::as_bytes(cs);
    ASSERT_EQ(cb.size(), s.size_bytes());
    ASSERT_EQ(cb.data(), reinterpret_cast<const vexocide::byte *>(s.data()));
  }
}

TEST(span, as_writeable_bytes) {
  {
    vexocide::span<int> s;
    vexocide::span<vexocide::byte> b = vexocide::as_writeable_bytes(s);
    ASSERT_EQ(b.size(), 0);
    ASSERT_EQ(b.data(), nullptr);
  }

  int a[2] = {1, 2};

  {
    vexocide::span<int> s{a};
    vexocide::span<vexocide::byte> b = vexocide::as_writeable_bytes(s);
    ASSERT_EQ(b.size(), s.size_bytes());
    ASSERT_EQ(b.data(), reinterpret_cast<vexocide::byte *>(s.data()));
  }

  {
    vexocide::span<int, 2> s{a};
    vexocide::span<vexocide::byte, static_cast<std::ptrdiff_t>(2 * sizeof(int))> b = vexocide::as_writeable_bytes(s);
    ASSERT_EQ(b.size(), s.size_bytes());
    ASSERT_EQ(b.data(), reinterpret_cast<vexocide::byte *>(s.data()));
  }}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
