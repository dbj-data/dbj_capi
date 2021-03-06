#pragma once
#ifndef DBJ_WCWIDTH_INC
#define DBJ_WCWIDTH_INC
/*
 * DBJ changed back to C
 * defined in wcwidth.c
 */
#ifdef __cplusplus
namespace dbj::utf {
    extern "C" {
#endif  // __cplusplus
	/**
	 * @param ucs          utf32 char
	 *
	 */
	extern int dbj_wcwidth(char32_t ucs);
	/**
	 * Calculate a char32_t string width
	 * @param pwcs  utf32 string
	 * @param n    length of text to calculate
	 */
	extern int dbj_wcswidth(const char32_t* pwcs, size_t n);
	
#ifdef __cplusplus
    } // extern "C" 
} // namespace dbj::utf 
#endif  // 

#endif // !DBJ_WCWIDTH_INC

