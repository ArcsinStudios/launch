# `distrib_int`
<small>Defined in `goodrand_concepts.h`</small>

## `template <typename T> concept distrib_int = /* see below */;`
The concept `distrib_int` is satisfied if and only if `T` denotes one of the following types:
- `short`
- `int`
- `long`
- `long long`
- `unsigned short`
- `unsigned int`
- `unsigned long`
- `unsigned long long`

### Implementation
```
template <typename T>
concept distrib_int =
    std::is_same_v<short, T> ||
    std::is_same_v<int, T> ||
    std::is_same_v<long, T> ||
    std::is_same_v<long long, T> ||
    std::is_same_v<unsigned short, T> ||
    std::is_same_v<unsigned int, T> ||
    std::is_same_v<unsigned long, T> ||
    std::is_same_v<unsigned long long, T>;
```