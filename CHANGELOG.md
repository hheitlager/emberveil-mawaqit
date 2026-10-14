# Changelog
Notable changes to Mawaqit Prayer Clock are documented here.

## [0.6.9] — Reliability and release-candidate hardening

### Improved
- Reuse a fresh, matching Mawaqit schedule cache after Explorer restarts instead of downloading unnecessarily.
- Store cache files in Windhawk-managed mod storage, allowing cleanup on uninstall.
- Refresh scheduling wakes around the December 31–January 1 boundary so the new year’s schedule can be requested promptly.
- Scale the taskbar widget and popup consistently across DPI settings.
- Recover the native XAML widget if taskbar elements are recreated, using the existing taskbar hook and a periodic health check.

### Fixed
- Retry pending settings on the taskbar countdown tick if dispatch fails, and preserve the retry request if settings application throws.
- Wake the startup worker immediately on shutdown rather than waiting for its fixed 1.5-second sleep.
- Keep native XAML object lifetime and settings updates on the appropriate UI thread.
- Replace system-wide mouse-hook dismissal and Escape-key polling with native popup activation and keyboard handling.
- Remove the advanced-settings visibility toggle that could leave hidden settings active.

### Notes
- Mawaqit remains the source of prayer times. The mod does not calculate or fabricate unavailable future schedules.
- Dynamic center remains experimental and may overlap taskbar elements.
- Author regression tests passed for settings, enable/disable cycles, Explorer restart, and popup behavior; a taskbar XAML-only recreation and the actual New Year transition have not been conclusively exercised.
- External network access to `mawaqit.net` is documented; upstream Windhawk acceptance remains subject to maintainer review.

## [0.6.8] - Selectable taskbar positions

### Added
- Five selectable taskbar positions, including experimental dynamic centering

## [0.6.7] — Native XAML taskbar integration and theme expansion

### Added
- Native XAML taskbar pill with reserved space and a live countdown.
- Optional popup auto-close timer (0 disables; 1–300 seconds).
- Eight themes: Emberveil Midnight, Emerald Mosque, Dracula, Nord, Gruvbox Dark, Tokyo Night, Solarized Dark, and Solarized Light; 13 total including Custom.

### Changed
- Replaced the GDI taskbar pill with native XAML integration while retaining the Win32 prayer popup.
- Preserved layout settings, custom pill/popup colors, and mosque-specific schedule updates.
- Standardized diagnostic and operational log prefixes to `[Mawaqit]`.

### Fixed
- Avoided stale popup window-class registrations across Windhawk reloads by using unique class names and teardown cleanup.
- Improved popup dismissal and first-open stability in the tested environment.

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

## [0.6.2] — Initial public release

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
