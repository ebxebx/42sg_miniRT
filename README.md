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

## ✨ Features

### 🧩 Parsing & scene setup
- tokenisation of each line, tolerant of tabs and repeated spaces
- dedicated parser per element: `A`, `C`, `L`, `sp`, `pl`, `cy`
- own `parse_double` (digit/dot validation, no reliance on libc `atof`)
- range validation on every numeric field, with a distinct error message per failure
- duplicate detection for `A` and `C` (exactly one each); `L` may appear one or more times
- direction/normal/axis vectors are rejected outright if any component is outside `[-1,1]` or the vector is all-zero

### 🎥 Camera & ray generation
- camera basis (`right`, `up`) derived from the parsed forward direction at parse time
- degenerate case handled: if the camera points almost straight up or down, the basis falls back to a `(0,0,1)` reference instead of producing a zero cross product
- per-pixel ray built from FOV, aspect ratio, and the camera basis, normalised once in `ray_init`

### 🔺 Shapes & intersections
- sphere: closest positive root of the standard ray–sphere quadratic
- plane: single division, rejecting rays parallel to the surface
- cylinder: body via the 2D projection perpendicular to the axis, plus two disc caps — closest of the three wins

### 💡 Lighting & shadows
- ambient light applied once per pixel, never letting a surface go fully black
- diffuse lighting summed across **every** light in the scene (not just one)
- hard shadows via a shadow ray offset along the normal by an epsilon, checked against the distance to the light so objects behind a light don't cast one

### 🎮 Interactive controls
- arrow keys rotate the camera around the scene
- `J/L` pan left/right and `I/K` pan up/down
- `+` / `-` dolly the camera forward/backward along world Z
- `1` / `2` narrow/widen the FOV, clamped to `[1, 180]`
- `F` toggles a fisheye projection on top of the current camera
- a reset key snaps the camera straight back to exactly what the `.rt` file described
- a debug overlay can toggle three coloured X/Y/Z axis lines on and off, useful for getting your bearings in a new scene
- full key list further down, under Usage examples

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

### Main ideas behind the project
- **Parser**: turns a text file into a `t_scene` — a camera, an ambient light, a linked list of lights, and a linked list of shapes
- **Camera**: turns a pixel coordinate into a world-space ray
- **Hit test**: turns a ray into the *nearest* thing it touches, or nothing
- **Shader**: turns a hit point into a colour, using the lights that can actually reach it
- **MLX loop**: turns a grid of colours into pixels on screen, and keeps listening for key presses

---
## 🧠 Concepts we worked through

### 📐 Why a ray is just a point and a direction

A ray is nothing more than `origin + t * direction` — for any `t >= 0`, you get a point further along the ray. Nearly everything in the renderer boils down to solving for `t`: which `t` makes the ray touch a sphere, a plane, or a cylinder. Once direction is normalised, `t` is also literally the distance from the origin, which is why every other part of the renderer trusts `t` as a real-world distance (for picking the closest hit, or for shadow-ray distance checks).

### 🎯 Why sphere intersection reduces to a quadratic equation

Substituting the ray equation into the sphere equation `|P - centre|² = r²` produces a classic quadratic in `t`. Its discriminant tells you how many times the ray crosses the sphere (0, 1, or 2), and the smaller positive root is the entry point — the surface the camera actually sees. It's the same shape of problem for the cylinder body, just projected onto the plane perpendicular to the axis first.

### 🩹 Why every hit needs an epsilon offset

A ray that just bounced off a surface starts its next test (a shadow ray, for example) *at* that surface. Floating-point rounding means the ray can register a near-zero self-intersection with the very object it came from. Every hit test rejects `t` below a small epsilon for exactly this reason — skip it, and lit surfaces come out speckled with dark "acne" from a surface shadowing itself.

### 🪞 Why the normal has to face the ray

A surface normal always points a fixed way (outward, for a sphere), but the ray can approach from either side. Shading math (`dot(normal, light_dir)`) only makes sense if the normal points back *toward* the ray's origin side, so every hit test flips the normal when it's pointing the same way as the incoming ray. Skip this, and the underside of a surface shades as if it were lit from behind.

### 🧭 Why the camera needs an orthonormal basis

To turn a 2D pixel into a 3D ray you need three mutually perpendicular axes: forward (parsed from the file), right, and up. `right` comes from `cross(forward, world_up)` — which collapses to a zero vector if the camera looks straight up or down, since forward and world_up become parallel. The fix is a fallback reference axis for exactly that case, computed once when the camera is built or rotated.

### 🌗 Why closest-t, not first-hit, decides what you see

A scene with three overlapping objects means a ray can hit more than one of them. Only the *nearest* hit is visible — everything else is behind it. That's why the hit loop keeps shrinking its search window (`t_max`) to the closest `t` found so far as it walks every object, rather than stopping at the first one it happens to test.

---

## 📦 About the Hit Record (`t_hit`)

A single boolean — "did the ray hit something?" — isn't enough information to shade a pixel. Shading needs to know *where* the ray landed, *which way* the surface faces there, *how far away* it is, and *which object* it belongs to (for its colour). That's what `t_hit` bundles together: `t`, `point`, `normal`, and `obj`.

### A simple mental picture

```text
        ray
         │
   ●─────┼────────────●
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
| `F`               | toggle a fisheye projection on top of the current camera        |
| `R`               | reset the camera to exactly what the `.rt` file described       |
| `A`               | toggle a debug X/Y/Z axis overlay on/off                        |

Every key press that changes the camera re-renders the full frame before returning control to MLX.

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

## ▶️ Usage examples

### Render a scene
```bash
./miniRT scenes/minimalist.rt
./miniRT scenes/full.rt
```

### Or via the Makefile's own scene shortcuts
```bash
make run    # renders scenes/minimalist.rt
make run2   # renders scenes/full.rt
```

### Controls once the window is open
```text
Esc / red ✕   quit
←  →          rotate camera left / right
↑  ↓          rotate camera up / down
J  L          pan camera left / right
I  K          pan camera up / down
+  -          dolly camera forward / backward (Z axis)
1  2          narrow / widen FOV (zoom in / out)
F             toggle fisheye projection
R             reset camera to the scene file's original view
A             toggle the X/Y/Z debug axes
```

---

## 🧪 Testing notes

### Leak-check a scene
```bash
make testv    # valgrind --leak-check=full on scenes/minimalist.rt
make testv2   # valgrind --leak-check=full on scenes/full.rt
```

### `scenes/broken.rt`
Built to exercise the parser's error paths one at a time — each malformed line is commented out except the one currently under test, so uncommenting a different line targets a different failure: duplicate `A`, an out-of-range ambient ratio, a negative sphere diameter, an out-of-range plane normal, an out-of-range cylinder colour.

### Useful things to test
- every numeric field just inside and just outside its valid range
- a scene with two or more `L` lines — lighting should visibly sum across all of them
- extra spaces/tabs between fields, empty lines, `#`-only lines
- a camera direction pointing straight up or down (`0,1,0` / `0,-1,0`)
- rotating the camera with the arrow keys, then pressing `R` to confirm it snaps back exactly
- `norminette srcs/ includes/` — zero errors expected
- `valgrind --leak-check=full --show-leak-kinds=all` on every scene, including error paths

---

## 📚 Resources

References used to understand the project topic:
- [_Ray Tracing in One Weekend_](https://raytracing.github.io/)
- _The Ray Tracer Challenge: A Test-Driven Guide to Your First 3D Renderer_ by Jamis Buck

AI was used for referencing, concept clarifications, visualisation and formula explanations

---
## 🌱 Final thought

The surprise was that wrong math doesn't necessary crash, it renders quietly wrong: a stretched sphere, a cross product whose swapped arguments happened to cancel out and look correct until a new scene exposed it. To debug, we added in tools(keys,axis) to help us visualise to find the bug, before we analysed the code. The geometry only clicked once we saw it spatially and understanding that made the project easier. ✨
