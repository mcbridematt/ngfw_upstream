#
# Regular cron jobs for the backports-3.17.1 package
#
0 4	* * *	root	[ -x /usr/bin/backports-3.17.1_maintenance ] && /usr/bin/backports-3.17.1_maintenance
