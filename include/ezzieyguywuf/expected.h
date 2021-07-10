#ifndef EZZIEY_EXPECTED_HEADER
#define EZZIEY_EXPECTED_HEADER

#include <functional>
#include <variant>

namespace nonstd
{
    template<typename Val, typename Err>
    class expected
    {
        public:
            explicit expected(const Val& v) : data(v){};
            explicit expected(const Err& e) : data(e){};

            auto has_value() const -> bool
            {
                return std::holds_alternative<Val>(data);
            }

            template<typename Val2>
            expected<Val2, Err> operator>>=(std::function<expected<Val2, Err>(const Val&)> f)
            {
                return has_value() ? f(std::get<Val>(data)) : *this;
            }

        private:
            std::variant<Val, Err> data;
    };

} // namespace nonstd
#endif
