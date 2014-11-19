-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA256

Format: 3.0 (quilt)
Source: wpa
Binary: hostapd, wpagui, wpasupplicant, wpasupplicant-udeb
Architecture: linux-any kfreebsd-any
Version: 2.3-1
Maintainer: Debian wpasupplicant Maintainers <pkg-wpa-devel@lists.alioth.debian.org>
Uploaders: Kel Modderman <kel@otaku42.de>, Stefan Lippers-Hollmann <s.l-h@gmx.de>, Jan Dittberner <jandd@debian.org>
Homepage: http://w1.fi/wpa_supplicant/
Standards-Version: 3.9.6
Vcs-Browser: http://anonscm.debian.org/viewvc/pkg-wpa/wpa/trunk/
Vcs-Svn: svn://anonscm.debian.org/pkg-wpa/wpa/trunk/
Build-Depends: debhelper (>> 9.20120115), libdbus-1-dev, libssl-dev, libqt4-dev, libncurses5-dev, libpcsclite-dev, libnl-3-dev [linux-any], libnl-genl-3-dev [linux-any], libnl-route-3-dev [linux-any], libpcap-dev [kfreebsd-any], libbsd-dev [kfreebsd-any], libreadline-dev, pkg-config, qt4-qmake, docbook-to-man, docbook-utils
Package-List:
 hostapd deb net optional arch=linux-any,kfreebsd-any
 wpagui deb net optional arch=linux-any,kfreebsd-any
 wpasupplicant deb net optional arch=linux-any,kfreebsd-any
 wpasupplicant-udeb udeb debian-installer standard arch=linux-any
Checksums-Sha1:
 7737a4306195ffaba8bb6777e2ede5a4a25e3ca0 1735544 wpa_2.3.orig.tar.xz
 5b59f88d07e341415f289b9ca7b15bdc12fe5e10 74784 wpa_2.3-1.debian.tar.xz
Checksums-Sha256:
 3d96034fa9e042c8aacb0812d8b2ab3d4c9aa6fc410802b4ee0da311e51c3eb3 1735544 wpa_2.3.orig.tar.xz
 b05e2f75fbf9891df9681be156416fb93a1761af886c1a257a6837f0b0cd6427 74784 wpa_2.3-1.debian.tar.xz
Files:
 d6dc9fa32a406506717ee6a4d076cd6d 1735544 wpa_2.3.orig.tar.xz
 83ae3ee4a5498deb0f5d347143a6b7b8 74784 wpa_2.3-1.debian.tar.xz

-----BEGIN PGP SIGNATURE-----
Version: GnuPG v1

iQIcBAEBCAAGBQJUPs1yAAoJEGrh3w1gjyLcrPwP/ifJ6IG+zu7Ohgpkc/gJvfob
zjyg2WSHbTQJWBaliBOEeU8t3FN+OUhlIvWR+Yp7dGiTTWAIgi9mEYvoxgyqP2j2
uJmlvrDGjED/JUFjVGRQgXTLEjqwSzCHjp9U6mfmuJCxDSIGDOKRzmJjnZlNz/b9
0dhmx2Dull2KevqF+/0tmS4Kw1o2ca2GYl6zuNDaGDNN5OD1MSGkzrjNONH1827/
hisCwbfaUGDfOEDAop4Rbpze+jMDJy5jb+UXI5U0c5mohFlUE9Nl9pRSvmvrN+84
pV+NtLx6AHrAxx7bnfiF+bgU7mh2jQg4qGpqdbZM/5/tt6FBRgfCRtwY8aMrND7S
JxWN590cp4AiAeuGa+WpDuvAx5pZy1M9nKO992t7b+jeNT4GllIHonkCzoTTuDTr
GTJ1HzGq52+0dzssAMg/6gK1O9MbFRgYV5aY9a474+rijWaYXHEklo65gMsYc/i5
FAYUYDN/BkGdK0TFr0xMR9/0zLaQFIByXMvN6EF/6u8vkUCRnjcFmuQ1ZDqLiylk
sdsq93YpcmxNE+tY5wE25fempNd5W7oKxvXCsQsZO3W41yWF4IlIaY7yoX+ZQxmq
m1k4KBFWFMHGUnpI6QMzFtBt07578t0yPwpRHTGpJJlrEJJ7MXzNRfMfw4l//LDn
WPXotmqb3x32VFkKWNrN
=pgBS
-----END PGP SIGNATURE-----
