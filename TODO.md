- Utilities
  - [x] String slices and iterators
    - [x] Creation.
    - [x] Trimming for slice.
  - [ ] String slice vector
    - [x] Creation
    - [x] Insertion/appending
    - [ ] Deletion (does my use-case even need it?)
    - [x] Nuking
    - [x] Testing and working well
  - [x] Thread-safe exiting (untested as of writing)
    - Do I really need this, or is it better to add a format option for each
      error before returning to the main thread then nuke the program?

- Logging
  - [x] Fancy coloring
  - [x] Hopefully thread-safe
  - [ ] Print stack trace
    - [ ] Might need some assembly

- [ ] CLI parsing
  - [x] help
  - [ ] version
    - [ ] `configure_file` with CMake to get the version.
