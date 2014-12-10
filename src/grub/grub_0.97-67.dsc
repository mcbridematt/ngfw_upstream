-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA256

Format: 1.0
Source: grub
Binary: grub-legacy, grub-disk, grub-doc, grub-legacy-doc, multiboot-doc
Architecture: i386 hurd-i386 amd64 all
Version: 0.97-67
Maintainer: GRUB Maintainers <pkg-grub-devel@lists.alioth.debian.org>
Uploaders: Robert Millan <rmh.debian@aybabtu.com>, Felix Zielcke <fzielcke@z-51.de>, Colin Watson <cjwatson@debian.org>
Dm-Upload-Allowed: yes
Standards-Version: 3.8.3
Vcs-Svn: svn://svn.debian.org/svn/pkg-grub/grub/
Build-Depends: debhelper (>= 5), quilt (>= 0.46-7), automake1.9, autoconf, autotools-dev, texinfo, libncurses5-dev | libncurses-dev, lib32ncurses5-dev [amd64], gcc-multilib [amd64]
Build-Depends-Indep: texi2html
Package-List: 
 grub-disk deb admin extra
 grub-doc deb doc extra
 grub-legacy deb admin extra
 grub-legacy-doc deb doc extra
 multiboot-doc deb doc extra
Checksums-Sha1: 
 2580626c4579bd99336d3af4482c346c95dac4fb 971783 grub_0.97.orig.tar.gz
 72593eb727608d7339f034e090e156703b3a9e1d 96400 grub_0.97-67.diff.gz
Checksums-Sha256: 
 4e1d15d12dbd3e9208111d6b806ad5a9857ca8850c47877d36575b904559260b 971783 grub_0.97.orig.tar.gz
 1a5113831c73ed61bc5ffdefa3bc373ed33bfa701c72c62870a4268ba0546af7 96400 grub_0.97-67.diff.gz
Files: 
 cd3f3eb54446be6003156158d51f4884 971783 grub_0.97.orig.tar.gz
 9950962dfcd94ef0e37f260e23dab321 96400 grub_0.97-67.diff.gz

-----BEGIN PGP SIGNATURE-----
Version: GnuPG v1.4.12 (GNU/Linux)
Comment: Colin Watson <cjwatson@debian.org> -- Debian developer

iQIVAwUBUQf3wzk1h9l9hlALAQj5qQ//bRj00O1RMKGL9dFsE7wgo36Rwzw/36FZ
FQBt7O3ARQtj35tFvZ9HRbT7FjaECgutbtEtjsVbIcHLfUq9EaUKc9Qx3uEg2nEJ
ixz1GjUwy1vB+Q2s1oGW5L1Tcla5lT6ZwhMKMBm2j3pW7uWrIzxPjLPMP1rf0r82
5w4FWkqZF0ckA0E7pWaxmVp6UH6OGK+rQc954QgpmzSLAjJdAUHt5qnnJoz7mze2
6I4epxMWTUuGm4cHenBUHe02VTuQ2AuGyzej0jldtKpcJGUuNRO0ZE5UvX32MnRi
DvGju9Ns7xZtvzqhyx7VdZS1P2RyytiX7vNs24IV8ScONgjz6LKUjfbDoRIn9nMN
ziOD3aCMUOqo/NmMmu2sxgEb7Dg0xkrb73nOW6CmJpvWTeoOGWWFNFYhvExMB4b6
8J62VOxcVHSdQOww9gT3DXleBZ4I7mLk3D6z3etNKe3opVU5KOK19ZTyOm2OVu3G
5pqzTHRUBpIQdmycfdtJXFA7/I8SDapAxQfmeBf5/kXXmSdDa5z3jYp/tOasGVYK
HzpJovx9eNyfiU2jpMxgQo8YGbDvIGRNc1gJiOFTSCHaTbgdGvqdfT+1f/LhCTzl
oxFaRu1ODMScZ7nlGXL6ZwkrgqNvcdbiAx93K+EHOYr0IXPI97evIgSHkMSgAZpv
XZrw0iAmFY4=
=amVc
-----END PGP SIGNATURE-----
