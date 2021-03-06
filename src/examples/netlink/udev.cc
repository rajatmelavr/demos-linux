/*
 * This file is part of the linuxapi package.
 * Copyright (C) 2011-2016 Mark Veltzer <mark.veltzer@gmail.com>
 *
 * linuxapi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * linuxapi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with linuxapi. If not, see <http://www.gnu.org/licenses/>.
 */

#include <firstinclude.h>
#include <stdlib.h>	// for EXIT_SUCCESS
#include <asm/types.h>	// for SOCK_DGRAM
#include <sys/socket.h>	// for socket(2)
#include <linux/netlink.h>	// for AF_NETLINK, NETLINK_KOBJECT_UEVENT
#include <err_utils.h>	// for CHECK_NOT_M1()
#include <unistd.h>	// for read(2)
#include <stdio.h>	// for printf(3)

/*
 * This application should show how to listen to udev events using API...
 *
 * Why would you want to do this ?
 * - you want a real small RT system and don't want udev on it.
 * - you hate the "system" approach that udev takes to running rules.
 * - you want to listen to udev events in parallel to other things with tight integration.
 * - you want to reduce boot time and want to do things in parallel
 *	(listen to drivers loading while doing other initialization work).
 *
 * Strictly speaking this demo is not a real time demo per se. It is a demo that will
 * usually be used on embedded systems where a full udev is not available but not
 * necessarily a real time system.
 */

int main(int argc, char** argv, char** envp) {
	int netlink_socket=CHECK_NOT_M1(socket(AF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT));
	const unsigned int SIZE=1024;
	char buf[SIZE];
	ssize_t s=CHECK_NOT_M1(read(netlink_socket, buf, SIZE));
	printf("s is %zd\n", s);
	CHECK_NOT_M1(close(netlink_socket));
	return EXIT_SUCCESS;
}
