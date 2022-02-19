# str_view

String View library for C

A string view is a constant character pointer coupled with a size. This eliminates the need for null terminating the
strings, and also allows for multiple string views to point to the same buffer without having to worry about strlen and
strcmp messing up due to the lack of a null terminator.

The struct provided is StrView which is defined as

 ```c
 struct StrView {
         const char *__buffer;
         size_t __size;
}
 ```

Also, two formatting helpers are provided, namely `SV_FMT` and `SV_ARG` which are meant to be used to print the views,
for example

 ```c
 StrView s1, s2;
 
 s1 = sv_from_cstr("Hello!");
 s2 = sv_from_parts(sv_at_ref(s1, 2), 3);
 
 printf("s1 = '" SV_FMT "'\n", SV_ARG(s1));
 printf("s2 = '" SV_FMT "'\n", SV_ARG(s2));
 ```

which prints `s1 = 'Hello!'` and `s2 = 'llo'`

It's important to note that accessing the buffer and using the standard libraries functions is not recommended, as it
can produce unwanted results. For example, if in the above example we were to do

 ```c
 printf("s2 = %s\n", s2.__buffer);
 ```

it would print `s2 = 'llo!'`, which is not what we would expect it to print.

Also note that this is *not* a dynamic string library. The code does no allocations anywhere, which is what makes it
fast and safe. A dynamic string library is on the works.

# Quick Start

Clone the repo in your project

```shell
git clone https://github.com/nikos-alexandris/str_view
```

and simply include the `str_view.h` header

 ```c
 #include "str_view/str_view.h"
 ```
