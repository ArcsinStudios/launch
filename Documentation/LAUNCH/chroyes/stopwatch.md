# `stopwatch`
<small>Defined in `chroyes_impl.h`</small>

## `class stopwatch;`
`stopwatch` is a stopwatch class which can pause and resume timing.

### Member functions
|Function|Description|
|---|---|
|(constructor)|constructs `stopwatch` object<br><small>(public member function)</small>|
|(destructor)|destroys `stopwatch` object<br><small>(public member function)</small>|

#### Timing
|Function|Description|
|---|---|
|`start`|start timing<br><small>(public member function)</small>|
|`stop`|stop timing<br><small>(public member function)</small>|
|`pause`|pause timing<br><small>(public member function)</small>|
|`resume`|resume timing<br><small>(public member function)</small>|

#### Value access
|Function|Description|
|---|---|
|`get_dur`|get the time elapsed between the most recent start and stop, excluding the duration of pauses<br><small>(public member function)</small>|