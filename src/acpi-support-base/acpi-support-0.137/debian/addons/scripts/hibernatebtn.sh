#!/bin/sh

test -f /usr/share/acpi-support/state-funcs || exit 0

. /usr/share/acpi-support/policy-funcs

if [ `CheckPolicy` = 0 ]; then
  # If gnome-power-manager or klaptopdaemon are running, generate the X "sleep"
  # key. The daemons will handle that keypress according to their settings.
  . /usr/share/acpi-support/key-constants
  acpi_fakekey $KEY_SUSPEND
else
  # No power management daemons are running. Divert to our own implementation.
  /etc/acpi/hibernate.sh
fi

