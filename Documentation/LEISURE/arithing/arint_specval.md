# `arint_specval`
<small>Defined in `arithing_impl.h`</small>

## `enum class arint_specval : unsigned char;`
`arint_specval` specifies the special values of `arint`.

### Enumerations
|Enumeration|Value|
|---|---|
|`nop`|`0b0000`|
|`neg`|`0b0001`|
|`nan`|`0b0010`|
|`inf`|`0b0100`|

### Note
`arint_specval` is not a [`BitmaskType`](https://en.cppreference.com/w/cpp/named_req/BitmaskType "link to en.cppreference.com").