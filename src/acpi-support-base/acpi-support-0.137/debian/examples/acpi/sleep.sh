#!/bin/sh

# This script HANDLES the sleep button (does not TRANSLATE it). It is part
# of the *suspend* side of acpi-support, not the special keys translation
# side. If this script is called, it is assumed to be the result of a suspend
# key press that can also be heard by other parts of the system. The only time
# that it actually does something is when it is determined that no other parts
# of the system are listening (this is what the CheckPolicy call does).

test -f /usr/share/acpi-support/key-constants || exit 0

. /usr/share/acpi-support/policy-funcs

if [ `CheckPolicy` != 0 ]; then
  # No power management daemons are running. Divert to our own implementation.
  /usr/share/acpi-support/suspendorhibernate suspend
fi


