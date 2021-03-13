# yasd

(yet another) self-driving car simulator

## Table of Contents

* [Introduction](#introduction)
* [How to compile](#how-to-compile)
* [License](#license)

## Introduction

**yasd** is an isolated simulation environment designed to study how autonomous cars could learn to properly drive and coexist without an initial well defined traffic law.

*complete*

## How to compile

Please [report any problems](https://github.com/mattiabiondi/yasd/issues/new) you run into when building the project.

### Dependencies

A compiler with C++11 support ([clang-3.3+](https://llvm.org/releases/download.html), [gcc-4.8+](https://gcc.gnu.org/releases.html))
- `git`
- `cmake 3.5+`
- `Qt 5.14+`

#### Get the source code

```sh
$ git clone https://github.com/mattiabiondi/yasd
```

#### Build

```sh
$ cd yasd
$ mkdir build
$ cd build
$ cmake ..
$ make
```

#### Launch

```sh
$ ./src/yasd
```

## License

**yasd** is licensed under the [GPL-3.0](https://www.gnu.org/licenses/gpl-3.0.en.html) license. [See LICENSE for more information](https://github.com/mattiabiondi/yasd/blob/main/LICENSE).
