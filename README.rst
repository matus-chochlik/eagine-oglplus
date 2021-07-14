==============
EAGine OGLplus
==============

:Author: Matúš Chochlík <chochlik@gmail.com>

EAGine is a collection of C++ libraries providing set of basic utilities, C++
wrappers for OpenGL, OpenAL, EGL, SSL, and a message bus useful for writing
potentially distributed, multi-process applications with graphics rendering
and/or audio playback.

This repository is one of the sub-modules of the main project hosted
at https://github.com/matus-chochlik/eagine-all and implements a C++ wrapper
around the OpenGL C API.

Cloning the repository
======================
::

 git clone https://github.com/matus-chochlik/eagine-oglplus.git

Building the code
=================

The project uses `cmake`-based build system so you can use the following
to build and install the code:

::

  mkdir -p /path/to/build/dir
  cd /path/to/build/dir
  cmake -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/path/to/install/dir \
        /path/to/eagine-oglplus/
  cmake --build . --target install --parallel 16

License
=======

Copyright Matus Chochlik, 2015-2021.
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt

The applications using Qt5 are distributed under
the GNU GENERAL PUBLIC LICENSE version 3.
See http://www.gnu.org/licenses/gpl-3.0.txt

