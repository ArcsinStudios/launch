> [!NOTE]
> Disambiguation: you might be looking for `genev_(class).md` instead of `genev_(header).md`.

# `genev`

## Global objects
<small>Defined in `genev_impl.cppm`</small>
|Object|Description|
|---|---|
|`meter`<br>`second`<br>`ampere`<br>`kelvin`<br>`candela`<br>`mole`|SI base units|
|`gram`|ditto <sup>[1]</sup>|
|`radian`<br>`steradian`|special SI derived units (formerly SI supplementary units <sup>[2]</sup>)|
|`hertz`<br>`newton`<br>`pascal`<br>`joule`<br>`watt`<br>`coulomb`<br>`volt`<br>`farad`<br>`ohm`<br>`siemens`<br>`weber`<br>`tesla`<br>`henry`<br>`lumen`<br>`lux`|SI derived units|
|`minute`<br>`hour`<br>`day`<br>`degree`<br>`arcminute`<br>`arcsecond`<br>`hectare`<br>`liter`<br>`ton`|non-SI units accepted for use with the SI|
|`units`|stores all of the base units|
|`units_str`|stores all of the base units in `std::string`|
|`units_str_si`|stores all of the base units (with `"kg"` instead of `"g"`) in `std::string`|
|`prefixes`|stores all of the prefixes|
|`prefixes_str`|stores all of the prefixes in `std::string`|
|`prefixes_str_sorted`|stores all of the prefixes in `std::string`<br>sorted by length in descending order|

## Functions
<small>Defined in `genev_impl.cppm`</small>
|Function|Description|
|---|---|
|`peta`<br>`tera`<br>`giga`<br>`mega`<br>`kilo`<br>`hecto`<br>`deca`<br>`deci`<br>`centi`<br>`milli`<br>`micro`<br>`nano`<br>`pico`<br>`femto`|part of SI prefixes|

## Note
[1] This is a technical implementation only. The base unit for mass is kg (kilogram) in SI.
[2] These are technical implementations only. The class of supplementary units as a separate unit class was eliminated by the 20th CGPM in 1995.