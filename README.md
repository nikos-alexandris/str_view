# str_view
 String View library for C
 
 A string view is a constant character pointer coupled with a size. This eliminates
 the need for null terminating the strings, and also allows for multiple string
 views to point to the same buffer without having to worry about strlen and strcmp
 messing up due to the lack of a null terminator.
 
 The struct provided is StrView which is defined as
 
 ```c
 struct StrView {
         const char *__buffer;
         size_t __size;
}
 ```
 
 Also, two formatting helpers are provided, namely `SV_FMT` and `SV_ARG` which are
 meant to be used to print the views, for example
 
 ```c
 StrView s1, s2;
 
 s1 = sv_from_cstr("Hello!");
 s2 = sv_from_parts(sv_at_ref(s1, 2), 3);
 
 printf("s1 = '" SV_FMT "'\n", SV_ARG(s1));
 printf("s2 = '" SV_FMT "'\n", SV_ARG(s2));
 ```
 
 which prints `s1 = 'Hello!'` and `s2 = 'llo'`
 
 It's important to note that accessing the buffer and using the standard libraries
 functions is not recommended, as it can produce unwanted results. For example, if
 in the above example we were to do 
 
 ```c
 printf("s2 = %s\n", s2.__buffer);
 ```
 it would print `s2 = 'llo!'`, which is not what we would expect it to print.
 
 Also note that this is *not* a dynamic string library. The code does no allocations
 anywhere, which is what makes it fast and safe. A dynamic string library is on the works.
 
 # Functions
 Below is a list of the provided functions (for now).
 Detailed descriptions of what each one of them does
 can be found as comments above each function in `str_view.h`
 
 ```c
 StrView
 sv_empty();
 ```
 
 ```c
 StrView
 sv_from_parts(const char *buf, size_t size);
 ```
 
 ```c
 StrView
 sv_from_slice(const char *start, const char *end);
 ```
 
 ```c
 StrView
 sv_from_cstr(const char *buf);
 ```
 
 ```c
 size_t
 sv_size(StrView s);
 ```
 
  ```c
 const char *
 sv_to_cstr(StrView s);
 ```
 
 ```c
 char
 sv_at(StrView s, size_t idx);
 ```
 
 ```c
 int
 sv_at_s(StrView s, size_t idx, char *c);
 ```
 
 ```c
 const char *
 sv_at_ref(StrView s, size_t idx);
 ```
 
 ```c
 int
 sv_at_ref_s(StrView s, size_t idx, const char **c);
 ```
 
 ```c
 int
 sv_cmp(StrView s1, StrView s2);
 ```
 
 ```c
 bool
 sv_split(StrView s, char delim, StrView *pre, StrView *post);
 ```
 
 ```c
 bool
 sv_split_n(StrView s, char delim, size_t n, StrView *pre, StrView *post);
 ```
 
 ```c
 bool
 sv_is_empty(StrView s);
 ```
 
 ```c
 bool
 sv_contains(StrView s, char c);
 ```
 
 ```c
 bool
 sv_first_occ(StrView s, char c, size_t *idx);
 ```
 
 ```c
 bool
 sv_last_occ(StrView s, char c, size_t *idx);
 ```
 
 ```c
 size_t
 sv_count(StrView s, char c);
 ```
 
 ```c
 bool
 sv_starts_with(StrView s, StrView prefix);
 ```
 
 ```c
 bool
 sv_ends_with(StrView s, StrView postfix);
 ```

 
 # Quick Start
 Just add the str_view.h and str_view.c files to your project and
 
 ```c
 #include "str_view/str_view.h"
 ```
