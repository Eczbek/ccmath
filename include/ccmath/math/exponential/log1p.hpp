/*
* Copyright (c) 2024-Present Ian Pike
 * Copyright (c) 2024-Present ccmath contributors
 *
 * This library is provided under the MIT License.
 * See LICENSE for more information.
 */

#pragma once

#include <type_traits>

namespace ccm
{
	template <typename T, std::enable_if_t<!std::is_integral_v<T>, bool> = true>
	constexpr T log1p(T num)
	{
		#if defined(__GNUC__) && (__GNUC__ > 6 || (__GNUC__ == 6 && __GNUC_MINOR__ >= 1)) && !defined(__clang__)
		if constexpr (std::is_same_v<T, float>) { return __builtin_log1p(num); }
		else if constexpr (std::is_same_v<T, double>) { return __builtin_log1p(num); }
		else if constexpr (std::is_same_v<T, long double>) { return __builtin_log1p(num); }
		else { return __builtin_log1p(num); }
		#else
		if constexpr (std::is_same_v<T, float>) { return 0; }
		else if constexpr (std::is_same_v<T, double>) { return 0; }
		else if constexpr (std::is_same_v<T, long double>) { return 0; }
		else { return 0; }
		#endif
	}

	template <typename Integer, std::enable_if_t<std::is_integral_v<Integer>, bool> = true>
	constexpr double log1p(Integer num)
	{
		return exp2<double>(static_cast<double>(num));
	}

	constexpr float log1pf(float num)
	{
		return ccm::exp2<float>(num);
	}

	constexpr long double log1pl(double num)
	{
		return ccm::exp2<double>(num);
	}
} // namespace ccm
