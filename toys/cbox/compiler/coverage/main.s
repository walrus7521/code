	.text
	.def	 fun1;
	.scl	2;
	.type	32;
	.endef
	.globl	fun1                    # -- Begin function fun1
	.p2align	4, 0x90
fun1:                                   # @fun1
.seh_proc fun1
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	callq	fun2
	nop
	addq	$40, %rsp
	retq
	.seh_handlerdata
	.text
	.seh_endproc
                                        # -- End function
	.def	 fun2;
	.scl	2;
	.type	32;
	.endef
	.globl	fun2                    # -- Begin function fun2
	.p2align	4, 0x90
fun2:                                   # @fun2
.seh_proc fun2
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	callq	fun3
	nop
	addq	$40, %rsp
	retq
	.seh_handlerdata
	.text
	.seh_endproc
                                        # -- End function
	.def	 fun3;
	.scl	2;
	.type	32;
	.endef
	.globl	fun3                    # -- Begin function fun3
	.p2align	4, 0x90
fun3:                                   # @fun3
# %bb.0:
	movl	$42, %eax
	retq
                                        # -- End function
	.def	 fun4;
	.scl	2;
	.type	32;
	.endef
	.globl	fun4                    # -- Begin function fun4
	.p2align	4, 0x90
fun4:                                   # @fun4
.seh_proc fun4
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	callq	fun1
	nop
	addq	$40, %rsp
	retq
	.seh_handlerdata
	.text
	.seh_endproc
                                        # -- End function

