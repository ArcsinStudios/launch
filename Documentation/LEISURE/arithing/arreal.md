# `arreal`
<small>Defined in `arithing_impl.h`</small>

## `class arreal;`
`arreal` is a rational type.

### Member functions
|Function|Description|
|---|---|
|(constructor)|constructs `arreal` object<br><small>(public member function)</small>|
|(destructor)|destroys `arreal` object<br><small>(public member function)</small>|
|`operator+=`<br>`operator-=`<br>`operator*=`<br>`operator/=`<br>`operator%=`|compound assignments of two `arreal`s<br><small>(public member functions)</small>|
|`operator+`<br>`operator-`|apply unary operators to `arreal`s<br><small>(public member functions)</small>|

### Non-member functions
|Function|Description|
|---|---|
|`operator+`<br>`operator-`<br>`operator*`<br>`operator/`<br>`operator%`|perform arithmetic on two `arreal`s|
|`operator<=>`<br>`operator==`|compare two `arreal`s|
|`operator<<`<br>`operator>>`|serialize and deserialize the value|
|`to_decimal`|converts an `arreal` to decimal|