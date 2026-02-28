# `readable`
<small>Defined in `fmtio_concepts.h`</small>

## `template <typename T> concept readable = /* see below */;`
The concept `readable` is satisfied if and only if a variable with type `T` can be chainingly read using `std::istream`.

### Implementation
```
template <typename T>
concept readable = requires(std::istream& in, T& x) {
    { in >> x } -> std::same_as<std::istream&>;
};
```