#ifndef _BEDROCK_MISCS_H_
#define _BEDROCK_MISCS_H_

/* -------------------------------------------------------------------------------------------------------- */
// ----------------------
//  Special Type Support
// ----------------------
#ifdef _BEDROCK_SPECIAL_TYPE_SUPPORT_
#define STATIC_ASSERT _Static_assert

typedef unsigned char bool;

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

STATIC_ASSERT(sizeof(u8)  == 1, "u8  must be 1 byte");
STATIC_ASSERT(sizeof(u16) == 2, "u16 must be 2 bytes");
STATIC_ASSERT(sizeof(u32) == 4, "u32 must be 4 bytes");
STATIC_ASSERT(sizeof(u64) == 8, "u64 must be 8 bytes");

typedef char      s8;
typedef short     s16;
typedef int       s32;
typedef long long s64;

STATIC_ASSERT(sizeof(s8)  == 1, "s8  must be 1 byte");
STATIC_ASSERT(sizeof(s16) == 2, "s16 must be 2 bytes");
STATIC_ASSERT(sizeof(s32) == 4, "s32 must be 4 bytes");
STATIC_ASSERT(sizeof(s64) == 8, "s64 must be 8 bytes");

#ifdef __SIZEOF_INT128__
	__extension__ typedef unsigned __int128 u128;
	__extension__ typedef          __int128 s128;

	STATIC_ASSERT(sizeof(u128) == 16, "u128 must be 16 bytes");
	STATIC_ASSERT(sizeof(s128) == 16, "s128 must be 16 bytes");
#endif //__SIZEOF_INT128__

#endif //_BEDROCK_SPECIAL_TYPE_SUPPORT_

/* -------------------------------------------------------------------------------------------------------- */
// -----------------
//  Printing Macros
// -----------------
#ifdef _BEDROCK_PRINTING_UTILS_
#define RED           "\033[31m"
#define GREEN         "\033[32m"
#define BLUE          "\033[34m"
#define PURPLE        "\033[35m"
#define CYAN          "\033[36m"
#define BRIGHT_YELLOW "\033[38;5;214m"    
#define RESET_COLOR   "\033[0m"

#define WARNING_COLOR BRIGHT_YELLOW
#define ERROR_COLOR   RED
#define DEBUG_COLOR   PURPLE
#define TODO_COLOR    CYAN
#define INFO_COLOR    BLUE

#define COLOR_STR(str, COLOR) COLOR str RESET_COLOR

#define ERROR_LOG(format, error_str, ...)    print(COLOR_STR("ERROR:%s:" __FILE__ ":%u: ", ERROR_COLOR) format "\n", error_str, __LINE__, ##__VA_ARGS__)
#define WARNING_LOG(format, ...)             print(COLOR_STR("WARNING:" __FILE__ ":%u: ", WARNING_COLOR) format "\n", __LINE__, ##__VA_ARGS__)
#define INFO_LOG(format, ...)                print(COLOR_STR("INFO:" __FILE__ ":%u: ", INFO_COLOR) format "\n", __LINE__, ##__VA_ARGS__)
#define TODO(format, ...)                    print(COLOR_STR("TODO:" __FILE__ ":%u: ", TODO_COLOR) COLOR_STR("function %s: ", PURPLE) format "\n", \
													 __LINE__, __func__, ##__VA_ARGS__)

#ifdef _DEBUG
#	define DEBUG_LOG(format, ...)            print(COLOR_STR("DEBUG:" __FILE__ ":%u: ", DEBUG_COLOR) format "\n", __LINE__, ##__VA_ARGS__)
#else 
#	define DEBUG_LOG(format, ...)
#endif //_DEBUG	

#ifndef _BEDROCK_NO_PERROR_
#ifdef _BEDROCK_USERSPACE_
#	include "./str_error.h"
#endif // _BEDROCK_USERSPACE_
#	define PERROR_LOG(format, ...)           print(COLOR_STR("WARNING:" __FILE__ ":%u: ", BRIGHT_YELLOW) format ", because: " COLOR_STR("'%s'", BRIGHT_YELLOW) ".\n", \
												   __LINE__, ##__VA_ARGS__, str_error())
#endif // _BEDROCK_NO_PERROR_

#endif //_BEDROCK_PRINTING_UTILS_

/* -------------------------------------------------------------------------------------------------------- */
// ------------------
//  Assert Utilities
// ------------------
#if !defined(BEDROCK_ASSERT) && !defined(_BEDROCK_KERNEL_)
#   define BEDROCK_ASSERT(condition) bedrock_assert(condition, #condition, __FILE__, __LINE__, __func__)
	BEDROCK_FUNCTION void bedrock_assert(bool condition, const char* condition_str, const char* file, const int line, const char* func) {
		if (condition) return;
		print(BEDROCK_COLOR_STR("ASSERT::%s:%u: ", ERROR_COLOR) "Failed to assert condition " BEDROCK_COLOR_STR("'%s'", BLUE) " in function " BEDROCK_COLOR_STR("'%s'", PURPLE) "\n",
			  file, 
			  line, 
			  condition_str, 
			  func
		);
		abort();
		return;
	}
#endif //BEDROCK_ASSERT

#endif //_BEDROCK_MISCS_H_

