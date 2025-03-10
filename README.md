* miniRT - mifavoke & zuzanapiarova * 

** RESOURCES **
Ray tracing basics Stanford paper
https://cs.stanford.edu/people/eroberts/courses/soco/projects/1997-98/ray-tracing/implementation.html
Starter ray tracing math:
https://www.gabrielgambetta.com/computer-graphics-from-scratch/01-common-concepts.html
Optimizing - not all objects are considered, only those in path of the ray:
https://gfxcourses.stanford.edu/cs348b/spring22content/media/intersection/rt1_3GyBK6F.pdf



* FOR YEVA *
- vectors must be normalized, we can check if they are during parsing, with function is_vector_normalized from math/vector.c that returns 0(no) or 1(yes) so we must put error if 0 - not normalized

* FOR ZUZANA *

** GENERAL INFORMATION **
- near plane = the canvas or the imaginary somputer screen we put between camera and the scene to map rays to pixels 
- origin: space center - in the middle of the scene 
- xyz orientation: x  and y describe the ground, z describes the height
- dot product: operation that takes two vectors and returns a single scalar value
- length of a vector = square root of the dot product of the vector by itself
- changing camera viewpoint coordinates ensures translation, changing normal vector ensures rotation


** DOING: ** 
- did viewport setup so we have info about the viewport plane, must be regenreated or each new scene/movement 
- working on finding corner points
- then will map each pixel to the viewport scale and get its coordinates in the 3d scene through which we will shoot the ray to scene 


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
- using dummies and drivers - one partner did parsing, other started working with dummy object, later replaces with real data object

CHECK OUT
- gimbal lock and code rotations for rotations of camera
- 