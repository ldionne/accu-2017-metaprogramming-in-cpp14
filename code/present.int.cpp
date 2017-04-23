// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#include <cstddef>


// sample(integral_constant)
template <typename T, T v>
struct integral_constant {
  static constexpr T value = v;
  using value_type = T;
  using type = integral_constant;
  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};
// end-sample

namespace classic {
// sample(operator-classic)
template <typename X, typename Y>
using plus = integral_constant<
  decltype(X::value + Y::value),
  X::value + Y::value
>;

using result = plus<integral_constant<int, 3>,
                    integral_constant<int, 4>>;
// end-sample
}

namespace hana_style {
// sample(operator-hana)
template <typename T, T x, T y>
constexpr auto
operator+(integral_constant<T, x>, integral_constant<T, y>)
{ return integral_constant<T, x + y>{}; }

auto result = integral_constant<int, 3>{} + integral_constant<int, 4>{};
// end-sample
}

constexpr int to_int(char c) {
  return static_cast<int>(c) - static_cast<int>('0');
}

template <char ...chars>
constexpr int parse() {
  constexpr char arr[] = {chars...};
  constexpr std::size_t N = sizeof...(chars);

  int base = 10, multiplier = 1, number = 0;
  for (std::size_t i = 0; i < N; ++i) {
    char c = arr[N - i - 1];
    number += to_int(c) * multiplier;
    multiplier *= base;
  }
  return number;
}

// sample(literal-operator)
template <char ...c>
constexpr auto operator"" _c() {
  constexpr int n = parse<c...>();
  return integral_constant<int, n>{};
}

auto n = 10_c + 30_c; // n is integral_constant<int, 40>
// end-sample

int main() { }
