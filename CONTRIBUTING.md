# LAUNCH - How to Contribute

## Part I - Issues

### First Things First

- Check the existing issues.
- Tell us your compiler and compiling options.

### Reproducing

You know what's going on and you gave us the most essential part.  
Or, if you don't:  
You don't know what exactly is going on but you gave us the most suspicious part.  
Or, if you don't:  
You don't know what's going on. You gave us the entire code.

## Part II - The Style Guide

### Identifiers

#### Variables, Functions & Classes

`snake_case`, with a few extra rules.  
1. Especially for class names, the name shouldn't be the same as names in standard libraries. For example, `duration` -> `timespan`.  
2. Especially for helper class names, use the main classes' names as prefixes. For example, `oper_type` -> `hedgehog_opertype`.  
3. Abbreviate names just right. For example, `arint_special_value` -> `arint_specval`.

#### Concepts

`Like_This`.

#### Constants & Macros

`SCREAMING_SNAKE_CASE`.

### Indentations & Formatting

#### Indentations

Use tabs. If possible, make them 4 spaces in width.

#### Formatting

- Always use braces (`{}`).
- There mustn't be anything after a semicolon (`;`), except comments and the three statements in `for` loops.

### Miscellaneous

#### Preprocessors

1. Use `#if defined(...)` and `#if !defined(...)` instead of `#ifdef` and `#ifndef`.  
2. No `#define`, thank you.

#### Member Things

- Use `this->foo` or `this->foo()` if `foo` is `public`.
- Use `bar` or `bar()` if `bar` is `private` or `protected`.
- Use `_Baz` instead of `baz` if it is a `private` or `protected` member function.

#### Templates

Use `template <typename T>` instead of `template <class T>`, even though they're the same.