# Mawaqit Prayer Clock
An unofficial, customizable **Mawaqit prayer clock for the Windows 11 taskbar**, built as a [Windhawk](https://windhawk.net/) mod.

Displays the upcoming prayer and a live countdown in a taskbar pill, with a clickable prayer-schedule popup. Designed with the **Emberveil** visual style in mind.

> **Release candidate: v0.6.7.** Tested by the project author in their Windows setup; broader compatibility has not yet been established.

> **Windhawk 2.0 or newer is recommended.** Earlier versions may differ in how advanced settings are presented.

## Features
- Upcoming prayer name, scheduled time, and live countdown
- Clickable prayer-schedule popup with optional auto-close timer
- 13 appearance themes: **Windows / System**, **Traditional Islamic**, **Catppuccin Mocha**, **Emberveil**, **Emberveil Midnight**, **Emerald Mosque**, **Dracula**, **Nord**, **Gruvbox Dark**, **Tokyo Night**, **Solarized Dark**, **Solarized Light**, and **Custom**
- Independent custom colors for the pill and popup
- Visibility switches for the prayer label, countdown, and popup
- Native XAML taskbar slot with reserved space and a live countdown
- Automatic or manual clock height, four-sided margin and padding, tray gap, and corner radius
- Background schedule updates through native WinHTTP, with configurable refresh interval
- Live settings updates without restarting Explorer

## Screenshots

The screenshots below are from the earlier theme collection; additional v0.6.7 theme screenshots have not yet been added.
Mawaqit Prayer Clock supports multiple appearance themes to match your Windows 11 desktop.

Windows System Default | Traditional Islamic |
|:---:|:---:|
![Windows](screenshots/Mawaqit-Windows-System-Default.png) | ![Traditional](screenshots/Mawaqit-Traditional-Islamic.png) |

| Catppucchin Mocha | Emberveil |
|:---:|:---:|
| ![Catppucchin](screenshots/Mawaqit-Catppucchin-Moca.png) | ![Emberveil](screenshots/Mawaqit-Emberveil.png) |

Desktop Integration

See how Mawaqit Prayer Clock integrates into a fully customized Windows 11 desktop.
![Desktop](screenshots/My-Desktop.png)

## Requirements
- Windows 11
- [Windhawk](https://windhawk.net/)
- Internet access to `mawaqit.net` for schedule updates
- A mosque page available on Mawaqit

The mod targets the 64-bit Windows Explorer process (`explorer.exe`). Other configurations have not been validated.

## Installation
1. Install and launch Windhawk.
2. Create a new mod in Windhawk's mod editor.
3. Copy the contents of [`src/windhawk-mawaqit.wh.cpp`](src/windhawk-mawaqit.wh.cpp) into the editor.
4. Compile and enable the mod in Windhawk.
5. Open the mod's settings and set your mosque identifier or Mawaqit URL.

This is a source distribution; no precompiled executable is included.

## Configuration
Settings are organized into the following groups:

| Group | Options |
| --- | --- |
| General | Mosque ID or URL; appearance theme |
| Display | Show next prayer; show countdown; enable prayer popup; popup auto-close (0–300 seconds) |
| Advanced customization | Show advanced options (off by default) |
| Mod settings (advanced) | Schedule refresh interval |
| Layout settings (advanced) | Width; Height; Margin (left, top, right, bottom); Padding (left, top, right, bottom); Gap before system tray; Corner radius; Fontsize |
| Custom theme settings (advanced) | Pill and popup color controls |

Set **Height** to `0` to follow the taskbar size automatically. **Margin** moves the clock without resizing it; **Padding** reserves space for text inside the clock without moving or resizing it. Both accept four comma-separated values in `left, top, right, bottom` order. See [CONFIGURATION.md](CONFIGURATION.md) for examples and the complete settings reference.

Custom color settings only affect the widget when **Custom** is selected. All three Display switches default to enabled.

For a mosque, enter a slug such as `al-haram-makkah-saudi-arabia` or a URL such as `https://mawaqit.net/en/al-haram-makkah-saudi-arabia`. The source defaults to `al-haram-makkah-saudi-arabia`; change it to your own mosque.

## What changed in v0.6.7
- Native XAML taskbar integration replaces the previous GDI taskbar pill.
- Eight new theme presets and an optional popup auto-close timer.
- Safer popup window-class registration and cleanup during mod reloads.
- Preserved mosque schedule fetching, custom colors, and live settings.

## How schedule updates work
The mod fetches the configured Mawaqit mosque page over HTTPS and reads schedule data embedded in the page. It caches generated schedule and metadata files under:

`%LOCALAPPDATA%\EmberveilMawaqit\`

The default refresh interval is 24 hours; failed updates are retried after one hour. This integration depends on the format and availability of the Mawaqit website, which may change.

## Troubleshooting
- **No prayer times:** Verify the mosque identifier/URL and internet access to `mawaqit.net`.
- **Widget missing:** Confirm the mod is enabled and Windows Explorer's taskbar/system tray is present; the native XAML slot may not appear if the taskbar tray is unavailable or unsupported.
- **Theme colors not changing:** Select **Custom** to use custom pill and popup colors.
- **Unexpected schedule:** Verify the mosque page and the local Windows date/time. The current updater uses the local Windows date when building the schedule.

## Disclaimer
This is an **unofficial community project**, not affiliated with, sponsored by, or endorsed by Mawaqit. Prayer data is provided by the configured Mawaqit page; verify important prayer times with your mosque. Before publishing or distributing broadly, review Mawaqit's applicable terms and data-use permissions.

## License
[MIT LICENSE](LICENSE)

## Credits
- Prayer schedule source: [Mawaqit](https://mawaqit.net/)
- Windows mod framework: [Windhawk](https://windhawk.net/)
- Project and visual direction: **[HHeitlager](https://github.com/hheitlager)**
