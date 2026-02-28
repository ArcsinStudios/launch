# `fmtin_deduce_auto`
<small>Defined in `exfmtio_impl.h`</small>

## `void fmtin_deduce_auto(launch::hedgehog& hh, size_t count = 1, std::istream& in = std::cin);`
Calls `fmtin_deduce<int, long long, unsigned long long, double, char, bool>()`.

### Parameters
**`hh`** - the target `hedgehog` to be filled.  
**`count`** - number of the elements to be read.  
**`in`** - the input stream to be read.

### Return value
(none)

### Complexity
Linear.