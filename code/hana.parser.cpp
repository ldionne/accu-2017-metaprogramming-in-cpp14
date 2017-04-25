// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/at.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/remove_if.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
namespace hana = boost::hana;


// sample(parser)
template <typename T>
struct parser {
  T operator()(std::istream& in) const {
    T result;
    in >> result;
    return result;
  }
};

template <typename T>
parser<T> parse() { return {}; }
// end-sample

// sample(literal)
struct void_ { };

struct literal_parser {
  char c;
  void_ operator()(std::istream& in) const {
    in.ignore(1, c);
    return {};
  }
};

literal_parser lit(char c) { return {c}; }
// end-sample

// sample(combine)
template <typename ...Parsers>
auto combine_parsers(Parsers const& ...parsers) {
  return [=](std::istream& in) {
    auto all = hana::make_tuple(parsers(in)...);
    auto result = hana::remove_if(all, [](auto const& result) {
      return hana::typeid_(result) == hana::type<void_>{};
    });
    return result;
  };
}
// end-sample

// sample(usage)
int main() {
  auto parser = combine_parsers(
    lit('(') , parse<int>()          ,
    lit(',') , parse<std::string>()  ,
    lit(',') , parse<double>()       ,
    lit(')')
  );

  std::istringstream text{"(1, foo, 3.3)"};
  hana::tuple<int, std::string, double> data = parser(text);

  assert(data == hana::make_tuple(1, "foo", 3.3));
}
// end-sample
