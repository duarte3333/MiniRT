# MiniRT

### Coordinate System

Standard system:

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled.png)

With a offset, just need to do: x = x + WIDTH/2 and y = -y + HEIGHT/2. The y axis was flipped also. 

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%201.png)

### Color manipulation

**Change intensity:**

k(R, G, B) = (kR, kG, KB)

So for example, (32, 0, 128) is twice time as bright as (16, 0, 64).

> **Attention:** If r, g or b > 255 becomes 255 to avoid overflow
> 

### Orientation and position of viewport

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%202.png)

### Coordinates of the world in pixel coordinates

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%203.png)

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%204.png)

If I have a window of 1000x1000 pixels, then for the pixel (1,1) will be 

Vx = x*(Vw/Cw) = 1*(1/1000) = 0.001

Vy = y*(Vw/Cw) = 1*(1/1000) = 0.001

which means that 1 pixel = 0.001 world units. 

### Ray Equation

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%205.png)

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%206.png)

The vector **O**(Ox, Oy, Oz) represents the origin of the rays and the vector **D** represents the direction of the rays.

The value of **t** goes from -infinite to +infinite, where:
t < 0 , it means that it is behind the camera.

- 0 <= t <= 1, it is between the camera and the projection plane
- t > 1, is in front of the projection/viewport plane.

<aside>
💡 So the idea is to shoot a ray to all the pixels and see which is the closest object that intersects and then paint.

</aside>

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%207.png)

### Intersection between sphere and ray

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%208.png)

Then, each sphere calculates its value of t in a loop, the sphere that has the lowest value of t "wins" that pixel because it is the one closest to the point of view and is painted with the color of the sphere that won.

### Intersection between plane and ray

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%209.png)

### Intersection between cylinder and ray

Not done yet.

## Ray of light interacting with surfaces

**Simplifying Assumptions:**

- All light is considered white, simplifying color calculations to a single intensity value (i).
- Atmospheric effects are ignored, avoiding complexity of dimming lights over distance due to air particles.

### Point Lights

They emit light equally in every direction; this is why they are also called *omnidirectional lights*.

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2010.png)

Its a good approximation of a light bulb.

### Directional Lights

Like point lights, directional lights have an intensity, but unlike them, they don’t have a position; instead, they have a fixed *direction*.(infinitely distant point lights located in the specified direction)

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2011.png)

Its a good approximation of the Sun.

### Ambient Light

How do rays of light reach the floor under a table?

Light hits objects scattering(espalhando) back into the scene, even from objects that receive light and scatter it. This cascading effect continues until all light energy is absorbed, implying all objects act as light sources, but for simplicity, this intricate process, known as global illumination, isn't be done, it will be simplified.

**Simplified solution:** Ambient light contributes some light to every point in the scene, regardless of where it is.

<aside>
💡 **Every object is a light source**

</aside>

Real-life = Ambient light + Directional light + Point light.

### Diffuse Reflection

Object’s can be ‘matte’ or ‘shiny’. A example of a matte is a wall because no matter if I move in relation to the wall, his color will not change.

Ray of light hits a matte object:

The ray is scattered back into the scene **equally** in every direction (**diffuse reflection**).

The amount of light **reflected depend on the angle:**

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2012.png)

**Math modelation:**

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2013.png)

A = Surface size; N = Surface normal; L= Light Direction

If N and L have the same direction: I =  A , so energy reflected per u.a is equal to incident energy.

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2014.png)

RS is the “width” of the ray.

### The Diffuse Reflection Term

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2015.png)

**Fraction of light that is reflected** as a function of the angle between the surface normal and the direction of the light:

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2016.png)

if cos(alpha) < 0, I needs to be zero, because I dont want the surface to become darker.

### The Diffuse Reflection Equation

For point light or directional light in ‘matte’ objects:

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2017.png)

being **n** the number of point/directional lights, **Ia** = ambient intensity light, **N** = normal in a scene,

**L** = directional of ray light.

### Sphere Normals

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2018.png)

The divison by his module his to the lenght of the vector became 1.

### How to transform RGB values to INT

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2019.png)

### How to perform color multiplication to increase the brightness

```c
/* Recebe o inteiro e depois da right shift para
levar os ter 8 bits do r, g ou b para o mais a 
direita possivel. O &255 assegura que nao existe 
overflow de cores.*/
int	color_multiply(t_color color, float brightness)
{
	int fcolor;
	
	fcolor = get_rgb(color.r, color.g, color.b);
	color.r = (fcolor >> 16 & 255) * brightness;
	color.g = (fcolor >> 8 & 255) * brightness;
	color.b = (fcolor & 255) * brightness;
	return (get_rgb(color.r , color.g, color.b));
}
```

### Specular Reflection

‘matte objects’ - scattered back to the scene equally in every direction

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2020.png)

‘shiny objects’ - it behaves like a mirror

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2021.png)

### Math model

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2022.png)

**L** = light direction, **R** total reflection vector, **V**= reflection vector

alpha = 0,  means all light is reflected.

alpha = 90, means no light is reflected.

The perfect way to describe this model is with a cos(alpha). 

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2023.png)

s is the exponent of the cossine(**specular exponent**), if s is higher the reflection becomes with less degrees of shininess and gets more shinier.

### The Specular Reflection Term

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2024.png)

### The full ilumination equation

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2025.png)

being **Ip =** total ilumination **, n** the number of point/directional lights, **Ia** = ambient intensity light, **N** = normal in a scene,**L** = directional of ray light, **R**=full reflection vector and **V**=reflection vector.

**Attention:** Although before in the scene the light intensities add up to 1.0, now that we’re adding the contributions of specular reflections, so the values could go beyond that range.

## Shadows and Reflections

### Shadows

If there’s an object between the point and the light, don’t add the illumination coming from this light.

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2026.png)

- Instead of starting from the camera, the ray starts from P.
- The direction of the ray is not (V - O), but L
- Range of t is from P to Inf

**Ray equation for shadows:** 

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2027.png)

Two intersections mean that the point is in shadow:

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2028.png)

### Intersections of shadows

In this example the point P1(a point from another sphere) only will have ambient light because it intersects a object in direction of the light.

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2029.png)

### Reflections

![Untitled](MiniRT%202e8584bf23274350941d1c03b9cb1aca/Untitled%2030.png)

For each pixel, we create a ray from the camera to the scene and we call `TraceRay` to figure out what color the camera “sees” in that direction.

If `TraceRay` determines that the camera is seeing a mirror, it just needs to compute the direction of the reflected ray and to figure out the color of the light coming from that direction. it must call . . . *itself*(**Recursive situation!!**).

It should avoid the infinite hall effect! (Case where the reflection has infinity surfaces to reflect).

r = 0, zero reflections. r = 1, first level of reflections… 

**Reflectiveness:** number between 0 and 1, for the intensity of reflection. objects can be partially reflective.

###
