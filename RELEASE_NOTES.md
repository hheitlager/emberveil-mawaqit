# Mawaqit Prayer Clock v0.6.8

**Selectable taskbar positions — release candidate**

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

**Native XAML taskbar integration — release candidate**

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
