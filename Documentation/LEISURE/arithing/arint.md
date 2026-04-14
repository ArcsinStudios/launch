# `arint`
<small>Defined in `arithing_impl.h`</small>

## `class arint;`
`arint` is a big integer class.

### Member functions
|Function|Description|
|---|---|
|(constructor)|constructs `arint` object<br><small>(public member function)</small>|
|(destructor)|destroys `arint` object<br><small>(public member function)</small>|
|`operator+=`<br>`operator-=`<br>`operator*=`<br>`operator/=`<br>`operator%=`<br>`operator^=`|compound assignments of two `arint`s<br><small>(public member functions)</small>|
|`operator++`<br>`operator++(int)`<br>`operator--`<br>`operator--(int)`|apply increment and decrement to `arint`s<br><small>(public member functions)</small>|
|`operator+`<br>`operator-`|apply unary operators to `arint`s<br><small>(public member functions)</small>|

### Non-member functions
|Function|Description|
|---|---|
|`operator+`<br>`operator-`<br>`operator*`<br>`operator/`<br>`operator%`<br>`operator^`|perform arithmetic on two `arint`s|
|`operator<=>`<br>`operator==`|compare two `arint`s|
|`operator<<`<br>`operator>>`|serialize and deserialize the value|
|`abs`<br>`sign`|get the absolute value and sign of an `arint`|
|`nan`<br>`inf`|tells if an `arint` is NaN or infinite|

### Note
`operator^=` and `operator^` are *not* bitwise XOR.