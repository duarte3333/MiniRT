# MiniRT

### Coordinate System

Standard system:
![Untitled](https://github.com/duarte3333/MiniRT/assets/76222459/5438c90a-4147-431e-920c-0e34759552c7)

With a offset, just need to do: x = x + WIDTH/2 and y = -y + HEIGHT/2. The y axis was flipped also. 

![Untitled 1](https://github.com/duarte3333/MiniRT/assets/76222459/568d1342-3ccd-41cd-93c0-2e93d37edb1c)

### Color manipulation

**Change intensity:**

k(R, G, B) = (kR, kG, KB)

So for example, (32, 0, 128) is twice time as bright as (16, 0, 64).

> **Attention:** If r, g or b > 255 becomes 255 to avoid overflow
> 

### Orientation and position of viewport
![Untitled 2](https://github.com/duarte3333/MiniRT/assets/76222459/c88543b0-4a2f-4231-89b9-ce86d4783a91)

### Coordinates of the world in pixel coordinates
![Untitled 3](https://github.com/duarte3333/MiniRT/assets/76222459/fa3ece66-c7f9-4942-8bab-2dfade77bd29)

![Untitled 4](https://github.com/duarte3333/MiniRT/assets/76222459/1e765ddd-2f69-4e63-9fed-086878415a22)

If I have a window of 1000x1000 pixels, then for the pixel (1,1) will be 

Vx = x*(Vw/Cw) = 1*(1/1000) = 0.001

Vy = y*(Vw/Cw) = 1*(1/1000) = 0.001

which means that 1 pixel = 0.001 world units. 

### Ray Equation

![Untitled 5](https://github.com/duarte3333/MiniRT/assets/76222459/9d65c832-14d5-4792-aee2-c01d00ac45a6)
![Untitled 6](https://github.com/duarte3333/MiniRT/assets/76222459/d56ec057-7991-4dbf-9913-a73aa0d396dc)

The vector **O**(Ox, Oy, Oz) represents the origin of the rays and the vector **D** represents the direction of the rays.

The value of **t** goes from -infinite to +infinite, where:
t < 0 , it means that it is behind the camera.

- 0 <= t <= 1, it is between the camera and the projection plane
- t > 1, is in front of the projection/viewport plane.

<aside>
💡 So the idea is to shoot a ray to all the pixels and see which is the closest object that intersects and then paint.

</aside>

![Untitled 7](https://github.com/duarte3333/MiniRT/assets/76222459/935fffd5-e215-4206-a168-9a27b5cb86de)

### Intersection between sphere and ray

![Untitled 8](https://github.com/duarte3333/MiniRT/assets/76222459/4d878d13-3778-457b-8206-c2b100831222)


Then, each sphere calculates its value of t in a loop, the sphere that has the lowest value of t "wins" that pixel because it is the one closest to the point of view and is painted with the color of the sphere that won.

### Intersection between plane and ray

![Untitled 9](https://github.com/duarte3333/MiniRT/assets/76222459/6b44fb14-00e4-4c23-93fc-fb4e83a08a2a)


### Intersection between cylinder and ray

Not done yet.

## Ray of light interacting with surfaces

**Simplifying Assumptions:**

- All light is considered white, simplifying color calculations to a single intensity value (i).
- Atmospheric effects are ignored, avoiding complexity of dimming lights over distance due to air particles.

### Point Lights

They emit light equally in every direction; this is why they are also called *omnidirectional lights*.

![Untitled 10](https://github.com/duarte3333/MiniRT/assets/76222459/f78d0e0c-1272-4b3b-a844-07b7e3d30042)


Its a good approximation of a light bulb.

### Directional Lights

Like point lights, directional lights have an intensity, but unlike them, they don’t have a position; instead, they have a fixed *direction*.(infinitely distant point lights located in the specified direction)

![Untitled 11](https://github.com/duarte3333/MiniRT/assets/76222459/291d085a-c095-45c9-878c-41f9e0467c22)

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

![Untitled 12](https://github.com/duarte3333/MiniRT/assets/76222459/808bf84e-6fd4-4a33-a03d-660fd73418a1)

**Math modelation:**

![Untitled 13](https://github.com/duarte3333/MiniRT/assets/76222459/a28b3550-bdd4-450c-a265-80118be8374a)


A = Surface size; N = Surface normal; L= Light Direction

If N and L have the same direction: I =  A , so energy reflected per u.a is equal to incident energy.

![Untitled 14](https://github.com/duarte3333/MiniRT/assets/76222459/03f00359-b3fe-41f2-a39f-2268fde5a089)

RS is the “width” of the ray.

### The Diffuse Reflection Term

![Untitled 15](https://github.com/duarte3333/MiniRT/assets/76222459/d7360b58-377c-4a1a-88d3-4c9d0194f384)


**Fraction of light that is reflected** as a function of the angle between the surface normal and the direction of the light:

![Untitled 16](https://github.com/duarte3333/MiniRT/assets/76222459/c37e2237-29f5-4b84-b584-f48bf1989b02)

if cos(alpha) < 0, I needs to be zero, because I dont want the surface to become darker.

### The Diffuse Reflection Equation

For point light or directional light in ‘matte’ objects:

![Untitled 17](https://github.com/duarte3333/MiniRT/assets/76222459/f7cab13d-77b4-4886-8751-0f2eeabaccf6)

being **n** the number of point/directional lights, **Ia** = ambient intensity light, **N** = normal in a scene,

**L** = directional of ray light.

### Sphere Normals

![Untitled 18](https://github.com/duarte3333/MiniRT/assets/76222459/3b66a9be-90f0-4dac-92f6-6bcb2c844aa1)

The divison by his module his to the lenght of the vector became 1.

### How to transform RGB values to INT

![Untitled 19](https://github.com/duarte3333/MiniRT/assets/76222459/cdf2821a-3237-4c94-947c-52e413e7d569)

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

![Untitled 20](https://github.com/duarte3333/MiniRT/assets/76222459/0054cdd4-5c0c-4502-aeb7-f029f2121ec2)

‘shiny objects’ - it behaves like a mirror

![Untitled 21](https://github.com/duarte3333/MiniRT/assets/76222459/0b9a3056-1c16-4726-afcd-119b23cdcdad)

### Math model

![Untitled 22](https://github.com/duarte3333/MiniRT/assets/76222459/f61231c4-a87e-4642-a964-1cb6fb0fb487)

**L** = light direction, **R** total reflection vector, **V**= reflection vector

alpha = 0,  means all light is reflected.

alpha = 90, means no light is reflected.

The perfect way to describe this model is with a cos(alpha). 

![Untitled 23](https://github.com/duarte3333/MiniRT/assets/76222459/0a4c182d-e965-4c01-a17a-6aedf3f3d617)

s is the exponent of the cossine(**specular exponent**), if s is higher the reflection becomes with less degrees of shininess and gets more shinier.

### The Specular Reflection Term

![Untitled 24](https://github.com/duarte3333/MiniRT/assets/76222459/c067d708-9b72-42bb-b96a-1c97dd1b0ec2)

### The full ilumination equation

![Untitled 25](https://github.com/duarte3333/MiniRT/assets/76222459/c3f0cc6b-ba2b-4157-a896-71b8faeab541)

being **Ip =** total ilumination **, n** the number of point/directional lights, **Ia** = ambient intensity light, **N** = normal in a scene,**L** = directional of ray light, **R**=full reflection vector and **V**=reflection vector.

**Attention:** Although before in the scene the light intensities add up to 1.0, now that we’re adding the contributions of specular reflections, so the values could go beyond that range.

## Shadows and Reflections

### Shadows

If there’s an object between the point and the light, don’t add the illumination coming from this light.

![Untitled 26](https://github.com/duarte3333/MiniRT/assets/76222459/93a9b839-e299-4abb-b8e2-19913922ba61)

- Instead of starting from the camera, the ray starts from P.
- The direction of the ray is not (V - O), but L
- Range of t is from P to Inf

**Ray equation for shadows:** 

![Untitled 27](https://github.com/duarte3333/MiniRT/assets/76222459/056ed0a3-0795-40bd-8716-3157a7202f36)

Two intersections mean that the point is in shadow:

![Untitled 28](https://github.com/duarte3333/MiniRT/assets/76222459/a93e1d44-7f24-465e-80e0-4f9f226f61ca)

### Intersections of shadows

In this example the point P1(a point from another sphere) only will have ambient light because it intersects a object in direction of the light.

![Untitled 29](https://github.com/duarte3333/MiniRT/assets/76222459/6a1de8a9-e238-40db-979d-faf6bef03414)

### Reflections

![Untitled 30](https://github.com/duarte3333/MiniRT/assets/76222459/740872af-ddbb-4977-8103-8f092e477c3b)

For each pixel, we create a ray from the camera to the scene and we call `TraceRay` to figure out what color the camera “sees” in that direction.

If `TraceRay` determines that the camera is seeing a mirror, it just needs to compute the direction of the reflected ray and to figure out the color of the light coming from that direction. it must call . . . *itself*(**Recursive situation!!**).

It should avoid the infinite hall effect! (Case where the reflection has infinity surfaces to reflect).

r = 0, zero reflections. r = 1, first level of reflections… 

**Reflectiveness:** number between 0 and 1, for the intensity of reflection. objects can be partially reflective.

###
