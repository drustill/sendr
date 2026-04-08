# sendr

Search for books, download them, and automatically have them emailed to an ereader directly from the command line.

sendr is over complicated. i was originally messing around with kqueue, then smtp, and so on. sendr will start a daemon process and listen to `~/sendr/lib/` using kqueue, and this is pretty much useless. it doesn't really make any sense. i am aware. books are downloaded through annas archive, and to use sendr you must have an annas archive secret key. sendr will look for configuration from `~/.config/sendr/sendr.conf`.

---

```bash
Usage:
  sendr search [options] <search terms…>
  sendr daemon <start|stop|restart|status>

Fetch Options:
  --max <N>           limit to top N matches (default: 1)
  --format <fmt>      desired format: epub, pdf (default: epub)
  --dry-run           print download URL, don’t download or send
  --query <query>     search query in quotes

Daemon Commands:
  start               launch the daemon process
  stop                stop the running daemon
  status              print daemon status (running or not)
  restart             restart the daemon
```

## Installing

just clone and build

## Shell Completions

Shell completions are available

```bash
./completions/install.sh
```

## Building

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

## Testing

Just make sure Catch2 is installed. Can do it through system package manager

