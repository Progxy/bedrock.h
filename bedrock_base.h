#ifndef _BEDROCK_BASE_H_
#define _BEDROCK_BASE_H_

/* -------------------------------------------------------------------------------------------------------- */
// ----------------------------------
//  Any Space Functions Declarations
// ----------------------------------

// NOTE: find_chr replaced with str_tok
// NOTE: strip replaced with trim

#define mem_set(ptr, value, size)    mem_set_var(ptr, value, size, sizeof(u8))
#define mem_set_32(ptr, value, size) mem_set_var(ptr, value, size, sizeof(u32))
#define mem_set_64(ptr, value, size) mem_set_var(ptr, value, size, sizeof(u64))
BEDROCK_FUNCTION void mem_set_var(void* ptr, const int value, const u64 size, const u64 val_size);
BEDROCK_FUNCTION u8 bit_size(const u8 val);
BEDROCK_FUNCTION u64 str_len(const char* str);
BEDROCK_FUNCTION void* mem_cpy(void* dest, const void* src, const u64 size);
BEDROCK_FUNCTION char* reverse_str(char* str);
BEDROCK_FUNCTION void* mem_move(void* dest, const void* src, u64 size);
BEDROCK_FUNCTION char* str_cpy(char* dest, const char* src);
BEDROCK_FUNCTION int str_tok(const char* str, const char* delim);
BEDROCK_FUNCTION char* to_hex_str(char* str, const u8* byte_str, const u64 byte_size);
BEDROCK_FUNCTION char* to_dec_str(char* str, const u8* byte_str, const u64 byte_size);
BEDROCK_FUNCTION char* to_bit_str(char* str, const u8* byte_str, const u64 byte_size);
BEDROCK_FUNCTION unsigned int ref_chr_cnt(const char* str, const unsigned int len, const char chr);
BEDROCK_FUNCTION int str_cmp(const char* str1, const char* str2);
BEDROCK_FUNCTION int str_n_cmp(const char* str1, const char* str2, const u64 n);
BEDROCK_FUNCTION void reverse_str_arr(char*** str_arr, const u64 size);
BEDROCK_FUNCTION int mem_copy_until(char* dest, const char* src, const char chr);
BEDROCK_FUNCTION int mem_n_cmp(const void* ptr1, const void* ptr2, u64 n);
BEDROCK_FUNCTION u64 find_next_whitespace(const char* str);
BEDROCK_FUNCTION int rev_find_next_chr(const char* str, const char chr);
BEDROCK_FUNCTION int starts_with(const char* str, const char* pattern);
BEDROCK_FUNCTION int str_to_int(const char* str, const char delim, s64* val);
BEDROCK_FUNCTION char* trim_str(char* str);
BEDROCK_FUNCTION u64 bytes_len(const u8* val, const u64 len);
BEDROCK_INLINE_FUNCTION u64 __ceil(const u64 a, const u64 b);

/* -------------------------------------------------------------------------------------------------------- */
BEDROCK_FUNCTION u8 bit_size(const u8 val) {
	u8 size = 8;
	for (s8 i = size - 1; i >= 0; --i) {
		if (GET_BIT(val, i)) break;
		size--;
	}
	return size;
}

BEDROCK_FUNCTION u64 str_len(const char* str) {
    if (str == NULL) return 0;
    const char* str_c = str;
	while (*str++);
    return (u64) (str - str_c - 1);
}

BEDROCK_FUNCTION void* mem_cpy(void* dest, const void* src, const u64 size) {
	if (dest == NULL || src == NULL) return NULL;
	for (u64 i = 0; i < size; ++i) CAST_PTR(dest, u8)[i] = CAST_PTR(src, u8)[i];
	return dest;
}

BEDROCK_FUNCTION void mem_set_var(void* ptr, const int value, const u64 size, const u64 val_size) {
	if (ptr == NULL) return;
	for (u64 i = 0; i < size; ++i) CAST_PTR(ptr, u8)[i] = CAST_PTR(&value, u8)[i % val_size]; 
	return;
}

BEDROCK_FUNCTION char* reverse_str(char* str) {
    const u64 len = str_len(str);
    for (u64 i = 0; i < (len / 2); ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return str;
}

BEDROCK_FUNCTION void* mem_move(void* dest, const void* src, u64 size) {
    if (dest == NULL || src == NULL || size == 0) return NULL;
    
	size_t s = size;
	u8* temp = (u8*) bedrock_calloc(size, sizeof(u8));
	if (temp == NULL) {
		BEDROCK_WARNING_LOG("Failed to allocate the temp buffer for mem_move.\n");
		return NULL;
	}
	
	u8* dp = CAST_PTR(dest, u8);
	u8* sp = (u8*) src;

	while (size--) *temp++ = *sp++;
	temp -= s, size = s;
	while (s--)	*dp++ = *temp++;
	
	bedrock_free(temp - size);
    
    return dest;
}

BEDROCK_FUNCTION char* str_cpy(char* dest, const char* src) {
	if (dest == NULL || src == NULL) return NULL;
	char* const o_dest = dest;
  	while ((*dest++ = *src++));
	return o_dest;
}

BEDROCK_FUNCTION int str_tok(const char* str, const char* delim) {
	const u64 len = str_len(str);
     for (u64 i = 0, j = 0; i <= len; ++i) {
         if (delim[j] == str[i]) {
            if ((j + 1) == str_len(delim)) return i - j;
            j++;
         } else if (j > 0) i -= j, j = 0;
    }
    return -1;
}

BEDROCK_FUNCTION char* to_hex_str(char* str, const u8* byte_str, const u64 byte_size) {
    char* const str_base = str;
	for (u64 j = 0; j < byte_size; ++j) {
        *str++ = HEX_TO_CHR_CAP((byte_str[j] >> 4) & 0xF);
        *str++ = HEX_TO_CHR_CAP(byte_str[j] & 0xF);
    }
    *str = '\0';
    return str_base;
}

BEDROCK_FUNCTION char* to_dec_str(char* str, const u8* byte_str, const u64 byte_size) {
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
	
	return str_base;
}

BEDROCK_FUNCTION char* to_bit_str(char* str, const u8* byte_str, const u64 byte_size) {
	char* const str_base = str;
    for (u64 j = 0; j < byte_size; ++j) {
		for (int i = 7; i >= 0; ++i) {
			*str++ = NUM_TO_CHR(GET_BIT(byte_str[i], i));
		}
	}
    *str = '\0';
    return str_base;
}

BEDROCK_FUNCTION unsigned int ref_chr_cnt(const char* str, const unsigned int len, const char chr) {
	unsigned int ref_cnt = 0;
	if (str == NULL) return 0;
	for (unsigned int i = 0; i < len; ++i) {
		if (str[i] == chr) ref_cnt++;
	}
	return ref_cnt;
}

BEDROCK_FUNCTION int str_cmp(const char* str1, const char* str2) {
    // Null Checks
    if (str1 == NULL && str2 == NULL) return 0;
    if (str1 == NULL) return -1;
    else if (str2 == NULL) return 1;

    for (; *str1 || *str2; ++str1, ++str2) {
        if (*str1 != *str2) return (int) (*str1 - *str2);
    }
    
	return 0;
}

BEDROCK_FUNCTION int str_n_cmp(const char* str1, const char* str2, const u64 n) {
    // Null Checks
    if (str1 == NULL && str2 == NULL) return 0;
    if (str1 == NULL) return -1;
    else if (str2 == NULL) return 1;

	for (u64 i = 0; (str1[i] || str2[i]) && i < n; ++i) {
        if (str1[i] != str2[i]) return (int) (str1[i] - str2[i]);
    }

	return 0;
}

BEDROCK_FUNCTION void reverse_str_arr(char*** str_arr, const u64 size) {
	for (u64 i = 0; i < (size >> 1); ++i) {
		char* temp = (*str_arr)[i];
		(*str_arr)[i] = (*str_arr)[size - 1 - i];
		(*str_arr)[size - 1 - i] = temp;
	}
	return;
}

// TODO: Maybe should return the full bytes copied instead of -1 (as that's what would have been done in that case)
BEDROCK_FUNCTION int mem_copy_until(char* dest, const char* src, const char chr) {
	const char* orig_src = src;
	while (*src != chr && *src) *dest++ = *src++;
	if (*src) return -1;
	return (int) (src - orig_src);
}

BEDROCK_FUNCTION int mem_n_cmp(const void* ptr1, const void* ptr2, u64 n) {
    // Null Checks
    if (ptr1 == NULL && ptr2 == NULL) return 0;
    if (ptr1 == NULL) return -1;
    else if (ptr2 == NULL) return 1;

    const u8* a = CAST_PTR(ptr1, u8);
    const u8* b = CAST_PTR(ptr2, u8);
	while (n--) {
		if (*a++ != *b++) return *(a - 1) - *(b - 1);
	}

	return 0;
}

BEDROCK_FUNCTION u64 find_next_whitespace(const char* str) {
	if (str == NULL) return 0;
	const char* const str_base = str;
	while (!IS_WHITESPACE(*str)) ++str;
	return (u64) (str - str_base - 1);
}

BEDROCK_FUNCTION int rev_find_next_chr(const char* str, const char chr) {
	if (str == NULL) return -2;
	u64 len = str_len(str);
	while ((str[len] != chr) && len > 0) --len;
	return len;
} 

BEDROCK_FUNCTION int starts_with(const char* str, const char* pattern) {
	if (str == NULL || pattern == NULL) return FALSE;
	for (; *str && *pattern; ++str, ++pattern) {
		if (*str != *pattern) return FALSE;
	}
	if (*str == '\0' && *pattern != '\0') return FALSE;
	return TRUE;
}

BEDROCK_FUNCTION int str_to_int(const char* str, const char delim, s64* val) {
	bool is_neg = FALSE;
	bool is_hex = FALSE;
	
	while (IS_WHITESPACE(*str)) str++;

	if (*str == '-') is_neg = TRUE, str++;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) is_hex = TRUE, str += 2;

	*val = 0;

	u8 base = is_hex ? 16 : 10;
	while (*str != delim && *str) {
		if (IS_A_NUM(*str)) *val += CHR_TO_NUM(*str);
		else if (is_hex && IS_A_HEX_VAL(*str)) *val += CHR_TO_HEX(*str);
		else return -1;
		
		*val *= (str++, *str != delim && *str) * base + (*str == delim || *str == '\0');
	}

	if (is_neg) *val *= -1;

	return 0;
}

BEDROCK_FUNCTION char* trim_str(char* str) {
	if (str == NULL) return str;
	u64 len = str_len(str);

	// Trim right 
	u64 ind = 0;
	while (IS_WHITESPACE(str[ind])) ++ind;
	for (u64 i = 0, j = ind; j <= len; ++i, ++j) str[i] = str[j];  

	// Trim left
	for (s64 i = len - ind - 1; (i >= 0) && IS_WHITESPACE(str[i]); --i) {
		str[i] = '\0';
	}

	return str;
}

BEDROCK_FUNCTION u64 bytes_len(const u8* val, const u64 len) {
	u64 bytes_len = len;
	for (s64 i = len - 1; i >= 0 && val[i] == 0; --i, --bytes_len);
	return bytes_len;
}

BEDROCK_INLINE_FUNCTION u64 __ceil(const u64 a, const u64 b) {
	u64 c = (a - (a % b)) / b;
	if (a % b) c++;
	return c;
}

#endif //_BEDROCK_BASE_H_

