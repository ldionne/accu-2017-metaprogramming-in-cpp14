// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#include <type_traits>


// sample(how)
template <char ...c> struct string { };

template <typename CharT, CharT ...c>
constexpr string<c...> operator"" _s() { return {}; }

template <char ...c1, char ...c2>
constexpr auto operator==(string<c1...>, string<c2...>) {
  return std::is_same<string<c1...>, string<c2...>>{};
}

template <char ...c1, char ...c2>
constexpr auto operator+(string<c1...>, string<c2...>) {
  return string<c1..., c2...>{};
}
// end-sample

// sample(string)
constexpr auto Hello_world = "hello"_s + " world"_s;
static_assert(Hello_world == "hello world"_s);
// end-sample

int main() { }
