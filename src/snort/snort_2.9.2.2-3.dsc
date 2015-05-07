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
Build-Depends: libnet1-dev, libpcap0.8-dev, libpcre3-dev, debhelper (>= 5.0.0), libmysqlclient-dev (>= 5.5), libpq-dev, po-debconf (>= 0.5.0), libprelude-dev, libgnutls-dev | libgnutls28-dev, libdumbnet-dev, libdaq-dev, flex, bison
Build-Depends-Indep: texlive, texlive-latex-base, ghostscript
Package-List:
 snort deb net optional arch=any
 snort-common deb net optional arch=all
 snort-common-libraries deb net optional arch=any
 snort-doc deb doc optional arch=all
 snort-mysql deb net extra arch=any
 snort-pgsql deb net optional arch=any
 snort-rules-default deb net optional arch=all
Checksums-Sha1:
 5b1e9bd527ecba7e42c007ae1a62ff51a4adb2c6 6529966 snort_2.9.2.2.orig.tar.gz
 4dd712c962f3cdaf5ae20a307bd4ea1f09635c5e 690492 snort_2.9.2.2-3.debian.tar.xz
Checksums-Sha256:
 63f4eeee24d79e4a4e4b573e085d0d2fd78fcf3b7ea730c37eab7b47fcd9b954 6529966 snort_2.9.2.2.orig.tar.gz
 fc80d5c300552cf2b9d8489f9db34cb4f3c2d26a2b2524d23cae116ae7c49cc6 690492 snort_2.9.2.2-3.debian.tar.xz
Files:
 4254389550e3be31afebc70e64e6002f 6529966 snort_2.9.2.2.orig.tar.gz
 f3d26a59f8bdc56d7072e455e26e3028 690492 snort_2.9.2.2-3.debian.tar.xz
