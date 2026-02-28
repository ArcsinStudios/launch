# `distrib_real`
<small>Defined in `goodrand_concepts.h`</small>

## `template <typename T> concept distrib_real = /* see below */;`
The concept `distrib_real` is satisfied if and only if `T` denotes one of the following types:
- `float`
- `double`
- `long double`

### Implementation
```
template <typename T>
concept distrib_real =
	std::is_same_v<float, T> ||
	std::is_same_v<double, T> ||
	std::is_same_v<long double, T>;
```