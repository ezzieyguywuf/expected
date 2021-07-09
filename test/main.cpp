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

int main()
{
    using EitherInt = nonstd::expected<int, std::string>;
    EitherInt val(10);

    if(not val.has_value())
    {
        return 1;
    }

    val = EitherInt("error");

    if (val.has_value())
    {
        return 0;
    }

    return 0;
}
