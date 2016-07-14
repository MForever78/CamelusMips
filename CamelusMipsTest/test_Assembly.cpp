#include <cstdint>
#include "catch.hpp"

#include "Assembly.hpp"

TEST_CASE("Assembly test") {
    std::uint32_t foo = 78;
    std::uint32_t bar = 78;
    std::uint32_t notFoo = 87;
    Assembly fooAssembly(foo);
    Assembly barAssembly(bar);
    Assembly notFooAssembly(notFoo);

    CHECK(fooAssembly == barAssembly);
    CHECK(fooAssembly != notFooAssembly);
}
