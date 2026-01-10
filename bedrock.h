#ifndef _BEDROCK_H_
#define _BEDROCK_H_

// ------------------------------------
//  General Definitions and Attributes
// ------------------------------------
#ifndef PACKED_STRUCT
	#define PACKED_STRUCT __attribute__((packed))
#endif // PACKED_STRUCT

#ifndef UNUSED_FUNCTION
	#define UNUSED_FUNCTION __attribute__((unused))
#endif // UNUSED_FUNCTION

#ifndef NAKED_FUNCTION
	#define NAKED_FUNCTION __attribute__((naked))
#endif // NAKED_FUNCTION

#ifndef UNUSED_VAR
	#define UNUSED_VAR(var) ((void) var)
#endif // UNUSED_VAR

#ifdef _BEDROCK_CHECK_UNUSED_
	#define BEDROCK_UNUSED UNUSED_FUNCTION
#else
	#define BEDROCK_UNUSED
#endif //_BEDROCK_CHECK_UNUSED_

#ifdef _BEDROCK_EXTERN_
	#define BEDROCK_FUNCTION BEDROCK_UNUSED extern
#else
	#define BEDROCK_FUNCTION BEDROCK_UNUSED static
#endif //_BEDROCK_EXTERN_

#define BEDROCK_INLINE_FUNCTION BEDROCK_FUNCTION inline

#ifndef _BEDROCK_CUSTOM_ALLOCATORS_
	#define bedrock_calloc  calloc
	#define bedrock_realloc realloc
	#define bedrock_free    free
#else
	#if !defined(bedrock_calloc) || !defined(bedrock_realloc) || !defined(bedrock_free)
		#error "If using custom allocators all bedrock_calloc, bedrock_realloc and bedrock_free must be defined."
		#include <stophere>
	#endif // check definitions
#endif //_BEDROCK_CUSTOM_ALLOCATORS_

/* -------------------------------------------------------------------------------------------------------- */
// ----------------------------------
//  Bedrock Internal Printing Macros
// ----------------------------------
#ifndef COLOR_STR
#	define RED           "\033[31m"
#	define BLUE          "\033[34m"
#	define PURPLE        "\033[35m"
#	define BRIGHT_YELLOW "\033[38;5;214m"    
#	define RESET_COLOR   "\033[0m"
#	define WARNING_COLOR BRIGHT_YELLOW
#	define ERROR_COLOR   RED
#endif // COLOR_STR

#define BEDROCK_COLOR_STR(str, COLOR) COLOR str RESET_COLOR

#ifndef WARNING_LOG
#	define BEDROCK_WARNING_LOG(format, ...)             print(BEDROCK_COLOR_STR("WARNING:" __FILE__ ":%u: ", WARNING_COLOR) format "\n", __LINE__, ##__VA_ARGS__)
#else
#	define BEDROCK_WARNING_LOG WARNING_LOG
#endif // WARNING_LOG

/* -------------------------------------------------------------------------------------------------------- */
// ------------------------
//  Bedrock Miscs Supports
// ------------------------
#ifndef _BEDROCK_USERSPACE_
#	define print printf
#elif defined(_BEDROCK_KERNEL_)
#	define print printk
#endif //_BEDROCK_KERNEL_

#include "./bedrock_miscs.h"

/* -------------------------------------------------------------------------------------------------------- */
// ----------------
//  Bedrock Macros
// ----------------
#define IS_A_HEX_VAL(chr)              (IS_A_NUM(chr) || (IS_LOWER_CASE(chr) && (chr) <= 'f') || (IS_UPPER_CASE(chr) && (chr) <= 'F'))
#define MASK_BITS_INTERVAL(a, b)       (((char) (a) >= (char) (b)) ? (MASK_BITS_PRECEDING(a) & ~MASK_BITS_PRECEDING(b)) : 0)
#define CHR_TO_HEX(chr)                (IS_LOWER_CASE(chr) ? ((chr) - 'a' + 10) : ((chr) - 'A' + 10))
#define BOOL2STR(cond)                 ((cond) ? COLOR_STR("TRUE", GREEN) : COLOR_STR("FALSE", RED))
#define IS_WHITESPACE(chr)             ((chr) == ' ' || (chr) == '\n' || (chr) == '\r' || (chr) == '\t')
#define HEX_TO_CHR_CAP(val)            ((val) > 9 ? (val) + 55 : (val) + '0')
#define HEX_TO_CHR(val)                ((val) > 9 ? (val) + 87 : (val) + '0')
#define IS_A_NUM(chr)                  (((chr) >= '0') && ((chr) <= '9'))
#define IS_LOWER_CASE(chr)             ((chr) >= 'a' && (chr) <= 'z')
#define IS_UPPER_CASE(chr)             ((chr) >= 'A' && (chr) <= 'Z')
#define GET_BIT(val, bit_pos)          (((val) >> (bit_pos)) & 0x01)
#define MASK_BITS_PRECEDING(bit_index) ((1ULL << (bit_index)) - 1)
#define CHR_TO_INT(chr)                ((int)(chr) - 48)
#define BITS_SIZE(val)                 (sizeof(val) * 8)
#define CAST_PTR(ptr, type)            ((type*) (ptr))
#define NUM_TO_CHR(val)                ((val) + '0')
#define CHR_TO_NUM(chr)                ((chr) - '0')
#define TO_BOOL(var)                   (!!(var))

#define TRACK_CALL(__call)                                       \
	printf("Call '%s' at %s:%d\n", #__call, __FILE__, __LINE__); \
	__call

#define SAFE_FREE(ptr) do { if ((ptr) != NULL) { free(ptr); (ptr) = NULL; } } while (0) 
#define MULTI_FREE(...)                                     \
	do {                                                    \
		void* ptrs[] = { NULL, ##__VA_ARGS__ };             \
		for (unsigned int i = 0; i < ARR_SIZE(ptrs); ++i) { \
			SAFE_FREE(ptrs[i]);                             \
		}                                                   \
	} while(0)

#define BE_CONVERT(ptr_val, size) be_to_le(ptr_val, size)
#if defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN || \
    defined(__LITTLE_ENDIAN__) ||                               \
    defined(__ARMEL__) ||                                       \
    defined(__THUMBEL__) ||                                     \
    defined(__AARCH64EL__) ||                                   \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)

	BEDROCK_FUNCTION void be_to_le(void* ptr_val, const u64 size) {
        for (u64 i = 0; i < size / 2; ++i) {
            unsigned char temp = CAST_PTR(ptr_val, u8)[i];
            CAST_PTR(ptr_val, u8)[i] = CAST_PTR(ptr_val, u8)[size - 1 - i];
            CAST_PTR(ptr_val, u8)[size - 1 - i] = temp;
        }
        return;
    }
#else
    #define be_to_le(ptr_val, size)
#endif // CHECK_ENDIANNESS

#ifndef TRUE
	#define TRUE  1
#endif // TRUE

#ifndef FALSE
	#define FALSE 0
#endif // FALSE

#ifndef ABS
	#define ABS(a) ((a) < 0 ? -(a) : (a))
#endif // ABS

#ifndef CLAMP
	#define CLAMP(val, min, max) ((val) > (max) ? (max) : ((val) < (min) ? (min) : (val)))
#endif // CLAMP

#ifndef ARR_SIZE
	#define ARR_SIZE(arr) (sizeof(arr) / sizeof(*(arr)))
#endif // ARR_SIZE

#ifndef MAX
	#define MAX(a, b) ((a) > (b) ? (a) : (b)) 
#endif // MAX

#ifndef MIN
	#define MIN(a, b) ((a) < (b) ? (a) : (b)) 
#endif // MIN

/* -------------------------------------------------------------------------------------------------------- */
// Bedrock Base (General Functions for both Kernel/User Space)
#include "./bedrock_base.h"

#ifdef _BEDROCK_VA_ARGS_
#	include "./bedrock_vargs.h"
#endif //_BEDROCK_VA_ARGS_

#ifndef _BEDROCK_USERSPACE_
#	include "./bedrock_kernel.h"
#endif //_BEDROCK_USERSPACE_

#ifndef _BEDROCK_KERNEL_
#	include "./bedrock_userspace.h"
#endif //_BEDROCK_KERNEL_

#endif //_BEDROCK_H_

