/*
 * This file is part of the linuxapi package.
 * Copyright (C) 2011-2014 Mark Veltzer <mark.veltzer@gmail.com>
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
// #include <iostream>	// for std::cout, std::endl
#include <assert.h>	// for assert(3)
#include <stdlib.h>	// for EXIT_SUCCESS

/*
 * This example investigates the structure of vtables in the
 * GCC compiler.
 *
 * It does so both for a simple single object and for inherited objects.
 *
 * It shows that GCC vtables are "flat". This means that the vtable for
 * a derived object has pointers to the virtual methods of the parent
 * at the begining of the table and then method to it's own method, in
 * order of declaration.
 *
 * The virtual tables are also not directly pointed to by the instances
 * but rather indirectly.
 */

class A {
public:
	virtual void vamethod0() {
	}
	virtual void vamethod1() {
	}
	virtual void vamethod2() {
	}
};

class B : public A {
public:
	virtual void vbmethod0() {
	}
	virtual void vbmethod1() {
	}
};

// this does not work...
// dumps core?!?
template <class T> void* convert(void (T::*p)()) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpmf-conversions"
	void* ret=(void*)p;
#pragma GCC diagnostic pop
	return ret;
}

int main(int argc, char** argv, char** envp) {
	// first lets see the size of the object (it should be 4
	// since it is empty and therefore has size 1 but also
	// has a vtable which overrides the 1 for empty and increases
	// the size to 4...)
	assert(sizeof(A)==4);
	// show that the first pointer in any object is the v table
	A obj1, obj2;
	// this is the vtable
	void** vp1=(void**)&obj1;
	void** vp2=(void**)&obj2;
	assert(*vp1==*vp2);
	// now lets show that the vtable simply has all methods in order
	// of declaration
	A a;
	void** va=*(void***)&a;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpmf-conversions"
	void* vAamethod0=(void*)&A::vamethod0;
	void* vAamethod1=(void*)&A::vamethod1;
	void* vAamethod2=(void*)&A::vamethod2;
#pragma GCC diagnostic pop
	assert(vAamethod0==va[0]);
	assert(vAamethod1==va[1]);
	assert(vAamethod2==va[2]);
	// show that size of B did not increase because it is a derived
	// object...
	assert(sizeof(B)==4);
	// show that the vtable of b has same charactersitics as vtable of A...
	B b;
	void** vb=*(void***)&b;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpmf-conversions"
	void* vBamethod0=(void*)&B::vamethod0;
	void* vBamethod1=(void*)&B::vamethod1;
	void* vBamethod2=(void*)&B::vamethod2;
	void* vBbmethod0=(void*)&B::vbmethod0;
	void* vBbmethod1=(void*)&B::vbmethod1;
#pragma GCC diagnostic pop
	assert(vBamethod0==vb[0]);
	assert(vBamethod1==vb[1]);
	assert(vBamethod2==vb[2]);
	assert(vBbmethod0==vb[3]);
	assert(vBbmethod1==vb[4]);
	return EXIT_SUCCESS;
}
