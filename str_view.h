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

/**
 * @brief Returns an empty StrView.
 * @Example
 * @code
 * StrView s = sv_empty();
 * assert(sv_is_empty(s) == true);
 * @endcode
 */
StrView
sv_empty();

/**
 * @brief Creates an StrView from a pointer and a __size.
 * @Example
 * @code
 * StrView s = sv_from_parts("Hello!, 4);
 * assert(sv_eq(s, sv_from("Hell")));
 * @endcode
 *
 */
StrView
sv_from_parts(const char *buf, size_t size);

/**
 * @brief Creates an StrView from a pointer range.
 * @Example
 * @code
 * StrView s1 = sv_from("Hello!");
 * StrView s2 = sv_from_slice(sv_ref(s1, 0), sv_ref(s1, 3));
 * assert(sv_eq(s2, sv_from("Hell")));
 * @endcode
 */
StrView
sv_from_slice(const char *start, const char *end);

/**
 * @brief Creates an StrView from a null terminated c string.
 * @Undefined
 * Undefined behaviour if buf is NULL
 * @Warning buf @b must be null terminated, because the
 * function uses strlen to determine its length.
 * @Example
 * @code
 * StrView s = sv_from("Hello!");
 * assert(sv_size(s) == 6);
 * assert(strncmp(sv_raw(s), "Hello!", sv_size(s)) == 0);
 * @endcode
 */
StrView
sv_from(const char *buf);

/**
 * @brief Returns a pointer to the underlying __buffer.
 *
 * @Warning
 * Usage of this function is not recommended. If you
 * want a reference to a char in the string, use sv_ref.
 */
const char *
sv_raw(StrView s);

/**
 * @brief Returns the __size of s.
 *
 * @Example
 * @code
 * StrView s = sv_from("Hello!");
 * assert(sv_size(s) == 6);
 * @endcode
 */
size_t
sv_size(StrView s);

/**
 * @brief Returns the idx-th char in s.
 * @Undefined
 * Undefined behaviour if idx is less than or equal to the __size of s.
 * @Example
 * @code
 * StrView s = sv_from("Hello!");
 * assert(sv_at(s, 0) == 'H');
 * assert(sv_at(s, sv_size(s) - 1), '!');
 * @endcode
 */
char
sv_at(StrView s, size_t idx);

/**
 * @brief Returns a reference to the idx-th char in s
 * @Undefined
 * Undefined behaviour if idx is less than or equal to the __size of s.
 * @Example
 * @code
 * StrView s = sv_from("Hello!");
 * assert(*sv_ref(s, 0) == 'H');
 * assert(sv_ref(s, 0)[1] == 'e');
 * @endcode
 */
const char *
sv_ref(StrView s, size_t idx);

/**
 * @brief strcmp for StrView
 */
int
sv_cmp(StrView s1, StrView s2);

/**
 * Returns true if s1 == s2
 * @Example
 * @code
 * StrView s1 = sv_from("Hello!");
 * assert(sv_eq(s1, sv_from("Hello!")));
 * @endcode
 */
bool
sv_eq(StrView s1, StrView s2);

/**
 * @brief Splits s into the part before delim and the part after delim.
 * If delim is not found in s, pre is assigned the whole s string, and
 * post is assigned the empty string starting at the first character
 * after the end of s.
 * @Examples
 * @code
 * StrView s, l, r;
 * s = sv_from("Hello!World");
 * sv_split(s, '!', &l, &r);
 *
 * assert(sv_eq(l, sv_from("Hello")));
 * assert(sv_eq(r, sv_from("World")));
 * @endcode
 * @code
 * StrView s, l, r;
 * s = sv_from("Hello!World");
 * sv_split(s, '@', &l, &r);
 *
 * assert(sv_eq(l, s));
 * assert(sv_eq(r, sv_empty()));
 * assert(sv_raw(r) == &sv_raw(s)[sv_size(s)]);
 * @endcode
 */
bool
sv_split(StrView s, char delim, StrView *pre, StrView *post);

/**
 * @brief Splits s into the part before delim and the part after delim,
 * checking at most n characters. If delim is not found in the first n
 * characters of s, pre is assigned the whole s string, and
 * post is assigned the empty string starting at the first character
 * after the end of s.
 * @Examples
 * @code
 * StrView s, l, r;
 * s = sv_from("Hello!World");
 * sv_split_n(s, '!', 6, &l, &r);
 *
 * assert(sv_eq(l, sv_from("Hello")));
 * assert(sv_eq(r, sv_from("World")));
 * @endcode
 * @code
 * StrView s, l, r;
 * s = sv_from("Hello!World");
 * sv_split_n(s, '!', 5, &l, &r);
 *
 * assert(sv_eq(l, s));
 * assert(sv_eq(r, sv_empty()));
 * assert(sv_raw(r) == &sv_raw(s)[sv_size(s)]);
 * @endcode
 */
bool
sv_split_n(StrView s, char delim, size_t n, StrView *pre, StrView *post);

/**
 * @brief Checks if s is empty
 */
bool
sv_is_empty(StrView s);

/**
 * @brief Returns true if there is at least one one occurrence of c in s.
 * Returns false otherwise.
 */
bool
sv_contains(StrView s, char c);

/**
 * @brief Returns true if there is at least one occurrence of c in s
 * and assigns the index of its first occurrence to idx.
 * Returns false otherwise.
 */
bool
sv_find(StrView s, char c, size_t *idx);

/**
 * @brief Returns true if there is at least one occurrence of c in s and
 * assigns the index of its last occurrence to idx. Returns false
 * otherwise.
 */
bool
sv_rfind(StrView s, char c, size_t *idx);

/**
 * @brief Returns the number of occurrences of c in s.
 */
size_t
sv_count(StrView s, char c);

/**
 * @brief Returns true if prefix is a prefix of s.
 * Returns false otherwise.
 * @Examples
 * @code
 * StrView s = sv_from("Hello World!");
 *
 * assert(sv_starts_with(s, sv_from("Hello")));
 * assert(sv_starts_with(s, sv_from("")));
 * @endcode
 */
bool
sv_starts_with(StrView s, StrView prefix);

/**
 * @brief Returns true if postfix is a postfix of s
 * Returns false otherwise.
 * @Examples
 * @code
 * StrView s = sv_from("Hello World!");
 *
 * assert(sv_ends_with(s, sv_from("World!")));
 * assert(sv_ends_with(s, sv_from("")));
 * @endcode
 */
bool
sv_ends_with(StrView s, StrView postfix);

#endif /* SV_H */
