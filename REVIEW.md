# RC review notes — v0.7.0

- **Source baseline:** author-tested, clang-formatted, UTF-8-corrected `windhawk-mawaqit-v0.7.0-dev.7f.1-formatted-utf8-fixed.wh.cpp`, uploaded as `windhawk-mawaqit.wh(20261016-194706).cpp`.
- **C++ release edit:** changed only the Windhawk `@version` metadata from `0.7.0-dev.7f.1` to `0.7.0`; no functional code changes during RC packaging.
- **Documentation:** aligned README, CONFIGURATION, CHANGELOG, and RELEASE_NOTES with the current hover-popup controls and dev.7a–7f.1 stability improvements. Prior release history retained.
- **Validation:** author reported 26/26 functional regression checks and successful additional Explorer restart/startup recovery testing on their Windows 11 setup. This environment has not independently compiled or executed the RC.
- **Before publishing:** compile the RC metadata build in Windhawk; check screenshot paths, documentation and settings in the editor; confirm the canonical `src/windhawk-mawaqit.wh.cpp` matches this RC; run `git diff --cached --check` after staging.
- **Known limitations:** crowded/portrait taskbars and other taskbar mods may affect placement; dynamic center is experimental; wider Windows 11 build compatibility and upstream acceptance remain unverified.
