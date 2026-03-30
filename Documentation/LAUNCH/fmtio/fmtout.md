# `fmtout`
<small>Defined in `fmtio_impl.h`</small>

## `void fmtout(const std::string& fmt, const hedgehog& cont = {}, bool raw = false, std::ostream& out = std::cout);`
Formats `cont` according to the format string `fmt`, and writes the result to `out`.

### Parameters
**`fmt`** - the format string. It consists of
- ordinary characters (except `{`, `}`, `[`, `]` and `|`), which are copied unchanged to the output,
- escape sequences `{{`, `}}`, `[[`, `]]` and `||`, which are replaced with `{`, `}`, `[`, `]` and `|` respectively in the output,
- placeholders `|`, which are discarded in the output and could be used to prevent greedy matching, and
- replacement fields.  
Each replacement field has the following format:  
<code>{ *elem-id* <small>(optional)</small> }</code>  
Represents a single element in `cont`.  
*`elem-id`* - specifies the index of the element in `cont` whose value is to be used for formatting; if it is omitted, the elements are used in order.  
The *`elem-id`* s in a format string must all be present or all be omitted. Mixing manual and automatic indexing is an error.  
<code>[ *separator* ]</code>  
Represents all elements in `cont`.  
*`separator`* - specifies the separator between elements in `cont`. Placeholders and escape sequences are also applicable to *`separator`*.  
Mixing brackets and braces is an error. Using multiple pairs of brackets is also an error.

**`cont`** - the `hedgehog` which contains the elements to be formatted.  
**`raw`** - indicates if `fmt` will be written as-is.  
**`out`** - the output stream to be written to.

### Return value
(none)

### Exceptions
Throws `std::format_error` if `fmt` is not a valid format string for the provided `hedgehog`.

### Complexity
Linear.