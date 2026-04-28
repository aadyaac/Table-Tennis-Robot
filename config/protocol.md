# Serial Command Protocol

The EC2-hosted controller sends ASCII commands to Arduino over serial.

Format:

`PAN=<deg>;TILT=<deg>;PWM=<0-255>;DWELL=<ms>`

Example:

`PAN=-10.5;TILT=12.0;PWM=168;DWELL=130`

Fields:
- `PAN`: Horizontal targeting angle (degrees).
- `TILT`: Vertical paddle/wheel angle (degrees).
- `PWM`: Launcher motor speed.
- `DWELL`: Trigger dwell time before reset.
