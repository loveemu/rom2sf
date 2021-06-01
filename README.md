ROM2SF: NDS ROM to 2SF Converter
================================
[![Travis Build Status](https://travis-ci.com/loveemu/rom2sf.svg?branch=master)](https://travis-ci.com/loveemu/rom2sf) [![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/2rt4mekcr74316lx/branch/master?svg=true)](https://ci.appveyor.com/project/loveemu/rom2sf/branch/master)

Program to turn a rom into a 2sf file. This is used mostly with manual rips.
<https://github.com/loveemu/rom2sf>

Downloads
---------

- [Latest release](https://github.com/loveemu/rom2sf/releases/latest)

Usage
-----

Syntax: `rom2sf <NDS Files>`

### Options ###

`--help`
  : Show help

`-o [output.2sf]`
  : Specify output filename

`--load [offset]`
  : Load offset of mini2sf executable

`--lib [libname.2sflib]`
  : Specify 2sflib library name

`--psfby`, `--2sfby` [name]
  : Set creator name of 2SF
