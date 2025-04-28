* miniRT - mifavoke & zuzanapiarova * 

** RESOURCES **
Ray tracing basics Stanford paper
https://cs.stanford.edu/people/eroberts/courses/soco/projects/1997-98/ray-tracing/implementation.html
Starter ray tracing math for object parametric equations and finding intersections:
https://www.gabrielgambetta.com/computer-graphics-from-scratch/01-common-concepts.html
Optimizing - not all objects are considered, only those in path of the ray:
https://gfxcourses.stanford.edu/cs348b/spring22content/media/intersection/rt1_3GyBK6F.pdf
Mapping coordinates from screen to viewport to 3d space 
https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
https://www.ogldev.org/www/tutorial13/tutorial13.html
Ray tracing pdf handbook:
https://www.researchgate.net/publication/230583216_Ray_Tracing_Algorithms_-_Theory_and_Practice
creating rotation matrices and general 3d rotation matrix:
https://en.wikipedia.org/wiki/Rotation_matrix
cylinder line intersection:
http://www.illusioncatalyst.com/notes_files/mathematics/line_cylinder_intersection.php
https://en.wikipedia.org/wiki/Line-cylinder_intersection
Intersection of a ray with different objects (or objects with objects)
https://www.realtimerendering.com/intersections.html


* FOR YEVA *
- NEW: before we were allocating new inter array for each new image, now we just allocate once and when creating new image, free the existing list of intersections there and assign the newly generated list intead - it happend in the math.c - shoot_rays() - seems faster now
- ALSO i removed the init pixels function and if there is no intersectoin, we assign the default background color in the shoot_rays again

* FOR ZUZANA *
check the transformations and rotations with keys
- i think we should handle being inside objects - now when first inter is behind camera, the second inter - so calculate even inters that are behind the camera and set the other inter to black - if the inter in front of the camera is black, it is inside and no difused light applies
- redo the rotations with the rotation matrices
- redo the printf for errors to write to stderr
- cylinder, maybe parboloid?
- multithreding - parallelization
- maybe optimization as in the article "Starter ray tracing math" above
- handle pixels in resize hook - now they are not freed and not reallocated when the size is different - have to do this 
- should we change viewport width in minirt struct when resizing? 
- rename cy->vector to cy->axis

** GENERAL INFORMATION **
- viewport/film/near plane = the canvas or the imaginary somputer screen we put between camera and the scene to map rays to pixels 
- origin: space center - in the middle of the scene
- by convention in ray tracing, viewport is often placed exactly 1 unit away from the camera's origin 
- xyz orientation: x  and y describe the ground, z describes the height
- dot product: operation that takes two vectors and returns a single scalar value
- length of a vector = square root of the dot product of the vector by itself
- changing camera viewpoint coordinates ensures translation, changing normal vector ensures rotation

TRANSLATION AND ROTATION
1. Translation (Movement)
Definition: Moving an object from one position to another without changing its shape, size, or orientation.
How it Works: Adds a fixed value to the object's coordinates.
Example: Moving a character in a game from (x, y) to (x + 5, y + 3).
Matrix Representation (2D):
| 1  0  Tx |
| 0  1  Ty |
| 0  0  1  |
Where (Tx, Ty) is the translation amount in the x and y directions.
2. Rotation
Definition: Rotating an object around a fixed point (usually the origin or center of the object).
How it Works: Applies a mathematical rotation formula based on angles.
Example: Spinning a spaceship in a game.
Matrix Representation (2D, counterclockwise by angle θ):
| cos(θ)  -sin(θ)  0 |
| sin(θ)   cos(θ)  0 |
|   0        0     1 
3. catastrophic cancellation - Still, on computers, we have a limited capacity to represent real numbers with the precision needed to calculate these roots as accurately as possible. Thus the formula suffers from the effect of a loss of significance. This happens when b and the root of the discriminant don't have the same sign but have values very close to each other. Because of the limited numbers used to represent floating numbers on the computer, in that particular case, the numbers would either cancel out when they shouldn't (this is called catastrophic cancellation) or round off to an unacceptable error (you will easily find more information related to this topic on the internet).

** PAIN POINTS DURING PROJECT **
- deciding the origin of the scene to which all objects including camera are relative
- when to make the ransformation from the top-left system to the 2d center system - when we shoot the ray? when we color the pixel?
- so far the wort thing was finding coordinates of a screen point in the viewport and in the 3d scene when there are rotations - done with transformation matrix 
- using dummies and drivers - one partner did parsing, other started working with dummy object, later replaces with real data object
- the program calculates something but it is lot of work to check if the values are actually true
- working with different orientation and assignment of the axis

CHECK OUT
- Bresenham-algorithm = transforms 2d coordinate to 3d space 
- camera-to-world transformation matrix
- gimbal lock and code rotations for rotations of camera
- are we gonna do preprocessing?


* TEST CASES *
1. order of the objects and intersections is correct from the camera view
2. object behind the camera
3. when rendering plane, ray and plane are parallel or even contained (plane normal  * ray = 0)