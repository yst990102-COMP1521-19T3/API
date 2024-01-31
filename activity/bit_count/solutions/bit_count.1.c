// COMP1521 19t3 ... test03_bit_count: count bits in a uint64_t
// An intrinsically better solution.
//
// 2019-09-28	Jashank Jeremy <jashank.jeremy@unsw.edu.au>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

//
// If I allow myself the luxury of calling a function, this exercise is
// very simple.  But ... this _isn't_ a function! :-)
//
// Many compilers contain what are called 'intrinsic' operations: those
// which are implemented in hardware, sometimes.  In GCC and Clang,
// there are several ways to invoke intrinsic operations, but the safest
// and most portable is to use a '__builtin_'-prefixed function name.
//
// The compiler, as it's doing code generation, can replace calls to
// these intrinsics with real hardware instructions, if they exist, or a
// software implementation if they don't.
//
// Here, I invoke the 'popcountl' intrinsic, which "returns the number
// of 1-bits in x", and where "the argument type is unsigned long".
// That sounds like exactly what I'm looking for!
//
// So, if I compile this 'bit_count' function on the AMD64 processor
// architecture, the result is 27 instructions long, and most of them
// implement the intrinsic by doing bitwise hackery.  (How that
// implementation works is left an as exercise to the reader.)
//
// But if I allow my compiler (here, Clang) to use an architecture
// extension, SSE4::
//
//   :jaenelle: clang -msse4 -O1 -c bit_count.1.c
//   :jaenelle: objdump -d bit_count.1.o | sed -ne '/<bit_count>:/,$ {p}'
//   0000000000000060 <bit_count>:
//     60:	f3 48 0f b8 c7       	popcnt %rdi,%rax
//     65:	c3                   	retq
//
// And that's pretty cool!
//
// So how did I boil 27 instructions down to just two?  Because the SSE4
// extension adds an instruction, 'POPCNT', which does exactly what the
// intrinsic wants: "return the count of number of bits set to 1":
//   <https://www.felixcloutier.com/x86/popcnt>
//
// It's definitely worth having a look through a list of compiler
// intrinsics to see what else your compiler can do.  Some won't be
// obvious in their use -- often, they're extremely specialised, or
// perform operations that you almost certainly don't want to invoke.
//
// GCC's builtins and intrinsics list:
//   <https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html>
// Clang's builtins and intrinsics list:
//   <https://clang.llvm.org/docs/LanguageExtensions.html#builtin-functions>
//
int bit_count(uint64_t value)
{
	return __builtin_popcountl (value);
}
