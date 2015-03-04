[![Build Status](https://travis-ci.org/csdms-contrib/storm.svg?branch=master)](https://travis-ci.org/csdms-contrib/storm)

# storm

**Storm** computes the windfield for a cyclone based on 
the pressure distribution and radius to maximum winds.
See the [model page](http://csdms.colorado.edu/wiki/Model:STORM)
on the CSDMS wiki for more information.

## Build

To build the **storm** BMI, executable, and tests,

    $ mkdir build && cd build
    $ cmake .. -DCMAKE_INSTALL_PREFIX=<path-to-installation>
    $ make

where `<path-to-installation>` is the base install directory
(**/usr/local** is the default).
To install,

    $ make install
