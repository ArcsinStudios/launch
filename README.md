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
[Appendix I: Optional Submodules](#appendix1)

<h2 id="part1">Part I: FAQs</h2>

| Qs | As |
|-|-|
| Where does the name *LAUNCH* come from? | It's a backronym - **L**ibrary of **A**bundant **U**tilities for **N**ew **C**reative **H**acks! |
| The namespace `launch` has the same name as `std::launch`. How do you deal with that? | It's just simply too expensive. Think about it, you not only have to change the code, but also the filenames, repo names, etc... Ugh. |
| How many modules are there? | Currently, there are 8 (LAUNCH itself) + 1 (LEISURE features). |
| Well, what's *LEISURE*, then? | It's still a backronym - **L**ibrary of **E**xperimental **I**deas for **SURE**! |
| What's your slogan? | "Build, LAUNCH, start creating. That simple." |


<h2 id="part2">Part II: Building / Using</h2>

### Part II-1: Building

This project uses CMake.  
For details, please go to `CMakeLists.txt`.

### Part II-2: Using

Simply `#include "launch.h"`.  
If you need more precise module controls, please `#define` macros in `launch_config.h`.
The macros look like this:
```cpp
LAUNCH_NO_<MODULENAME> // To disable a specific module.
LAUNCH_<MODULENAME>_<SUBMODULENAME> // To enable a specific submodule.
LAUNCH_EXPERIMENTAL // To enable LEISURE features.
LAUNCH_NO_THREAD_SAFE // As the name implies.
```
Or, there's a special macro: `LAUNCH_EVERYTHING`, which enables every submodule and also LEISURE features.

<h2 id="part3">Part III: The Modules</h2>

### \<chroyes\>

- What does the name mean?  
**-** From \<chro**no**\> to \<chro**yes**\>
- What can \<chroyes\> do?
```cpp
launch::stopwatch watch;
watch.start();
/* do something */
std::this_thread::sleep_for(1s);
watch.pause();
/* take a rest */
std::this_thread::sleep_for(1s);
watch.resume();
/* back to work */
std::this_thread::sleep_for(1s);
watch.stop();
std::cout << "Time elapsed: " << watch.get_dur().milliseconds(); << "ms\n";
```
- Expected output:
```
Time elapsed: 2000ms
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
- Expected output (with no parameters):
```
false
```
- Expected output (with parameter `--flag` or `-f`):
```
true
```
- Expected output (with parameter `--option <value>` or `-o <value>`):
```
<value> false
```
- Expected output (with parameter `--flag --option <value>` or `--flag -o <value>` or `-f --option <value>` or `-f -o <value>` or `-fo <value>` or `--option <value> --flag` or `--option <value> -f` or `-o <value> --flag` or `-o <value> -f`):
```
<value> true
```

### \<escseq\>

- What does the name mean?  
**-** ANSI **Esc**ape **Seq**uences (ANSI Escape Code)
- What can \<escseq\> do?
```cpp
std::cout << launch::gen_style(launch::escseq_style::italic | launch::escseq_style::underline)
          << launch::foreground_color(0, 0, 255)
          << launch::background_color(255, 255, 255)
          << "Hyperlink"
          << launch::rendl_fast;
```
- Expected output: <p style="font-style: italic; text-decoration: underline; color: #0000ff; background-color: #ffffff;">Hyperlink</p>

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
- Expected output:
```
int: 42, double: 3.14, bool: true, string: Hello World!, char: A
<input...>
You entered: <input0> & <input1>.
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
- Expected output:
```
Sine value of <random>deg: <sin(random)>
Cosine value of <random>deg: <cos(random)>
```

### \<arithing\> (LEISURE feature)

- What does the name mean?  
**-** **Ari***th*metic *Th***ing**s
- What can \<arithing\> do?
```cpp
std::cout <<
    "Very big: " <<
    launch::arint(std::numeric_limits<unsigned long long>::max()) <<
    "\n";
std::cout <<
    "Very small (hey, it's way too small): " <<
    launch::arint(std::numeric_limits<unsigned long long>::max(), launch::arint_specval::neg) <<
    "\n";
std::cout <<
    "Wait, what?: " <<
    launch::arint(0, launch::arint_specval::inf) <<
    " " <<
    launch::arint(0, launch::arint_specval::inf | launch::arint_specval::neg) <<
    " " <<
    launch::arint(0, launch::arint_specval::nan) <<
    "\n";
std::cout << "Ooh, rational: " << launch::arreal(22, 7) << "\n";
```
Expected output:
```
Very big: 18446744073709551615
Very small (hey, it's way too small): -18446744073709551615
Wait, what?: inf -inf NaN
Ooh, rational: 22/7
```

<h2 id="part4">Part IV: Conclusion</h2>

Conclusion: LAUNCH is good. Use LAUNCH, thank you.

---

<h2 id="appendix1">Appendix I: Optional Submodules</h2>

### \<fmtio_nullstream\>

- What does the name mean?  
**-** `fmtio`: This submodule is a part of \<fmtio\>.  
**-** `nullstream`: It's just, well, a `stream` that sends text into `null`, i.e., nowhere. (Sorry for the tautology.)
- What can `nullstream` do?
```cpp
launch::nullout << "Hello World...? Anyone here?\n"; // nullout is a global nullstream instance
```
Expected output: (nothing)

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