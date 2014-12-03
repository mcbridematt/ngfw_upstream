#!/bin/sh -e
# /usr/lib/emacsen-common/packages/remove/backports-3.17.1

FLAVOR=$1
PACKAGE=backports-3.17.1

if [ ${FLAVOR} != emacs ]; then
    if test -x /usr/sbin/install-info-altdir; then
        echo remove/${PACKAGE}: removing Info links for ${FLAVOR}
        install-info-altdir --quiet --remove --dirname=${FLAVOR} /usr/share/info/backports-3.17.1.info.gz
    fi

    echo remove/${PACKAGE}: purging byte-compiled files for ${FLAVOR}
    rm -rf /usr/share/${FLAVOR}/site-lisp/${PACKAGE}
fi
