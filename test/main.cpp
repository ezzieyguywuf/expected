#include "ezzieyguywuf/expected.h"

#include <string>
#include <iostream>

int main()
{
    using EitherInt = nonstd::expected<int, std::string>;
    EitherInt val(10);

    std::cout << "val.has_value() = " << std::boolalpha
              << val.has_value() << '\n';

    val = EitherInt("error");

    std::cout << "val.has_value() = " << std::boolalpha
              << val.has_value() << '\n';

    return 0;
}
