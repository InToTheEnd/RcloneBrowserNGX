# AI Rules

## Tech stack

- This is **Rclone Browser NG**, a cross-platform desktop GUI for the rclone command-line tool.
- The application is written in **C++17**; use C++17-compatible language features.
- **Qt 6** is the application framework, with a source-build minimum of Qt 6.4.
- **Qt Core** is for non-visual primitives, object model, settings, and asynchronous/process support.
- **Qt Widgets** is the UI toolkit; the interface uses Qt Designer `.ui` files alongside C++ widgets and dialogs.
- **Qt Network** is used for networking functionality, including interactions with rclone's remote-control interface.
- **CMake 3.16+** configures and builds the app; `src/CMakeLists.txt` defines the application sources and Qt integration.
- **CTest and Qt Test** are used for the C++ unit and regression tests; Python scripts support packaging and release validation.
- **rclone** is an external runtime dependency and the source of remote storage and transfer operations; integrate with it through the existing process/RC layers.

## Library and implementation rules

- Use **Qt Core** APIs for strings, containers, file and settings access, timers, processes, and asynchronous work. Prefer Qt types at Qt-facing boundaries.
- Use **Qt Widgets** for desktop UI. Keep visual components in the existing widget/dialog architecture and use `.ui` files for established Designer-based forms; do not introduce a web UI framework.
- Use **Qt Network** for network and HTTP functionality. Reuse the existing rclone RC/request abstractions instead of creating a parallel transport layer.
- Use **Qt Test** for C++ tests, and register new test targets with CMake/CTest following the existing test patterns. Use Python only where it fits existing release or packaging scripts.
- Use the **C++ standard library** for general-purpose algorithms and data structures when Qt-specific behavior is not needed; avoid adding third-party libraries without a clear requirement and build-system integration.
- Route rclone commands and remote-control requests through the existing backend abstractions. Do not assemble unsafe shell command strings; pass arguments as structured process arguments and preserve existing validation/security boundaries.
- Follow the existing separation between UI, domain/backend logic, and parsing/serialization. Keep UI work on the GUI thread and use established asynchronous patterns for long-running operations.
- Keep changes cross-platform across Windows, macOS, and Linux/BSD. Guard platform-specific code and dependencies explicitly, and do not assume a shell, filesystem layout, or mount backend is universal.
- Match repository conventions: source and headers live under `src/`, tests under `tests/`, and build/configuration changes belong in CMake. Avoid unrelated refactors and document security-sensitive behavior through code and tests.
