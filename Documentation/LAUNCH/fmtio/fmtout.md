# `fmtout`
<small>Defined in `fmtio_impl.h`</small>

## `void fmtout(const std::string& fmt, const hedgehog& hh = {}, std::ostream& out = std::cout);`
Formats `hh` according to the format string `fmt`, and writes the result to `out`.

### Parameters
**`fmt`** - the format string. It consists of
- ordinary characters (except `{` and `}`), which are copied unchanged to the output,
- escape sequences `{{` and `}}`, which are replaced with `{` and `}` respectively in the output, and
- replacement fields.  
Each replacement field has the following format:  
<code>{ *arg-id* <small>(optional)</small> }</code>  
*`arg-id`* - specifies the index of the argument in args whose value is to be used for formatting; if it is omitted, the arguments are used in order.  
The *`arg-id`* s in a format string must all be present or all be omitted. Mixing manual and automatic indexing is an error.

**`hh`** - a `hedgehog` which contains the elements to be formatted.  
**`out`** - output stream to be written to.

### Return value
(none)

### Exceptions
Throws `std::runtime_error` if `fmt` is not a valid format string for the provided `hedgehog`.

### Complexity
Linear.