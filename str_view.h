#ifndef SV_H
#define SV_H

#include <stdbool.h>
#include <stddef.h>

typedef struct StrView {
	const char *__buffer;
	size_t __size;
} StrView;

#define SV_FMT "%.*s"
#define SV_ARG(s) (int)(s).__size, (s).__buffer

/*
 * Returns an empty StrView.
 * The user can test if an StrView is empty
 * with the sv_is_empty function.
 */
StrView
sv_empty();

/*
 * Returns an StrView constructed from the
 * given pointer and size.
 *
 * The function doesn't
 * check for correctness, so if buf is "Hello" and
 * size is bigger than 6, the result is undefined.
 *
 * To construct an StrView from a null terminated
 * string safely, use sv_from_cstr.
 */
StrView
sv_from_parts(const char *buf, size_t size);

/*
 * Returns an StrView constructed from the range
 * [start, end).
 *
 * If end < start, the arguments are inverted, and
 * the StrView is constructed from the range [end, start).
 */
StrView
sv_from_slice(const char *start, const char *end);

/*
 * Returns an StrView constructed from the given string.
 *
 * The string *must* be null terminated, because the function
 * uses strlen to determine its length.
 */
StrView
sv_from_cstr(const char *buf);

/*
 * Returns the size of the view.
 *
 * Note that even if the view is constructed by a null
 * terminated const char *, the size will not account for
 * the '\0'. For example, if a view is constructed from
 * "Hello!", the size of the view will be 6.
 */
size_t
sv_size(StrView s);

/*
 * This function returns a pointer to the beginning
 * of the underlying buffer.
 *
 * WARNING: It is *not* recommended accessing the underlying
 * buffer in its raw form unless you know what you are doing.
 */
const char *
sv_to_cstr(StrView s);

/*
 * Returns the character in the idx-th position.
 * This function does *not* bounds-check.
 * For a safe alternative, use sv_at_s.
 */
char
sv_at(StrView s, size_t idx);

/*
 * If idx is less than the view's size, returns
 * 0 and assigns the idx-th character to c;
 * else returns -1.
 */
int
sv_at_s(StrView s, size_t idx, char *c);

/*
 * Returns a reference to the character in the
 * idx-th position. This function does *not* bounds-check.
 * For a safe alternative, use sv_at_ref_s.
 */
const char *
sv_at_ref(StrView s, size_t idx);

/*
 * If idx is less than the view's size, returns
 * 0 and assigns the reference to the idx-th character
 * to c; else returns -1.
 */
int
sv_at_ref_s(StrView s, size_t idx, const char **c);

/*
 * strcmp for StrView
 */
int
sv_cmp(StrView s1, StrView s2);

/*
 * Splits the view into the part before the delimiter and
 * the part after the delimiter, and assigns them to pre
 * and post respectively.
 *
 * If the delimiter is found in the view, the function returns
 * true, else it returns false.
 *
 * For example:
 *
 * `sv_split(sv_from_cstr("Hello!World", '!', &pre, &post);`
 *
 * will return true, and will assign "Hello" to pre, and "World" to post,
 * whereas
 *
 * `sv_split(sv_from_cstr("Hello World", '!', &prem &post);`
 *
 * will return false, and will assign "Hello World" to pre, and
 * post will get assigned an empty string starting at the character
 * after the end of s.
 *
 * Any or both of the pre and post args can be null.
 */
bool
sv_split(StrView s, char delim, StrView *pre, StrView *post);

/*
 * Same as sv_split, but only checks the first n characters for the delimiter
 */
bool
sv_split_n(StrView s, char delim, size_t n, StrView *pre, StrView *post);

/*
 * Checks if the size of s is zero.
 */
bool
sv_is_empty(StrView s);

/*
 * Checks if s contains the character c
 */
bool
sv_contains(StrView s, char c);

/*
 * Returns true if s contains the character c, and assigns its first occurrence
 * index to idx. Else, it returns false.
 *
 * idx can be null
 */
bool
sv_first_occ(StrView s, char c, size_t *idx);

/*
 * Returns true if s contains the character c, and assigns its last occurrence
 * index to idx. Else, it returns false.
 *
 * idx can be null
 */
bool
sv_last_occ(StrView s, char c, size_t *idx);

/*
 * Returns the number of occurrences of c in s
 */
size_t
sv_count(StrView s, char c);

/*
 * Returns true if prefix is a prefix of s, else returns false
 */
bool
sv_starts_with(StrView s, StrView prefix);

/*
 * Returns true if postfix is a postfix of s, else returns false
 */
bool
sv_ends_with(StrView s, StrView postfix);

#endif /* SV_H */
