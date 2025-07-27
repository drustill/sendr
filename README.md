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

## Stage of development

- [x] kqueue events emitted to registered listeners.
- [x] mailfs cli

- `mailfs` cli design
  ```bash
    Usage: mailfs fetch [--engine <name>] [--max N] [--format epub|pdf] <search terms…>

    Options:
      --engine <name>     which indexer to query (anna, libgen, openlib, gutenberg)
      --max N             limit to top N matches (default: 1)
      --format <fmt>      desired file format (epub, pdf; default: epub)
      --dry-run           just print URLs, don’t download or send
      --out-dir <path>    download into this directory instead of mailing
      --send-to-kindle    after download, email to your Kindle address
      --config <file>     path to ~/.mailfs/config (SMTP/IMAP creds, Kindle email)
  ```
