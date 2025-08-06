# sendr

Search for books, download them, and automatically have them emailed to an ereader directly from the command line

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
- [x] ./sendr 'query' and see list of results
- [x] bare sendr cli

- [ ] SmtpClient with logging
- [ ] SmtpClient with TLS/OpenSSL
- [ ] SmtpClient AUTH LOGIN
- [ ] SmtpClient SendMail()

- [ ] Mailer wiring
- [ ] MailerListener::OnEvent()

- [ ] full sendr cli
- [ ] polish

- `sendr` cli design
  ```bash
    Usage: sendr get [--max N] [--format epub|pdf] <search terms…>

    Options:
      --max N             limit to top N matches (default: 1)
      --format <fmt>      desired file format (epub, pdf; default: epub)
      --dry-run           just print URLs, don’t download or send
  ```
