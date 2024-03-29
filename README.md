# yasd

(yet another) self-driving car simulator

## Table of Contents

* [Introduction](#introduction)
* [How to compile](#how-to-compile)
* [License](#license)

## Introduction

**yasd** is an isolated simulation environment designed to study how autonomous cars could learn to properly drive and coexist without an initial well defined traffic law.

https://user-images.githubusercontent.com/17249927/140613637-8e865076-4d08-4d3c-8c0c-5dd2a0b2e8db.mp4

## How to compile

Please [report any problems](https://github.com/mattiabiondi/yasd/issues/new) you run into when building the project.

### Dependencies

A compiler with C++11 support ([clang-3.3+](https://llvm.org/releases/download.html), [gcc-4.8+](https://gcc.gnu.org/releases.html))
- `git`
- `cmake 3.5+`
- `Qt 5.14+`
- `Qt Charts`

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
$ ./yasd
```

## License

**yasd** is licensed under the [GPL-3.0](https://www.gnu.org/licenses/gpl-3.0.en.html) license. [See LICENSE for more information](https://github.com/mattiabiondi/yasd/blob/main/LICENSE).
