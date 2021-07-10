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

            //! throws if `has_value` is `false`
            auto value() const -> Val
            {
                return std::get<Val>(data);
            }

            //! throws if `has_value` is `true`
            auto error() const -> Err
            {
                return std::get<Err>(data);
            }

            auto has_value() const -> bool
            {
                return std::holds_alternative<Val>(data);
            }

            /**
             *  The "monadic bind" operation. In short:
             *
             *  1. if `this` contains an Err, return `this`
             *  2. otherwise, return result of calling the supplied function `f`
             *     with the Val contained in `this` as an arguement
             *
             *  Since it returns another `expected` these can be chained.
             */
            template<typename F>
            auto operator>=(F f) -> std::invoke_result_t<F, Val>
            {
                return has_value() ? f(std::get<Val>(data)) : *this;
            }

            /**
             *  Like `>=` operator, except the function does not take any
             *  arguments. In other words, discard the results from the previous
             *  computation.
             */
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
