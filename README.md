* miniRT - mifavoke & zuzanapiarova * 

** RESOURCES **
Ray tracing basics Stanford paper
https://cs.stanford.edu/people/eroberts/courses/soco/projects/1997-98/ray-tracing/implementation.html
Starter ray tracing math:
1. https://www.gabrielgambetta.com/computer-graphics-from-scratch/01-common-concepts.html

** GENERAL INFORMATION **
- near plane = the canvas or the imaginary somputer screen we put between camera and the scene to map rays to pixels 
- origin: space center - in the middle of the scene 
- xyz orientation: x  and y describe the ground, z describes the height
- dot product: operation that takes two vectors and returns a single scalar value
- length of a vector = square root of the dot product of the vector by itself


** DOING: ** 


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

** PAIN POINTS DURING PROJECT **
- deciding the origin of the scene to which all objects including camera are relative
- when to make the ransformation from the top-left system to the 2d center system - when we shoot the ray? when we color the pixel?

CHECK OUT
- gimbal lock and code rotations for rotations of camera
- 