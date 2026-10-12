# Mawaqit Prayer Clock v0.6.6

**Taskbar-aware layout update — release candidate**

A customizable, unofficial Mawaqit prayer clock for the Windows 11 taskbar, powered by Windhawk.

### Highlights

- Live next-prayer display and countdown in a taskbar pill
- Clickable popup with prayer schedule
- Five themes: Emberveil, Windows / System, Traditional Islamic, Catppucchin Mocha, and Custom
- Independent custom colors for pill and popup
- Visibility switches for prayer label, countdown, and popup
- Automatic height that adapts to Windows taskbar sizing, plus manual height override
- Four-sided margins for positioning and four-sided padding for text spacing
- Simplified layout settings labels and order
- Corrected rounded corners at automatic height
- Configurable background schedule updates and live settings changes

### Upgrading from older versions

The previous `OffsetX`, `OffsetY`, and `PillPadding` settings are no longer used. Configure `Margins` and `Padding` instead. `PillHeight = 0` enables automatic height. See [CONFIGURATION.md](CONFIGURATION.md) for examples.

### Installation

Install Windhawk, create a new mod, paste `src/windhawk-mawaqit.wh.cpp`, compile, enable, and configure your Mawaqit mosque in the mod settings. See README for details.

### Notes

- Source release; no precompiled binary.
- Tested in the author's environment; compatibility across Windows builds is not yet established.
- Unofficial project, not affiliated with Mawaqit.
- Requires access to Mawaqit's website; upstream page changes can affect schedule retrieval.