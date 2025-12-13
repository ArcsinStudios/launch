> [!NOTE]
> This README was written in assistance of MPE (Visual Studio Code extension).  
> Some of the features used may not work on GitHub.  
> For the best reading experience, please use MPE.  
> Thank you for your understanding.

<div style="position: absolute;">

<div style="position: relative; display: flex; align-items: center; gap: 15px;">
  <img
    src="LAUNCH.svg"
    alt="Logo of LAUNCH"
    style="height: 75px;"
  />
  <h1>LAUNCH - Introduction</h1>
</div>

<h2 style="
  position: relative;
  top: -70px;
  left: 400px;
  color: orange;
  transform-origin: 20%;
  animation: splash 1.2s ease-in-out infinite;
">Also try Boost!</h2>

</div>

<div style="height: 100px;"></div>

---

![](https://img.shields.io/badge/Language-C++-blue) ![](https://img.shields.io/badge/Standard-C++20-blue) ![](https://img.shields.io/badge/Dependencies-STL_Only-green) ![](https://img.shields.io/badge/License-MIT-yellow) ![](https://img.shields.io/badge/Platform-Any-lightgrey)

## Navigation

[Part I: FAQs](#part1)  
[Part II: Building / Using](#part2)  
[Part III: The Modules](#part3)  
[Part IV: Conclusion](#part4)

<h2 id="part1">Part I: FAQs</h2>

| Qs | As |
|-|-|
| Where does the name *LAUNCH* come from? | It's a backronym - **L**ibrary of **A**bundant **U**tilities for **N**ew **C**reative **H**acks! |
| The namespace `launch` has the same name as `std::launch`. How do you deal with that? | We don't deal with that; we don't want to deal with that. Legacy problems are always annoying >:-( |
| How many modules are there? | Currently, there are 9 (LAUNCH itself) + 1 (LEISURE features). |
| Well, what's LEISURE, then? | It's still a backronym - **L**ibrary of **E**xperimental **I**deas for **SURE**! |
| What's your slogan? | "Build, LAUNCH, start creating. That simple." |


<h2 id="part2">Part II: Building / Using</h2>

### Part II-1: Building

This project uses CMake.  
For details, please go to `CMakeLists.txt`.

### Part II-2: Using

Simply `#include "launch.h"`.  
If you need more precise module controls, please `#define` macros before `#include "launch.h"`.
The macros look like this:
```cpp
LAUNCH_NO_<MODULENAME> // to disable a specific module such as caref, chroyes, etc.
LAUNCH_<MODULENAME>_<SUBMODULENAME> // to enable a specific submodule such as arint, nullstream, etc.
LAUNCH_NO_THREAD_SAFE // to disable thread safety in some modules
LAUNCH_EXPERIMENTAL // to enable LEISURE features
```

<h2 id="part3">Part III: The Modules</h2>

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
/* back to work */
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

### \<goodmath\>, \<goodrand\> & \<goodstr\>

- What do the names mean?  
**-** They're just *the goods*. (Or technically, we use these names to prevent ambiguity.)
- What can they do?
```cpp
std::string hint = "Sine value of ";
launch::randgen_real rand(0.0, 360.0);
double deg = rand.next();
std::cout << hint << deg << "deg: " << launch::sin(launch::dtor(deg)) << "\n";
std::cout << launch::replace(hint, "Sine", "Cosine");
std::cout << hint << deg << "deg: " << launch::cos(launch::dtor(deg)) << "\n";
```

### \<lidevec\> (LEISURE feature)

- What does the name mean?  
**-** To be honest, it's a legacy name -  but "vec" stands for **vec**tor, of course.
- What can \<lidevec\> do?  
(Notice that `lidevec` does **not** support iterators.)  
While iterating through `lidevec` forward, you'll find that it's really fast to do **any** **operation**!  
Actually, it's **hundreds** **of** **times** **faster** than `vector` when `erase`-ing, and **dozens** **of** **times** **faster** than `vector` when `insert`-ing!  
(But it's, well, extremely slow when iterating backwards.)


<h2 id="part4">Part IV: Conclusion</h2>

Conclusion: LAUNCH is good. Use LAUNCH, thank you.

---

<sub>Author: Arcsin Studios<br>License (of this README): CC BY-SA 4.0</sub>

<style>
@keyframes splash {
  0% {
    transform: rotate(-15deg) scale(1);
  }
  50% {
    transform: rotate(-15deg) scale(1.1);
  }
  100% {
    transform: rotate(-15deg) scale(1);
  }
}
</style>