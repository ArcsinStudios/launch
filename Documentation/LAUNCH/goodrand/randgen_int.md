# `randgen_int`
<small>Defined in `goodrand_impl.h`</small>

## `template <distrib_int T> class randgen_int;`
`randgen_int` is a random number generator class.  
The program is ill-formed if `distrib_int<T>` is `false`.

### Template parameters
**`T`** - type of the random numbers to be generated.

### Member functions
|Function|Description|
|---|---|
|(constructor)|constructs `randgen_int` object<br><small>(public member function)</small>|
|(destructor)|destroys `randgen_int` object<br><small>(public member function)</small>|

#### Generator
|Function|Description|
|---|---|
|`next`|generates the next random number|

#### Modifiers
|Function|Description|
|---|---|
|`seed`|sets engine seed|
|`set_range`|sets distribution range to [`min`, `max`]|
|`reset`|resets distribution|