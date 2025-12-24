#ifndef _BEDROCK_H_
#define _BEDROCK_H_

// -----------------------------
//  Constants and Common Macros
// -----------------------------
#ifndef PACKED_STRUCT
	#define PACKED_STRUCT __attribute__((packed))
#endif //PACKED_STRUCT

#ifndef UNUSED_FUNCTION
	#define UNUSED_FUNCTION __attribute__((unused))
#endif //UNUSED_FUNCTION

#ifndef UNUSED_VAR
	#define UNUSED_VAR(var) ((void) var)
#endif //UNUSED_VAR

#ifndef TRUE
	#define TRUE  1
#endif //TRUE

#ifndef FALSE
	#define FALSE 0
#endif //FALSE

#ifndef ABS
	#define ABS(a) ((a) < 0 ? -(a) : (a))
#endif // ABS

#define CLAMP(val, min, max) ((val) > (max) ? (max) : ((val) < (min) ? (min) : (val)))

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(*(arr)))

#define SAFE_FREE(ptr) do { if ((ptr) != NULL) { free(ptr); (ptr) = NULL; } } while (0) 
#define CAST_PTR(ptr, type) ((type*) (ptr))
#define MAX(a, b) ((a) > (b) ? (a) : (b)) 
#define MIN(a, b) ((a) < (b) ? (a) : (b)) 
#define ARR_SIZE(arr) (sizeof(arr) / sizeof(*(arr)))

#define GET_BIT(val, bit_pos) (((val) >> (bit_pos)) & 0x01)

#define CHR_TO_INT(chr) ((int)(chr) - 48)
#define IS_A_VAL(chr)   (((chr) >= 48) && ((chr) <= 57))
#define TO_BOOL(var)    (!!(var))

#define MASK_BITS_INTERVAL(a, b) (((char)(a) >= (char)(b)) ? (QCOW_MASK_BITS_PRECEDING(a) & ~QCOW_MASK_BITS_PRECEDING(b)) : 0)
#define BOOL2STR(cond) (cond ? COLOR_STR("TRUE", GREEN) : COLOR_STR("FALSE", RED))
#define MASK_BITS_PRECEDING(bit_index) ((1ULL << (bit_index)) - 1)
#define ARR_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define CAST_PTR(ptr, type) ((type*) (ptr))

#define QCOW_BE_CONVERT(ptr_val, size) qcow_be_to_le(ptr_val, size)
#if defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN || \
    defined(__LITTLE_ENDIAN__) || \
    defined(__ARMEL__) || \
    defined(__THUMBEL__) || \
    defined(__AARCH64EL__) || \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)

	UNUSED_FUNCTION static void qcow_be_to_le(void* ptr_val, size_t size) {
        for (size_t i = 0; i < size / 2; ++i) {
            unsigned char temp = QCOW_CAST_PTR(ptr_val, unsigned char)[i];
            QCOW_CAST_PTR(ptr_val, unsigned char)[i] = QCOW_CAST_PTR(ptr_val, unsigned char)[size - 1 - i];
            QCOW_CAST_PTR(ptr_val, unsigned char)[size - 1 - i] = temp;
        }
        return;
    }

#else
    #define qcow_be_to_le(ptr_val, size)
#endif // CHECK_ENDIANNESS

#define QCOW_SAFE_FREE(ptr) do { if ((ptr) != NULL) qcow_free(ptr), (ptr) = NULL; } while(0)
#define QCOW_MULTI_FREE(...) 															\
	do {																				\
		void* ptrs[] = { NULL, ##__VA_ARGS__ };							 				\
		for (unsigned int i = 0; i < QCOW_ARR_SIZE(ptrs); ++i) QCOW_SAFE_FREE(ptrs[i]);	\
	} while(0)

#define IS_A_HEX_VAL(chr) (IS_A_NUM(chr) || (IS_LOWER_CASE(chr) && (chr) <= 'f') || (IS_UPPER_CASE(chr) && (chr) <= 'F'))
#define OSAS_BOOL2STR(cond) (cond ? COLOR_STR("TRUE", GREEN) : COLOR_STR("FALSE", RED))
#define CHR_TO_HEX(chr) (IS_LOWER_CASE(chr) ? ((chr) - 'a' + 10) : ((chr) - 'A' + 10))
#define IS_WHITESPACE(chr) (chr == ' ' || chr == '\n' || chr == '\r' || chr == '\t')
#define HEX_TO_CHR_CAP(val) ((val) > 9 ? (val) + 55 : (val) + '0')
#define HEX_TO_CHR(val) ((val) > 9 ? (val) + 87 : (val) + '0')
#define STR_BITS(val, str) str_bits(val, BITS_SIZE(val), str)
#define IS_LOWER_CASE(chr) ((chr) >= 'a' && (chr) <= 'z')
#define IS_UPPER_CASE(chr) ((chr) >= 'A' && (chr) <= 'Z')
#define ARR_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define IS_A_NUM(chr) ((chr >= '0') && (chr <= '9'))
#define UNUSED_FUNCTION __attribute__((unused))
#define NAKED_FUNCTION __attribute__((naked))
#define PACKED_STRUCT __attribute__((packed))
#define CAST_PTR(ptr, type) ((type*) (ptr))
#define BITS_SIZE(val) (sizeof(val) * 8)
#define NUM_TO_CHR(val) ((val) + '0')
#define CHR_TO_NUM(chr) (chr - '0') 
#define UNUSED_VAR(var) (void) var
#define TO_BOOL(val) (!!(val))

#define OSAS_BE_CONVERT(ptr_val, size) osas_be_to_le(ptr_val, size)
#if defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN || \
    defined(__LITTLE_ENDIAN__)                               || \
    defined(__ARMEL__)                                       || \
    defined(__THUMBEL__)                                     || \
    defined(__AARCH64EL__)                                   || \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
 	
	UNUSED_FUNCTION static void osas_be_to_le(void* ptr_val, size_t size) {
        for (size_t i = 0; i < size / 2; ++i) {
            unsigned char temp = CAST_PTR(ptr_val, unsigned char)[i];
            CAST_PTR(ptr_val, unsigned char)[i] = CAST_PTR(ptr_val, unsigned char)[size - 1 - i];
            CAST_PTR(ptr_val, unsigned char)[size - 1 - i] = temp;
        }
        return;
    }

#else
    #define osas_be_to_le(ptr_val, size)
#endif // CHECK_ENDIANNESS

#define SAFE_FREE(ptr) do { if ((ptr) != NULL) free(ptr), (ptr) = NULL; } while(0)
#define MULTI_FREE(...)                                     \
	do {                                                    \
		void* ptrs[] = { NULL, ##__VA_ARGS__ };             \
		for (unsigned int i = 0; i < ARR_SIZE(ptrs); ++i) { \
			SAFE_FREE(ptrs[i]);                             \
		}                                                   \
	} while(0)

#define XCOMP_MASK_BITS_INTERVAL(a, b) (((char)(a) >= (char)(b)) ? (XCOMP_MASK_BITS_PRECEDING(a) & ~XCOMP_MASK_BITS_PRECEDING(b)) : 0)
#define XCOMP_BOOL2STR(cond) (cond ? COLOR_STR("TRUE", GREEN) : COLOR_STR("FALSE", RED))
#define XCOMP_MASK_BITS_PRECEDING(bit_index) ((1ULL << (bit_index)) - 1)
#define XCOMP_ARR_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define XCOMP_CAST_PTR(ptr, type) ((type*) (ptr))

#ifndef MIN
	#define MIN(a, b) (a < b ? a : b)
	#define MAX(a, b) (a > b ? a : b)
#endif //MIN

#define XCOMP_SAFE_FREE(ptr) do { if ((ptr) != NULL) xcomp_free(ptr), (ptr) = NULL; } while(0)
#define XCOMP_MULTI_FREE(...) 															\
	do {																				\
		void* ptrs[] = { NULL, ##__VA_ARGS__ };							 				\
		for (unsigned int i = 0; i < XCOMP_ARR_SIZE(ptrs); ++i) XCOMP_SAFE_FREE(ptrs[i]);	\
	} while(0)

#define TRACK_CALL(__call) printf("Call '%s' at %s:%d\n", #__call, __FILE__, __LINE__); \
						   __call

/* -------------------------------------------------------------------------------------------------------- */
// ---------------------
//  General Definitions
// ---------------------
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

	#define ERROR_LOG(format, error_str, ...) printf(COLOR_STR("ERROR:%s:" __FILE__ ":%u: ", ERROR_COLOR) format "\n", error_str, __LINE__, ##__VA_ARGS__)
	#define WARNING_LOG(format, ...)          printf(COLOR_STR("WARNING:" __FILE__ ":%u: ", WARNING_COLOR) format "\n", __LINE__, ##__VA_ARGS__)
	#define INFO_LOG(format, ...)             printf(COLOR_STR("INFO:" __FILE__ ":%u: ", INFO_COLOR) format "\n", __LINE__, ##__VA_ARGS__)
	#ifdef _DEBUG
		#define DEBUG_LOG(format, ...)            printf(COLOR_STR("DEBUG:" __FILE__ ":%u: ", DEBUG_COLOR) format "\n", __LINE__, ##__VA_ARGS__)
	#else 
		#define DEBUG_LOG(format, ...)
	#endif //_DEBUG	
	
	#define TODO(format, ...)            printf(COLOR_STR("TODO:" __FILE__ ":%u: ", TODO_COLOR) COLOR_STR("function %s: ", PURPLE) format "\n", __LINE__, __func__, ##__VA_ARGS__)

	#ifndef _BEDROCK_NO_PERROR_
		#include "./str_error.h"
		#define PERROR_LOG(format, ...) printf(COLOR_STR("WARNING:" __FILE__ ":%u: ", BRIGHT_YELLOW) format ", because: " COLOR_STR("'%s'", BRIGHT_YELLOW) ".\n", __LINE__, ##__VA_ARGS__, str_error())
	#endif // _BEDROCK_NO_PERROR_

#endif //_BEDROCK_PRINTING_UTILS_

/* -------------------------------------------------------------------------------------------------------- */
// ------------------
//  Assert Utilities
// ------------------
#ifndef BEDROCK_ASSERT
#define BEDROCK_ASSERT(condition) bedrock_assert(condition, #condition, __FILE__, __LINE__, __func__)
static void bedrock_assert(bool condition, const char* condition_str, const char* file, const int line, const char* func) {
	if (condition) return;
	printf(COLOR_STR("ASSERT::%s:%u: ", ERROR_COLOR) "Failed to assert condition " COLOR_STR("'%s'", BLUE) " in function " COLOR_STR("'%s'", PURPLE) "\n", file, line, condition_str, func);
	abort();
	return;
}
#endif //BEDROCK_ASSERT

/* -------------------------------------------------------------------------------------------------------- */
// ----------------------------------
//  Any Space Functions Declarations
// ----------------------------------
#define mem_set(ptr, value, size)    mem_set_var(ptr, value, size, sizeof(u8))
#define mem_set_32(ptr, value, size) mem_set_var(ptr, value, size, sizeof(u32))
#define mem_set_64(ptr, value, size) mem_set_var(ptr, value, size, sizeof(u64))
BEDROCK_FUNCTION void mem_set_var(void* ptr, int value, size_t size, size_t val_size);
BEDROCK_FUNCTION void* mem_cpy(void* dest, const void* src, size_t size);
BEDROCK_FUNCTION void mem_move(void* dest, const void* src, size_t size);
BEDROCK_FUNCTION static int mem_n_cmp(const void* ptr1, const void* ptr2, size_t n);
BEDROCK_FUNCTION static size_t str_len(const char* str);
BEDROCK_FUNCTION static int str_n_cmp(const char* str1, const char* str2, size_t n);

/* -------------------------------------------------------------------------------------------------------- */
BEDROCK_FUNCTION u8 bit_size(u8 val) {
	u8 size = 8;
	for (s8 i = size - 1; i >= 0; --i) {
		if (GET_BIT(val, i)) break;
		size--;
	}
	return size;
}

BEDROCK_FUNCTION size_t str_len(const char* str) {
    if (str == NULL) return 0;
    const char* str_c = str;
	while (*str++);
    return (size_t) (str - str_c - 1);
}

BEDROCK_FUNCTION void* mem_cpy(void* dest, const void* src, size_t size) {
	if (dest == NULL || src == NULL) return NULL;
	for (size_t i = 0; i < size; ++i) CAST_PTR(dest, u8)[i] = CAST_PTR(src, u8)[i];
	return dest;
}

BEDROCK_FUNCTION void mem_set_var(void* ptr, int value, size_t size, size_t val_size) {
	if (ptr == NULL) return;
	for (size_t i = 0; i < size; ++i) CAST_PTR(ptr, u8)[i] = CAST_PTR(&value, u8)[i % val_size]; 
	return;
}

BEDROCK_FUNCTION char* reverse_str(char* str) {
    int len = str_len(str);
    for (int i = 0; i < (len / 2); ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return str;
}

BEDROCK_FUNCTION void* mem_move(void* dest, const void* src, size_t size) {
    if (dest == NULL || src == NULL || size == 0) return NULL;
    
	size_t s = size;
	u8* temp = (u8*) calloc(size, sizeof(u8));
	if (temp == NULL) {
		printf("Failed to allocate the temp buffer for mem_move.\n");
		return NULL;
	}
	
	u8* dp = CAST_PTR(dest, u8);
	u8* sp = (u8*) src;

	while (size--) *temp++ = *sp++;
	temp -= s, size = s;
	while (s--)	*dp++ = *temp++;
	
	free(temp - size);
    
    return dest;
}

BEDROCK_FUNCTION char* str_cpy(char* dest, const char* restrict src) {
	if (dest == NULL || src == NULL) return NULL;
	char* o_dest = dest;
  	while ((*dest++ = *src++));
	return o_dest;
}

BEDROCK_FUNCTION int str_tok(const char* str, const char* delim) {
     for (u64 i = 0, j = 0; i <= str_len(str); ++i) {
         if (delim[j] == str[i]) {
            if ((j + 1) == str_len(delim)) return i - j;
            j++;
         } else if (j > 0) i -= j, j = 0;
    }
    return -1;
}

BEDROCK_FUNCTION void byte_str_into_hex_str(char* str, const u8* byte_str, u8 byte_size) {
	for (u8 i = 0, j = 0; i < byte_size; ++i, ++j) {
		str[j++] = hex_chrs[(byte_str[i] >> 4) & 0xF];
		str[j] = hex_chrs[byte_str[i] & 0xF];
		if (i < byte_size - 1) str[++j] = ' ';
	}
	return;
}

BEDROCK_FUNCTION void byte_str_into_hex_val(char* str, const u8* byte_str, u8 byte_size) {
	str[0] = '0', str[1] = 'x', str += 2;
	for (u8 i = byte_size, j = 0; i > 0; --i, ++j) {
		str[j++] = hex_chrs[(byte_str[i - 1] >> 4) & 0xF];
		str[j] = hex_chrs[byte_str[i - 1] & 0xF];
	}
	return;
}

BEDROCK_FUNCTION void byte_str_into_dec_val(char* str, const u8* byte_str, u8 byte_size) {
	u64 val = 0;
	for (u8 i = byte_size; i > 0; --i) {
		val *= 256;
		val += byte_str[i - 1];
	}
	
	char* const str_base = str;
	while (val) {
		mem_move(str_base + 1, str_base, str - str_base);
		u8 value = val % 10;
		*str_base = value + '0', str++;
		val = (val - (val % 10)) / 10;
	}
	
	return;
}

BEDROCK_FUNCTION unsigned int ref_chr_cnt(const char* str, unsigned int len, char chr) {
	unsigned int ref_cnt = 0;
	if (str == NULL) return 0;
	for (unsigned int i = 0; i < len; ++i) if (str[i] == chr) ref_cnt++;
	return ref_cnt;
}

BEDROCK_FUNCTION long long int find_chr(const char* str, unsigned int len, char chr) {
	if (str == NULL) return -2;
	for (unsigned int i = 0; i < len; ++i) if (str[i] == chr) return (int) i;
	return -1;
}

BEDROCK_FUNCTION long long int str_to_int(const char* str) {
	long long int value = 0;
	if (str == NULL) return 0;

	unsigned int i = 0;
	while (str[i] != '\0') {
		if (!IS_A_VAL(str[i])) {
			KMESG_ERR(" this is not a valid value: " CRITICAL_COLOR "'%s'" RESET_COLOR ".\n", str);
			return -1;
		}
	
		value = (value * 10) + CHR_TO_INT(str[i]);
		++i;
	}
	
	return value;
}

BEDROCK_FUNCTION int str_cmp(const char* str1, const char* str2) {
    // Null Checks
    if (str1 == NULL && str2 == NULL) return 0;
    if (str1 == NULL) return -1;
    else if (str2 == NULL) return 1;

    size_t i = 0;
    while (str1[i] != '\0' || str2[i] != '\0') {
        if (str1[i] != str2[i]) return str1[i] - str2[i];
        ++i;
    }
    
	return 0;
}

BEDROCK_FUNCTION int str_n_cmp(const char* str1, const char* str2, size_t n) {
    // Null Checks
    if (str1 == NULL && str2 == NULL) return 0;
    if (str1 == NULL) return -1;
    else if (str2 == NULL) return 1;

    size_t i = 0;
    while ((str1[i] != '\0' || str2[i] != '\0') && i < n) {
        if (str1[i] != str2[i]) return str1[i] - str2[i];
        ++i;
    }

	return 0;
}

BEDROCK_FUNCTION void reverse_str_arr(char*** str_arr, unsigned int size) {
	for (unsigned int i = 0; i < (size >> 1); ++i) {
		char* temp = (*str_arr)[i];
		(*str_arr)[i] = (*str_arr)[size - 1 - i];
		(*str_arr)[size - 1 - i] = temp;
	}
	return;
}

BEDROCK_FUNCTION int mem_copy_until(char* dest, char* src, const char chr) {
	const char* orig_src = src;
	while (*src != chr && *src != '\0') *dest++ = *src++;
	if (*src == '\0') return -1;
	return src - orig_src;
}

BEDROCK_FUNCTION void mem_set_var(void* ptr, int value, size_t size, size_t val_size) {
	if (ptr == NULL) return;
	for (size_t i = 0; i < size; ++i) QCOW_CAST_PTR(ptr, unsigned char)[i] = QCOW_CAST_PTR(&value, unsigned char)[i % val_size]; 
	return;
}

BEDROCK_FUNCTION void* mem_cpy(void* dest, const void* src, size_t size) {
	if (dest == NULL || src == NULL) return NULL;
	for (size_t i = 0; i < size; ++i) QCOW_CAST_PTR(dest, unsigned char)[i] = QCOW_CAST_PTR(src, unsigned char)[i];
	return dest;
}

BEDROCK_FUNCTION void mem_move(void* dest, const void* src, size_t size) {
    if (dest == NULL || src == NULL || size == 0) return;
    
	unsigned char* temp = (unsigned char*) qcow_calloc(size, sizeof(unsigned char));
	
	for (size_t i = 0; i < size; ++i) *QCOW_CAST_PTR(temp + i, unsigned char) = *QCOW_CAST_PTR(QCOW_CAST_PTR(src, unsigned char) + i, unsigned char); 
    for (size_t i = 0; i < size; ++i) *QCOW_CAST_PTR(QCOW_CAST_PTR(dest, unsigned char) + i, unsigned char) = *QCOW_CAST_PTR(temp + i, unsigned char);
    
	QCOW_SAFE_FREE(temp);
    
    return;
}

BEDROCK_FUNCTION int mem_n_cmp(const void* ptr1, const void* ptr2, size_t n) {
    // Null Checks
    if (ptr1 == NULL && ptr2 == NULL) return 0;
    if (ptr1 == NULL) return -1;
    else if (ptr2 == NULL) return 1;

    unsigned char* a = (unsigned char*) ptr1;
    unsigned char* b = (unsigned char*) ptr2;

	while (n--) if (*a++ != *b++) return *(a - 1) - *(b - 1);

	return 0;
}

BEDROCK_FUNCTION size_t str_len(const char* str) {
    if (str == NULL) return 0;
	size_t i = 0;
    while (*str++) ++i;
    return i;
}

BEDROCK_FUNCTION int str_n_cmp(const char* str1, const char* str2, size_t n) {
    // Null Checks
    if (str1 == NULL && str2 == NULL) return 0;
    if (str1 == NULL) return -1;
    else if (str2 == NULL) return 1;

    size_t i = 0;
    while ((str1[i] != '\0' || str2[i] != '\0') && i < n) {
        if (str1[i] != str2[i]) return str1[i] - str2[i];
        ++i;
    }

	return 0;
}

BEDROCK_FUNCTION void mem_move(void* dest, const void* src, size_t size) {
    if (dest == NULL || src == NULL || size == 0) return;
    
	unsigned char* temp = (unsigned char*) bedrock_calloc(size, sizeof(unsigned char));
	
	for (size_t i = 0; i < size; ++i) *CAST_PTR(temp + i, unsigned char) = *CAST_PTR(CAST_PTR(src, unsigned char) + i, unsigned char); 
    for (size_t i = 0; i < size; ++i) *CAST_PTR(CAST_PTR(dest, unsigned char) + i, unsigned char) = *CAST_PTR(temp + i, unsigned char);
    
	bedrock_free(temp);
    
    return;
}

#define mem_set(ptr, value, size)    mem_set_var(ptr, value, size, sizeof(u8))
#define mem_set_32(ptr, value, size) mem_set_var(ptr, value, size, sizeof(u32))
#define mem_set_64(ptr, value, size) mem_set_var(ptr, value, size, sizeof(u64))
BEDROCK_FUNCTION void mem_set_var(void* ptr, int value, size_t size, size_t val_size) {
	if (ptr == NULL) return;
	for (size_t i = 0; i < size; ++i) CAST_PTR(ptr, unsigned char)[i] = CAST_PTR(&value, unsigned char)[i % val_size]; 
	return;
}

BEDROCK_FUNCTION void* mem_cpy(void* dest, const void* src, size_t size) {
	if (dest == NULL || src == NULL) return NULL;
	for (size_t i = 0; i < size; ++i) CAST_PTR(dest, unsigned char)[i] = CAST_PTR(src, unsigned char)[i];
	return dest;
}

BEDROCK_FUNCTION size_t str_len(const char* str) {
    if (str == NULL) return 0;
	size_t i = 0;
    while (*str++) ++i;
    return i;
}

BEDROCK_FUNCTION int str_cmp(const char* str1, const char* str2) {
    // Null Checks
    if (str1 == NULL && str2 == NULL) return 0;
    if (str1 == NULL) return -1;
    else if (str2 == NULL) return 1;

    size_t i = 0;
    while (str1[i] != '\0' || str2[i] != '\0') {
        if (str1[i] != str2[i]) return str1[i] - str2[i];
        ++i;
    }
    
	return 0;
}

BEDROCK_FUNCTION int mem_n_cmp(const void* ptr1, const void* ptr2, size_t n) {
    // Null Checks
    if (ptr1 == NULL && ptr2 == NULL) return 0;
    if (ptr1 == NULL) return -1;
    else if (ptr2 == NULL) return 1;
    
    unsigned char* a = (unsigned char*) ptr1;
    unsigned char* b = (unsigned char*) ptr2;
    
	while (n--) if (*a++ != *b++) return *(a - 1) - *(b - 1);

	return 0;
}

BEDROCK_FUNCTION int str_n_cmp(const char* str1, const char* str2, size_t n) {
    // Null Checks
    if (str1 == NULL && str2 == NULL) return 0;
    if (str1 == NULL) return -1;
    else if (str2 == NULL) return 1;

    size_t i = 0;
    while ((str1[i] != '\0' || str2[i] != '\0') && i < n) {
        if (str1[i] != str2[i]) return str1[i] - str2[i];
        ++i;
    }

	return 0;
}

BEDROCK_FUNCTION char* str_cpy(char* dest, const char* restrict src) {
	if (dest == NULL || src == NULL) return NULL;
	char* o_dest = dest;
  	while ((*dest++ = *src++));
	return o_dest;
}

BEDROCK_FUNCTION char* str_bits(unsigned long long int val, unsigned char size_bits, char* str) {
    unsigned char i = 0;
    for (i = 0; i < size_bits; ++i) {
        str[i] = ((val >> (size_bits - 1 - i)) & 1) + 48;
    }
    str[i] = '\0';
    return str;
}

BEDROCK_FUNCTION char* to_hex_str(u8* val, unsigned int size, char* str) {
	unsigned int i = 0;
    for (unsigned int j = 0; j < size; i += 3, ++j) {
        str[i] = HEX_TO_CHR_CAP((val[j] >> 4) & 0xF);
        str[i + 1] = HEX_TO_CHR_CAP(val[j] & 0xF);
		str[i + 2] = ' ';	
    }
    str[i] = '\0';
    return str;
}

BEDROCK_FUNCTION int find_next_chr(const char* str, char chr) {
	if (str == NULL) return -2;
	size_t i = 0;
	while ((str[i] != chr) && (str[i] != '\0')) ++i;
	if (str[i] == '\0') return -1;
	return i;
} 

BEDROCK_FUNCTION size_t find_next_whitespace(const char* str) {
	if (str == NULL) return 0;
	size_t i = 0;
	while (!IS_WHITESPACE(str[i])) ++i;
	return i;
}

BEDROCK_FUNCTION int str_tok(const char* str, const char* token) {
	if (str == NULL || token == NULL) return -1;
	
	unsigned int j = 0;
	const unsigned int token_len = str_len(token);
	for (unsigned int i = 0; str[i] != '\0'; ++i) {
		for (j = 0; str[i + j] != '\0' && j < token_len; ++j) {
			if (str[i + j] != token[j]) break;
		}
		if (j == token_len) return i;
	}
	
	return -1;
}

BEDROCK_FUNCTION int rev_find_next_chr(const char* str, char chr) {
	if (str == NULL) return -2;
	size_t len = str_len(str);
	while ((str[len] != chr) && len > 0) --len;
	return len;
} 

BEDROCK_FUNCTION int starts_with(char* str, char* pattern) {
	if (str == NULL || pattern == NULL) return FALSE;
	size_t i = 0;
	while ((str[i] != '\0') && (pattern[i] != '\0')) {
		if (str[i] != pattern[i]) return FALSE;
		++i;
	}
	if (str[i] == '\0' && pattern[i] != '\0') return FALSE;
	return TRUE;
}

BEDROCK_FUNCTION long long int str_to_num(const char* str, char delim) {
	long long int ret = 0;
	bool is_neg = FALSE;
	bool is_hex = FALSE;
	
	while (IS_WHITESPACE(*str)) str++;

	if (*str == '-') is_neg = TRUE, str++;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) is_hex = TRUE, str += 2;

	unsigned char base = is_hex ? 16 : 10;
	while (*str != delim && *str != '\0') {
		if (IS_A_NUM(*str)) ret += CHR_TO_NUM(*str);
		else if (is_hex && IS_A_HEX_VAL(*str)) ret += CHR_TO_HEX(*str);
		else return -1;
		
		ret *= (str++, *str != delim && *str != '\0') * base + (*str == delim || *str == '\0');
	}

	if (is_neg) ret *= -1;

	return ret;
}

BEDROCK_FUNCTION char* reverse_str(char* str) {
    int len = str_len(str);
    for (int i = 0; i < (len / 2); ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return str;
}

BEDROCK_FUNCTION_INLINE int hex_to_str(char* str, unsigned long long int val, unsigned char size) {
    unsigned char i = 0;                       
    for (i = 0; i < size * 2; ++i) {
		str[i] = HEX_TO_CHR_CAP(val & 0x0F);
		val >>= 4;
    }

    reverse_str(str);
    
	str[i] = '\0';
	
	return i;
}

BEDROCK_FUNCTION_INLINE int oct_to_str(char* str, unsigned long long int val, unsigned int size) {
    unsigned char i = 0;                 
    
	unsigned int sz = (size * 8) / 3;
	for (i = 0; i < sz; ++i) {           
		str[i] = NUM_TO_CHR(val & 0x07); 
		val >>= 3;                       
    }                                    
    
	reverse_str(str);                    
    
	str[i] = '\0';                    
	
	return i;
}

BEDROCK_FUNCTION_INLINE int dec_to_str(char* str, unsigned long long int val, unsigned int is_neg) {
    if (is_neg) val = (long long int) val * -1;
    
	unsigned char i = 0;                  
    do {                                 
        str[i] = NUM_TO_CHR(val % 10);  
        ++i;                          
        if (val < 10) break;         
        val = (val - (val % 10)) / 10; 
    } while (TRUE);                   
    
	if (is_neg) str[i] = '-', ++i; 

    reverse_str(str);              
  
  	str[i] = '\0';

	return i;
}

#ifdef _OSAS_SPRINTF_
#define MAX_NUM_LEN 65

BEDROCK_FUNCTION int osas_snprintf(char* str, size_t size, const char* format, ...);
BEDROCK_FUNCTION int osas_vsnprintf(char* str, size_t size, const char* format, va_list args);

BEDROCK_FUNCTION int osas_snprintf(char* str, size_t size, const char* format, ...) {
    va_list args;
    va_start(args, format);
	int ret = osas_vsnprintf(str, size, format, args);
    va_end(args);
    return ret;
}

BEDROCK_FUNCTION int osas_vsnprintf(char* str, size_t size, const char* format, va_list args) {
	if (str == NULL || format == NULL) return -1;
	
	size_t format_size = str_len(format);
	size_t str_index = 0;
	
	// TODO: Missing size checks for out-of-bound accesses
	for (size_t i = 0; (i <= format_size) && (str_index < size); ++i) {
		if (starts_with((char*) format + i, "%%")) {
			str[str_index] = 'h';
			str_index++;
			++i;
		} else if (starts_with((char*) format + i, "%c")) {
			char var_chr = (char) va_arg(args, int);	
			str[str_index] = var_chr;
			str_index++;
			++i;
		} else if (starts_with((char*) format + i, "%s")) {
			char* var_str = va_arg(args, char*);	
			if (var_str == NULL) var_str = "(null)";
			if (str_len(var_str) + str_index >= size) return str_index;
			str_cpy(str + str_index, var_str);
			str_index += str_len(var_str);
			++i;
		} else if (starts_with((char*) format + i, "%S")) {
			int var_cnt = (char) va_arg(args, int);	
			if (var_cnt + str_index >= size) return str_index;
			mem_set(str + str_index, ' ', var_cnt);
			str_index += var_cnt;
			++i;
		} else if (starts_with((char*) format + i, "%p")) {
			if (2 + str_index >= size) return str_index;
			str[str_index] = '0';
			str[str_index + 1] = 'x';
			str_index += 2;
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned long long int var_ptr = (unsigned long long int) va_arg(args, void*);	
			str_index += hex_to_str(str + str_index, var_ptr, sizeof(var_ptr));
			++i;
		} else if (starts_with((char*) format + i, "%d") || starts_with((char*) format + i, "%i")) {
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			int var_int = va_arg(args, int);	
			str_index += dec_to_str(str + str_index, var_int, var_int < 0);
			++i;
		} else if (starts_with((char*) format + i, "%u")) {
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned int var_uint = va_arg(args, unsigned int);	
			str_index += dec_to_str(str + str_index, var_uint, FALSE);
			++i;
		} else if (starts_with((char*) format + i, "%ld")) {
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			long int var_lint = va_arg(args, long int);	
			str_index += dec_to_str(str + str_index, var_lint, var_lint < 0);
			i += 2;
		} else if (starts_with((char*) format + i, "%lu")) {
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned long int var_luint = va_arg(args, unsigned long int);	
			str_index += dec_to_str(str + str_index, var_luint, FALSE);
			i += 2;
		} else if (starts_with((char*) format + i, "%lld")) {
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			long long int var_llint = va_arg(args, long long int);	
			str_index += dec_to_str(str + str_index, var_llint, var_llint < 0);
			i += 3;
		} else if (starts_with((char*) format + i, "%llu")) {
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned long long int var_lluint = va_arg(args, unsigned long long int);	
			str_index += dec_to_str(str + str_index, var_lluint, FALSE);
			i += 3;
		} else if (starts_with((char*) format + i, "%X") || starts_with((char*) format + i, "%x")) {
			if (2 + str_index >= size) return str_index;
		    str[str_index] = '0';
		    str[str_index + 1] = 'x';
			str_index += 2;
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned int var_uint = va_arg(args, unsigned int);	
			str_index += hex_to_str(str + str_index, var_uint, sizeof(var_uint));
			++i;
		} else if (starts_with((char*) format + i, "%lX") || starts_with((char*) format + i, "%lx")) {
			if (2 + str_index >= size) return str_index;
		    str[str_index] = '0';
		    str[str_index + 1] = 'x';
			str_index += 2;
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned long int var_luint = va_arg(args, unsigned long int);	
			str_index += hex_to_str(str + str_index, var_luint, sizeof(var_luint));
			i += 2;
		} else if (starts_with((char*) format + i, "%llX") || starts_with((char*) format + i, "%llx")) {
			if (2 + str_index >= size) return str_index;
		    str[str_index] = '0';
		    str[str_index + 1] = 'x';
			str_index += 2;
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned long long int var_lluint = va_arg(args, unsigned long long int);	
			str_index += hex_to_str(str + str_index, var_lluint, sizeof(var_lluint));
			i += 3;
		} else if (starts_with((char*) format + i, "%b")) {
			if (2 + str_index >= size) return str_index;
		    str[str_index] = '0';
		    str[str_index + 1] = 'b';
			str_index += 2;
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned int var_uint = va_arg(args, unsigned int);	
			str_bits(var_uint, BITS_SIZE(var_uint), str + str_index);
			str_index += BITS_SIZE(var_uint);
			++i;
		} else if (starts_with((char*) format + i, "%lb")) {
			if (2 + str_index >= size) return str_index;
		    str[str_index] = '0';
		    str[str_index + 1] = 'b';
			str_index += 2;
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned long int var_luint = va_arg(args, unsigned long int);	
			str_bits(var_luint, BITS_SIZE(var_luint), str + str_index);
			str_index += BITS_SIZE(var_luint);
			i += 2;
		} else if (starts_with((char*) format + i, "%llb")) {
			if (2 + str_index >= size) return str_index;
		    str[str_index] = '0';
		    str[str_index + 1] = 'b';
			str_index += 2;
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned long long int var_lluint = va_arg(args, unsigned long long int);	
			str_bits(var_lluint, BITS_SIZE(var_lluint), str + str_index);
			str_index += BITS_SIZE(var_lluint);
			i += 3;
		} else if (starts_with((char*) format + i, "%o")) {
			if (1 + str_index >= size) return str_index;
            str[str_index] = '0';
            str_index++;
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned int var_uint = va_arg(args, unsigned int);	
			str_index += oct_to_str(str + str_index, var_uint, sizeof(var_uint));
			++i;
		} else if (starts_with((char*) format + i, "%lo")) {
			if (1 + str_index >= size) return str_index;
            str[str_index] = '0';
            str_index++;
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned long int var_luint = va_arg(args, unsigned long int);	
			str_index += oct_to_str(str + str_index, var_luint, sizeof(var_luint));
			i += 2;
		} else if (starts_with((char*) format + i, "%llo")) {
			if (1 + str_index >= size) return str_index;
            str[str_index] = '0';
            str_index++;
			if (MAX_NUM_LEN + str_index >= size) return str_index;
			unsigned long long int var_lluint = va_arg(args, unsigned long long int);	
			str_index += oct_to_str(str + str_index, var_lluint, sizeof(var_lluint));
			i += 3;
		} else {
			str[str_index] = format[i];
			str_index++;
		}
	}

	return str_index;
}

#endif //_OSAS_SPRINTF_

BEDROCK_FUNCTION void trim_str(char* str) {
	if (str == NULL) return;
	size_t len = str_len(str);

	// Trim right 
	size_t ind = 0;
	while (IS_WHITESPACE(str[ind])) ++ind;
	for (size_t i = 0, j = ind; j <= len; ++i, ++j) str[i] = str[j];  

	// Trim left
	for (int i = len - ind - 1; (i >= 0) && IS_WHITESPACE(str[i]); --i) {
		str[i] = '\0';
	}

	return;
}

BEDROCK_FUNCTION void mem_set_var(void* ptr, int value, size_t size, size_t val_size) {
	if (ptr == NULL) return;
	for (size_t i = 0; i < size; ++i) XCOMP_CAST_PTR(ptr, unsigned char)[i] = XCOMP_CAST_PTR(&value, unsigned char)[i % val_size]; 
	return;
}

BEDROCK_FUNCTION void* mem_cpy(void* dest, const void* src, size_t size) {
	if (dest == NULL || src == NULL) return NULL;
	for (size_t i = 0; i < size; ++i) XCOMP_CAST_PTR(dest, unsigned char)[i] = XCOMP_CAST_PTR(src, unsigned char)[i];
	return dest;
}

BEDROCK_FUNCTION void mem_move(void* dest, const void* src, size_t size) {
    if (dest == NULL || src == NULL || size == 0) return;
    
	unsigned char* temp = (unsigned char*) xcomp_calloc(size, sizeof(unsigned char));
	
	for (size_t i = 0; i < size; ++i) *XCOMP_CAST_PTR(temp + i, unsigned char) = *XCOMP_CAST_PTR(XCOMP_CAST_PTR(src, unsigned char) + i, unsigned char); 
    for (size_t i = 0; i < size; ++i) *XCOMP_CAST_PTR(XCOMP_CAST_PTR(dest, unsigned char) + i, unsigned char) = *XCOMP_CAST_PTR(temp + i, unsigned char);
    
	XCOMP_SAFE_FREE(temp);
    
    return;
}

BEDROCK_FUNCTION int mem_n_cmp(const void* ptr1, const void* ptr2, size_t n) {
    // Null Checks
    if (ptr1 == NULL && ptr2 == NULL) return 0;
    if (ptr1 == NULL) return -1;
    else if (ptr2 == NULL) return 1;

    unsigned char* a = (unsigned char*) ptr1;
    unsigned char* b = (unsigned char*) ptr2;

	while (n--) if (*a++ != *b++) return *(a - 1) - *(b - 1);

	return 0;
}

BEDROCK_FUNCTION size_t str_len(const char* str) {
    if (str == NULL) return 0;
	size_t i = 0;
    while (*str++) ++i;
    return i;
}

BEDROCK_FUNCTION int str_n_cmp(const char* str1, const char* str2, size_t n) {
    // Null Checks
    if (str1 == NULL && str2 == NULL) return 0;
    if (str1 == NULL) return -1;
    else if (str2 == NULL) return 1;

    size_t i = 0;
    while ((str1[i] != '\0' || str2[i] != '\0') && i < n) {
        if (str1[i] != str2[i]) return str1[i] - str2[i];
        ++i;
    }

	return 0;
}

BEDROCK_FUNCTION void strip(char** str) {
    unsigned int len = 0;
    STR_LEN(*str, len);

    len--; // skip the null terminator

    while ((*str)[len] == ' ' || (*str)[len] == '\n' || (*str)[len] == '\r') { len--; }
    
    len++; // skip to the position of the last whitespace

    (*str)[len] = '\0';

    len++;

    *str = (char*) realloc(*str, sizeof(char) * (len + 1));
    
    unsigned int ind = 0;
    for (ind = 0; ind < len && ((*str)[ind] == ' ' || (*str)[ind] == '\n' || (*str)[len] == '\r'); ++ind) { }
    
    char* new_str = (char*) calloc(len - ind, sizeof(char));

    for (unsigned int i = 0; ind < len; ++i, ++ind) {
        new_str[i] = (*str)[ind];
    }

    free(*str);
    *str = new_str;

    return;
}

BEDROCK_FUNCTION char* to_hex_str(u8* val, unsigned int size, char* str, bool use_space) {
	unsigned int i = 0;
    for (int j = size - 1; j >= 0; i += 2 + use_space, --j) {
        str[i] = HEX_TO_CHR_CAP((val[j] >> 4) & 0xF);
        str[i + 1] = HEX_TO_CHR_CAP(val[j] & 0xF);
		if (use_space) str[i + 2] = ' ';	
    }
    str[i] = '\0';
    return str;
}

BEDROCK_FUNCTION u8* concat(u64 len, u64* size, ...) {
	va_list args;
    va_start(args, size);
	
	for (u64 i = 0; i < len; i += 2) {
		u8* element = va_arg(args, u8*);	
		(void) element;
		*size += va_arg(args, u64);
	}

	va_end(args);

	u8* concatenation = kocket_calloc(*size, 1);
	if (concatenation == NULL) {
		WARNING_LOG("Failed to allocate concatentation buffer of %llu bytes.", *size);
		return NULL;
	}
    
	va_start(args, size);
	
	u64 current_size = 0;
	for (u64 i = 0; i < len; i += 2) {
		u8* element = va_arg(args, u8*);	
		u64 element_size = va_arg(args, u64);
		mem_cpy(concatenation + current_size, element, element_size);	
		current_size += element_size;
	}

	va_end(args);

	return concatenation;
}

BEDROCK_FUNCTION u8 bit_size(u8 val) {
	u8 size = 8;
	for (s8 i = size - 1; i >= 0; --i) {
		if (GET_BIT(val, i)) break;
		size--;
	}
	return size;
}

BEDROCK_FUNCTION char* reverse_str(char* str) {
    int len = str_len(str);
    for (int i = 0; i < (len / 2); ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return str;
}

BEDROCK_FUNCTION u64 bytes_len(const u8* val, const u64 len) {
	u64 bytes_len = len;
	for (s64 i = len - 1; i >= 0 && val[i] == 0; --i, --bytes_len);
	return bytes_len;
}

BEDROCK_FUNCTION_INLINE u64 __ceil(u64 a, u64 b) {
	u64 c = (a - (a % b)) / b;
	if (a % b) c++;
	return c;
}

/* -------------------------------------------------------------------------------------------------------- */
// -------------------------------------
//  Kernel Space Functions Declarations
// -------------------------------------
#ifndef _BEDROCK_USERSPACE_
#endif //_BEDROCK_USERSPACE_

/* -------------------------------------------------------------------------------------------------------- */
// -------------------------------------
//  User Space Functions Declarations
// -------------------------------------
#ifndef _BEDROCK_KERNEL_
#endif //_BEDROCK_KERNEL_

#endif //_BEDROCK_H_

