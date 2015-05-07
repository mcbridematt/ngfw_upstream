-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA1

Format: 3.0 (quilt)
Source: snort
Binary: snort, snort-common, snort-doc, snort-mysql, snort-pgsql, snort-rules-default, snort-common-libraries
Architecture: any all
Version: 2.9.2.2-3
Maintainer: Javier Fernández-Sanguino Peña <jfs@debian.org>
Uploaders: Andrew Pollock <apollock@debian.org>
Homepage: http://www.snort.org/
Standards-Version: 3.9.2
Vcs-Browser: http://anonscm.debian.org/gitweb/?p=pkg-snort/pkg-snort.git
Vcs-Git: git://git.debian.org/git/pkg-snort/pkg-snort.git
Build-Depends: libnet1-dev, libpcap0.8-dev, libpcre3-dev, debhelper (>= 5.0.0), libmysqlclient-dev (>= 5.5), libpq-dev, po-debconf (>= 0.5.0), libprelude-dev, libgnutls-dev, libdumbnet-dev, libdaq-dev, flex, bison
Build-Depends-Indep: texlive, texlive-latex-base, ghostscript
Package-List: 
 snort deb net optional
 snort-common deb net optional
 snort-common-libraries deb net optional
 snort-doc deb doc optional
 snort-mysql deb net extra
 snort-pgsql deb net optional
 snort-rules-default deb net optional
Checksums-Sha1: 
 5b1e9bd527ecba7e42c007ae1a62ff51a4adb2c6 6529966 snort_2.9.2.2.orig.tar.gz
 77178e80091fa45d33146d06601ae5cedb5186c9 1591288 snort_2.9.2.2-3.debian.tar.gz
Checksums-Sha256: 
 63f4eeee24d79e4a4e4b573e085d0d2fd78fcf3b7ea730c37eab7b47fcd9b954 6529966 snort_2.9.2.2.orig.tar.gz
 e7e6b44659d09379f7e68b7f965b3eb1d22b75c3da9330f6af510dd8b60b262b 1591288 snort_2.9.2.2-3.debian.tar.gz
Files: 
 4254389550e3be31afebc70e64e6002f 6529966 snort_2.9.2.2.orig.tar.gz
 80de9a751c67aed5a22183a717838a39 1591288 snort_2.9.2.2-3.debian.tar.gz

-----BEGIN PGP SIGNATURE-----
Version: GnuPG v1.4.12 (GNU/Linux)

iD8DBQFQIbq2sandgtyBSwkRAvYrAJ9cDGPyEbLP4KQK9geh/n5WuCo29ACeOYse
nnBRONdYehNtQ+O/9fpRwHQ=
=d9cw
-----END PGP SIGNATURE-----
