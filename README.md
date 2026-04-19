# Amit Labs

Personal R&D workspace: a C++ **engine**, **standalone programs**, **tools**, and a **sandbox** for informal experiments and learning. The CMake project name is **`amit-labs`** (see root `CMakeLists.txt`).

## Repository layout

Everything below is relative to this repository root.

```text
amit-labs/
├── cmake/                 Shared CMake modules, find scripts, toolchain hints
├── data/                  Planning docs, engine shader assets, progress captures
│   ├── design_and_planning/
│   ├── engine/
│   └── progress/
├── external/              Vendored third-party SDKs and libraries (own licenses)
├── source/
│   ├── engine/            Core engine code: maths, graphics, GPU, platform, tests, shader build helpers, …
│   ├── projects/          Standalone applications (e.g. CpuRasterizer)
│   ├── tools/             Small command-line or build utilities
│   └── sandbox/           Scratch work, prototypes, and study material (not all of it is built by CMake)
├── CMakeLists.txt
├── LICENSE
├── README.md
└── tmp/                   Build outputs (binaries, libs, generated paths — see cmake/build_config.cmake)
```

Use any empty directory for CMake’s **binary dir** (for example `bld/` locally); it only holds generated project files and intermediates and is not part of the layout above.

## Planning and roadmap

Phased goals and checklists live in **`data/design_and_planning/`**, including:

- **`projects_list.md`** — engine use cases and longer-term graphics / processing ideas
- **`NeuralRenderingPlan.md`** — phased roadmap toward neural rendering
- **`graphics_re-entry.md`** — graphics re-grounding and session structure
- **`week_1_cpu_rasterizer_tasks.md`** — CPU rasterizer hands-on checklist

Shader-related files sit under **`data/engine/shaders/`**; rasterizer progress imagery under **`data/progress/cpu_rasterizer/`**.

## Build (CMake)

- **CMake 3.25+**, **C++20**. First configure may **download** [nlohmann/json](https://github.com/nlohmann/json) via `FetchContent`.
- **Windows:** the engine build expects **Agility SDK** and related GPU tooling (see `cmake/FindAgilitySDK.cmake`, `FindDxcCompiler.cmake`, and `external/`). Adjust compiler paths in `cmake/build_global_defs.cmake` if needed.
- From the repository root:

```bat
cmake -S . -B bld
cmake --build bld --config Debug
```

## License

Project code is under the **MIT License** — see [`LICENSE`](LICENSE). Material under **`external/`** stays under its **original** upstream licenses.
