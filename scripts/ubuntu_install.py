#!/usr/bin/python3

'''
this script will install all the required packages that you need on
ubuntu to compile and work with this package.

TODO
- the intel compiler auto-installation is not supported.
'''

###########
# imports #
###########
import subprocess # for check_call
import os # for uname
import sys # for exit

##############
# parameters #
##############
# debug this script?
opt_debug=False
# exit after debug?
opt_exit=False
# what boost to install?
opt_boost_version='1.58.0'
opt_boost_version_short='1.58'
# install kernels?
opt_do_kernel=True
# install debug packages for kernels?
opt_do_ddebs=False
# version of the papi library
opt_papiversion='5.4.1'
# do templar?
opt_do_templar=False

########
# code #
########
release=os.uname().release
short_release=release[:release.rfind('-')]
source_release=short_release[:short_release.rfind('-')]
release_lowlatency=short_release
release_generic=short_release
codename=subprocess.check_output(['lsb_release', '--codename', '--short']).decode().rstrip()

if codename=='trusty':
	opt_urcu_ver=1
else:
	opt_urcu_ver=2

if opt_debug:
	print('release is [{0}]'.format(release))
	print('short_release is [{0}]'.format(short_release))
	print('source_release is [{0}]'.format(source_release))
	print('release_lowlatency is [{0}]'.format(release_lowlatency))
	print('release_generic is [{0}]'.format(release_generic))
	print('codename is [{0}]'.format(codename))
	print('opt_urcu_ver is [{0}]'.format(opt_urcu_ver))
if opt_exit:
	sys.exit(0)

packs=[
        # most important - compiler parts
        'gcc-doc', # gcc documentation
        'cpp-doc', # gcc documentation

	# manual pages
	'manpages',
	'manpages-dev',
	'manpages-posix',
	'manpages-posix-dev',
	'gnulib',
	'bikeshed',

	# debugging
	'cgdb',
	'xxgdb',
	'qtcreator',

	# code measurements
	'sloccount',
	'cloc',

        # basic tools
	'binutils-dev', # for demangle.h
	'binutils-doc', # for demangle.h
	'aspectc++',
	'dialog',
	'iptables-dev',
	'unoconv',

        # libraries
	'libevent-dev',
	'libevent-2.0-5',
        'libiberty-dev',
	'libncurses5',
	'libncurses5-dev',
	'libncursesw5',
	'libncursesw5-dev',
	'ncurses-doc',
	'libprocps3',
	'libprocps3-dev',
	'libgnomeui-0',
	'libgnomeui-dev',
	'libgnomeui-doc',
	'libsigc++-2.0-0v5',
	'libsigc++-2.0-dev',
	'libsigc++-2.0-doc',
	'libgtkmm-2.4-dev',
	'libgtkmm-2.4-doc',
	'libgtkmm-3.0-dev',
	'libgtkmm-3.0-doc',
	'libpq-dev',
	'liblog4cpp5-dev',
	'libmysqlclient-dev',
	'libcwd',
	'libqt4-dev',
	'libwxgtk2.8-dev',
	'libmysql++-dev',
	'libsdl1.2-dev',
	'libace-dev',
	'libboost'+opt_boost_version_short+'-dev', # for boost threading
	'libboost-thread'+opt_boost_version, # for the actual library
	'libpcap-dev',
	'libasound2',
	'libasound2-dev',
	'libasound2-doc',
	'libdmalloc5',
	'libdmalloc-dev',
	'libcpufreq-dev', # for cpufreq.h
	'libnetfilter-queue1',
	'libnetfilter-queue-dev',
	'libcap-dev', # for capability.h
	'liburcu{0}'.format(opt_urcu_ver), # rcu library
	'liburcu-dev', # rcu library
	'libunwind8', # unwind library
	'libunwind-setjmp0', # unwind library
	'libunwind8-dev', # unwind library
	'libunwind-setjmp0-dev', # unwind library
	'libelf1', # for reading elf files
	'libdw1',
	'libdw-dev',
	'libasm1',
	'libasm-dev',
	'libstdc++6-4.7-doc',
	'aspell-doc',
	'libaspell-dev',
	'libacl1-dev',
	'libattr1-dev',

	# compilers
	'gcc-4.7-plugin-dev',
	'gcc-4.8-plugin-dev',
	'gcc-4.7',
	'g++-4.7',
	'gcc-4.7-doc',
	'gcc-4.8',
	'g++-4.8',
	'gcc-4.8-doc',
	#'g++-4.9',
	'gcc-snapshot',
	'clang',

	# libc
	'glibc-doc',
	'glibc-doc-reference',

	# tools for demos
	'linux-tools-common', # for perf(1)
	'python3-uno', # for soffice conversion
	'electric-fence',
	#'vnstat', # causes performance problems
	#'vnstati', # causes performance problems
	'wireshark-common',
	'wireshark',
	'ngrep',
	'iftop',
	'traceroute',
	'valgrind',
	'dwarves',
	'kerneltop',
	'tshark',
	'google-perftools',
	'pv',
	'splint',
	'patchelf',
	'schedtool',
	'blktrace',
	'systemtap-sdt-dev',
	'fdutils', # floppy disk utilities ?!?
	'iotop', # for the iotop command
	'jnettop', # for the jnettop command
	'smartmontools',
	'gsmartcontrol',
	'lm-sensors',
	'inxi',
	'hddtemp',
	'htop',
	'sysprof',
	'mutrace',
	'cpulimit', # for the cpulimit command
	'bridge-utils', # for bridging utilities to demo creation of a bridge
	'iptraf',
	'numactl',
	'pstack',
	'x86info',
	'lsscsi',
	'chrpath',
	'latencytop',
	'devmem2',
	'elfutils', # for manipulating elf files
	#'elfkickers',
	'pax-utils',
	'paxctl',
	'execstack',
	'prelink',
	'dstat',
	#'netperf', # causes performance problems
	#'netserver', # causes performance problems
	'sysstat',
	'nmon',
	'saidar',
	'sysdig',
	'iperf',
	'smem',
	'sysbench',
	#'icinga-core', # causes performance problems
	#'nagios3-core', # causes performance problems
	'ksysguard',
	'gnome-system-monitor',
	'xfce4-taskmanager',
	'mrtg',
	#'multipath-tools', # causes performance problems
	#'monit', # causes performance problems
	#'munin', # causes performance problems
	#'lttng-tools', # causes performance problems
	#'atop', # causes performance problems
	'isag',
	'sdparm',
	#'nfs-common', # for nfsiostats(1), mountstats(1), nfsstat(1) cause performance problems
	'mytop',
	'cutils',
	'jlint',
	'jlint-doc',
	'hlint',
	'dlint',
	'oprofile',
	'ioapps',
	'powertop',
	'rt-tests',
	#'lttng-modules-dkms',
	'procinfo',
	'wavemon',
	'bum',

	# fun stuff
	'figlet',
	'sl',

	# package used tools used by the linuxapi package
	'libreoffice-common', # for soffice conversion
	'ccache', # for ccache(1) (faster building)
	'xutils-dev', # for makedepend(1)
	'uncrustify', # for uncrustify(1) (code formatting)
	'indent', # for indent(1) (code formatting)
	'astyle', # for indent(1) (code formatting)

	# these packages are for the developers pleasure...:)
	'vim',
	'tofrodos',
	'pipemeter',
	'blktool',
	'scons',
	'scons-doc',
	'doxygen',
	'make',
	'make-doc',

	# memory testing tools
	'memtester',
	'memtest86+',

	# papi
	'libpapi-dev', # PAPI development files (headers and API documentation)
	'libpapi'+opt_papiversion, # PAPI runtime (shared libraries)
	'papi-dbg', # PAPI debug symbols
	'papi-examples', # PAPI example files and test programs
	'papi-tools', # PAPI utilities

	# assmebly
	'nasm',
	'yasm',

	# kernel debugging
	'systemtap',
	'systemtap-common',
	'systemtap-runtime',
	'systemtap-doc',

	# kexec and kernel crash debugging
	'crash',
	'kdump-tools',
	'kexec-tools',
	'linux-crashdump',
	'makedumpfile',

	# databases
	'tora',
	'postgresql-client',
	'postgresql-client-common',
	'postgresql-doc',

	# watchdogs
	'rtkit',
	'watchdog',
	'supervisor',
	'daemontools',
	'ruby-god',
	'monit',
]

if opt_do_templar:
	packs.extend([
		# my own stuff
		'templar',
	])

if opt_do_kernel:
	packs.extend([
		# kernel stuff
		'linux-image-'+release_generic+'-generic',
		'linux-image-'+release_lowlatency+'-lowlatency',
		'linux-headers-generic',
		'linux-headers-lowlatency',
		'linux-headers-'+release_generic+'-generic',
		'linux-headers-'+release_lowlatency+'-lowlatency',
		#'linux-tools', # there is no such package
		'linux-tools-generic',
		'linux-tools-lowlatency',
		'linux-tools-'+release_generic+'-generic',
		'linux-tools-'+release_lowlatency+'-lowlatency',
		'linux-source',
		'linux-source-'+source_release,
	])

if opt_do_ddebs:
	packs.extend([
		# for systemtap - this one does not exist in the regular ubuntu archives
		# ubuntu does not always carry the "-lowlatency" dbgsym and that why
		# it is commented out...
		# TODO: make this script add sources to the dbgsyms if need be
		'linux-image-'+release_generic+'-generic'+'-dbgsym',
		'linux-image-'+release_lowlatency+'-lowlatency'+'-dbgsym',
	])

args=[
	'sudo',
	'apt-get',
	'install',
	'--assume-yes'
]
args.extend(packs)
try:
	subprocess.check_call(args)
except:
	pass
