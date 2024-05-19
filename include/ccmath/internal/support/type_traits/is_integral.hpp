/*
 * Copyright (c) 2024-Present Ian Pike
 * Copyright (c) 2024-Present ccmath contributors
 *
 * This library is provided under the MIT License.
 * See LICENSE for more information.
 */

#pragma once

#include "ccmath/internal/config/type_support.hpp"
#include "ccmath/internal/support/type_traits/is_same.hpp"
#include "ccmath/internal/support/type_traits/remove_cv.hpp"

namespace ccm::support::traits
{
	template <typename T>
	struct is_integral
	{
	private:
		template <typename Head, typename... Args>
		static constexpr bool internal_is_unqualified_any_of()
		{
			return (... || is_same_v<remove_cv_t<Head>, Args>);
		}

	public:
		static constexpr bool value = internal_is_unqualified_any_of<T,
#ifdef CCM_TYPES_HAS_INT128
																	 __int128_t, __uint128_t,
#endif
																	 char, signed char, unsigned char, short, unsigned short, int, unsigned int, long,
																	 unsigned long, long long, unsigned long long, bool>();
	};
	template <typename T>
	constexpr bool is_integral_v = is_integral<T>::value;
} // namespace ccm::support::traits