# Graphics Re-Entry → NeRF Transition Plan

## Purpose
Rebuild graphics intuition in a grounded, pressure-free way, then transition naturally into neural rendering (NeRF).

This plan prioritizes:
- intuition over performance
- implementation over theory recall
- calm consistency over intensity

---

## Phase Placement

- **Phase 1.5** — Traditional graphics grounding (regulating)
- **Phase 2** — Differentiable graphics thinking
- **Phase 3** — Neural rendering (NeRF)

---

## Guardrails (Non-Negotiable)

- 30–90 minute sessions
- 2–4 sessions per week
- No deadlines
- No portfolio framing
- Stop when intuition returns, not when code is perfect

> If urgency appears, pause the work.

---

## Phase 1.5 — Graphics Re-Grounding (4–6 weeks)

### Goal
Restore spatial, geometric, and visibility intuition.

### Modules

#### 1. Rasterization & Visibility
- Triangle setup
- Barycentric coordinates
- Depth buffer
- Clipping intuition

**Mini-projects**
- CPU triangle rasterizer
- Depth buffer visualization
- Overdraw heatmap

---

#### 2. Lighting & Shading
- Lambert
- Blinn-Phong
- GGX / microfacet intuition

**Mini-projects**
- BRDF comparison viewer
- Interactive roughness and light sliders

---

#### 3. Cameras, Transforms & Rays
- View / projection matrices
- Pixel-to-ray mapping

**Mini-projects**
- Camera explorer
- Ray bundle visualization

---

#### 4. Texture Sampling & Filtering
- UVs
- Mipmaps
- Aliasing

**Mini-projects**
- Nearest vs bilinear vs trilinear sampling
- Mipmap level visualization

---

#### 5. Integration Week
- Combine camera + shading + textures
- Fix one artifact end-to-end

---

## Phase 2 — Differentiable Graphics

### Goal
Shift from forward rendering to optimization thinking.

**Projects**
- Inverse lighting optimization
- Material parameter estimation
- Camera pose recovery via loss minimization

---

## Phase 3 — Neural Rendering (NeRF)

### Goal
Implement NeRF with strong geometric intuition.

**Projects**
- Minimal NeRF from scratch
- Ray marching visualization
- Convergence and sampling experiments

---

## Anchor
> Rebuild depth first. Speed comes later.
