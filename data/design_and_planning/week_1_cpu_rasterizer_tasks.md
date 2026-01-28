# Week 1 — CPU Rasterizer (Hands-On Checklist)

## Goal
Rebuild visibility and spatial intuition by implementing a minimal CPU triangle rasterizer.

This is not about performance.
This is about seeing why pixels land where they do.

---

## Rule
Stop when intuition is restored — not when code is “clean”.

---

## Session 1 — Skeleton & Frame (30–60 min)

**Outcome:** You can draw something to a framebuffer.

### Tasks
- Create a framebuffer (width × height array)
- Define basic math types (`Vec2`, `Vec3`)
- Define `Triangle { v0, v1, v2 }` in screen space
- Clear framebuffer with a solid color
- Write image to disk (PPM / PNG)

**Success check**
- Blank image renders
- One hardcoded triangle outline appears

---

## Session 2 — Triangle Rasterization (45–90 min)

**Outcome:** Solid triangle fill via barycentric coordinates.

### Tasks
- Compute triangle bounding box
- Implement edge function
- Compute barycentric coordinates per pixel
- Inside-triangle test
- Fill pixels inside triangle

**Optional**
- Color by barycentric weights (RGB = weights)

**Success check**
- Triangle fills correctly
- Barycentric gradients are visible

---

## Session 3 — Depth Buffer (45–90 min)

**Outcome:** Correct occlusion.

### Tasks
- Add depth buffer (float array, init to +∞)
- Interpolate depth using barycentrics
- Depth test per pixel
- Render overlapping triangles at different depths
- Output depth buffer as grayscale image

**Success check**
- Front triangle wins consistently
- Depth image makes geometric sense

---

## Session 4 — Overdraw & Debug Views (Optional)

**Outcome:** Performance intuition without optimization.

### Tasks
- Count pixel write frequency
- Visualize overdraw as heatmap
- Render multiple overlapping triangles

**Success check**
- Overdraw hotspots are obvious

---

## Hard Constraints (Do NOT Break)

- No perspective correction
- No textures
- No SIMD or optimization
- No refactoring for cleanliness
- No GPU pipeline comparisons

---

## Expected Intuition by End of Week

You should understand:
- Pixel inclusion/exclusion
- Edge behavior
- Depth artifacts
- Why rasterization is deterministic but fragile

---

## Anchor
> I’m restoring intuition, not proving skill.
