/******************************************************************************
 *  Copyright (C) 2017 Broadcom. The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 ******************************************************************************/
#pragma once

// EXTERN_C_*
#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif

// ATTRIBUTE_FORMAT
#ifdef __GNUC__
#define ATTRIBUTE_FORMAT(ARCHETYPE, STRING_INDEX, FIRST_TO_CHECK)  __attribute__ ((format (ARCHETYPE, STRING_INDEX, FIRST_TO_CHECK)))
#else
#define ATTRIBUTE_FORMAT(ARCHETYPE, STRING_INDEX, FIRST_TO_CHECK)
#endif

// ATTRIBUTE_UNUSED
#ifdef __GNUC__
#define ATTRIBUTE_UNUSED __attribute__((unused))
#else
#define ATTRIBUTE_UNUSED
#endif

// ATTRIBUTE_NORETURN
#ifdef __GNUC__
#define ATTRIBUTE_NORETURN __attribute__((noreturn))
#elif defined(_MSC_VER)
#define ATTRIBUTE_NORETURN __declspec(noreturn)
#else
#define ATTRIBUTE_NORETURN
#endif

#define unused(x) ((void)(x))

// countof
#if defined(_MSC_VER)
    #include <stdlib.h>
    #define countof _countof
#elif defined(__cplusplus)
   #include <type_traits>
   template<typename Tin>
   constexpr std::size_t countof()
   {
      using T = typename std::remove_reference<Tin>::type;
      static_assert(std::is_array<T>::value, "countof() requires an array argument");
      static_assert(std::extent<T>::value > 0, "zero- or unknown-size array");
      return std::extent<T>::value;
   }
   #define countof(a) countof<decltype(a)>()
#else
   #define countof(x) (sizeof((x)) / sizeof((x)[0]))
#endif

// alignof
#ifdef _MSC_VER
   #define align_of(T) __alignof(T)
#elif defined(__GNUC__)
   #define align_of(T) __alignof__(T)
#else
   #define align_of(T) (sizeof(struct { T t; char ch; }) - sizeof(T))
#endif

// Max alignment reported by alignof() for any type, ie the alignment that malloc() guarantees
#define MAX_ALIGN 8 // Just assume this for now

// ALIGNED
#ifdef _MSC_VER
   #define ALIGNED(X) __declspec(align(X))
#elif defined(__GNUC__)
   #define ALIGNED(X) __attribute__((aligned(X)))
#endif

// inline is a keyword in C99 and C++, although MSVC supports a
// good portion of C99, somehow the inline keyword missed the list
#if defined(_MSC_VER) && !defined(inline) && !defined(__cplusplus)
#define inline __inline
#endif

// constexpr
#if defined(__cplusplus) && defined(_MSC_VER) && (_MSC_VER < 1900)
#define constexpr const
#define _ALLOW_KEYWORD_MACROS
#endif

// noexcept
#if !defined(__cplusplus)
#define noexcept
#elif defined(_MSC_VER) && (_MSC_VER < 1900)
#define noexcept throw()
#endif

// thread_local
#if defined(__cplusplus)
   // Assume C++11, use built-in thread_local
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112l)
#  include <threads.h> // Defines thread_local
#elif defined(__GNUC__)
#  define thread_local __thread
#elif defined(_MSC_VER)
#  define thread_local __declspec(thread)
#endif

#ifdef NDEBUG
#define IS_DEBUG 0
#else
#define IS_DEBUG 1
#endif

#ifdef NDEBUG
#define debug_only(x) do { } while(0)
#else
#define debug_only(x) do { x; } while(0)
#endif

#ifdef _MSC_VER
#define PRIuSIZE "Iu"
#define PRIxSIZE "Ix"
#else
#define PRIuSIZE "zu"
#define PRIxSIZE "zx"
#endif
