#pragma once
#include "Framework/Core/Log/Log.h"
#include <stdint.h>
#include <string>
#include <vector>
#include <map>

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define ENUM_FLAG_OPERATORS(ENUMTYPE)                                                                    \
    inline ENUMTYPE operator|(ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) | ((int)b)); }          \
    inline ENUMTYPE operator|=(ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) |= ((int)b)); } \
    inline ENUMTYPE operator&(ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) & ((int)b)); }          \
    inline ENUMTYPE operator&=(ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) &= ((int)b)); } \
    inline ENUMTYPE operator~(ENUMTYPE a) { return (ENUMTYPE)(~((int)a)); }                              \
    inline ENUMTYPE operator^(ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) ^ ((int)b)); }          \
    inline ENUMTYPE operator^=(ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) ^= ((int)b)); }

/// \def NO_COPY(typeName)
/// Deletes copy constructors from \typeName class so the class can not be copied.
#define NO_COPY(typeName)                \
    typeName(const typeName &) = delete; \
    typeName &operator=(const typeName &) = delete;

/// \def NO_MOVE(typeName)
/// Deletes move constructors from \typeName class so the class can not be moved.
#define NO_MOVE(typeName)                 \
    typeName(const typeName &&) = delete; \
    typeName &operator=(const typeName &&) = delete;

/// Aligns a size up to the specified amount.
///
/// @param [in] val         The value to align.
/// @param [in] alignment   The alignment to align the value to.
///
/// @returns                The new aligned (if not already aligned) value.
template<typename T> inline T AlignUp(T val, T alignment)
{
    return (val + alignment - (T)1) & ~(alignment - (T)1);
}

/// Computes the rounded-up integer division of two unsigned integers.
///
/// @param [in] a The dividend.
/// @param [in] b The divisor.
///
/// @return The smallest integer greater than or equal to the exact division of a and b.
constexpr uint32_t DivideRoundingUp(uint32_t a, uint32_t b)
{
    return (a + b - 1) / b;
}

inline float CalculateMipBias(float upscalerRatio)
{
    return std::log2f(1.f / upscalerRatio) - 1.f + std::numeric_limits<float>::epsilon();
}

namespace Rosefinch
{
    enum AssertLevel
    {
        ASSERT_WARNING = 0,
        ASSERT_ERROR,
        ASSERT_CRITICAL
    };

    inline void RosefinchAssert(AssertLevel severity, bool condition, const char *format, ...)
    {
        if (!condition)
        {
            char buffer[512];

            va_list args;
            va_start(args, format);
            vsprintf(buffer, format, args);
            va_end(args);

            // Most common
            if (severity == ASSERT_CRITICAL)
            {
                LOG_CRITICAL(buffer);
                throw 1;
            }
            else if (severity == ASSERT_ERROR)
            {
                LOG_ERROR(buffer);
            }
            else
            {
                LOG_WARN(buffer);
            }
        } 
    }
}

