# LAUNCH - How to Contribute

## Part I - Issues

### First Things First

- Check the existing issues.
- Tell us your compiler and compiling options.

### Reproducing

You know what's going on and you gave us the most essential part.  
Or, if you don't:  
You don't know what **exactly** is going on but you gave us the **most** **suspicious** part.  
Or, if you don't:  
You don't know what's going on. You gave us the entire code.

## Part II - Pull Requests

### First Things First - The Style Guide

#### Identifiers

##### Variables, Functions & Classes

`snake_case`, with a few extra rules.  
1. Especially for class names, the name shouldn't be the same as names in standard libraries. For example, `duration` -> `timespan`.  
2. Especially for helper class names, the name shouldn't be too common. In this case, use prefixes. For example, `oper_type` -> `hedgehog_opertype`.  
3. Abbreviate names just right. For example, `arint_special_value` -> `arint_specval`.

##### Constants & Macros

`SCREAMING_SNAKE_CASE`.

#### Indentations & Formatting

##### Indentations

Use tabs. If possible, make them 4 spaces in width.

##### Formatting

- Always use braces (`{}`).
- There mustn't be anything after a semicolon (`;`), except comments and the three statements in `for` loops.

#### Preprocessors

##### About `#if`, `ifdef` & `#ifndef`

Use `#if defined(...)` and `#if !defined(...)` instead of `#ifdef` and `#ifndef`.

##### About `#define`

Never, unless you `#undef`-ed it after use. Thank you.

#### Miscellaneous

##### Member Function Calls

When calling other member functions in a member function:
- If the function called is a `public` function, then use `this->foo()`.
- Else, use `foo()`.