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
