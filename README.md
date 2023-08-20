# soundstation

A simple DAW made by Johan Solbakken.

## Dependencies
For macos
~~~
cd dependencies
cd macos
brew bundle
~~~

## Build and run

~~~bash
git clone --recursive https://github.com/johansolbakken/soundstation
cd soundstation
mkdir build
cd build
cmake ..
make
cd soundstation
./soundstation
~~~

![](images/v3.png)