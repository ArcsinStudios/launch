# `randgen_real`
<small>Defined in `goodrand_impl.h`</small>

## `template <distrib_real T> class randgen_real;`
`randgen_real` is a random number generator class.  
The program is ill-formed if `distrib_real<T>` is `false`.

### Template parameters
**`T`** - type of the random numbers to be generated.

### Member functions
|Function|Description|
|---|---|
|(constructor)|constructs `randgen_real` object<br><small>(public member function)</small>|
|(destructor)|destroys `randgen_real` object<br><small>(public member function)</small>|

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