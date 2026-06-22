> [!NOTE]
> Disambiguation: you might be looking for `genev_(header).md` instead of `genev_(class).md`.

# `genev`
<small>Defined in `genev_impl.h`</small>

## `class genev;`
`genev` is a physical quantity class.

### Data members
|Member|Value|
|---|---|
|<small style="color: lightgray;">[static]</small> `dim_count`|`9`|
|<small style="color: lightgray;">[static]</small> `prefix_count`|`14`|

### Member functions
|Function|Description|
|---|---|
|(constructor)|constructs `genev` object<br><small>(public member function)</small>|
|(destructor)|destroys `genev` object<br><small>(public member function)</small>|
|`operator+=`<br>`operator-=`<br>`operator*=`<br>`operator/=`<br>`operator^=`|compound assignments of two `genev`s<br><small>(public member functions)</small>|
|`operator+`<br>`operator-`|apply unary operators to `genev`s<br><small>(public member functions)</small>|
|`operator<=>`<br>`operator==`|compare two `genev`s<br><small>(public member functions)</small>|
|`value`|returns the value part<br><small>(public member function)</small>|
|`unit`|returns the unit part<br><small>(public member function)</small>|

### Non-member functions
|Function|Description|
|---|---|
|`operator+`<br>`operator-`<br>`operator*`<br>`operator/`<br>`operator^`|perform arithmetic on two `genev`s|
|`operator<<`<br>`operator>>`|serialize and deserialize the quantity|

### Note
`genev::operator^=` and `operator^` are not bitwise XOR.