# `escseq_style`
<small>Defined in `escseq_impl.h`</small>

## `enum class escseq_style : unsigned char;`
`escseq_style` specifies the font style.

### Enumerations
|Enumeration|Value|
|---|---|
|`bold`|`0b00000001`|
|`dim`|`0b00000010`|
|`italic`|`0b00000100`|
|`underline`|`0b00001000`|
|`blink`|`0b00010000`|
|`inverse`|`0b00100000`|
|`hidden`|`0b01000000`|
|`strikethrough`|`0b10000000`|

### Note
`escseq_style` is not a [`BitmaskType`](https://en.cppreference.com/w/cpp/named_req/BitmaskType "link to en.cppreference.com").