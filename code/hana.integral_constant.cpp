// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#include <cstddef>


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

// sample(how)
template <typename T, T v>
struct integral_constant {
  static constexpr T value = v;
  constexpr operator T() const noexcept { return value; }
  // etc...
};

template <char ...c>
constexpr auto operator"" _c() {
  constexpr int n = parse<c...>();
  return integral_constant<int, n>{};
}

template <typename T, T x, T y>
constexpr auto operator+(integral_constant<T, x>,
                         integral_constant<T, y>)
{ return integral_constant<T, x + y>{}; }
// end-sample

int main() { }
