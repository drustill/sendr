# sendr

Search for books, download them, and automatically have them emailed to an ereader directly from the command line.

sendr is intentionally over complicated. sendr will start a daemon process and listen to `~/sendr/lib/` using kqueue.
Books are downloaded through annas archive, and to use sendr you must have an annas archive secret key. sendr will look for
configuration from `~/.config/sendr/sendr.conf`. On installation (once registered on homebrew) a default config is created.

---

## Installing

### TODO!
`brew install sendr`

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

- [x] SmtpClient with logging
- [x] SmtpClient with TLS/OpenSSL
- [x] SmtpClient AUTH LOGIN
- [x] SmtpClient SendMail()

- [x] Mailer wiring
- [x] MailerListener::OnEvent()

- [x] sendr cli

- `sendr` cli design
  ```bash
Usage:
  sendr fetch [options] <search terms…>
  sendr daemon <start|stop|restart|status>

Fetch Options:
  --max <N>           limit to top N matches (default: 1)
  --format <fmt>      desired format: epub, pdf (default: epub)
  --dry-run           print download URL, don’t download or send

Daemon Commands:
  start               launch the daemon process
  stop                stop the running daemon
  status              print daemon status (running or not)
  restart             restart the daemon

  ```
