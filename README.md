# fdf

 fdf (fil-de-fer) project for School 42 Paris

![Screenshot from 2023-11-22 13-52-14](https://github.com/jlupito/fdf/assets/113239012/dd0f2ab7-5960-48d1-bfe0-3f9b63f623e6)

This is the first graphic project within School 42 common core.
This projet is about creating a simplified 3D representation of
a relief landscape by:

 - placing various points in space
 - drawing segments to join the points (using Bresenham's line algorithm)
 - observe the scene from a particular viewpoint (here faking isometric projection)
 - also including events programming (keyboard, possibly mouse)

...all of this using the minilibX (42 homemade graphic library).

The program takes a xxx.fdf map as argument, which, for each point of the map, gives
an integer that corresponds to the altitude and possibly an hexadecimal for the color to
be set. Two points with different colors are linked by a segment using color 
interpolation (lerp).
