;; -*-emacs-lisp-*-
;;
;; Emacs startup file, e.g.  /etc/emacs/site-start.d/50backports-3.17.1.el
;; for the Debian backports-3.17.1 package
;;
;; Originally contributed by Nils Naumann <naumann@unileoben.ac.at>
;; Modified by Dirk Eddelbuettel <edd@debian.org>
;; Adapted for dh-make by Jim Van Zandt <jrv@debian.org>

;; The backports-3.17.1 package follows the Debian/GNU Linux 'emacsen' policy and
;; byte-compiles its elisp files for each 'emacs flavor' (emacs19,
;; xemacs19, emacs20, xemacs20...).  The compiled code is then
;; installed in a subdirectory of the respective site-lisp directory.
;; We have to add this to the load-path:
(let ((package-dir (concat "/usr/share/"
                           (symbol-name debian-emacs-flavor)
                           "/site-lisp/backports-3.17.1")))
;; If package-dir does not exist, the backports-3.17.1 package must have
;; removed but not purged, and we should skip the setup.
  (when (file-directory-p package-dir)
    (if (fboundp 'debian-pkg-add-load-path-item)
        (debian-pkg-add-load-path-item package-dir)
      (setq load-path (cons package-dir load-path)))
    (autoload 'backports-3.17.1-mode "backports-3.17.1-mode"
      "Major mode for editing backports-3.17.1 files." t)
    (add-to-list 'auto-mode-alist '("\\.backports-3.17.1$" . backports-3.17.1-mode))))

