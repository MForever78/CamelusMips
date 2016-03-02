#include <cstdint>
#include "gtest/gtest.h"

#include "../src/Assembly.hpp"

TEST(AssemblyTest, InitializeTest) {
    std::uint32_t foo = 78;
    std::uint32_t bar = 78;
    std::uint32_t notFoo = 87;
    Assembly fooAssembly(foo);
    Assembly barAssembly(bar);
    Assembly notFooAssembly(notFoo);

    EXPECT_EQ(fooAssembly, barAssembly);
    EXPECT_NE(fooAssembly, notFooAssembly);
}
