# `hedgehog_elemproxy`
<small>Defined in `hedgehog_impl.h`</small>

## `class hedgehog_elemproxy;`
`hedgehog_elemproxy` is a wrapper around `std::any`.

### Member functions
|Function|Description|
|---|---|
|(constructor)|constructs `hedgehog_elemproxy` object<br><small>(public member function)</small>|
|(destructor)|destroys `hedgehog_elemproxy` object<br><small>(public member function)</small>|
|`operator+=`<br>`operator-=`<br>`operator*=`<br>`operator/=`<br>`operator%=`|compound assignments of two `hedgehog_elemproxy`s<br><small>(public member functions)</small>|

#### Getter
|Function|Description|
|---|---|
|`as`|gets the value as type `T`<br><small>(function template)</small>|

#### Observer
|Function|Description|
|---|---|
|`type`|gets the type<br><small>(public member function)</small>|
|`is`|checks if the type is `T`<br><small>(function template)</small>|

#### Assertion
|Function|Description|
|---|---|
|`throw_if_not`|throws `std::runtime_error` if the type is not `T`<br><small>(function template)</small>|

### Non-member functions
|Function|Description|
|---|---|
|`operator+`<br>`operator-`<br>`operator*`<br>`operator/`<br>`operator%`|perform arithmetic on two `hedgehog_elemproxy`s|
|`operator<<`|serializes the value|