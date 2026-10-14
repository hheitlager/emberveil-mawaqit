# Mawaqit Prayer Clock v0.6.9

**Reliability and compatibility improvements**

This release builds on v0.6.8.4 and the tested dev-9 baseline. It focuses on stable taskbar integration, popup behavior, settings updates, and schedule caching rather than new visual features.

### Highlights
- **Taskbar recovery:** Reinsert the prayer clock if Windows recreates the taskbar’s XAML elements, with a periodic health check.
- **Safer popup handling:** Native activation and dismissal replace the system-wide mouse hook and Escape polling.
- **Improved display scaling:** Better handling of DPI for the pill and popup.
- **Cache management:** Store schedules in Windhawk-managed mod storage and reuse a fresh cache after Explorer restarts.
- **Year-boundary refresh:** Wake around New Year so the next calendar year's schedule can be requested.
- **Settings stability:** Apply UI-owned settings on the taskbar UI thread, retry failed dispatch on the countdown tick, and remove the redundant advanced-settings visibility toggle.
- **Faster shutdown:** Interrupt the startup worker wait when the mod is disabled or reloaded.

### Compatibility and limitations
- All five taskbar positions remain available. **Dynamic center is experimental** and can overlap other taskbar elements.
- Prayer times are supplied by Mawaqit; the mod cannot supply dates missing from Mawaqit's published schedule. December 31 after Isha may show tomorrow as unavailable until January's data is obtained.
- The actual New Year transition and recovery after a taskbar XAML-only recreation have not been conclusively tested. Broader Windows 11 compatibility remains unverified.
- The mod makes HTTPS requests to `mawaqit.net` for public schedule data. The website format or availability may change.

### Upgrade notes
- Existing mosque, theme, display, layout, custom-color and taskbar-position setting keys are retained.
- The legacy `%LOCALAPPDATA%\EmberveilMawaqit` cache folder is no longer used. v0.6.9 uses Windhawk-managed mod storage; any old folder may require manual cleanup.
- The mod-specific advanced-settings visibility switch was removed. Advanced settings remain available in Windhawk.

### Validation
Author regression tests passed for startup, theme and position switching, popup behavior, repeated enable/disable cycles, Explorer restart, and normal shutdown. The final settings-exception safeguard still requires compilation and regression testing. This is not a claim of compatibility with every Windows 11 build or taskbar mod.

### Installation
Install or update the source in Windhawk using `src/windhawk-mawaqit.wh.cpp`, compile and enable it, then configure your mosque. See [README.md](README.md) and [CONFIGURATION.md](CONFIGURATION.md).

### Notes
- Source release; no precompiled binary.
- Unofficial community project, not affiliated with Mawaqit.
- Upstream Windhawk submission remains subject to maintainer review.

---

# Mawaqit Prayer Clock v0.6.8

**Selectable taskbar positions — release**

This update adds five selectable positions for the native XAML prayer clock, with live switching directly from the **General → Taskbar position** setting. The prayer schedule updater, themes, popup, and existing customization options remain available.

### Highlights

- **Before system tray** — the default, with the clock participating in the tray layout.
- **After system tray** — places the clock beyond the tray.
- **Before taskbar icons** — anchors the clock before application buttons.
- **After taskbar icons** — follows the application buttons as their position changes.
- **Dynamic center (experimental)** — starts at the physical taskbar center and moves right when application buttons approach.
- Switch positions without restarting Windows Explorer.
- Taskbar position is a **General** setting, not hidden under advanced customization.

### Known limitation

**Dynamic center (experimental)** is an overlay and does not reserve space in the application-button layout. Windows may not automatically combine or resize taskbar buttons to accommodate it. On crowded taskbars, the clock can overlap other elements. Use one of the four anchored positions if you prefer native layout spacing.

### Upgrade notes

The new setting is `General.Position`, defaulting to `before-tray`. The four other choices are `after-tray`, `before-icons`, `after-icons`, and `center`. Existing mosque, theme, display, layout, and custom-color settings remain in their current groups. If you use other taskbar customization mods, verify the clock placement after updating.

### Validation

Author-tested: all five positions, live position switching, dynamic-center movement, and a subsequent cleanup regression pass. This does not establish compatibility with every Windows 11 build or combination of taskbar mods.

### Installation

Install Windhawk, create or update the mod using `src/windhawk-mawaqit.wh.cpp`, compile and enable it, then configure your mosque. See [README.md](README.md) and [CONFIGURATION.md](CONFIGURATION.md).

### Notes

- Source release; no precompiled binary.
- Unofficial community project, not affiliated with Mawaqit.
- Schedule retrieval depends on Mawaqit's website format and availability.

---

# Mawaqit Prayer Clock v0.6.7

**Native XAML taskbar integration — release**

This update moves the taskbar prayer clock to a native XAML slot while retaining the existing Mawaqit schedule updater and prayer schedule popup.

### Highlights

- Native Windows 11 XAML taskbar pill with reserved taskbar space and live countdown.
- 13 appearance themes: Windows / System, Traditional Islamic, Catppuccin Mocha, Emberveil, Emberveil Midnight, Emerald Mosque, Dracula, Nord, Gruvbox Dark, Tokyo Night, Solarized Dark, Solarized Light, and Custom.
- Ten independent custom colors for pill and popup.
- Optional popup auto-close (0 = disabled; 1–300 seconds).
- Layout controls for width, height, margins, padding, tray gap, corner radius, and font size.
- Popup class lifecycle improvements to avoid stale registrations during hot reloads.
- Operational logs consistently prefixed `[Mawaqit]`.

### Upgrade notes

Existing setting keys for mosque, theme, display, layout, and custom colors are retained. The taskbar pill implementation changes from GDI to native XAML. The popup remains Win32-based. If you use third-party taskbar mods, verify the pill position after updating.

### Validation

Author-tested: settings/behavior (8/8), popup auto-close (6/6), and visual inspection (7/7), plus all eight new theme presets. These tests do not establish compatibility with every Windows 11 build or taskbar customization.

### Installation

Install Windhawk, create or update the mod using `src/windhawk-mawaqit.wh.cpp`, compile and enable it, then configure your mosque. See [README.md](README.md) and [CONFIGURATION.md](CONFIGURATION.md).

### Notes

- Source release; no precompiled binary.
- Unofficial community project, not affiliated with Mawaqit.
- Schedule retrieval depends on Mawaqit's website format and availability.
