# miniRT - Ray tracing engine

## Mathematical Foundations

### Ray tracing algorithm

The ray tracing engine follows these fundamental steps:

1. For each pixel, generate a ray from the camera through the pixel center
2. Test ray intersections with all scene objects
3. Find the nearest intersection point
4. Apply lighting models to determine pixel color
5. Cast shadow rays to determine object occlusion

### Ray-Object intersections

#### Sphere intersection
Using the parametric ray equation `P = O + t * D` and sphere equation `|P - C|² = r²`:

```
Vector cam_to_sphere = sphere_center - ray_origin
a = dot(ray_direction, ray_direction)
b = 2 * dot(cam_to_sphere, ray_direction)  
c = dot(cam_to_sphere, cam_to_sphere) - radius²

discriminant = b² - 4ac
if discriminant >= 0:
    t1,t2 = (-b ± √discriminant) / 2a
```

#### Plane intersection
Using plane equation `(P - Q) · n = 0` where Q is a point on the plane and n is the normal:

```
to_plane = plane_point - ray_origin
denominator = dot(ray_direction, plane_normal)
t = dot(to_plane, plane_normal) / denominator
```

#### Cylinder intersection
Cylinders require testing both the cylindrical surface and end caps:

```
ray_axis_cross = cross(ray_direction, cylinder_axis)
base_ray_vector = cylinder_base - ray_origin

a = dot(ray_axis_cross, ray_axis_cross)
b = 2 * dot(base_ray_vector, ray_axis_cross)
c = dot(base_ray_vector, base_ray_vector) - radius²
```

### Lighting model - Phong Reflection

The engine implements the Phong reflection model combining three lighting components:

#### Ambient lighting
Provides base illumination to prevent completely dark areas:
```
I_ambient = ka * I_a * material_color
```

#### Diffuse lighting (Lambertian Reflectance)
Creates the matte appearance based on surface orientation:
```
I_diffuse = kd * I_light * max(0, N · L)
```
Where:
- `N` = surface normal vector
- `L` = light direction vector

#### Specular lighting
Creates shiny highlights using the reflection vector:
```
R = L - 2 * N * (L · N)
I_specular = ks * I_light * max(0, R · V)^n
```
Where:
- `R` = reflected light vector  
- `V` = view direction vector
- `n` = shininess coefficient (REFLECTION = 100)

### Shadow calculation

Shadows are calculated by casting rays from intersection points toward light sources:

1. From intersection point to light source
2. Check if any objects block the shadow ray
3. Only consider objects between surface and light
4. Reduce lighting contribution if occluded

## Controls

### Camera Movement
- **W/S**: Move up/down along camera's local up axis
- **A/D**: Strafe left/right along camera's local right axis  
- **Mouse Scroll**: Zoom in/out along camera's forward axis

### Camera Rotation
- **Arrow Keys Up/Down**: Pitch rotation around X-axis
- **J/K**: Yaw rotation around Y-axis
- **Arrow Keys Left/Right**: Roll rotation around Z-axis

### Object Interaction
- **Mouse Click**: Select objects for resizing
- **Mouse Drag**: Resize selected objects

### System Controls
- **ESC**: Exit program

## Scene File Format (.rt)

The program must take a scene description file with the .rt extension as an argument.

./minirt scenes/scene1.rt

The .rt file contains parameters that describe the scene, and includes the lightning parameters, camera information, and descriptions of objects in the scene. Each type of element can be set in any order in the file. The project must expect at least the following parameters with properties:

Mandatory paramters:
Ambient lighting   A  0.2  255,255,255
ambient lighting ratio in the range [0.0,1.0]
R, G, B colors in the range [0-255]
Can only be declared once in the scene
Camera   C  -50.0,0,20  0,0,1  70
x, y, z coordinates of the viewpoint
3D normalized orientation vector in the range [-1,1] for each x, y, z axis
Horizontal field of view (FOV) in degrees in the range [0,180]
Can only be declared once in the scene
Light   L  -40.0,50.0,0.0  0.6  10,0,255
x, y, z coordinates of the light point
brightness ratio in the range [0.0,1.0]
light color described by R, G, B colors in the range [0-255]
Scene objects:
A. Sphere   sp  0.0,0.0,20.6  12.6  10,0,255

x, y, z coordinates of the sphere center
the sphere diameter
R,G,B colors in the range [0-255]
B. Plane   pl  0.0,0.0,-10.0  0.0,1.0,0.0  0,0,225

x, y, z coordinates of a point in the plane
3D normalized normal vector in the range [-1,1] for each x, y, z axis
R,G,B colors in the range [0-255]
C. Cylinder   cy  50.0,0.0,20.6  0.0,0.0,1.0  14.2  21.42  10,0,255

x, y, z coordinates of the center of the cylinder
3D normalized vector of axis of cylinder in the range [-1,1] for each x, y, z axis
the cylinder diameter
the cylinder height
R, G, B colors in the range [0,255]
On top of that, the program must be able to resize the unique properties of objects (diameter for a sphere and the width and height for a cylinder). The program must also be able to apply translation and rotation transformations to objects, lights, and cameras (except for spheres and lights that cannot be rotated).

Example input to the project - lollypop.rt:
```
A 0.1             0,0,0      
C 0,0,60          0,0,-1            70 
L 0,40,50         0.6               255,255,255
L 0,50,30         0.4               255,0,0

sp 0,0,0          10                255,80,100
cy 0,0,0          0,1,0             12 2.5           60,220,200
cy 0,-15,0        0,-1,0            2 30             255,255,230
pl 0,-30,0        0,1,0             200,200,200
pl 0,50,0         0,-1,0            220,220,230
pl 0,0,-50        0,0,1             100,100,120
pl -50,0,0        1,0,0             140,120,120
pl 50,0,0         -1,0,0            120,140,140
```

## Authors

Built by Yeva Husieva & Piarová Zuzana
