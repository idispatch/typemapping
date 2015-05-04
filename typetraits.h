#ifndef INCLUDED_TYPETRAITS_H
#define INCLUDED_TYPETRAITS_H

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

struct Category_Sequence {};
struct Category_Choice {};
struct Category_Enumeration {};
struct Category_Primitive {};
struct Category_Nullable {};
struct Category_Unknown {};

template<typename T>
struct category {
    typedef typename if_<IsSequence<T>::Value,         Category_Sequence,
                typename if_<IsChoice<T>::Value,       Category_Choice,
                    typename if_<IsNullable<T>::Value, Category_Nullable,
                        typename if_<IsEnum<T>::Value, Category_Enumeration,
                                                       Category_Primitive>::Value>::Value>::Value>::Value Value;
};

#endif
