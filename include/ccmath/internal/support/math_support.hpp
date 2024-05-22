/*
 * Copyright (c) 2024-Present Ian Pike
 * Copyright (c) 2024-Present ccmath contributors
 *
 * This library is provided under the MIT License.
 * See LICENSE for more information.
 */

#pragma once

#include "ccmath/internal/support/type_traits.hpp"
#include "ccmath/internal/predef/has_builtin.hpp"
#include "ccmath/internal/support/is_constant_evaluated.hpp"

#include <climits>

namespace ccm::support
{
#define RETURN_IF(TYPE, BUILTIN)                                               \
  if constexpr (std::is_same_v<T, TYPE>)                                       \
    return BUILTIN(a, b, carry_in, carry_out);

    // Returns the result of 'a + b' taking into account 'carry_in'.
    // The carry out is stored in 'carry_out' it not 'nullptr', dropped otherwise.
    // We keep the pass by pointer interface for consistency with the intrinsic.
    template <typename T>
    [[nodiscard]] constexpr std::enable_if_t<traits::ccm_is_unsigned_v<T>, T>
    add_with_carry(T a, T b, T carry_in, T& carry_out)
    {
        if constexpr (!is_constant_evaluated())
        {
#if CCM_HAS_BUILTIN(__builtin_addcb)
    RETURN_IF(unsigned char, __builtin_addcb)
#elif CCM_HAS_BUILTIN(__builtin_addcs)
    RETURN_IF(unsigned short, __builtin_addcs)
#elif CCM_HAS_BUILTIN(__builtin_addc)
            RETURN_IF(unsigned int, __builtin_addc)
#elif CCM_HAS_BUILTIN(__builtin_addcl)
    RETURN_IF(unsigned long, __builtin_addcl)
#elif CCM_HAS_BUILTIN(__builtin_addcll)
    RETURN_IF(unsigned long long, __builtin_addcll)
#endif
        }
        T sum = {};
        T carry1 = add_overflow(a, b, sum);
        T carry2 = add_overflow(sum, carry_in, sum);
        carry_out = carry1 | carry2;
        return sum;
    }

    // Returns the result of 'a - b' taking into account 'carry_in'.
    // The carry out is stored in 'carry_out' it not 'nullptr', dropped otherwise.
    // We keep the pass by pointer interface for consistency with the intrinsic.
    template <typename T>
    [[nodiscard]] constexpr std::enable_if_t<traits::ccm_is_unsigned_v<T>, T>
    sub_with_borrow(T a, T b, T carry_in, T& carry_out)
    {
        if constexpr (!is_constant_evaluated())
        {
#if CCM_HAS_BUILTIN(__builtin_subcb)
    RETURN_IF(unsigned char, __builtin_subcb)
#elif CCM_HAS_BUILTIN(__builtin_subcs)
    RETURN_IF(unsigned short, __builtin_subcs)
#elif CCM_HAS_BUILTIN(__builtin_subc)
            RETURN_IF(unsigned int, __builtin_subc)
#elif CCM_HAS_BUILTIN(__builtin_subcl)
    RETURN_IF(unsigned long, __builtin_subcl)
#elif CCM_HAS_BUILTIN(__builtin_subcll)
    RETURN_IF(unsigned long long, __builtin_subcll)
#endif
        }
        T sub = {};
        T carry1 = sub_overflow(a, b, sub);
        T carry2 = sub_overflow(sub, carry_in, sub);
        carry_out = carry1 | carry2;
        return sub;
    }

#undef RETURN_IF
	// Create a bitmask with the count right-most bits set to 1, and all other bits
	// set to 0.  Only unsigned types are allowed.
	template <typename T, std::size_t count>
	static constexpr std::enable_if_t<traits::ccm_is_unsigned_v<T>, T> mask_trailing_ones()
	{
		constexpr unsigned T_BITS = CHAR_BIT * sizeof(T);
		static_assert(count <= T_BITS && "Invalid bit index");
		return count == 0 ? 0 : (T(-1) >> (T_BITS - count));
	}

	// Create a bitmask with the count left-most bits set to 1, and all other bits
	// set to 0.  Only unsigned types are allowed.
	template <typename T, std::size_t count>
	static constexpr std::enable_if_t<traits::ccm_is_unsigned_v<T>, T> mask_leading_ones()
	{
		return T(~mask_trailing_ones<T, CHAR_BIT * sizeof(T) - count>());
	}

	// Create a bitmask with the count right-most bits set to 0, and all other bits
	// set to 1.  Only unsigned types are allowed.
	template <typename T, std::size_t count>
	static constexpr std::enable_if_t<traits::ccm_is_unsigned_v<T>, T> mask_trailing_zeros()
	{
		return mask_leading_ones<T, CHAR_BIT * sizeof(T) - count>();
	}

	// Create a bitmask with the count left-most bits set to 0, and all other bits
	// set to 1.  Only unsigned types are allowed.
	template <typename T, std::size_t count>
	static constexpr std::enable_if_t<traits::ccm_is_unsigned_v<T>, T> mask_leading_zeros()
	{
		return mask_trailing_ones<T, CHAR_BIT * sizeof(T) - count>();
	}

} // namespace ccm::support