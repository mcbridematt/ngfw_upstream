#!/bin/sh

test -f /usr/share/acpi-support/state-funcs || exit 0

/usr/share/acpi-support/suspendorhibernate hibernate
