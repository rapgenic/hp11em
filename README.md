# HP11em: a C++, GTK, linux HP11C calculator emulator

HP11em is still in development, and almost only 50% completed.

## Building

At the moment HP11em compiles on Linux systems only.

To compile it you need to install:

- libgtkmm-3.0-dev
- autoconf-archive

Generate compilation files running:

```console
$ ./autogen.sh
```

Build the image resources running in the project root:

```console
$ ./generate_resources.sh
```

Then compile with:

```console
$ ./configure		# run with "--with-debug" option for debug
$ make
```

And optionally install with:

```console
$ sudo make install
```

## License

Code is released under GPLv3 license, for more information see the COPYING file in the root of the project

Every `*.svg` image is licensed under CC BY-SA 4.0 (see http://creativecommons.org/licenses/by-sa/4.0/legalcode)
