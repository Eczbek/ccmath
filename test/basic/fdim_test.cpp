/*
 * Copyright (c) 2024-Present Ian Pike
 * Copyright (c) 2024-Present ccmath contributors
 *
 * This library is provided under the MIT License.
 * See LICENSE for more information.
 */

#include <gtest/gtest.h>

#include <ccmath/detail/basic/fdim.hpp>
#include <cmath>
#include <limits>


TEST(CcmathBasicTests, Fdim)
{
	EXPECT_EQ(ccm::fdim(1.0, 1.0), std::fdim(1.0, 1.0));
	EXPECT_EQ(ccm::fdim(1.0, 0.0), std::fdim(1.0, 0.0));
	EXPECT_EQ(ccm::fdim(0.0, 1.0), std::fdim(0.0, 1.0));
	EXPECT_EQ(ccm::fdim(0.0, 0.0), std::fdim(0.0, 0.0));
	EXPECT_EQ(ccm::fdim(-1.0, 1.0), std::fdim(-1.0, 1.0));
	EXPECT_EQ(ccm::fdim(1.0, -1.0), std::fdim(1.0, -1.0));
	EXPECT_EQ(ccm::fdim(-1.0, -1.0), std::fdim(-1.0, -1.0));
	EXPECT_EQ(ccm::fdim(-1.0, 0.0), std::fdim(-1.0, 0.0));

}
