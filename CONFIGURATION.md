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
  "General.Mosque": "masjidomar",
  "General.Theme": "catppuccin",
  "Display.ShowNextPrayer": 1,
  "Display.ShowCountdown": 1,
  "Display.EnablePopup": 1,
  "AdvancedCustomization.AdvancedOptions": 1,
  "AdvancedCustomization.ModSettingsAdvanced.RefreshHours": 24,
  "AdvancedCustomization.LayoutSettings.Width": 220,
  "AdvancedCustomization.LayoutSettings.PillHeight": 0,
  "AdvancedCustomization.LayoutSettings.Margins": "10, 0, 0, 0",
  "AdvancedCustomization.LayoutSettings.Padding": "8, 0, 8, 0",
  "AdvancedCustomization.LayoutSettings.TrayGap": 0,
  "AdvancedCustomization.LayoutSettings.CornerRadius": 13,
  "AdvancedCustomization.LayoutSettings.FontSize": 15,
  "AdvancedCustomization.CustomThemeSettings.CustomPillBackground": "#211E32",
  "AdvancedCustomization.CustomThemeSettings.CustomPillText": "#F5E6C8",
  "AdvancedCustomization.CustomThemeSettings.CustomPillSeparator": "#B8A98A",
  "AdvancedCustomization.CustomThemeSettings.CustomPillCountdown": "#FFBC5E",
  "AdvancedCustomization.CustomThemeSettings.CustomPopupBackground": "#1D1D2D",
  "AdvancedCustomization.CustomThemeSettings.CustomPopupBorder": "#3B3B58",
  "AdvancedCustomization.CustomThemeSettings.CustomPopupText": "#D3D0E8",
  "AdvancedCustomization.CustomThemeSettings.CustomPopupMuted": "#B8B3D1",
  "AdvancedCustomization.CustomThemeSettings.CustomPopupRule": "#424158",
  "AdvancedCustomization.CustomThemeSettings.CustomPopupFooter": "#A29DBB"
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
| `Width` | Clock width | 180–400 px; default 220 |
| `PillHeight` (**Height**) | Clock height | `0` = automatic based on taskbar height; 1–100 px = manual override, capped to taskbar height; default 0 |
| `Margins` (**Margin**) | Moves the entire clock relative to its automatic position | Four comma-separated signed integers `left, top, right, bottom`; each −100 to 100 px; default `"0, 0, 0, 0"` |
| `Padding` | Reserves space between the clock edges and text, without moving or resizing the clock | Four comma-separated integers `left, top, right, bottom`; each 0–100 px; default `"0, 0, 0, 0"` |
| `TrayGap` (**Gap before system tray**) | Horizontal gap before the tray | 0–100 px; default 0 |
| `CornerRadius` (**Corner radius**) | Corner roundness | 0–30 px; capped to half the painted width/height; default 13 |
| `FontSize` (**Fontsize**) | Clock text size | 10–24 px; default 15 |

## Layout examples

The names in parentheses in the reference table are the labels shown in Windhawk; the code-formatted names are the JSON keys. Keep those keys unchanged when editing Advanced JSON.

- **Automatic height:** Set `PillHeight` to `0`. The clock follows the available taskbar height, including the Windows taskbar size setting.
- **Manual height:** Set `PillHeight` to `26` for a fixed requested height (still limited to the taskbar height).
- **Margin:** `"10, 0, 0, 0"` moves the clock 10 px right; `"0, 5, 0, 0"` moves it 5 px down; right and bottom margins move it in the opposite directions. Opposing values cancel each other.
- **Padding:** `"8, 0, 8, 0"` reserves 8 px on each horizontal side for the text. `"0, 4, 0, 0"` reserves 4 px above the text, moving the available text area's center down. Padding may clip text when space is limited.

Margin affects **position only**; padding affects the **text area only**. Neither changes the clock's width or height. Invalid four-value strings revert to zero insets. The old `OffsetX`, `OffsetY`, and `PillPadding` keys are no longer used by v0.6.6; update any older saved configuration to use `Margins` and `Padding`.

**Custom theme:** To use custom colors, set `"Theme": "custom"` in Advanced JSON. Selecting a built-in preset ignores the custom color values without deleting them. The regular appearance dropdown intentionally excludes `custom`.

**Compatibility:** Conditional visibility requires Windhawk 2.0. The mod uses `#! $showIf` annotations so the same source still validates on Windhawk 1.x, which displays all advanced settings.
