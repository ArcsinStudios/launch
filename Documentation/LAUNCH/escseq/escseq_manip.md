# `escseq_manip`
<small>Defined in `escseq_impl.h`</small>

## `class escseq_manip;`
`escseq_manip` is a wrapper around `std::string`.

### Global objects
|Object|Description|
|---|---|
|`reset_cursor`|resets cursor position|
|`show_cursor`|shows cursor|
|`hide_cursor`|hides cursor|
|`clear_front`|clears everything behind the cursor|
|`clear_back`|clears everything after the cursor|
|`clear_screen`|clears everything|
|`erase_front`|clears everything on this line behind the cursor|
|`erase_back`|clears everything on this line after the cursor|
|`erase_line`|clears everything on this line|
|`bold`|bold|
|`dim`|dim|
|`italic`|Italic|
|`underline`|underline|
|`blink`|blink|
|`inverse`|inverse|
|`hidden`|hidden|
|`strikethrough`|strikethrough|
|`reset_foreground`|resets foreground color|
|`reset_background`|resets background color|
|`reset_font`|resets font style *and* color|

### Member functions
|Function|Description|
|---|---|
|(constructor)|constructs `escseq_manip` object<br><small>(public member function)</small>|
|(destructor)|destroys `escseq_manip` object<br><small>(public member function)</small>|

### Non-member functions
|Function|Description|
|---|---|
|`operator<<`|serializes the escape sequence|