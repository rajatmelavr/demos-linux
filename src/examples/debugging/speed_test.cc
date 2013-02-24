/*
	This file is part of the linuxapi project.
	Copyright (C) 2011-2013 Mark Veltzer <mark.veltzer@gmail.com>

	The linuxapi package is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	The linuxapi package is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with the GNU C Library; if not, write to the Free
	Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
	02111-1307 USA.
*/

#include <firstinclude.h>
#include <stdio.h> // for printf(3)
#include <stdlib.h> // for EXIT_SUCCESS

/*
* A simple speed test app to show the difference between software and
* hardware breakpoints.
*
* You use this example by running it in gdb once under "break" and once
* under "hbreak" and show the difference in speed.
*
* Compare the following:
* 1) break /home/mark/git/branches/linuxapi/src/examples/debugging/speed_test.cc:43
* if sum=8000
* 2) break /home/mark/git/branches/linuxapi/src/examples/debugging/speed_test.cc:43
* 3) hbreak /home/mark/git/branches/linuxapi/src/examples/debugging/speed_test.cc:43
*
* EXTRA_COMPILE_FLAGS=-g3
*/

int main(int argc,char** argv,char** envp) {
	volatile long sum=0;
	for(long i=0;i<1000000;i++) {
		for(long j=0;j<1000000000;j++) {
			sum+=i+j;
		}
		printf("%ld: one step\n",i);
	}
	printf("sum is %ld\n",sum);
	return EXIT_SUCCESS;
}
