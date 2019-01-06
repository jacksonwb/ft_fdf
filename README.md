# FdF - A simple 3D wireframe renderer built in C

![A simple scene](https://github.com/jacksonwb/ft_fdf/blob/master/screens/screen.png)

## Features
The program will render a simple map in orthographic or perspective projection. Maps are defined with very simple syntax. Demo maps are include in the maps directory. The model can be rotated and scaled, and the projection can be changed with adjustable focal length.

## Controls
* <kbd>Left Mouse</kbd> - Rotate X and Y
* <kbd>Right Mouse</kbd> - Scale
* <kbd>1</kbd> - Top View
* <kbd>2</kbd> - Side View 1
* <kbd>3</kbd> - Side View 2
* <kbd>4</kbd> - Isometric View
* <kbd>5</kbd> - <kbd>9</kbd> - Colors 1 - 5
* <kbd>P</kbd> - Toggle Perspective
* <kbd>-</kbd> and <kbd>+</kbd> - Change Focal Length

## Usage
This program requires `clang` to build.

Run `make` and then `./fdf [map]`

This has currently only been tested on MacOS