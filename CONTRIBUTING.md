# LAUNCH - How to Contribute

## Issue

### First Things First

- Check the existing issues.
- Tell us your compiler and compiling options.

### Reproducing

You know what's going on and you gave us the most essential part.  
Or, if you don't:  
You don't know what **exactly** is going on but you gave us the **most** **suspicious** part.  
Or, if you don't:  
You don't know what's going on. You gave us the entire code.

## Part II - Pulling Requests

First: make sure your code is our style. (Read also: Appendix I)  
And, by the way, it's OK to PR toy projects! They're great sources of ideas.

## Appendix I - Style guide

### Identifiers

#### Variables, Functions & Classes

`snake_case`, but remember to use abbreviations when the identifier name is too long.  
Good examples: `hedgehog_elemproxy` (**Hedgehog** **Elem**ent **Proxy**), `escseq` (**Esc**ape **Seq**uence), `clap` (**C**ommand **L**ine **A**rgument **P**arser)

#### Constants & Macros

`SCREAMING_SNAKE_CASE`.

### Indentations & Formatting

#### Indentations

Use tabs. If possible, make them 4 spaces in width.

#### Formatting

- **Always** use braces (`{}`).
- There mustn't be anything after a semicolon (`;`), except the three statements in `for` loops.

### Preprocessors

#### About `#if`, `ifdef` & `#ifndef`

Use `#if defined(...)` and `#if !defined(...)` instead of `#ifdef` and `#ifndef`.

#### About `#define`

**Never**, unless you `#undef`-ed it after use. Thank you.