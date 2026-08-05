*This project has been created as part of the 42 curriculum by zchoo, ka-tan.*

# 🔦 miniRT

> _One ray, one pixel, one bounce at a time_ ✨

miniRT is a small ray tracer written in C as part of the 42 curriculum, rendered live into a window with MiniLibX.
The goal of the project is to understand **how a renderer actually sees a scene**: parsing a scene description, firing a ray through every pixel, figuring out what that ray hits first, and working out how much light reaches that point.

It is basically a deep dive into **vectors, geometry, and light** — all the math a renderer hides behind a pretty picture 🔺

---

## 📖 Description

A ray tracer is a program that, for every pixel on screen:
1. builds a ray from the camera through that pixel
2. finds the closest object that ray hits, if any
3. works out how lit that point is — ambient light, plus any light source it can actually see
4. packs the result into a colour and writes it to the frame

miniRT recreates that loop in C, on top of a scene described in a plain-text `.rt` file.

The renderer is designed to:
- read a `.rt` scene file line by line, skipping blank lines and `#` comments
- validate every field strictly — wrong ranges, wrong token counts, and degenerate vectors are all rejected with a specific error
- build a camera basis (forward/right/up) from the parsed direction, including a fallback for the near-vertical case
- cast one ray per pixel and test it against every sphere, plane, and cylinder in the scene
- shade the closest hit with ambient + diffuse lighting, summed across every light source, with hard shadows
- stay interactive — the camera can be rotated and reset without restarting the program

Rather than aiming for a full path tracer, the project focuses on the subset explicitly required by the subject: three shapes, one bounce of light, no reflections or refractions.

---

## 🏗️ Project overview

A simplified flow of the renderer looks like this:

```text
parse_scene() -> t_scene (camera, ambient, lights, objects)
                       |
                       v
              for each pixel (x, y):
                camera_ray() -> hit_scene() -> shade_hit() -> pack_color()
                                    |
                                    -> closest of: sphere / plane / cylinder
```

---

## 🛠️ Instructions

1. To compile
```bash
make
```

2. Run
```bash
./miniRT scenes/minimalist.rt
```

3. Clean object files
```bash
make clean
```

4. Remove all generated files
```bash
make fclean
```

5. Rebuild from scratch
```bash
make re
```

---

## ⚙️ Execution flow notes

### Parsing
The parser reads the `.rt` file with `get_next_line`, skipping blank lines and `#` comments, and hands each remaining line to a tokeniser before dispatching on the first token (`A`, `C`, `L`, `sp`, `pl`, `cy`). Every parser checks its exact token count before touching any of them — a common failure mode fixed early on was assuming a fixed layout and reading past a short line.

```text
A <ambient ratio 0.0-1.0>   <R,G,B>
C <pos x,y,z>               <dir x,y,z, each in [-1,1], not all zero>   <fov 0-180, whole number>
L <pos x,y,z>                <brightness 0.0-1.0>                       <R,G,B>   (one or more)
sp <centre x,y,z>            <diameter>                                 <R,G,B>
pl <point x,y,z>             <normal x,y,z, each in [-1,1], not all zero> <R,G,B>
cy <centre x,y,z>            <axis x,y,z, each in [-1,1], not all zero>  <diameter> <height> <R,G,B>
```

### Camera & ray generation
Once `C` is parsed, the camera's `right`/`up` basis and `tan(fov/2)` are precomputed once — not per pixel. Every pixel then maps to a normalised-device coordinate, then a viewport offset along `right`/`up`, then a ray direction, normalised on construction.

### Intersection tests
Each shape gets its own hit function returning the closest valid `t` inside a `[t_min, t_max]` window. The scene-wide hit test walks every object, shrinking that window to the closest `t` found, so the surviving hit is always the nearest one.

### Shading & shadows
Ambient is added once per pixel. Then, for every light in the scene, a shadow ray checks whether *anything* sits between the hit point and that light before adding its diffuse contribution — an object behind the light doesn't count, which is why the shadow ray's hit test is capped at the distance to the light, not `infinity`.

### MLX loop & keybindings
`main` parses the scene, opens the MiniLibX window, renders one full frame, then hands control to `mlx_loop`. From there, everything is event-driven:

| Key / event      | Effect                                                        |
|-------------------|----------------------------------------------------------------|
| `Esc`             | closes the window and exits cleanly                            |
| red ✕ (titlebar)  | same as `Esc` — clean exit                                     |
| `←` / `→`         | yaw the camera left / right around the scene                   |
| `↑` / `↓`         | pitch the camera up / down                                     |
| `J` / `L`         | pan the camera left / right                                    |
| `I` / `K`         | pan the camera up / down                                       |
| `+` / `-`         | dolly the camera forward / backward along world Z (`=`/`-` key) |
| `1` / `2`         | narrow / widen the FOV by 5°, clamped to `[1°, 180°]`           |
| `F`               | toggle fisheye projection **on / off** for the current camera   |
| `R`               | reset the camera to exactly what the `.rt` file described       |
| `A`               | toggle a debug X/Y/Z axis overlay on/off                        |

Every key press that changes the camera re-renders the full frame before returning control to MLX.

---

## 🧠 Concepts we worked through

### 📐 Why a ray is just a point and a direction

A ray is nothing more than `origin + t * direction` — for any `t >= 0`, you get a point further along the ray. Nearly everything in the renderer boils down to solving for `t`: which `t` makes the ray touch a sphere, a plane, or a cylinder. Once direction is normalised, `t` is also literally the distance from the origin, which is why every other part of the renderer trusts `t` as a real-world distance (for picking the closest hit, or for shadow-ray distance checks).

### 🔄 Why we trace rays backward — camera → object → light

Physically, light starts at the source and scatters in every direction until, by chance, some of it reaches the eye. Simulating that literally would mean firing rays out from every light and hoping a tiny fraction happens to land on a pixel — almost all of that work is wasted. We flip the direction instead: fire one ray per pixel from the camera, find what it hits, then fire a second, short ray from that hit point straight at each light asking a single yes/no question — "is anything in the way?" Every ray computed this way directly contributes to the final image; none are spent searching for a path that might never arrive. It isn't how light actually travels, but for direct lighting with no bounces it produces the same picture, for a fraction of the rays a physically forward simulation would need.

### 🎯 Why sphere intersection reduces to a quadratic equation

Substituting the ray equation into the sphere equation `|P - centre|² = r²` produces a classic quadratic in `t`. Its discriminant tells you how many times the ray crosses the sphere (0, 1, or 2), and the smaller positive root is the entry point — the surface the camera actually sees. It's the same shape of problem for the cylinder body, just projected onto the plane perpendicular to the axis first.

### 🩹 Why every hit needs an epsilon offset

A ray that just bounced off a surface starts its next test (a shadow ray, for example) *at* that surface. Floating-point rounding means the ray can register a near-zero self-intersection with the very object it came from. Every hit test rejects `t` below a small epsilon for exactly this reason — skip it, and lit surfaces come out speckled with dark "acne" from a surface shadowing itself.

### 🪞 Why the normal has to face the ray

A surface normal always points a fixed way (outward, for a sphere), but the ray can approach from either side. Shading math (`dot(normal, light_dir)`) only makes sense if the normal points back *toward* the ray's origin side, so every hit test flips the normal when it's pointing the same way as the incoming ray. Skip this, and the underside of a surface shades as if it were lit from behind.

### 🧭 Why the camera needs an orthonormal basis

To turn a 2D pixel into a 3D ray you need three mutually perpendicular axes: forward (parsed from the file), right, and up. `right` comes from `cross(forward, world_up)` — which collapses to a zero vector if the camera looks straight up or down, since forward and world_up become parallel. The fix is a fallback reference axis for exactly that case, computed once when the camera is built or rotated.

### 🌐 Why rectilinear projection has a hard breaking point near FOV 180°

The standard camera formula maps a pixel to a ray angle via `offset = tan(θ)`, where `θ` is half the FOV. That's fine until `θ` approaches 90° (FOV → 180°): `tan(θ)`, and the true camera-to-plane distance `R·sec(θ)`, both run off toward infinity, because the edge ray becomes parallel to a flat image plane and never actually crosses it. Rather than rewriting the whole projection, we clamp the parsed FOV a hair below 180° — the subject only requires we not crash or produce garbage at the edge of the allowed range, not that we render a mathematically perfect 180°.

### 🐟 Why the fisheye toggle exists, and what it trades away

Fisheye swaps `tan(θ)` for a direct linear mapping, `offset = R·θ` — equivalent to projecting rays onto a curved dome instead of a flat plane. Equal angle steps land at equal spacing on a dome no matter how wide `θ` gets, so it never blows up the way the flat-plane version does. The trade-off: unwrapping a curved surface onto a flat screen bends straight lines, in exchange for keeping objects a more consistent size near the frame edges instead of the "stretched" look rectilinear gives at wide FOV. `F` swaps between the two live so the difference is easy to see on the same scene.

### 📏 Why every direction vector gets normalised before it's used

A vector carries both a direction and a length; `dot()` only collapses to a clean `cos(θ)` when both inputs are unit length. Skip normalising, and every dot product used for shading or angle comparisons gets scaled by whatever leftover magnitude the raw vector had — no crash, just quietly wrong brightness. Normalising once, right after a vector is computed (camera basis at parse time, ray direction in `ray_init`), keeps that assumption true everywhere else in the codebase without re-deriving it per call.

### 🌗 Why closest-t, not first-hit, decides what you see

A scene with three overlapping objects means a ray can hit more than one of them. Only the *nearest* hit is visible — everything else is behind it. That's why the hit loop keeps shrinking its search window (`t_max`) to the closest `t` found so far as it walks every object, rather than stopping at the first one it happens to test.

---

## 📦 About the Hit Record (`t_hit`)

A single boolean — "did the ray hit something?" — isn't enough information to shade a pixel. Shading needs to know *where* the ray landed, *which way* the surface faces there, *how far away* it is, and *which object* it belongs to (for its colour). That's what `t_hit` bundles together: `t`, `point`, `normal`, and `obj`.

### A simple mental picture

```text
         ray
          │
   ●──────┼────────────●
 sphere   │           plane
          │
          ▼
      t_hit {
        t      = distance along the ray
        point  = origin + t * direction
        normal = surface normal at that point, facing the ray
        obj    = the object that owns this surface
      }
```

When a ray could hit several objects, the loop keeps re-testing with a shrinking `t_max` and only overwrites the `t_hit` when a closer one turns up. By the time every object has been checked, the surviving `t_hit` is exactly the one thing the camera can see through that pixel — everything the shader needs, and nothing it doesn't.

---

## 🎁 Bonus features

### 💡 Multi-light support

The mandatory spec allows exactly one `L` per scene. The bonus build lifts that restriction — a `.rt` file can declare several `L` lines, and each one contributes its own diffuse term and its own independent shadow ray at every hit point, summed together. It's the same "sum across every light" logic already covered above; the bonus build just removes the single-light limit that fed it, and the parser's duplicate-check that rejects a second `A` or `C` deliberately does not apply to `L`.

```bash
make bonus
./miniRT scenes_bonus/multi_light.rt
```

### ✨ Specular highlights

Diffuse alone makes a lit surface look flat and matte — real materials also throw back a small, bright highlight wherever the surface happens to be angled exactly right to bounce a light straight into the camera. We add that with the Phong model: reflect the light direction around the surface normal, then raise `max(0, dot(reflect_dir, view_dir))` to a shininess exponent, so the highlight falls off sharply instead of fading gradually the way diffuse does. It's added on top of ambient + diffuse per light, and gated by the same shadow ray already used for diffuse — no visible light, no highlight either.

```bash
make bonus
./miniRT scenes_bonus/specular_highlights.rt
```
### ✨ Checker boards

The bonus parser enables a procedural checkerboard whenever an object has an optional second RGB colour. The normal object colour becomes the first set of squares, while the extra colour becomes the alternating set:

```text
pl <point> <normal> <R,G,B> <checker R,G,B>
sp <centre> <diameter> <R,G,B> <checker R,G,B>
cy <centre> <axis> <diameter> <height> <R,G,B> <checker R,G,B>
```

For example, this creates a light-grey and dark-grey checkerboard plane:

```text
pl 0,-2,0 0,1,0 225,225,225 35,35,35
```

At each hit point, the renderer calculates a checker-cell index and selects the
first colour for even cells or the second colour for odd cells. Planes use two
local axes along their surface, so their checkerboard follows the plane when it
is rotated. Spheres and cylinders currently use a three-dimensional world-space
grid rather than UV mapping, producing a procedural block pattern across their
curved surfaces.

The global square size is configured in `includes_bonus/miniRT_bonus.h`:

```c
# define CHECKER_SIZE 2.0
```

A smaller value produces more, finer squares; a larger value produces fewer,
larger squares. Omitting the second RGB colour keeps the object solid.

```bash
make bonus
./miniRT_bonus scenes_bonus/checkerboard.rt
```

---

## 📚 Resources

References used to understand the project topic:
- [_Ray Tracing in One Weekend_](https://raytracing.github.io/)
- _The Ray Tracer Challenge: A Test-Driven Guide to Your First 3D Renderer_ by Jamis Buck

AI was used for referencing, concept clarifications, visualisation and formula explanations

---

## 🌱 Final thought

We were surprised when our wrong math didn't crash the program but rendered quietly wrong: a stretched sphere, a swapped cross product that cancelled out and looked right until a new scene exposed it. Chasing bugs like that made the math feel real: vectors and dot products turning into shadows, highlights, a sphere that actually looks round. The closer we followed light's actual behaviour, the more real the render looked, and the more we understood exactly what the math was trying to show us. ✨
