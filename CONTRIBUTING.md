# LAUNCH - How to Contribute

## Part O - First Things First

Please check the existing issues before you do anything.

## Part I - Issue Template

#### Defect Reports

Title:  
Defect - (one-line description)

Content:  
**\*Module**: (module name)  
**Applicable** **version(s)**: since (6-digit commit hash)  
**Environment**: (compiler) (compiler version) (compile options) on (OS)  
**\*Description**: (detailed description)  
**Expected** **behaviour**: (expected behaviour)  
**Reproducing**: (code)

Items without asterisks (*) aren't absolutely necessary. However, the more information you provide, the faster we can locate and fix the problem.

#### Feature Requests

Title:  
Feat. req. - (one-line description)

Content:  
**Module**: (module name)  
**Description**: (detailed description)  
**Reason**: (reason)

The reason can be omitted if the feature should have existed in the first place.

## Part II - Submitting PRs

Feel free to submit PRs. However, please always remember the following points:
- Link to an existing issue.
- Edit on a new branch.
- Follow the style guide (introduced below).
- Rebase before finally submitting.
- Take an active part in the discussion of your PR.
- If we misunderstood your intention, please tell us.

## Part III - The Style Guide

### Identifiers

#### Variables, Functions, Classes & Structs

`snake_case`, with a few extra rules.  
1. Especially for class and struct names, the name shouldn't be the same as names in standard libraries. For example, `duration` -> `timespan`.  
2. Especially for helper class and struct names, use the main classes' names as prefixes. For example, `oper_type` -> `hedgehog_opertype`.  
3. Abbreviate names just right. For example, `arint_special_value` -> `arint_specval`.

#### Constants & Macros

`SCREAMING_SNAKE_CASE`.

#### Concepts & Template Parameters

`PascalCase`.

### Indentations & Formatting

#### Indentations

Use tabs. If possible, make them 4 spaces in width.

#### Formatting

- Always use braces (`{}`).
- Nothing may follow a semicolon (`;`) unless in special cases (single-line comments, `for` loops, etc.).

### Miscellaneous

#### Preprocessors

- Use `#if defined(...)` and `#if !defined(...)` instead of `#ifdef` and `#ifndef`.  

#### Member Things

- Use `this->foo` or `this->foo()` if `foo` is `public`.
- Use `bar` or `bar()` if `bar` is `private` or `protected`.
- Use `_Baz` instead of `baz` if it is a `private` or `protected` member function.

#### Templates

Use `template <typename T>` instead of `template <class T>`, even though they're the same.

---

<sub>Author: Arcsin Studios<br>License (of this document): CC BY-SA 4.0</sub>