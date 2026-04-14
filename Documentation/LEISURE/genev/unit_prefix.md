# `unit_prefix`
<small>Defined in `genev_impl.h`</small>

## `enum class unit_prefix : unsigned char;`
`unit_prefix` specifies an SI prefix.

### Enumerations
|Enumeration|Multiplier|Note (if applicable)|
|---|---|---|
|`G`|10<sup>9</sup>|N/A|
|`M`|10<sup>6</sup>|N/A|
|`k`|10<sup>3</sup>|N/A|
|`h`|10<sup>2</sup>|N/A|
|`da`|10<sup>1</sup>|N/A|
|`none`|10<sup>0</sup>|This is a technical prefix and does not stand for a literal "none".|
|`d`|10<sup>-1</sup>|N/A|
|`c`|10<sup>-2</sup>|N/A|
|`m`|10<sup>-3</sup>|N/A|
|`u`|10<sup>-6</sup>|\<genev\> uses "u" instead of the Greek letter Mu in order to be ASCII-friendly.|
|`n`|10|10<sup>-9</sup>|N/A|