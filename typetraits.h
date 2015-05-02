#ifndef TYPETRAITS_H
#define TYPETRAITS_H

#include <string>

struct TrueType  { enum {Value = true }; };
struct FalseType { enum {Value = false }; };

template<typename T>
struct IsEnum : FalseType {};

template<typename T>
struct IsSequence : FalseType {};

template<typename T>
struct IsChoice : FalseType {};

template<typename T>
struct IsPrimitive : FalseType {};

template<>
struct IsPrimitive<bool> : TrueType {};

template<>
struct IsPrimitive<char> : TrueType {};

template<>
struct IsPrimitive<signed char> : TrueType {};

template<>
struct IsPrimitive<unsigned char> : TrueType {};

template<>
struct IsPrimitive<unsigned int> : TrueType {};

template<>
struct IsPrimitive<signed short> : TrueType {};

template<>
struct IsPrimitive<unsigned short> : TrueType {};

template<>
struct IsPrimitive<signed int> : TrueType {};

template<>
struct IsPrimitive<unsigned long long> : TrueType {};

template<>
struct IsPrimitive<signed long long> : TrueType {};

template<>
struct IsPrimitive<float> : TrueType {};

template<>
struct IsPrimitive<double> : TrueType {};

template<>
struct IsPrimitive<std::string> : TrueType {};

template<typename T>
struct IsNullable : FalseType {};

template<bool, typename TRUE, typename FALSE>
struct if_ {
    typedef FALSE Value;
};

template<typename TRUE, typename FALSE>
struct if_<true, TRUE, FALSE> {
    typedef TRUE Value;
};

struct category_sequence {};
struct category_choice {};
struct category_enumeration {};
struct category_primitive {};
struct category_nullable {};
struct category_unknown {};

template<typename T>
struct category {
    typedef typename if_<IsSequence<T>::Value,         category_sequence,
                typename if_<IsChoice<T>::Value,       category_choice,
                    typename if_<IsNullable<T>::Value, category_nullable,
                        typename if_<IsEnum<T>::Value, category_enumeration,
                                                       category_primitive>::Value>::Value>::Value>::Value Value;
};

#endif // TYPETRAITS_H
