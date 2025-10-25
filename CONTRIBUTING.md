# LAUNCH - How to Contribute

## Part O - Check the existing issues.

## Part I - How to reproduce?

### First things first

Tell us your compiler and compiling options.

### The best situation

You know what's going on and you gave us the most essential part.

### Fallback I

You don't know what **exactly** is going on but you gave us the most **suspicious** part.

### Fallback II

You don't know what's going on. You gave us the entire code.

## Part II - Pulling Requests

### First things first

Make sure your code is [our style](#part3).

### While pulling

Just keep track.

### To those...

It's OK to PR toy projects (except hello-world-level projects). They're great sources of ideas.

<h2 id="part3">Part III - Style guide</h2>

### Identifiers

#### Variables, functions & classes

`snake_case`, but remember to use abbreviations when a long word appears (or the identifier itself is too long).

Good examples: `hedgehog_elemproxy` (**Hedgehog** **Elem**ent **Proxy**), `avail_size` (**Avail**able **Size**), `clap`

#### Constants & macros

`SCREAMING_SNAKE_CASE`.

### Indentations & formatting

#### Indentations

Use tabs. If possible, make them 4 spaces in width.

#### Formatting

- **Always** use braces (`{}`).
- There mustn't be anything after a semicolon (`;`), except the three statements in `for` loops, and comments (we rarely use comments).
- (Optional, if you're using Visual Studio) At 125% zoom with Solution Explorer opening, a line of code must be seen entirely.

### Preprocessors

#### Conditions

Use `#if defined(...)` and `#if !defined(...)` instead of `#ifdef` and `#ifndef`.

#### About `#define`

Never, unless you `#undef`-ed it after use. Thank you.