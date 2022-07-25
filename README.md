<div align="center">

# Urbanite

Search words on Urban Dictionary at the comfort of your terminal.

![Urbanite demo](media/urbanite-demo.gif)

---

Urbanite is a program for searching words and their definitions on [Urban Dictionary](https://www.urbandictionary.com/) within a terminal emulator/shell. Now you never need to leave your cozy terminal window to search for your memes.

Pounds of customization available, tons coming soon.

---

</div>

## Table of contents
* [Usage and Features](#usage-and-features)
* [Installation](#installation)
  * [Linux](#linux)
    * Desktop
    * Android (Termux)
  * [MacOS](#macos)
  * [BSD/Other Unix-like](#bsdother-unix-like)
  * [Windows](#windows)
* License & Libraries

## Usage and Features

Usage: `urbanite ... [OPTIONS] ...`

For a basic word/phrase search, just run `urbanite your word or phrase here`. For more help about command line options, run `urbanite --help`. A basic overview of the available features is given here.

* **Custom Figlet fonts -**
  You can use your own figlet fonts to change the look of the output using the `-f (--font-file)` option. Urbanite comes bundled with a few font files by default and you can use more by using this option.
* **Like/Dislike counts and stats -**
  You can see the like and dislike counts, like to dislike ratio and percentage of likes of a definition
  * **Custom symbols/emojis to denote the like/dislike counts -**
    You can customize the symbols used to denote the like and dislike counts and ratios. Comes with 4 sets of symbols and a custom symbol option. Just use `-e (--emoji-style)`.
* More features and Windows support coming soon. Request features on the [Issues page](https://github.com/NMrocks/urbanite/issues) :)

## Installation

### From release binaries

Binaries are provided for Linux and Termux in tarballs on the [Releases page](https://github.com/NMrocks/urbanite/releases). Extract the tar archives and run `make install` in the extracted directory to install the binaries. You will need the libcurl package from your package manager becuase this program depends on the libcurl binaries.

`.deb` archives are also available for Debian-based distros in [Releases](https://github.com/NMrocks/urbanite/releases).

### From source

To compile from source, you must have [libcurl](https://curl.se/libcurl/) and [nlohmann's JSON library](https://json.nlohmann.me/) installed on the device the program is being compiled on. You will also need the libcurl package from your package manager becuase this program depends on the libcurl binaries.

#### Linux

* **Desktop**

  On most desktop Linux distributions, the Makefile should work out of the box. Just run:
  ```
  $ make
  ```
  To compile, and then
  ```
  # make install
  ```
  To install Urbanite. The Makefile installs the binary by default to `/usr/local/bin` and the font files to `/usr/local/share/urbanite`, which should normally not be changed. If they need to be changed, you can pass your own prefix directory to `make` when compiling, for example `make prefix=/path/to/prefix`.

* **Android (Termux)**

  Termux's directory structure is the same as Linux but the prefix directory is different. To compile and install a working binary on Termux, you need to run:
  ```sh
  $ make prefix=$PREFIX # Compile
  $ make install prefix=$PREFIX # Install
  ```

#### MacOS

Install instructions for desktop Linux will work fine on MacOS. Just `make` and then `make install`.

#### BSD/Other Unix-like

Linux instructions should work on other Unix-like systems like BSD-based OSs.

#### Windows

Windows is not supported yet but Windows support is planned. Stay tuned!

### Uninstall a from-source installation

To uninstall a from-source/tarball installation, simply run the install command you used but replace the `install` with an `uninstall`. For example,
```sh
make install prefix=/my/path/to/prefix # Install command
```
```sh
make uninstall prefix=/my/path/to/prefix # Uninstall command
```

## License and Libraries

This program is licensed under the GNU General Public License v3 or later.

This program was made possible by the following libraries:

* [Urban++](https://github.com/NMrocks/urban-plus-plus) by [Nishant Mishra](https://github.com/NMrocks) -
  A library for searching words and their related info on Urban Dictionary. This NM guy is very nice, you should check him out ;)

  This library depends on:
  * The [cURL](https://github.com/curl/curl/tree/master/include/curl) library by [Daniel Stenberg](https://github.com/bagder)
  * The [JSON for Modern C++](https://github.com/nlohmann/json) library by [Niels Lohmann](https://github.com/nlohmann)

* [Figlet For C++](https://github.com/srilakshmikanthanp/figlet) by [Sri Lakshmi Kanthan P](https://github.com/srilakshmikanthanp)
  The library which makes the output more fancy