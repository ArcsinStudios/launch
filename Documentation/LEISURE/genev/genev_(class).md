> [!NOTE]
> Disambiguation: you might be looking for `genev_(header).md` instead of `genev_(class).md`.

# `genev`
<small>Defined in `genev_impl.h`</small>

## `class genev;`
`genev` is a physical quantity class.

### Member functions
|Function|Description|
|---|---|
|(constructor)|constructs `genev` object<br><small>(public member function)</small>|
|(destructor)|destroys `genev` object<br><small>(public member function)</small>|
|`operator+=`<br>`operator-=`<br>`operator*=`<br>`operator/=`|compound assignments of two `genev`s<br><small>(public member functions)</small>|
|`operator+`<br>`operator-`<br>`operator*`<br>`operator/`|perform arithmetic on two `genev`s<br><small>(public member functions)</small>|
|`operator+`<br>`operator-`|apply unary operators to `genev`s<br><small>(public member functions)</small>|
|`operator<=>`<br>`operator==`|compare two `genev`s<br><small>(public member functions)</small>|
|`same_unit`|tells if two `genev`s are of the same unit<br><small>(private member function)</small>|

### Non-member functions
|Function|Description|
|---|---|
|`operator<<`<br>`operator>>`|serialize and deserialize the quantity|
|`unify`|converts the unit into a combination of SI base units|
|`simplify`|simplifies the unit|
|`convert`|converts the quantity into a specific unit|