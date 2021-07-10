#include "ezzieyguywuf/expected.h"

#include <string>
#include <iostream>

struct A
{
    int x;
};

struct B
{
    std::string s;
};

using EitherAB = nonstd::expected<A, B>;

auto good() -> EitherAB
{
    return EitherAB(A(10));
}

auto goodUsesA(const A&) -> EitherAB
{
    return EitherAB(A(20));
}

auto badUsesA(const A&) -> EitherAB
{
    return EitherAB(B("Dang"));
}

auto bad() -> EitherAB
{
    return EitherAB(B("Whoops"));
}

int main()
{
    using EitherInt = nonstd::expected<int, std::string>;
    EitherInt val(10);

    if(not val.has_value()) return 1;

    val = EitherInt("error");

    if (val.has_value()) return 0;

    EitherAB first  = good();
    EitherAB second = bad();

    if (not first.has_value()) return 1;
    if (second.has_value()) return 1;

    auto ret = good() >= goodUsesA >= badUsesA;

    if (ret.has_value()) return 1;

    return 0;
}
