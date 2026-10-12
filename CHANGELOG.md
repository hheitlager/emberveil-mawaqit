# Changelog

Notable changes to Mawaqit Prayer Clock are documented here.

## [0.6.6] — Taskbar-aware layout and settings cleanup

### Added
- Automatic clock height that adapts to Windows taskbar size; `PillHeight = 0` enables automatic sizing.
- Manual height override with taskbar-height bounds.
- Four-sided `Margins` positioning and four-sided `Padding` for the internal text area.

### Changed
- Replaced the old horizontal and vertical offset controls with one margin setting.
- Replaced the legacy left-only padding control with four-sided padding.
- Simplified and reordered layout labels: Width, Height, Margin, Padding, Gap before system tray, Corner radius, and Fontsize.
- Kept margin positioning, padding, sizing, and corner rendering independent.

### Fixed
- Restored rounded-corner rendering with automatic height.
- Resolved Windows `RECT` coordinate type mismatches in padding calculations.

## [0.6.2] — Initial public release candidate

### Changed
- Reorganized settings labels and descriptions into Mawaqit, Appearance, Display, Custom pill, Custom popup, Layout, and Advanced groups.
- Clarified that custom colors only apply to the Custom theme.
- Retained existing settings keys and `PillPadding` compatibility.

## [0.6.1]

### Added
- Show/hide next prayer label.
- Show/hide live countdown.
- Enable/disable prayer schedule popup.
- Live application of visibility settings.

## [0.6.0]

### Added
- Unified appearance theme engine for pill and popup.
- Emberveil, Windows / System, Traditional Islamic, Custom, and Catppucchin Mocha presets.
- Independent custom pill and popup color options.

## [0.5.4]

### Improved
- Live settings handling without restarting Explorer.
- Stable GDI rounded-pill rendering.
- Native background schedule updater and prayer popup baseline.

Earlier development builds were internal iterations; this changelog summarizes the milestones rather than claiming a complete historical release record.
