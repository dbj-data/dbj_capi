#pragma once
// Copyright 1999 - 2021 dbj@dbj.org All rights reserved.
// https://dbj.org/dbj_license

#ifndef DBJ_PUBLIC_C_SYSTEM_MACROS_H_
#define DBJ_PUBLIC_C_SYSTEM_MACROS_H_

#undef DBJ_EXTERN_C_BEGIN
#undef DBJ_EXTERN_C_END

#ifdef __cplusplus                
#define		DBJ_EXTERN_C_BEGIN extern "C" {
#define		DBJ_EXTERN_C_END  }
#else // ! __cplusplus
#define		DBJ_EXTERN_C_BEGIN
#define		DBJ_EXTERN_C_END
#endif // !__cplusplus


#include <stddef.h>
#include <stdint.h>

#if !defined(__cplusplus)
#include <assert.h>    // Defines static_assert() in C11.
#include <stdalign.h>  // Defines alignof() in C11.
#endif

//   DBJ_STATIC_ASSERT(sizeof(struct Foo) == 12, "Foo has invalid size");
#define DBJ_STATIC_ASSERT(expr, msg) static_assert(expr, msg)

// 
#define DBJ_ALIGNOF(type) alignof(type)

// Provides a convenient test for the presence of a field in a user-provided
// structure from a potentially older version of the ABI. Presence is determined
// by comparing the struct's provided |struct_size| value against the known
// offset and size of the field in this version of the ABI. Because fields are
// never reordered or removed, this is a sufficient test for the field's
// presence within whatever version of the ABI the client is programmed against.
// not my macro
#define DBJ_IS_STRUCT_FIELD_PRESENT(struct_pointer, field)    \
  ((size_t)(uintptr_t)((const char*)&(struct_pointer)->field - \
                       (const char*)(struct_pointer)) +        \
       sizeof((struct_pointer)->field) <=                      \
   (struct_pointer)->struct_size)

//   struct DBJ_ALIGNAS(8) Foo { ... };
// alignment| must be an integer!
// Following can't use alignas() in C11 mode because unlike the C++11 the
// C11 code alignment can't be used on struct declarations.
#if defined(__cplusplus)
#define DBJ_ALIGNAS(alignment) alignas(alignment)
#elif defined(__GNUC__)
#define DBJ_ALIGNAS(alignment) __attribute__((aligned(alignment)))
#elif defined(_MSC_VER)
#define DBJ_ALIGNAS(alignment) __declspec(align(alignment))
#else
#error "Please define DBJ_ALIGNAS() for your compiler."
#endif

// https://stackoverflow.com/a/3312896/10870835
/*

ALLWAYS pack the structures on declaration.
For both MSVC and "others" use the bellow as this:

DBJ_PACK_STRUCT(struct myStruct
{
    int a;
    int b;
});

With typedefs:

DBJ_PACK_STRUCT(typedef struct { int x; }) MyStruct;

See the usage in: machine_wide/dbj_sds.h

*/
#undef DBJ_PACK_STRUCT

#if defined(__GNUC__) || defined(__clang__)
#define DBJ_PACK_STRUCT( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#if defined(_MSC_VER) && (! defined(__clang__))
#define DBJ_PACK_STRUCT( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif

#endif  // DBJ_PUBLIC_C_SYSTEM_MACROS_H_