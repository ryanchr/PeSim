#NO_APP
gcc_compiled.:
.text
	.even
_label_rtx:
	link a6,#0
	movel a2,sp@-
	movel a6@(8),a2
	cmpb #40,a2@(12)
	jeq L2
	jbsr _abort
L2:
	tstl a2@(64)
	jeq L3
	movel a2@(64),d0
	jra L1
L3:
	jbsr _gen_label_rtx
	movel d0,a2@(64)
L1:
	movel a6@(-4),a2
	unlk a6
	rts
	.even
.globl _emit_jump
_emit_jump:
	link a6,#0
	jbsr _do_pending_stack_adjust
	movel a6@(8),sp@-
	jbsr _gen_jump
	movel d0,sp@-
	jbsr _emit_jump_insn
	jbsr _emit_barrier
	unlk a6
	rts
