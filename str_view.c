#include "str_view.h"

#include <string.h>

StrView
sv_empty()
{
	return sv_from_parts(NULL, 0);
}

StrView
sv_from_parts(const char *buf, size_t size)
{
	return (StrView){.__buffer = buf, .__size = size};
}

StrView
sv_from_slice(const char *start, const char *end)
{
	const char *s, *e;

	if (start > end) {
		s = end;
		e = start;
	} else {
		s = start;
		e = end;
	}

	return sv_from_parts(s, (size_t)(e - s));
}

StrView
sv_from_cstr(const char *buf)
{
	return sv_from_parts(buf, strlen(buf));
}

size_t
sv_size(StrView s)
{
	return s.__size;
}

const char *
sv_to_cstr(StrView s)
{
	return s.__buffer;
}

const char *
sv_at_ref(StrView s, size_t idx)
{
	return &s.__buffer[idx];
}

int
sv_at_ref_s(StrView s, size_t idx, const char **c)
{
	if (idx >= sv_size(s))
		return -1;
	*c = sv_at_ref(s, idx);
	return 0;
}

char
sv_at(StrView s, size_t idx)
{
	return *sv_at_ref(s, idx);
}

int
sv_at_s(StrView s, size_t idx, char *c)
{
	const char *p;

	if (sv_at_ref_s(s, idx, &p) != 0)
		return -1;

	*c = *p;
	return 0;
}

int
sv_cmp(StrView s1, StrView s2)
{
	return strncmp(
	  s1.__buffer,
	  s2.__buffer,
	  sv_size(s1) > sv_size(s2) ? sv_size(s2) : sv_size(s1));
}

bool
sv_split(StrView s, char delim, StrView *pre, StrView *post)
{
	bool ret;
	size_t i;

	ret = false;
	for (i = 0; i < sv_size(s); i++) {
		if (sv_at(s, i) == delim) {
			ret = true;
			break;
		}
	}

	if (pre)
		*pre = sv_from_parts(sv_at_ref(s, 0), i - 1);

	if (post)
		*post = ret ? sv_from_parts(sv_at_ref(s, i + 1), sv_size(s) - i)
			    : sv_from_parts(sv_at_ref(s, sv_size(s)), 0);

	return ret;
}

bool
sv_split_n(StrView s, char delim, size_t n, StrView *pre, StrView *post)
{
	bool ret;
	size_t i;

	ret = false;
	for (i = 0; i < (n < sv_size(s) ? n : sv_size(s)); i++) {
		if (sv_at(s, i) == delim) {
			ret = true;
			break;
		}
	}

	if (pre)
		*pre = ret ? sv_from_parts(s.__buffer, i - 1) : s;

	if (post)
		*post = ret ? sv_from_parts(sv_at_ref(s, i + 1), sv_size(s) - i)
			    : sv_from_parts(sv_at_ref(s, sv_size(s)), 0);

	return ret;
}

bool
sv_is_empty(StrView s)
{
	return sv_size(s) == 0;
}

bool
sv_contains(StrView s, char c)
{
	size_t i;

	for (i = 0; i < sv_size(s); i++)
		if (sv_at(s, i) == c)
			return true;

	return false;
}

bool
sv_first_occ(StrView s, char c, size_t *idx)
{
	size_t i;

	for (i = 0; i < sv_size(s); i++)
		if (sv_at(s, i) == c) {
			if (idx)
				*idx = i;
			return true;
		}

	return false;
}

bool
sv_last_occ(StrView s, char c, size_t *idx)
{
	size_t i;

	for (i = sv_size(s); i > 0; i--)
		if (sv_at(s, i - 1) == c) {
			if (idx)
				*idx = i - 1;
			return true;
		}

	return false;
}

size_t
sv_count(StrView s, char c)
{
	size_t i, cnt;

	cnt = 0;
	for (i = 0; i < sv_size(s); i++)
		if (sv_at(s, i) == c)
			cnt++;

	return cnt;
}

bool
sv_starts_with(StrView s, StrView prefix)
{
	size_t i;

	if (sv_size(prefix) > sv_size(s))
		return false;

	for (i = 0; i < sv_size(prefix); i++)
		if (sv_at(s, i) != sv_at(prefix, i))
			return false;

	return true;
}

bool
sv_ends_with(StrView s, StrView postfix)
{
	size_t i, j;

	if (sv_size(postfix) > sv_size(s))
		return false;

	for (i = sv_size(s), j = sv_size(postfix); j > 0; i--, j--)
		if (sv_at(s, i - 1) != sv_at(postfix, j - 1))
			return false;

	return true;
}
