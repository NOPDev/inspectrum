# pyinspectrum - a fork of inspectrum
A tool for analysing captured signals, primarily from software-defined radio receivers that implements an ipython console and bindings for analyzing symbols on the fly.

![pyinspectrum screenshot](/screenshot.jpg)

## Try it
### Prerequisites

 * cmake
 * fftw 3.x
 * [liquid-dsp](https://github.com/jgaeddert/liquid-dsp)
 * pkg-config
 * qt5
 * python3
 * qtconsole
 * 
 
### Ubuntu 16.04
  The recommended way to test pyinspectrum is to use the [pyinspectrum PPA](https://launchpad.net/~defunctio/+archive/ubuntu/inspectrum).
  ```
  sudo add-apt-repository ppa:defunctio/inspectrum
  sudo apt-get update
  sudo apt-get install pyinspectrum
  pip3 install --user qtconsole
  ```

### Building on Debian-based distros
  For now the build process is a bit convoluted and has yet to be fully documented. If you wish to build the source on ubuntu it is recommended that you use `apt-get source pyinspectrum`
    
 ```   
  sudo apt-get install qt5-default libfftw3-dev cmake pkg-config python3-dev python3-pip python3 python3-pyqt5 python3-pyqt5.qtsvg python3-pyqt5.qtmultimedia python3-pyqt5.qtwebkit
  pip3 install --user qtconsole
  mkdir build
  cd build
  cmake ..
  make
  sudo make install
 ```
### Run

    ./inspectrum

## Input
inspectrum supports the following file types:
 * `*.cf32`, `*.cfile` - Complex 32-bit floating point samples (GNURadio, osmocom_fft)
 * `*.cs16` - Complex 16-bit signed integer samples (BladeRF)
 * `*.cs8` - Complex 8-bit signed integer samples (HackRF)
 * `*.cu8` - Complex 8-bit unsigned integer samples (RTL-SDR)

If an unknown file extension is loaded, inspectrum will default to `*.cf32`.

## Features
 * Large (multi-gigabyte) file support
 * Spectrogram with zoom/pan
 * Plots of amplitude, frequency and IQ samples
 
## Contact
 * #inspectrum on freenode IRC
