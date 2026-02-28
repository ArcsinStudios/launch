# `timespan`
<small>Defined in `chroyes_impl.h`</small>

## `class timespan;`
`timespan` is a wrapper around `std::chrono::duration`.

### Member functions
|Function|Description|
|---|---|
|(constructor)|constructs `timespan` object<br><small>(public member function)</small>|
|(destructor)|destroys `timespan` object<br><small>(public member function)</small>|
|`operator=`|assigns `timespan` object<br><small>(public member function)</small>|

#### Value access
|Function|Description|
|---|---|
|`seconds`|get the stored time in seconds<br><small>(public member function)</small>|
|`milliseconds`|get the stored time in milliseconds<br><small>(public member function)</small>|
|`microseconds`|get the stored time in microseconds<br><small>(public member function)</small>|
|`nanoseconds`|get the stored time in nanoseconds<br><small>(public member function)</small>|
|`std_nanoseconds`|get the stored time in `std::chrono::nanoseconds`<br><small>(public member function)</small>|