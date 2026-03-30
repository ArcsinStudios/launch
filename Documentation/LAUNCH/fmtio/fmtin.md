# `fmtin`
<small>Defined in `fmtio_impl.h`</small>

## `template <readable... Ts> void fmtin(hedgehog& cont, std::istream& in = std::cin)`
Reads elements with types `Ts...` from `in` and puts them into `cont`.  
The program is ill-formed if any of `Ts...` does not satisfy the concept `readable`.

### Template parameter
**`Ts`** - types of the elements to be read.

### Parameters
**`cont`** - the target `hedgehog` to be filled.  
**`in`** - the input stream to be read.

### Return value
(none)

### Complexity
Linear.

### Helper function
|Function|Description|
|---|---|
|`fmtin_process`|reads a single element with type `T`<br><small>(function template)</small>|