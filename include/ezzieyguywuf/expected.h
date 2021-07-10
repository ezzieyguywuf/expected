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

            template<typename F>
            auto operator>=(F f) -> std::invoke_result_t<F, Val>
            {
                return has_value() ? f(std::get<Val>(data)) : *this;
            }

            template<typename F>
            auto operator>(F f) -> std::invoke_result_t<F>
            {
                return has_value() ? f() : *this;
            }

        private:
            std::variant<Val, Err> data;
    };

} // namespace nonstd
#endif
