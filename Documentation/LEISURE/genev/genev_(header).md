> [!NOTE]
> Disambiguation: you might be looking for `genev_(class).md` instead of `genev_(header).md`.

# `genev`

## Global objects
<small>Defined in `genev_impl.h`</small>
|Object|Description|
|---|---|
|`unit_str_map`|maps a `base_unit` to `std::string`|
|`prefix_str_map`|maps a `unit_prefix` to `std::string`|
|`prefix_exp_map`|maps a `unit_prefix` to `signed char`|
|`str_unit_map`|maps a `std::string` to `base_unit`|
|`str_prefix_map`|maps a `std::string` to `unit_prefix`|
|`str_prefix_map_alt`|an alternative `str_prefix_map` for nonstandard time units|

## Type alias
<small>Defined in `genev_impl.h`</small>
|Alias|Actual type|
|---|---|
|`unit_type`|`std::tuple<unit_prefix, base_unit, long long>`|