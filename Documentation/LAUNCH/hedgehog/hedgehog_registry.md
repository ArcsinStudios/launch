# `hedgehog_registry`
<small>Defined in `hedgehog_impl.h`</small>

## `class hedgehog_registry;`
`hedgehog_registry` is a registry class.

### Global objects
|Object|Description|
|---|---|
|`hreg`|global `hedgehog_registry` instance|

### Member functions
|Function|Description|
|---|---|
|(constructor)|constructs `hedgehog_registry` object<br><small>(public member function)</small>|
|(destructor)|destroys `hedgehog_registry` object<br><small>(public member function)</small>|

#### Registrations
|Function|Description|
|---|---|
|`regtype_output`|registers output function<br><small>(public member function)</small>|
|`regtype_oper`<br>`regtype_add`<br>`regtype_sub`<br>`regtype_mul`<br>`regtype_div`<br>`regtype_mod`|register operation functions<br><small>(public member functions)</small>|
|`regtype_output_auto`|registers output function automatically<br><small>(public member function)</small>|
|`regtype_add_auto`<br>`regtype_sub_auto`<br>`regtype_mul_auto`<br>`regtype_div_auto`<br>`regtype_mod_auto`|register operation functions automatically<br><small>(function templates)</small>|
|`regtype_4ops_auto`<br>`regtype_5ops_auto`|register multiple operation functions automatically<br><small>(function templates)</small>|
|`regtype_add_auto_rev`<br>`regtype_sub_auto_rev`<br>`regtype_mul_auto_rev`<br>`regtype_div_auto_rev`<br>`regtype_mod_auto_rev`|register operation functions automatically and in reverse<br><small>(function templates)</small>|
|`regtype_4ops_auto_rev`<br>`regtype_5ops_auto_rev`|register multiple operation functions automatically and in reverse<br><small>(function templates)</small>|
|`regtype_helper_process`|helper function of `regtype_helper`<br><small>(function template)</small>|
|`regtype_helper`|registers all possible output and operation functions between every possible pair of (T1, T2) in the template parameters<br><small>(function template)</small>|

#### Lookups
|Function|Description|
|---|---|
|`output_func_it`|looks up the corresponding output function of a given `std::type_index`<br><small>(public member function)</small>|
|`oper_func_it`|looks up the corresponding operation function of a given `hedgehog_opersign`<br><small>(public member function)</small>|
|`output_reg_end`|returns `output_reg.end()`<br><small>(public member function)</small>|
|`oper_reg_end`|returns `oper_reg.end()`<br><small>(public member function)</small>|

### Helper classes
|Class|Description|
|---|---|
|`hedgehog_opertype`|specifies the operation type|
|`hedgehog_opersign`|represents an operation signature|
|`std::hash<hedgehog_opersign>`|hash of `hedgehog_opersign`|