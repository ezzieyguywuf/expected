This is my attempt at `std::expected`. My main goals were:

1. keep the code readable (don't use too many templates)
2. implement some version of haskell's `>>` operator

While there are obviously some venerable alternative options out there (I've
been using [this one][1] so far and it's great), I haven't found one that hits
on both these points so I thought I'd take a stab at it myself

[1]: https://github.com/TartanLlama/expected

Here is a brief demo - see [the small test program](./test/main.cpp) for a full
working demo

```cpp
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
```
