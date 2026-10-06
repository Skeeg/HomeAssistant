# Vendored from ssieb/esphome_components

- **Author:** Samuel Sieb (@ssieb)
- **Upstream:** https://github.com/ssieb/esphome_components
- **Commit:** `23eb1124819261a3ea75585d8414f4ec65b50e2a` (2026-09-05)
- **Copied:** 2026-10-06, unmodified

Kept here so builds do not depend on the upstream repo staying available.

## License

`LICENSE` is upstream's file, copied verbatim. Python files (`__init__.py`) are MIT. C++ files (`.cpp`, `.h`) are GPLv3; firmware built with them is GPLv3, and this repository carries the source.

## Components

| Component | Used by |
|---|---|
| `magic_switch/` | `common/magic_switch/true.yaml` (Sonoff Basic R4, GPIO5 wall-switch sense) |

To refresh: re-copy the component directory and `LICENSE` from upstream, update the commit line, and rebuild an R4 config with `magic_switch: "true"`.
