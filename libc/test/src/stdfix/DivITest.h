//===-- Utility class to test fxdivi functions ------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "test/UnitTest/Test.h"

#include "src/__support/fixed_point/fx_rep.h"
#include "src/__support/macros/sanitizer.h"

#include "hdr/signal_macros.h"

template <typename XType>
class DivITest : public LIBC_NAMESPACE::testing::Test {
  using FXRep = LIBC_NAMESPACE::fixed_point::FXRep<int>;

public:
  typedef XType (*DivIFunc)(int, int);

  void testBasic(DivIFunc func) {
    auto c1 = func(2, 3);
    auto e1 = 0.666666;
    EXPECT_EQ(static_cast<XType>(c1), static_cast<XType>(e1));

    c1 = func(3, 4);
    e1 = 0.75;
    EXPECT_EQ(static_cast<XType>(c1), static_cast<XType>(e1));

    c1 = func(1043, 2764);
    e1 = 0.37735;
    EXPECT_EQ(static_cast<XType>(c1), static_cast<XType>(e1));

    c1 = func(60000, 720293);
    e1 = 0.083299;
    EXPECT_EQ(static_cast<XType>(c1), static_cast<XType>(e1));

    c1 = func(7, 3);
    e1 = 2.33333;
    EXPECT_EQ(static_cast<XType>(c1), static_cast<XType>(e1));
  }
};

#define LIST_DIVI_TESTS(Name, XType, func)                                     \
  using LlvmLibc##Name##diviTest = DivITest<XType>;                            \
  TEST_F(LlvmLibc##Name##diviTest, Basic) { testBasic(&func); }                \
  static_assert(true, "Require semicolon.")
