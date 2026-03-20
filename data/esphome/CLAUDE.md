# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## ESPHome CLI Commands

```bash
# Validate a device config
esphome config <device>.yaml

# Compile firmware for a device
docker exec esphome esphome compile /config/<device>.yaml

# Upload firmware OTA (always separate from compile — never use `run`, it holds an open connection)
docker exec esphome esphome upload /config/<device>.yaml

# Upload via serial
esphome upload <device>.yaml --device /dev/ttyUSB0

# View logs from a running device
esphome logs <device>.yaml

# Lint/validate all configs at once
for f in *.yaml; do esphome config "$f"; done
```

## Architecture

Every device config is a thin composition layer — it sets substitutions and lists packages, nothing more. The actual component implementations live in `common/` and `devices/`.

**Three-layer structure:**

1. **`<device>.yaml`** (root) — Per-device file. Defines `substitutions:` (name, IP, pins, behavior) and `packages:` listing what to include. May add an `esphome: area:` override.

2. **`devices/`** — Hardware blueprints. Each file describes how a specific hardware model is wired (pins, platform, sensors). Devices include the correct hardware blueprint via packages.

3. **`common/`** — Shared components included by most devices:
   - `esphome.yaml`, `api.yaml`, `wifi.yaml`, `logger.yaml`, `ota.yaml`, `time.yaml`, `web-server.yaml` — boilerplate for every device
   - `common-elements.yaml` — bundles the standard binary_sensors/buttons/sensors packages together
   - `common-esp8266.yaml` / `common-esp32.yaml` — platform-specific base config
   - `timers/` — cron-style and sun-based automation templates
   - `infrared/` — IR code definitions; `infrared_controls/` — interactive automations using those codes
   - `sensors/`, `binary_sensors/`, `buttons/` — individual reusable component packages

**Substitutions used across most devices:**

| Key | Purpose |
|-----|---------|
| `name` / `friendly_name` | ESPHome node identity |
| `ip_address` | Static IP (all devices use `10.3.2.x` or `10.3.3.x`) |
| `device_class` | HA device class (fan, outlet, switch, light, etc.) |
| `device_restore_mode` | Power-loss behavior (`ALWAYS_ON`, `RESTORE_DEFAULT_OFF`, etc.) |
| `mdi_icon` | Material Design icon for HA UI |
| `relay_pin` / `physical_button_pin` / `status_led_pin` | Hardware GPIO assignments |
| `on_timer_minutes` / `off_timer_hours` | Timer automation schedules |

## Docker Environment

The ESPHome service is defined in `config/compose.yml` (relative to the repo root). All compile and upload operations should be run through the container rather than a locally installed ESPHome binary, since the container version tracks the deployed release.

The container name is `esphome` and the ESPHome binary inside it is `/usr/local/bin/esphome`. Device YAML files are mounted into the container's working directory, so filenames used inside the container match the filenames in `data/esphome/`.

To update ESPHome to a new release: pull the new image and recreate the container via `config/compose.yml`, then do a rolling compile+upload pass (see below).

## Rolling Compile & Upload

When asked to do a full rolling compile+upload — after a config change, adding a new device, or refreshing after a container update — use **two parallel background agents** with an even/odd device split to cut the total time roughly in half.

**Procedure:**

1. Get the full numbered device list (excluding `secrets`):
   ```bash
   ls ./data/esphome/*.yaml | xargs -I{} basename {} .yaml | grep -v '^secrets$' | sort | nl -ba
   ```

2. Split by line number: odd-numbered devices → Agent A, even-numbered devices → Agent B.

3. Launch both agents with `run_in_background: true` and `model: "haiku"` (cost-effective for mechanical compile/upload work). Each agent iterates its device list and for each device:
   ```bash
   docker exec esphome esphome compile /config/<device>.yaml
   docker exec esphome esphome upload /config/<device>.yaml
   ```
   - Continue on upload failure (device may be offline/seasonal) — do not abort
   - Do not skip compile failures — report them and continue

4. When both agents complete, report a combined summary:
   - Total attempted, successful uploads, compile failures, upload failures
   - List each failed device with the failure stage and notable error output

**Notes:**
- Never use `esphome run` — it holds an open connection for the full duration. Always `compile` then `upload` as separate commands.
- Each device builds to its own directory under `/config/.esphome/build/<device>/` so parallel compiles do not conflict.
- Upload failures for seasonal/unplugged devices (christmas, holiday, front-yard-decor, etc.) are expected and non-fatal.
- Before kicking off a full update, ask the user if any devices need config changes first (e.g. disabling timers on seasonal devices).

## Secrets

All credentials are in `secrets.yaml` and referenced with `!secret`. Never hardcode WiFi passwords, API keys, encryption keys, or OTA passwords in device configs.

## Adding a New Device

1. Find the matching hardware blueprint in `devices/` (or create one if the hardware is new).
2. Create `<device-name>.yaml` in the root with substitutions + packages.
3. Add a static IP in the `10.3.2.x`/`10.3.3.x` range (check `secrets.yaml` and existing devices to avoid conflicts).
4. Validate with `esphome config <device>.yaml` before flashing.

## Inactive Devices

Devices no longer in use go in `spares/uninstalled/`. Devices pending repair go in `spares/possible_repairs/`. Do not delete configs for physical hardware that may be reused.
