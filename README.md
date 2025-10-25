> [!NOTE]
> This README was written in assistance of MPE (Visual Studio Code extension).
> Some of the features used may not work on GitHub.
> For the best reading experience, please use MPE.
> Thank you for your understanding.

<div style="position: absolute;">

# LAUNCH - Brief Introduction

![](https://img.shields.io/badge/Language-C++-blue) ![](https://img.shields.io/badge/Standard-C++20-blue) ![](https://img.shields.io/badge/Dependencies-STL_Only-green) ![](https://img.shields.io/badge/License-MIT-yellow) ![](https://img.shields.io/badge/Platform-Any-lightgrey)

<p id="slogan">Build, LAUNCH, start creating. That simple.</p>

<h2 style="
  position: relative;
  top: -140px;
  left: 400px;
  color: orange;
  transform: rotate(-20deg);
  transform-origin: 10% 25%;
  animation: splash 1.2s ease-in-out infinite;
">Also try Boost!</h2>

</div>

<div style="height: 170px;"></div>

---

## Navigation

[Part I: FAQs](#part1)
[Part II: Building / Using](#part2)
[Part III: Introductions that may be not so brief](#part3)
[Part IV: Conclusion](#part4)

<h2 id="part1">Part I: FAQs</h2>

| Qs | As |
|-|-|
| Where does the name *LAUNCH* come from? | It's a backronym - **L**ibrary of **A**bundant **U**tilities for **N**ew **C**reative **H**acks! |
| The namespace `launch` has the same name as `std::launch`. How do you deal with that? | You should ask WG21 why they are choosing this widely used name. |
| How many modules are there? | Currently, there are 8. |
| What's your slogan? | [Here!](#slogan) |


<h2 id="part2">Part II: Building / Using</h2>

### Part II-1: Building

This project uses CMake.
For details, please go to `CMakeLists.txt`.

### Part II-2: Using

We recommend `#include`-ing `<launch.h>` and `#define`-ing macros to disable modules or enable sub-modules, instead of `#include`-ing a bunch of modules or sub-modules.

<h2 id="part3">Part III: Introductions that may be not so brief</h2>

### \<caref\>
- What does the name mean?
**-** **C**lever & **A**utomatic **Ref**erence
- What can \<caref\> do?
```cpp
launch::caref<int> observer;
// observer - construct
{
    launch::caref<int> owner(new int(42));
    // owner - construct
    std::cout << *owner << "\n";
    observer = owner;
    // observer - observing
    std::cout << *observer << "\n";
    owner.move(observer);
    // owner - move ownership to observer
}
// owner - destruct
std::cout << *observer << "\n";
// as you can see - the observer is still alive!
```

### \<chroyes\>
- What does the name mean?
**-** From \<chro**no**\> to \<chro**yes**\>
- What can \<chroyes\> do?
```cpp
launch::stopwatch watch;
watch.start();
/* do something */
watch.pause();
/* take a rest */
watch.resume();
/* continue */
watch.pause();
/* I'm too lazy */
watch.resume();
/* continue */
watch.stop();
long long dur = watch.get_duration().milliseconds();
```

### \<clap\>
- What does the name mean?
**-** **C**ommand **L**ine **A**rgument **P**arser
- What can \<clap\> do?
```cpp
int main(int argc, char* argv[]) {
    launch::clap parser(argc, argv, {{"o", "option"}, {"f", "flag"}});
    // the third parameter (aliases) maps short options to corresponding long options
    // aliases is an empty std::unordered_map by default
    std::optional<std::string> option = parser.get_opt("option");
    bool flag = parser.get_flag("flag");
    // clap only recognizes long options
    if (option) {
        std::cout << option.value() << "\n";
    }
    std::cout << std::boolalpha << flag << "\n";
    return 0;
}
```

### \<escseq\>
- What does the name mean?
**-** ANSI **Esc**ape **Seq**uences (ANSI Escape Code)
- What can \<escseq\> do?
```cpp
std::cout << launch::gen_font(launch::FONT_ITALIC | launch::FONT_UNDERLINE)
          << launch::foreground_color(0, 0, 255)
          << launch::background_color(255, 255, 255)
          << "Hyperlink"
          << launch::l_endl_fast;
```

### \<fmtio\> & \<hedgehog\>
- *(\<fmtio\>)* What does the name mean?
**-** **F**or**m**a**t**ted **I**nput/**O**utput
- *(\<hedgehog\>)* What does the name mean?
**-** You see, hedgehogs' spines don't care what they're carrying - that's what `hedgehog` does!
- What can they do?
```cpp
launch::hedgehog hh1 = { 42, 3.14, true, "Hello World!", 'A' };
launch::hedgehog hh2 = { };
launch::fmtout("int: {0}, double: {1}, bool: {2}, string: {3}, char: {4}\n", hh1);
launch::fmtin<int, double>(hh2);
launch::fmtout("You entered: {0} & {1}.\n", hh2);
```

### \<goodmath\> & \<goodstr\>
- What do the names mean?
**-** They're just *the goods*. (Or technically, we use this name to prevent ambiguity.)
- What can they do?
```cpp
double deg;
std::cin >> deg;
std::cout << "Sine value: " << launch::sin(launch::dtor(deg)) << "\n";
launch::hstr str = "Hello World!\n";
std::cout << launch::replace(str, "Hello", "Goodbye");
```

<h2 id="part4">Part IV: Conclusion</h2>

Conclusion: LAUNCH is good. Use LAUNCH, thank you.

<sub>
Author: Arcsin Studios

License: CC BY-SA 4.0
</sub>

<style>
@keyframes splash {
  0% {
    transform: rotate(-20deg) scale(1);
  }
  50% {
    transform: rotate(-20deg) scale(1.1);
  }
  100% {
    transform: rotate(-20deg) scale(1);
  }
}
</style>