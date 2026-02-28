# `fmtin_deduce`
<small>Defined in `exfmtio_impl.h`</small>

## `template <readable... Ts> void fmtin_deduce(launch::hedgehog& hh, size_t count = 1, std::istream& in = std::cin);`
Reads `count` elements from `in` and puts them into `hh`; types of the elements will be deduced automatically.  
The program is ill-formed if any of `Ts...` does not satisfy the concept `readable`.

### Template parameters
**`Ts`** - candidate types to be tried. If all attempts to deduce the type failed, the type will be deduced as `std::string`.

### Parameters
**`hh`** - the target `hedgehog` to be filled.  
**`count`** - number of the elements to be read.  
**`in`** - the input stream to be read.

### Return value
(none)

### Complexity
Quadratic.

### Helper function
|Function|Description|
|---|---|
|`fmtin_deduce_process`|tries to deduce the type as `T`|
|`fmtin_deduce_single`|reads one element and deduces its type|