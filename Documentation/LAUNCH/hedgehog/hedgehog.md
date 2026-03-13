# `hedgehog`

## Concepts
<small>Defined in `hedgehog_concepts.h`</small>
|Concept|Requirement(s)|
|---|---|
|`writable<T>`|`T` can be chainingly written using `std::ostream`|
|`arithmetic_preq<T>`|`T` is not a pointer type or `bool`|
|`arithmetic_add<T, U>`|both `T` and `U` satisfy `arithmetic_preq`, and the operation between `T` and `U` is supported or either of `T` and `U` is `std::string`|
|`arithmetic_sub<T, U>`<br>`arithmetic_mul<T, U>`<br>`arithmetic_div<T, U>`<br>`arithmetic_mod<T, U>`<br>|both `T` and `U` satisfy `arithmetic_preq`, and the operation between `T` and `U` is supported|
|`arithmetic<T, U>`|all four operations between `T` and `U` are supported|
|`fully_arithmetic<T, U>`|all five operations between `T` and `U` are supported|

## Type aliases
<small>Defined in `hedgehog_impl.h`</small>
|Alias|Actual type|
|---|---|
|`output_func_t`|`std::function<std::ostream&(std::ostream&, const std::any&)>`|
|`oper_func_t`|`std::function<std::any(const std::any&, const std::any&)>`|
|`output_reg_t`|`std::unordered_map<std::type_index, output_func_t>`|
|`oper_reg_t`|`std::unordered_map<hedgehog_opersign, oper_func_t>`|
|`hedgehog_alloc<Allocator>`|`std::vector<hedgehog_elemproxy, Allocator>`|
|`hedgehog`|`hedgehog_alloc<std::allocator<hedgehog_elemproxy>>`|