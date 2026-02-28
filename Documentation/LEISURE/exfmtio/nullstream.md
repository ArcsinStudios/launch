# `nullstream`
<small>Defined in `exfmtio_impl.h`</small>

## `class nullstream : public std::ostream;`
`nullstream` is an output stream class derived from `std::ostream` and all writes to it will be discarded.

### Global objects
|Object|Description|
|---|---|
|`nullout`|global `nullstream` instance|

### Helper classes
|Class|Description|
|---|---|
|`nullbuf`|null buffer|