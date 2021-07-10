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
    std::cout << "good" << '\n';
    return EitherAB(A(10));
}

auto goodUsesA(const A&) -> EitherAB
{
    std::cout << "goodUsesA" << '\n';
    return EitherAB(A(20));
}

auto badUsesA(const A&) -> EitherAB
{
    std::cout << "badUsesA" << '\n';
    return EitherAB(B("Dang"));
}

auto bad() -> EitherAB
{
    std::cout << "bad" << '\n';
    return EitherAB(B("Whoops"));
}

int main()
{
    // Demo of c++-style bind operators
    //
    // >>= from haskell will be >= here
    // >>  from haskell will be >  here
    //
    // I couldn't match the operators exactly due to precedence and
    // associativity, which are not definable in c++
    using EitherInt = nonstd::expected<int, std::string>;

    // It should have a value because we made sure it did
    EitherInt val(10);
    if(not val.has_value()) return 1;

    // This one definitely has an error
    val = EitherInt("error");
    if (val.has_value()) return 0;

    //  This should short-circuit on `badUsesA`
    auto ret = good() >= goodUsesA >= badUsesA >= goodUsesA;
    if (ret.has_value()) return 1;

    // This sholud go all the way through - notice we can discard results with
    // operator::>
    ret = good() >= goodUsesA > good;
    if (not ret.has_value()) return 1;

    // Finally, this will short-circuit on `bad`, just like the >= operator
    ret = good() >= goodUsesA > good > good > bad > good > good > good;
    if (ret.has_value()) return 1;

    return 0;
}
