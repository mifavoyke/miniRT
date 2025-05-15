* miniRT - mifavoyke & zuzanapiarova * 

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
https://www.cs.uaf.edu/2012/spring/cs481/section/0/lecture/01_26_ray_intersections.html
https://www.realtimerendering.com/intersections.html
Torus (donut) intersection:
https://arxiv.org/pdf/2301.03191


* FOR ZUZANA *
- multithreding - parallelization?
- maybe optimization as in the article "Starter ray tracing math" above
- should we change viewport width in minirt struct when resizing? 

** GENERAL INFORMATION **
- viewport/film/near plane = the canvas or the imaginary somputer screen we put between camera and the scene to map rays to pixels 
- origin: space center - in the middle of the scene
- by convention in ray tracing, viewport is often placed exactly 1 unit away from the camera's origin 
- xyz orientation: x  and y describe the ground, z describes the height
- dot product: operation that takes two vectors and returns a single scalar value
- length of a vector = square root of the dot product of the vector by itself
- changing camera viewpoint coordinates ensures translation, changing normal vector ensures rotation
- camera is positioned in 3D space and oriented by a transformation matrix from default position (0, 0, 0) and default forward vector (0, 1, 0) to its specififed orientation and point in 3D
- in most cases, no, you do not need to explicitly normalize the camera's orientation vectors after applying the rotation matrices, because rotation matrices are orthogonal. This means that, after applying a rotation matrix, the basis vectors (right, forward, up) are guaranteed to remain normalized if they were initially normalized. BUT we normalize to avoid small deviations whn working with floats
- movement happens relative to camera, not relative to world origin 

In graphics/math practice:
It’s very common to treat positions and vectors interchangeably when doing algebra — because both are just 3D tuples (𝑥,𝑦,𝑧)
The distinction (point vs. vector) matters conceptually in geometry: 
A point defines a location in space.
A vector defines a direction and magnitude.
But for calculations like intersections, we often "abuse" this distinction when we’re only interested in the component-wise operations.

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
--> how transformation matrix is found:  
// finds transformation matrix of camera from origin to defined position C
// from C0[0,0,0] and v0(0, 1, 0) to Cn(cx, cy, cz) and vn(vx, vy, vz)
// to be applied to all points of the viewport - each pixel centre
// 1. initially, camera is placed in O[0,0,0] with orientation vector (0,1,0)-y
// 2. new orientation vn is set as camera's y(forward) axis
// 3. camera's x(right) axis is found as cross product of camera forward and global up vectors
// 4. camera's z(camera's up) axis is found as cross product of camera's forward and camera's right directions
// --> the R, F, U vectors form the matrice's x, y, z columns
// 5. translation from point C0 to point Cn is applied as last column
--> mapping pixel from 2d top-left screen to 3D viewport placed in the scene AND creating the ray
// 0. we start with pixel P0 in screen described by P0[x,y]
// 1. find Pv - transform pixel from different systems and find its center:
// from center of pixel in 2D in top left corner of screen
// to 2D viewport coord relative to center of viewport
// x,y specify start of the pixel - middle is P[x + 0.5, y + 0.5]
// 2. apply transformation matrix to point Pv to get its position in 3D
// Pv = point in viewport without transformation
// Pnew = point in 3d space relative to camera
// ray_vector = resulting vector

CYLINDER INTRESECTION:
// any point in ray: P = C + t*ray
// cylinder is defined by distance to its axis, not to a point or a plane, unlike a sphere
// cylinder is defined by all points that are at a fixed distance r from the cylinder’s axis
// to check whether a point lies on the cylinder surface, you need to find how far it is from the axis (not from a point)
// but in 3D, this “distance to a line” is hard to work with directly — so we project everything onto the plane perpendicular to the axis
// project both the ray(helper 2) and vector from the cylinder axis to the ray origin(helper 1) onto the plane perpendicular to the cylinder’s axis
// then the problem becomes 2D problem of a line intersecting a circle of radius r
// cylinder coat: || a x (p - b) || = r -> a=axis vector, b=cylinder base center, p=any point on coat
// cylinder height: 0 <= a o (p - b) <= h
// line: t = c + n*d  -> c=point on line, n=line unit vector, d=distance 
// t = a o (c + n*d - b)
// 1. solve for d
// Solving for d only gives you the distance at which the line intersects the infinite cylinder
// To see if the intersection occurs within the part we consider the actual cylinder, we need to check if
// the signed distance t from the cylinder base b along the axis a to the intersection p is within -h/2 and h/2 cylinder
// 2. solve for t - t means how far along the cylinder axis the point is
// --> -h/2 <= t <= h/2
// 3. find caps intersections


** PAIN POINTS DURING PROJECT **
- deciding the origin of the scene to which all objects including camera are relative
- when to make the ransformation from the top-left system to the 2d center system - when we shoot the ray? when we color the pixel?
- so far the wort thing was finding coordinates of a screen point in the viewport and in the 3d scene when there are rotations - done with transformation matrix 
- using dummies and drivers - one partner did parsing, other started working with dummy object, later replaces with real data object
- the program calculates something but it is lot of work to check if the values are actually true
- working with different orientation and assignment of the axis
- rotations and trasformation of the camera - we haev to transform around teh local camera axis and specify it with its R,F,U vectors by changing them using Rodriguezes formula and update the transformation matrix
- cylinder intersection !!!

CHECK OUT
- Bresenham-algorithm = transforms 2d coordinate to 3d space 
- camera-to-world transformation matrix
- gimbal lock and code rotations for rotations of camera


* TEST CASES *
1. order of the objects and intersections is correct from the camera view
2. object behind the camera
3. when rendering plane, ray and plane are parallel or even contained (plane normal  * ray = 0)
4. parsing: missing/extra parameters