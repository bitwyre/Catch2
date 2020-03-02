/*
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_CATCH_MATCHERS_CONTAINS_HPP_INCLUDED
#define TWOBLUECUBES_CATCH_MATCHERS_CONTAINS_HPP_INCLUDED

#include <catch2/matchers/catch_matchers_templates.hpp>

#include <algorithm>
#include <functional>
#include <utility>

namespace Catch {
    namespace Matchers {
        template <typename T, typename Equality>
        class ContainsElementMatcher final : public MatcherGenericBase {
            T m_desired;
            Equality m_eq;
        public:
            template <typename T2, typename Equality2>
            ContainsElementMatcher(T2&& target, Equality2&& predicate):
                m_desired(std::forward<T2>(target)),
                m_eq(std::forward<Equality2>(predicate))
            {}

            std::string describe() const override {
                return "contains element " + Catch::Detail::stringify(m_desired);
            }

            template <typename RangeLike>
            bool match(RangeLike&& rng) const {
                using std::begin; using std::end;

                return end(rng) != std::find_if(begin(rng), end(rng),
                                               [&](auto const& elem) {
                                                    return m_eq(elem, m_desired);
                                               });
            }
        };


        /**
         * Creates a matcher that checks whether a range contains a specific element.
         *
         * Uses `std::equal_to` to do the comparison
         */
        template <typename T>
        ContainsElementMatcher<T, std::equal_to<>> Contains(T&& elem) {
            return { std::forward<T>(elem), std::equal_to<>{} };
        }

        /**
         * Creates a matcher that checks whether a range contains a specific element.
         *
         * Uses `eq` to do the comparisons
         */
        template <typename T, typename Equality>
        ContainsElementMatcher<T, Equality> Contains(T&& elem, Equality&& eq) {
            return { std::forward<T>(elem), std::forward<Equality>(eq) };
        }

    }
}

#endif // TWOBLUECUBES_CATCH_MATCHERS_CONTAINS_HPP_INCLUDED
