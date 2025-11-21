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

`snake_case`, but remember to use abbreviations when the identifier name is too long.  
Good examples: `hedgehog_elemproxy` (**Hedgehog** **Elem**ent **Proxy**), `escseq` (**Esc**ape **Seq**uence), `clap` (**C**ommand **L**ine **A**rgument **P**arser)

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