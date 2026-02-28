# `fmtin_single`
<small>Defined in `fmtio_impl.h`</small>

## `template <readable T> void fmtin_single(T& x, std::istream& in = std::cin)`
Reads one element with type `T` from `in` and puts it into `x`.  
The program is ill-formed if `readable<T>` is `false`.

### Template parameter
**`T`** - type of the element to be read.

### Parameters
**`x`** - variable to be filled.  
**`in`** - input stream to be read.

### Return value
(none)

### Complexity
Constant.