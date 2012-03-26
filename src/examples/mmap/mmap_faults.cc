#include<stdio.h> // for printf(3)
#include<sys/mman.h> // for mmap(2), munmap(2)
#include<sys/types.h> // for open(2), fstat(2)
#include<sys/stat.h> // for open(2), fstat(2)
#include<fcntl.h> // for open(2)
#include<unistd.h> // for fstat(2), close(2), getpagesize(2)
#include<sys/time.h> // for getrusage(2)
#include<sys/resource.h> // for getrusage(2)

#include "us_helper.hh"

/*
 * This example shows the page faults that are generated by access to an mmaped file.
 *
 * The example maps the full /etc/passwd file to user space.
 *
 * 	Mark Veltzer
 */

//const char* file_to_map="/etc/passwd";
const char* file_to_map="/boot/initrd.img-3.0.0-16-generic";

void show_vmem() {
	struct rusage usage;
	CHECK_NOT_M1(getrusage(RUSAGE_SELF,&usage));
	printf("usage.ru_maxrss=%lu\n",usage.ru_maxrss);
	printf("usage.ru_minflt=%lu\n",usage.ru_minflt);
}

int main(int argc,char** argv,char** envp) {
	show_vmem();
	int fd;
	CHECK_NOT_M1(fd=open(file_to_map,O_RDONLY));
	struct stat stat_buf;
	CHECK_NOT_M1(fstat(fd,&stat_buf));
	printf("size is %ld\n",stat_buf.st_size);
	printf("fd is %d\n",fd);
	const int size=stat_buf.st_size;
	const int pagesize=getpagesize();
	void *res;
	CHECK_NOT_VAL(res=mmap(
		NULL,/* addr: dont recommend address */
		size,/* size: the size of the file */
		PROT_READ,/* prot: we just want read */
		//MAP_PRIVATE | MAP_POPULATE, /* flags: PRIVATE or SHARED ** MUST** be specified */
		MAP_PRIVATE, /* flags: PRIVATE or SHARED ** MUST** be specified */
		fd,/* fd: our file descriptor */
		0/* offset: from the begining of the file */
	),MAP_FAILED);
	// we have the mmap address, we don't need the file anymore...
	CHECK_NOT_M1(close(fd));
	// lets read the memory...
	// I must collect the sum and print it otherwise the compiler will optimize
	// this entire loop out of my code...
	int sum=0;
	for(int i=0;i<size;i+=pagesize) {
		sum+=((char*)res)[i];
	}
	printf("sum is %d\n",sum);
	CHECK_NOT_M1(munmap(res,stat_buf.st_size));
	show_vmem();
	return 0;
}