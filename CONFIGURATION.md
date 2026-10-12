# Mawaqit Prayer Clock — Advanced Configuration

Windhawk provides two editors for this mod:

- **Settings:** Mosque, appearance preset, three display toggles, and **Show advanced options** (off by default).
- **Advanced → Mod settings:** The complete JSON settings object, including every color and layout key.

On Windhawk 2.0, the advanced options switch reveals the additional controls in the Settings tab. On Windhawk 1.x, the controls remain visible because conditional visibility is unsupported there.

## Editing advanced values

1. Open Windhawk → Mawaqit Prayer Clock → **Advanced**.
2. Find **Mod settings**, and copy the JSON somewhere safe before editing.
3. Edit only the values you want to change, keeping valid JSON syntax and existing keys.
4. Click **Save**. Existing visual settings continue to apply live.

The **Advanced** tab is part of Windhawk; no external configuration file is required. The `AdvancedOptions` key only controls visibility in the Settings form. It does not disable any features.

## Example

```json
{
  "Mosque": "masjidomar",
  "RefreshHours": 24,
  "Theme": "catppuccin",
  "ShowNextPrayer": 1,
  "ShowCountdown": 1,
  "EnablePopup": 1,
  "AdvancedOptions": 0,
  "CustomPillBackground": "#211E32",
  "CustomPillText": "#CDD6F4",
  "CustomPillSeparator": "#B4BEFE",
  "CustomPillCountdown": "#CFA1FF",
  "CustomPopupBackground": "#302D47",
  "CustomPopupBorder": "#58536F",
  "CustomPopupText": "#CDD6F4",
  "CustomPopupMuted": "#A6ADC8",
  "CustomPopupRule": "#58536F",
  "CustomPopupFooter": "#B4BEFE",
  "Width": 180,
  "OffsetX": 0,
  "OffsetY": 0,
  "TrayGap": 0,
  "PillHeight": 24,
  "CornerRadius": 8,
  "PillPadding": 0,
  "FontSize": 14
}
```

This is a **sample configuration**, not the mod's built-in defaults. The settings editor's current JSON is the authoritative starting point for your installation.

## Setting reference

| Setting | Purpose | Valid values / behavior |
|---|---|---|
| `Mosque` | Mawaqit mosque identifier or URL | String |
| `RefreshHours` | Schedule refresh interval | 1–168 hours; default 24 |
| `Theme` | Built-in theme or custom palette | `emberveil`, `system`, `traditional`, `catppuccin`, `custom` |
| `ShowNextPrayer` | Prayer label and time | 0 or 1 |
| `ShowCountdown` | Live countdown | 0 or 1 |
| `EnablePopup` | Clickable prayer schedule | 0 or 1 |
| `AdvancedOptions` | Reveal advanced controls in Windhawk 2.0 Settings | 0 or 1; default 0 |
| `CustomPillBackground` | Pill background | `#RRGGBB` |
| `CustomPillText` | Prayer label | `#RRGGBB` |
| `CustomPillSeparator` | Separator dot | `#RRGGBB` |
| `CustomPillCountdown` | Countdown text | `#RRGGBB` |
| `CustomPopupBackground` | Popup background | `#RRGGBB` |
| `CustomPopupBorder` | Popup outline | `#RRGGBB` |
| `CustomPopupText` | Popup primary text | `#RRGGBB` |
| `CustomPopupMuted` | Popup secondary text | `#RRGGBB` |
| `CustomPopupRule` | Popup divider lines | `#RRGGBB` |
| `CustomPopupFooter` | Popup footer | `#RRGGBB` |
| `Width` | Pill width | 180–400 px |
| `OffsetX`, `OffsetY` | Position offsets | Signed pixel values |
| `TrayGap` | Gap before tray | 0–100 px |
| `PillHeight` | Painted pill height | 12–30 px |
| `CornerRadius` | Corner radius | 0–30 px; clamped to half height |
| `PillPadding` | Minimum left inset | 0–40 px |
| `FontSize` | Taskbar pill text size | 10–24 px; default 15 |

**Custom theme:** To use custom colors, set `"Theme": "custom"` in Advanced JSON. Selecting a built-in preset ignores the custom color values without deleting them. The regular appearance dropdown intentionally excludes `custom`.

**Compatibility:** Conditional visibility requires Windhawk 2.0. The mod uses `#! $showIf` annotations so the same source still validates on Windhawk 1.x, which displays all advanced settings.
