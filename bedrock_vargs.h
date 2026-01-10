#ifndef _BEDROCK_VARGS_H_
#define _BEDROCK_VARGS_H_

/* -------------------------------------------------------------------------------------------------------- */
// ------------------------------
//  Variable Arguments Functions
// ------------------------------
#define MAX_NUM_LEN 65

// ------------------------
//  Functions Declarations
// ------------------------
BEDROCK_FUNCTION int bedrock_snprintf(char* str, const u64 size, const char* format, ...);
BEDROCK_FUNCTION int bedrock_vsnprintf(char* str, const u64 size, const char* format, const va_list args);
BEDROCK_FUNCTION_INLINE u64 hex_to_str(char* str, u64 val, const u64 size);
BEDROCK_FUNCTION_INLINE u64 oct_to_str(char* str, u64 val, const u64 size);
BEDROCK_FUNCTION_INLINE u64 dec_to_str(char* str, s64 val, const bool is_neg);

/* -------------------------------------------------------------------------------------------------------- */
// -----------------------
//  Functions Definitions
// -----------------------
BEDROCK_FUNCTION_INLINE u64 hex_to_str(char* str, u64 val, const u64 size) {
    u64 i = 0;                       
    for (i = 0; i < size * 2; ++i) {
		str[i] = HEX_TO_CHR_CAP(val & 0x0F);
		val >>= 4;
    }
    reverse_str(str);
	str[i] = '\0';
	return i;
}

BEDROCK_FUNCTION_INLINE u64 oct_to_str(char* str, u64 val, const u64 size) {
    u64 i = 0;                 
	u64 oct_size = (size * 8) / 3;
	for (i = 0; i < oct_size; ++i) {           
		str[i] = NUM_TO_CHR(val & 0x07); 
		val >>= 3;                       
    }                                    
	reverse_str(str);                    
	str[i] = '\0';                    
	return i;
}

BEDROCK_FUNCTION_INLINE u64 dec_to_str(char* str, s64 val, const bool is_neg) {
    if (is_neg) val = val * -1;
	
	u64 i = 0;                  
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

BEDROCK_FUNCTION int bedrock_snprintf(char* str, const u64 size, const char* format, ...) {
    va_list args;
    va_start(args, format);
	int ret = bedrock_vsnprintf(str, size, format, args);
    va_end(args);
    return ret;
}

BEDROCK_FUNCTION int bedrock_vsnprintf(char* str, const u64 size, const char* format, const va_list args) {
	if (str == NULL || format == NULL) return -1;
	
	u64 format_size = str_len(format);
	u64 str_index = 0;
	
	// TODO: Missing size checks for out-of-bound accesses
	for (u64 i = 0; (i <= format_size) && (str_index < size); ++i) {
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

BEDROCK_FUNCTION u8* concat(const u64 len, u64* size, ...) {
	va_list args;
    va_start(args, size);
	
	for (u64 i = 0; i < len; i += 2) {
		u8* element = va_arg(args, u8*);	
		(void) element;
		*size += va_arg(args, u64);
	}

	va_end(args);

	u8* concatenation = bedrock_calloc(*size, 1);
	if (concatenation == NULL) {
		BEDROCK_WARNING_LOG("Failed to allocate concatentation buffer of %llu bytes.", *size);
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

#endif //_BEDROCK_VARGS_H_

