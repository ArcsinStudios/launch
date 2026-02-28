# `std::numeric_limits`
<small>Defined in `arithing_limits.h`</small>

## `std::numeric_limits<arint>`

### Member constants
|Constant|Value|
|---|---|
|`is_specialized`|`true`|
|`is_signed`|`true`|
|`is_integer`|`true`|
|`is_exact`|`true`|
|`has_infinity`|`true`|
|`has_quiet_NaN`|`true`|
|`has_signaling_NaN`|`false`|
|`has_denorm`|`std::denorm_absent`|
|`has_denorm_loss`|`false`|
|`round_style`|`std::round_toward_zero`|
|`is_iec559`|`false`|
|`is_bounded`|`true`|
|`is_modulo`|`false`|
|`digits`|`64`|
|`digits10`|`19`|
|`max_digits10`|`0`|
|`radix`|`2`|
|`min_exponent`|`0`|
|`min_exponent10`|`0`|
|`max_exponent`|`0`|
|`max_exponent10`|`0`|
|`traps`|`false`|
|`tinyness_before`|`false`|

### Member functions
|Function|Return value|
|---|---|
|min|-18446744073709551615 <small>(probable)</small>|
|lowest|-18446744073709551615 <small>(probable)</small>|
|max|18446744073709551615 <small>(probable)</small>|
|epsilon|0|
|round_error|0|
|infinity|inf|
|quiet_NaN|NaN|
|signaling_NaN|0|
|denorm_min|0|

## `std::numeric_limits<arreal>`

### Member constants
|Constant|Value|
|---|---|
|`is_specialized`|`true`|
|`is_signed`|`true`|
|`is_integer`|`false`|
|`is_exact`|`true`|
|`has_infinity`|`true`|
|`has_quiet_NaN`|`true`|
|`has_signaling_NaN`|`false`|
|`has_denorm`|`std::denorm_absent`|
|`has_denorm_loss`|`false`|
|`round_style`|`std::round_toward_zero`|
|`is_iec559`|`false`|
|`is_bounded`|`true`|
|`is_modulo`|`false`|
|`digits`|`0`|
|`digits10`|`0`|
|`max_digits10`|`0`|
|`radix`|`2`|
|`min_exponent`|`0`|
|`min_exponent10`|`0`|
|`max_exponent`|`0`|
|`max_exponent10`|`0`|
|`traps`|`false`|
|`tinyness_before`|`false`|

### Member functions
|Function|Return value|
|---|---|
|min|1/18446744073709551615 <small>(probable)</small>|
|lowest|-18446744073709551615 <small>(probable)</small>|
|max|18446744073709551615 <small>(probable)</small>|
|epsilon|1/18446744073709551615 <small>(probable)</small>|
|round_error|0|
|infinity|inf|
|quiet_NaN|NaN|
|signaling_NaN|0|
|denorm_min|0|