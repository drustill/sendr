# mailfs

FileSystem over E-Mail (particularly for Kindle)

---

## Test Prerequisites

Install Catch2 through system package manager:

- **macOS**
  ```bash
  brew install catch2
  ```

- **Ubuntu or whatever**
  ```bash
  sudo apt-get update
  sudo apt-get install catch2
  ```

## CMake Presets

Build presets are in `CMakePresets.json`, and will build the program with or without tests

- **Build**
  ```bash
  cmake --preset default
  cmake --build build
  ```
- **Build + run tests**
  ```bash
  cmake --preset with-tests
  cmake --build build-tests
  ctest --test-dir build-tests
  ```
