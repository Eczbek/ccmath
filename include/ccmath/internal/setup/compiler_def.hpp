/*
 * Copyright (c) 2024-Present Ian Pike
 * Copyright (c) 2024-Present ccmath contributors
 *
 * This library is provided under the MIT License.
 * See LICENSE for more information.
 */

#pragma once

#if defined(__GNUC__) && !defined(CCMATH_COMPILER_GCC)
	#define CCMATH_COMPILER_GCC
    #define CCMATH_COMPILER_GCC_VER ((__GNUC__ * 100) + (__GNUC_MINOR__ * 10) + __GNUC_PATCHLEVEL__)
	#define CCMATH_COMPILER_GCC_VER_MAJOR __GNUC__
    #define CCMATH_COMPILER_GCC_VER_MINOR __GNUC_MINOR__
    #define CCMATH_COMPILER_GCC_VER_PATCH __GNUC_PATCHLEVEL__

	#ifndef CCMATH_FOUND_COMPILER
		#define CCMATH_FOUND_COMPILER
	#endif
#endif

// MSVC
#if defined(_MSC_VER) && !defined(__clang__)
	#define CCMATH_COMPILER_MSVC
    #define CCMATH_COMPILER_MSVC_VER _MSC_VER

	#ifndef CCMATH_FOUND_COMPILER
		#define CCMATH_FOUND_COMPILER
	#endif
#endif

#if defined(_MSC_VER) && defined(__clang__)
	#define CCMATH_COMPILER_CLANG_CL
	#define CCMATH_COMPILER_CLANG_CL_VER ((__clang_major__ * 100) + (__clang_minor__ * 10) + __clang_patchlevel__)
    #define CCMATH_COMPILER_CLANG_CL_VER_MAJOR __clang_major__
    #define CCMATH_COMPILER_CLANG_CL_VER_MINOR __clang_minor__
    #define CCMATH_COMPILER_CLANG_CL_VER_PATCH __clang_patchlevel__

	#ifndef CCMATH_COMPILER_CLANG_BASED
		#define CCMATH_COMPILER_CLANG_BASED
    #endif
	#ifndef CCMATH_FOUND_COMPILER
		#define CCMATH_FOUND_COMPILER
	#endif
#endif

// Clang
#if defined(__clang__)
	#define CCMATH_COMPILER_CLANG
	#define CCMATH_COMPILER_CLANG_VER ((__clang_major__ * 100) + (__clang_minor__ * 10) + __clang_patchlevel__)
	#define CCMATH_COMPILER_CLANG_VER_MAJOR __clang_major__
    #define CCMATH_COMPILER_CLANG_VER_MINOR __clang_minor__
    #define CCMATH_COMPILER_CLANG_VER_PATCH __clang_patchlevel__

	#ifndef CCMATH_COMPILER_CLANG_BASED
        #define CCMATH_COMPILER_CLANG_BASED
    #endif
	#ifndef CCMATH_FOUND_COMPILER
		#define CCMATH_FOUND_COMPILER
	#endif
#endif

// Intel DPC++ Compiler
#if defined(SYCL_LANGUAGE_VERSION) && defined (__INTEL_LLVM_COMPILER)
	#define CCMATH_COMPILER_INTEL
    #define CCMATH_COMPILER_INTEL_VER __INTEL_LLVM_COMPILER
	#define CCMATH_COMPILER_INTEL_YEAR (__INTEL_LLVM_COMPILER / 10000)


	#ifndef CCMATH_COMPILER_CLANG_BASED
		#define CCMATH_COMPILER_CLANG_BASED
    #endif
	#ifndef CCMATH_FOUND_COMPILER
		#define CCMATH_FOUND_COMPILER
	#endif
#endif

// Nvidia HPC SDK
#if defined(__NVCOMPILER) || defined(__NVCOMPILER_LLVM__) && !defined(CCMATH_USING_CLANG_BASED_COMPILER)
	#define CCMATH_COMPILER_NVIDIA
	#define CCMATH_COMPILER_NVIDIA_VER (__NVCOMPILER / 10000)

	#ifndef CCMATH_COMPILER_CLANG_BASED
		#define CCMATH_COMPILER_CLANG_BASED
    #endif
	#ifndef CCMATH_FOUND_COMPILER
		#define CCMATH_FOUND_COMPILER
	#endif
#endif



#if !defined(CCMATH_FOUND_COMPILER)
	#define CCMATH_UNKNOWN_COMPILER
#endif
