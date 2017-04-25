// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana.hpp>
#include <type_traits>
namespace hana = boost::hana;


#if 0
// sample(how)
template <typename T>
struct type { };

template <typename T>
constexpr type<T*> add_pointer(type<T>)
{ return {}; }

template <typename T, typename U>
constexpr std::false_type operator==(type<T>, type<U>)
{ return {}; }

template <typename T>
constexpr std::true_type operator==(type<T>, type<T>)
{ return {}; }
// end-sample
#endif

// sample(usage)
constexpr auto Int = hana::typeid_(3);
// -> type<int>

constexpr auto IntPtr = hana::traits::add_pointer(Int);
// -> type<int*>

static_assert(IntPtr == hana::type<int*>{});
// end-sample

int main() { }
