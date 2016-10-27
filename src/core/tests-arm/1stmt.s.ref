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
	.even
.globl _expand_label
_expand_label:
	link a6,#0
	movel d2,sp@-
	movel a6@(8),d2
	jbsr _do_pending_stack_adjust
	movel d2,sp@-
	jbsr _label_rtx
	movel d0,sp@-
	jbsr _emit_label
	addqw #8,sp
	tstl _stack_block_stack
	jeq L6
	pea 8:w
	jbsr _oballoc
	movel d0,a0
	movel _stack_block_stack,a1
	movel a1@(36),a0@
	movel a0,a1@(36)
	movel d2,a0@(4)
L6:
	movel a6@(-4),d2
	unlk a6
	rts
	.even
.globl _expand_goto
_expand_goto:
	link a6,#0
	movel d2,sp@-
	movel a6@(8),d2
	clrl sp@-
	movel d2,sp@-
	jbsr _label_rtx
	addqw #4,sp
	movel d0,sp@-
	movel d2,sp@-
	jbsr _expand_goto_internal
	movel a6@(-4),d2
	unlk a6
	rts
LC0:
	.ascii "jump to `%s' invalidly jumps into binding contour\0"
	.even
_expand_goto_internal:
	link a6,#0
	moveml #0x2038,sp@-
	movel a6@(8),a3
	movel a6@(12),a4
	clrl d2
	cmpw #17,a4@
	jeq L9
	jbsr _abort
L9:
	tstl a4@(8)
	jeq L10
	movel _block_stack,a2
	tstl a2
	jeq L12
L17:
	movel a2@(20),a0
	movel a0@(4),d1
	cmpl a4@(4),d1
	jlt L12
	tstl a2@(16)
	jeq L15
	movel a2@(16),d2
L15:
	tstl a2@(28)
	jeq L13
	clrl sp@-
	movel a2@(28),sp@-
	jbsr _expand_cleanups
	addqw #8,sp
L13:
	movel a2@(4),a2
	tstl a2
	jne L17
L12:
	tstl d2
	jeq L18
	movel d2,sp@-
	movel _stack_pointer_rtx,sp@-
	jbsr _emit_move_insn
	addqw #8,sp
L18:
	tstl a3
	jeq L20
	btst #3,a3@(13)
	jeq L20
	movel a3@(36),a0
	movel a0@(20),sp@-
	pea LC0
	jbsr _error
	addqw #8,sp
	jra L20
L10:
	movel a6@(16),sp@-
	movel a4,sp@-
	movel a3,sp@-
	jbsr _expand_fixup
	addw #12,sp
	tstl d0
	jne L20
	tstl a3
	jeq L20
	orb #64,a3@(14)
L20:
	movel a4,sp@-
	jbsr _emit_jump
	moveml a6@(-16),#0x1c04
	unlk a6
	rts
	.even
_expand_fixup:
	link a6,#0
	moveml #0x3030,sp@-
	movel a6@(12),d2
	movel a6@(16),d3
	tstl _cond_stack
	jeq L25
	movel _cond_stack,a0
	cmpl a0@(16),d2
	jeq L26
	cmpl a0@(20),d2
	jne L25
L26:
	movel _cond_stack,a3
	jra L27
L25:
	tstl _loop_stack
	jeq L28
	movel _loop_stack,a0
	cmpl a0@(16),d2
	jeq L29
	cmpl a0@(20),d2
	jeq L29
	cmpl a0@(24),d2
	jne L28
L29:
	movel _loop_stack,a3
	jra L27
L28:
	subl a3,a3
L27:
	tstl a3
	jeq L31
	movel a3@,a1
	movel _block_stack,a2
	tstl a1
	jeq L33
L34:
	cmpl a1,a2
	jeq L33
	movel a1@,a1
	tstl a1
	jne L34
L33:
	tstl a1
	jeq L35
	clrl d0
	jra L24
L35:
	movel _block_stack,a0
	movel a0@(4),a1
	movel a0,a2
	cmpl a2,a3
	jeq L54
L40:
	cmpl a2,a1
	jne L38
	movel a1@(4),a1
L38:
	movel a2@,a2
	cmpl a2,a3
	jne L40
L54:
	movel a1,a3
L31:
	movel _block_stack,a2
	cmpl a2,a3
	jeq L42
L46:
	tstl a2@(16)
	jne L42
	tstl a2@(28)
	jne L42
	movel a2@(4),a2
	cmpl a2,a3
	jne L46
L42:
	cmpl a2,a3
	jeq L47
	pea 24:w
	jbsr _oballoc
	movel d0,a3
	jbsr _do_pending_stack_adjust
	addqw #4,sp
	tstl d3
	jeq L48
	movel d3,d0
	jra L49
L48:
	jbsr _get_last_insn
L49:
	movel d0,a3@(4)
	movel a6@(8),a3@(8)
	movel d2,a3@(12)
	clrl a3@(16)
	tstl a2@(32)
	jne L52
	tstl a2@(28)
	jeq L50
L52:
	movel a2@(32),sp@-
	movel a2@(28),sp@-
	clrl sp@-
	jbsr _tree_cons
	jra L51
L50:
	clrl d0
L51:
	movel d0,a3@(20)
	movel _goto_fixup_chain,a3@
	movel a3,_goto_fixup_chain
L47:
	tstl a2
	sne d0
	moveq #1,d1
	andl d1,d0
L24:
	moveml a6@(-16),#0xc0c
	unlk a6
	rts
LC1:
	.ascii "label `%s' used before containing binding contour\0"
	.even
_fixup_gotos:
	link a6,#0
	moveml #0x3c3c,sp@-
	movel a6@(8),a4
	movel a6@(12),d3
	movel a6@(16),d5
	movel a6@(20),a5
	movel a6@(24),d4
	subl a0,a0
	movel _goto_fixup_chain,a3
	tstl a3
	jeq L84
L81:
	tstl a3@(4)
	jne L60
	tstl a0
	jeq L59
	movel a3@,a0@
	jra L59
L60:
	movel a3@(12),a0
	tstl a0@(8)
	jeq L63
	tstl a3@(8)
	jeq L64
	tstl d4
	jne L65
	tstl d3
	jne L65
	tstl d5
	jeq L64
L65:
	movel a3@(4),a0
	movel a5@(4),d1
	cmpl a0@(4),d1
	jle L64
	movel a3@(8),a0
	btst #6,a0@(14)
	jne L64
	pea LC1
	movel a0,sp@-
	jbsr _error_with_decl
	movel a3@(8),a0
	orb #64,a0@(14)
	addqw #8,sp
L64:
	tstl a3@(20)
	jeq L66
	movel a3@(20),a2
	tstl a2
	jeq L66
	movel a3,d2
	addql #4,d2
L71:
	btst #6,a2@(14)
	jeq L69
	tstl a2@(20)
	jeq L69
	movel d2,sp@-
	movel a2@(20),sp@-
	jbsr _fixup_cleanups
	addqw #8,sp
L69:
	movel a2@(4),a2
	tstl a2
	jne L71
L66:
	tstl a3@(16)
	jeq L72
	movel a3@(4),sp@-
	movel a3@(16),sp@-
	movel _stack_pointer_rtx,sp@-
	jbsr _gen_move_insn
	addqw #8,sp
	movel d0,sp@-
	jbsr _emit_insn_after
	addqw #8,sp
L72:
	clrl a3@(4)
	jra L59
L63:
	tstl a4
	jeq L59
	movel a3@(20),a0
	tstl a0
	jeq L82
L79:
	movel a0@(4),d1
	cmpl a4@(32),d1
	jne L77
	orb #64,a0@(14)
L77:
	movel a0@(4),a0
	tstl a0
	jne L79
L82:
	tstl d3
	jeq L59
	movel d3,a3@(16)
L59:
	movel a3,a0
	movel a3@,a3
	tstl a3
	jne L81
L84:
	moveml a6@(-32),#0x3c3c
	unlk a6
	rts
	.even
.globl _expand_asm
_expand_asm:
	link a6,#0
	movel a6@(8),a0
	movel a0@(24),sp@-
	clrl sp@-
	pea 21:w
	jbsr _gen_rtx
	movel d0,sp@-
	jbsr _emit_insn
	clrl _last_expr_type
	unlk a6
	rts
LC2:
	.ascii "input operand constraint contains `+'\0"
LC3:
	.ascii "output operand constraint lacks `='\0"
LC4:
	.ascii "more than %d operands in `asm'\0"
LC5:
	.ascii "\0"
LC6:
	.ascii "hard register `%s' listed as input operand to `asm'\0"
LC7:
	.ascii "input operand constraint contains `%c'\0"
LC8:
	.ascii "unknown register name `%s' in `asm'\0"
	.even
.globl _expand_asm_operands
_expand_asm_operands:
	link a6,#-4
	moveml #0x3f3c,sp@-
	movel a6@(16),sp@-
	lea _list_length,a2
	jbsr a2@
	movel d0,d5
	movel a6@(12),sp@-
	jbsr a2@
	movel d0,d4
	movel a6@(20),sp@-
	jbsr a2@
	movel d0,a6@(-4)
	movel d4,d0
	asll #2,d0
	addw #12,sp
	addql #1,d0
	moveq #-2,d7
	andl d7,d0
	subl d0,sp
	movel sp,a5
	clrl _last_expr_type
	clrl d3
	movel a6@(12),a3
	tstl a3
	jeq L146
L99:
	movel a3@(20),a4
	movel a4@(8),d7
	cmpl _error_mark_node,d7
	jeq L86
	clrl d1
	clrl d0
	jra L91
L96:
	movel a3@(16),a0
	movel a0@(24),a0
	cmpb #43,a0@(d0:l)
	jne L94
	pea LC2
	jbsr _error
	jra L86
L94:
	movel a3@(16),a0
	movel a0@(24),a0
	cmpb #61,a0@(d0:l)
	jne L93
	moveq #1,d1
L93:
	addql #1,d0
L91:
	movel a3@(16),a0
	cmpl a0@(20),d0
	jlt L96
	tstl d1
	jne L97
	pea LC3
	jbsr _error
	jra L86
L97:
	cmpb #43,a4@(12)
	jeq L98
	cmpb #44,a4@(12)
	jeq L98
	cmpb #49,a4@(12)
	jeq L98
	movel a4@(8),a0
	clrl d0
	moveb a0@(28),d0
	movel d0,sp@-
	jbsr _gen_reg_rtx
	movel d0,d2
	movel d2,sp@-
	movel a4,sp@-
	pea 112:w
	jbsr _build_nt
	movel d0,a2
	movel _save_expr_regs,sp@-
	movel d2,sp@-
	clrl sp@-
	pea 2:w
	jbsr _gen_rtx
	movel d0,_save_expr_regs
	movel a2,a3@(20)
	movel a4@(8),a2@(8)
	addw #32,sp
L98:
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a3@(20),sp@-
	jbsr _expand_expr
	movel d0,a5@(d3:l:4)
	addw #16,sp
	movel a3@(4),a3
	addql #1,d3
	tstl a3
	jne L99
L146:
	movel d5,d0
	addl d4,d0
	moveq #5,d7
	cmpl d0,d7
	jge L100
	pea 5:w
	pea LC4
	jbsr _error
	jra L86
L100:
	movel d5,sp@-
	lea _rtvec_alloc,a2
	jbsr a2@
	movel d0,d6
	movel d5,sp@-
	jbsr a2@
	movel d0,d2
	movel a6@(32),sp@-
	movel a6@(28),sp@-
	movel d2,sp@-
	movel d6,sp@-
	clrl sp@-
	pea LC5
	movel a6@(8),a1
	movel a1@(24),sp@-
	clrl sp@-
	pea 22:w
	jbsr _gen_rtx
	movel d0,a4
	movel a6@(24),d7
	bfins d7,a4@(3){#3:#1}
	clrl d3
	movel a6@(16),a3
	addw #44,sp
	tstl a3
	jeq L145
L112:
	movel a3@(20),a0
	movel a0@(8),d7
	cmpl _error_mark_node,d7
	jeq L86
	tstl a3@(16)
	jne L105
	movel a0@(24),sp@-
	pea LC6
	jbsr _error
	jra L86
L105:
	clrl d0
	jra L106
L111:
	movel a3@(16),a0
	movel a0@(24),a0
	cmpb #61,a0@(d0:l)
	jeq L110
	cmpb #43,a0@(d0:l)
	jne L108
L110:
	movel a3@(16),a0
	movel a0@(24),a0
	moveb a0@(d0:l),d7
	extbl d7
	movel d7,sp@-
	pea LC7
	jbsr _error
	jra L86
L108:
	addql #1,d0
L106:
	movel a3@(16),a0
	cmpl a0@(20),d0
	jlt L111
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a3@(20),sp@-
	jbsr _expand_expr
	movel a4@(16),a0
	movel d0,a0@(4,d3:l:4)
	movel a3@(16),a0
	movel a0@(24),sp@-
	movel a3@(20),a0
	movel a0@(8),a0
	clrl d0
	moveb a0@(28),d0
	movel d0,sp@-
	pea 21:w
	jbsr _gen_rtx
	movel a4@(20),a0
	movel d0,a0@(4,d3:l:4)
	addql #1,d3
	addw #28,sp
	movel a3@(4),a3
	tstl a3
	jne L112
L145:
	clrl d3
	cmpl d3,d5
	jle L144
L116:
	clrl sp@-
	movel a4@(16),a0
	movel a0@(4,d3:l:4),sp@-
	jbsr _protect_from_queue
	movel a4@(16),a0
	movel d0,a0@(4,d3:l:4)
	addqw #8,sp
	addql #1,d3
	cmpl d3,d5
	jgt L116
L144:
	clrl d3
	cmpl d3,d4
	jle L143
L120:
	pea 1:w
	movel a5@(d3:l:4),sp@-
	jbsr _protect_from_queue
	movel d0,a5@(d3:l:4)
	addqw #8,sp
	addql #1,d3
	cmpl d3,d4
	jgt L120
L143:
	moveq #1,d7
	cmpl d4,d7
	jne L121
	tstl a6@(-4)
	jne L121
	movel a6@(12),a1
	movel a1@(16),a0
	movel a0@(24),a4@(8)
	movel a4,sp@-
	movel a5@,sp@-
	clrl sp@-
	pea 25:w
	jbsr _gen_rtx
	movel d0,sp@-
	jra L147
L121:
	tstl d4
	jne L123
	tstl a6@(-4)
	jeq L141
L123:
	movel a4,d5
	movel d4,a0
	tstl a0
	jne L125
	movew #1,a0
L125:
	movel a6@(-4),d7
	pea a0@(d7:l)
	jbsr _rtvec_alloc
	movel d0,sp@-
	clrl sp@-
	pea 20:w
	jbsr _gen_rtx
	movel d0,a4
	clrl d3
	movel a6@(12),a3
	addw #16,sp
	tstl a3
	jeq L142
L129:
	movel a6@(32),sp@-
	movel a6@(28),sp@-
	movel d2,sp@-
	movel d6,sp@-
	movel d3,sp@-
	movel a3@(16),a0
	movel a0@(24),sp@-
	movel a6@(8),a1
	movel a1@(24),sp@-
	clrl sp@-
	pea 22:w
	lea _gen_rtx,a2
	jbsr a2@
	movel d0,sp@-
	movel a5@(d3:l:4),sp@-
	clrl sp@-
	pea 25:w
	jbsr a2@
	movel a4@(4),a0
	movel d0,a0@(4,d3:l:4)
	movel a4@(4),a0
	movel a0@(4,d3:l:4),a0
	movel a0@(8),a0
	movel a6@(24),d7
	bfins d7,a0@(3){#3:#1}
	addw #52,sp
	movel a3@(4),a3
	addql #1,d3
	tstl a3
	jne L129
L142:
	tstl d3
	jne L130
	movel a4@(4),a0
	movel d5,a0@(4,d3:l:4)
	addql #1,d3
L130:
	movel a6@(20),a3
	tstl a3
	jeq L141
	lea _reg_names,a5
L140:
	movel a3@(20),a0
	movel a0@(24),d4
	clrl d2
L138:
	movel a5@(d2:l:4),sp@-
	movel d4,sp@-
	jbsr _strcmp
	addqw #8,sp
	tstl d0
	jeq L135
	addql #1,d2
	moveq #55,d7
	cmpl d2,d7
	jge L138
L135:
	moveq #56,d7
	cmpl d2,d7
	jne L139
	movel d4,sp@-
	pea LC8
	jbsr _error
	jra L86
L139:
	movel d2,sp@-
	pea 1:w
	pea 34:w
	lea _gen_rtx,a2
	jbsr a2@
	movel d0,sp@-
	clrl sp@-
	pea 27:w
	jbsr a2@
	movel a4@(4),a0
	movel d0,a0@(4,d3:l:4)
	addw #24,sp
	movel a3@(4),a3
	addql #1,d3
	tstl a3
	jne L140
L141:
	movel a4,sp@-
L147:
	jbsr _emit_insn
	clrl _last_expr_type
L86:
	moveml a6@(-44),#0x3cfc
	unlk a6
	rts
LC9:
	.ascii "statement with no effect\0"
	.even
.globl _expand_expr_stmt
_expand_expr_stmt:
	link a6,#0
	movel a2,sp@-
	movel a6@(8),a2
	tstl _extra_warnings
	jeq L149
	tstl _expr_stmts_for_value
	jne L149
	btst #4,a2@(13)
	jne L149
	cmpl _error_mark_node,a2
	jeq L149
	pea LC9
	movel _emit_lineno,sp@-
	movel _emit_filename,sp@-
	jbsr _warning_with_file_and_line
	addw #12,sp
L149:
	movel a2@(8),_last_expr_type
	tstl _flag_syntax_only
	jne L150
	clrl sp@-
	clrl sp@-
	tstl _expr_stmts_for_value
	jeq L151
	clrl d0
	jra L152
L151:
	movel _const0_rtx,d0
L152:
	movel d0,sp@-
	movel a2,sp@-
	jbsr _expand_expr
	movel d0,_last_expr_value
	addw #16,sp
L150:
	jbsr _emit_queue
	movel a6@(-4),a2
	unlk a6
	rts
	.even
.globl _clear_last_expr
_clear_last_expr:
	link a6,#0
	clrl _last_expr_type
	unlk a6
	rts
	.even
.globl _expand_start_stmt_expr
_expand_start_stmt_expr:
	link a6,#0
	moveml #0x3020,sp@-
	jbsr _start_sequence
	movel d0,d2
	jbsr _suspend_momentary
	movel d0,d3
	pea 113:w
	jbsr _make_node
	movel d0,a2
	movel d3,sp@-
	jbsr _resume_momentary
	movel d2,a2@(24)
	addql #1,_expr_stmts_for_value
	movel a2,d0
	moveml a6@(-12),#0x40c
	unlk a6
	rts
	.even
.globl _expand_end_stmt_expr
_expand_end_stmt_expr:
	link a6,#0
	moveml #0x2020,sp@-
	movel a6@(8),a2
	movel a2@(24),d2
	jbsr _do_pending_stack_adjust
	tstl _last_expr_type
	jne L156
	movel _void_type_node,_last_expr_type
	movel _const0_rtx,_last_expr_value
L156:
	movel _last_expr_type,a2@(8)
	movel _last_expr_value,a2@(24)
	jbsr _get_insns
	movel d0,a2@(20)
	movel _rtl_expr_chain,sp@-
	movel a2,sp@-
	clrl sp@-
	jbsr _tree_cons
	movel d0,_rtl_expr_chain
	movel d2,sp@-
	jbsr _end_sequence
	orb #16,a2@(13)
	movel _last_expr_value,sp@-
	jbsr _volatile_refs_p
	bfins d0,a2@(14){#3:#1}
	clrl _last_expr_type
	subql #1,_expr_stmts_for_value
	movel a2,d0
	moveml a6@(-8),#0x404
	unlk a6
	rts
	.even
.globl _expand_start_cond
_expand_start_cond:
	link a6,#0
	movel a2,sp@-
	pea 40:w
	jbsr _xmalloc
	movel d0,a2
	movel _cond_stack,a2@(4)
	movel _nesting_stack,a2@
	addql #1,_nesting_depth
	movel _nesting_depth,a2@(8)
	clrl a2@(20)
	jbsr _gen_label_rtx
	movel d0,a2@(16)
	addqw #4,sp
	tstl a6@(12)
	jne L159
	clrl d0
L159:
	movel d0,a2@(12)
	movel a2,_cond_stack
	movel a2,_nesting_stack
	clrl sp@-
	movel a2@(16),sp@-
	movel a6@(8),sp@-
	jbsr _do_jump
	movel a6@(-4),a2
	unlk a6
	rts
	.even
.globl _expand_end_cond
_expand_end_cond:
	link a6,#0
	moveml #0x2020,sp@-
	movel _cond_stack,a2
	jbsr _do_pending_stack_adjust
	movel a2@(16),sp@-
	jbsr _emit_label
	addqw #4,sp
	movel _nesting_stack,a0
	movel a0@(8),d2
L164:
	movel _cond_stack,a0
	movel a0@(4),_cond_stack
	movel a0@,_nesting_stack
	movel a0@(8),_nesting_depth
	movel a0,sp@-
	jbsr _free
	addqw #4,sp
	cmpl _nesting_depth,d2
	jlt L164
	clrl _last_expr_type
	moveml a6@(-8),#0x404
	unlk a6
	rts
	.even
.globl _expand_start_else
_expand_start_else:
	link a6,#0
	jbsr _gen_label_rtx
	movel _cond_stack,a0
	movel d0,a0@(20)
	tstl a0@(12)
	jeq L168
	movel d0,a0@(12)
L168:
	movel _cond_stack,a0
	movel a0@(20),sp@-
	jbsr _emit_jump
	movel _cond_stack,a0
	addqw #4,sp
	tstl a0@(16)
	jeq L169
	movel a0@(16),sp@-
	jbsr _emit_label
L169:
	unlk a6
	rts
	.even
.globl _expand_end_else
_expand_end_else:
	link a6,#0
	moveml #0x2020,sp@-
	movel _cond_stack,a2
	jbsr _do_pending_stack_adjust
	tstl a2@(20)
	jeq L171
	movel a2@(20),sp@-
	jbsr _emit_label
	addqw #4,sp
L171:
	movel _nesting_stack,a0
	movel a0@(8),d2
L175:
	movel _cond_stack,a0
	movel a0@(4),_cond_stack
	movel a0@,_nesting_stack
	movel a0@(8),_nesting_depth
	movel a0,sp@-
	jbsr _free
	addqw #4,sp
	cmpl _nesting_depth,d2
	jlt L175
	clrl _last_expr_type
	moveml a6@(-8),#0x404
	unlk a6
	rts
	.even
.globl _expand_start_loop
_expand_start_loop:
	link a6,#0
	moveml #0x30,sp@-
	pea 40:w
	jbsr _xmalloc
	movel d0,a3
	movel _loop_stack,a3@(4)
	movel _nesting_stack,a3@
	addql #1,_nesting_depth
	movel _nesting_depth,a3@(8)
	lea _gen_label_rtx,a2
	jbsr a2@
	movel d0,a3@(16)
	jbsr a2@
	movel d0,a3@(20)
	movel a3@(16),a3@(24)
	addqw #4,sp
	tstl a6@(8)
	jeq L179
	movel a3@(20),d0
	jra L180
L179:
	clrl d0
L180:
	movel d0,a3@(12)
	movel a3,_loop_stack
	movel a3,_nesting_stack
	jbsr _do_pending_stack_adjust
	jbsr _emit_queue
	pea -4:w
	clrl sp@-
	jbsr _emit_note
	movel a3@(16),sp@-
	jbsr _emit_label
	moveml a6@(-8),#0xc00
	unlk a6
	rts
	.even
.globl _expand_start_loop_continue_elsewhere
_expand_start_loop_continue_elsewhere:
	link a6,#0
	movel a6@(8),sp@-
	jbsr _expand_start_loop
	jbsr _gen_label_rtx
	movel _loop_stack,a0
	movel d0,a0@(24)
	unlk a6
	rts
	.even
.globl _expand_loop_continue_here
_expand_loop_continue_here:
	link a6,#0
	jbsr _do_pending_stack_adjust
	pea -8:w
	clrl sp@-
	jbsr _emit_note
	movel _loop_stack,a0
	movel a0@(24),sp@-
	jbsr _emit_label
	unlk a6
	rts
	.even
.globl _expand_end_loop
_expand_end_loop:
	link a6,#0
	moveml #0x2038,sp@-
	jbsr _get_last_insn
	movel d0,a3
	movel _loop_stack,a0
	movel a0@(16),a4
	jbsr _do_pending_stack_adjust
	tstl _optimize
	jeq L184
	cmpw #14,a3@
	jne L185
	movel a3@(16),a0
	cmpw #25,a0@
	jne L185
	movel a0@(4),d1
	cmpl _pc_rtx,d1
	jne L185
	movel a0@(8),a0
	cmpw #42,a0@
	jeq L184
L185:
	movel _loop_stack,a0
	movel a0@(16),a3
	tstl a3
	jeq L187
	movel _loop_stack,a1
L192:
	cmpw #14,a3@
	jne L188
	movel a3@(16),a0
	cmpw #25,a0@
	jne L188
	movel a0@(4),d1
	cmpl _pc_rtx,d1
	jne L188
	movel a0@(8),a0
	cmpw #42,a0@
	jne L188
	movel a0@(8),a0
	cmpw #38,a0@
	jne L191
	movel a0@(4),d1
	cmpl a1@(20),d1
	jeq L187
L191:
	movel a3@(16),a0
	movel a0@(8),a0
	movel a0@(12),a0
	cmpw #38,a0@
	jne L188
	movel a0@(4),d1
	cmpl a1@(20),d1
	jeq L187
L188:
	movel a3@(12),a3
	tstl a3
	jne L192
L187:
	tstl a3
	jeq L184
	jbsr _gen_label_rtx
	movel d0,a2
	movel a4@(8),sp@-
	movel a2,sp@-
	jbsr _emit_label_after
	jbsr _get_last_insn
	movel d0,sp@-
	movel a3,sp@-
	movel a4,sp@-
	jbsr _reorder_insns
	movel a2@(8),sp@-
	movel a4,sp@-
	jbsr _gen_jump
	addqw #4,sp
	movel d0,sp@-
	jbsr _emit_jump_insn_after
	movel a2@(8),sp@-
	jbsr _emit_barrier_after
	movel a2,a4
	addw #32,sp
L184:
	movel a4,sp@-
	jbsr _emit_jump
	pea -5:w
	clrl sp@-
	jbsr _emit_note
	movel _loop_stack,a0
	movel a0@(20),sp@-
	jbsr _emit_label
	addw #16,sp
	movel _nesting_stack,a0
	movel a0@(8),d2
L197:
	movel _loop_stack,a0
	movel a0@(4),_loop_stack
	movel a0@,_nesting_stack
	movel a0@(8),_nesting_depth
	movel a0,sp@-
	jbsr _free
	addqw #4,sp
	cmpl _nesting_depth,d2
	jlt L197
	clrl _last_expr_type
	moveml a6@(-16),#0x1c04
	unlk a6
	rts
	.even
.globl _expand_continue_loop
_expand_continue_loop:
	link a6,#0
	clrl _last_expr_type
	tstl _loop_stack
	jne L202
	clrl d0
	jra L201
L202:
	clrl sp@-
	movel _loop_stack,a0
	movel a0@(24),sp@-
	clrl sp@-
	jbsr _expand_goto_internal
	moveq #1,d0
L201:
	unlk a6
	rts
	.even
.globl _expand_exit_loop
_expand_exit_loop:
	link a6,#0
	clrl _last_expr_type
	tstl _loop_stack
	jne L204
	clrl d0
	jra L203
L204:
	clrl sp@-
	movel _loop_stack,a0
	movel a0@(20),sp@-
	clrl sp@-
	jbsr _expand_goto_internal
	moveq #1,d0
L203:
	unlk a6
	rts
	.even
.globl _expand_exit_loop_if_false
_expand_exit_loop_if_false:
	link a6,#0
	clrl _last_expr_type
	tstl _loop_stack
	jne L206
	clrl d0
	jra L205
L206:
	clrl sp@-
	movel _loop_stack,a0
	movel a0@(20),sp@-
	movel a6@(8),sp@-
	jbsr _do_jump
	moveq #1,d0
L205:
	unlk a6
	rts
	.even
.globl _expand_exit_something
_expand_exit_something:
	link a6,#0
	clrl _last_expr_type
	movel _nesting_stack,a0
	tstl a0
	jeq L213
L212:
	tstl a0@(12)
	jeq L210
	clrl sp@-
	movel a0@(12),sp@-
	clrl sp@-
	jbsr _expand_goto_internal
	moveq #1,d0
	jra L207
L210:
	movel a0@,a0
	tstl a0
	jne L212
L213:
	clrl d0
L207:
	unlk a6
	rts
	.even
.globl _expand_null_return
_expand_null_return:
	link a6,#0
	clrl sp@-
	jbsr _expand_null_return_1
	unlk a6
	rts
	.even
_expand_null_return_1:
	link a6,#0
	movel d2,sp@-
	movel a6@(8),d2
	jbsr _clear_pending_stack_adjust
	jbsr _do_pending_stack_adjust
	clrl _last_expr_type
	movel d2,sp@-
	movel _return_label,sp@-
	clrl sp@-
	jbsr _expand_goto_internal
	movel a6@(-4),d2
	unlk a6
	rts
	.even
.globl _expand_return
_expand_return:
	link a6,#0
	moveml #0x2030,sp@-
	movel a6@(8),a3
	clrl d2
	movel _block_stack,a0
	tstl a0
	jeq L220
L223:
	tstl a0@(28)
	jeq L221
	moveq #1,d2
	jra L220
L221:
	movel a0@(4),a0
	tstl a0
	jne L223
L220:
	cmpb #45,a3@(12)
	jeq L254
	cmpb #55,a3@(12)
	jeq L227
	cmpb #56,a3@(12)
	jne L226
L227:
	movel a3@(20),a0
	cmpb #45,a0@(12)
	jne L226
	movel a3@(24),a2
	jra L225
L226:
	movel a3@(8),d1
	cmpl _void_type_node,d1
	jne L229
L254:
	movel a3,a2
	jra L225
L229:
	subl a2,a2
L225:
	tstl _optimize
	jeq L233
	tstl a2
	jeq L233
	tstl _frame_offset
	jne L233
	cmpb #60,a2@(12)
	jne L233
	movel a2@(20),a0
	cmpb #114,a0@(12)
	jne L233
	movel a0@(20),d1
	cmpl _this_function,d1
	jne L233
	movel _this_function,a0
	movel a0@(52),sp@-
	movel a2@(24),sp@-
	jbsr _tail_recursion_args
	addqw #8,sp
	tstl d0
	jeq L233
	tstl _tail_recursion_label
	jne L232
	jbsr _gen_label_rtx
	movel d0,_tail_recursion_label
	movel _tail_recursion_reentry,sp@-
	movel d0,sp@-
	jbsr _emit_label_after
	addqw #8,sp
L232:
	jbsr _get_last_insn
	movel d0,sp@-
	movel _tail_recursion_label,sp@-
	clrl sp@-
	jbsr _expand_goto_internal
	jbsr _emit_barrier
	jra L218
L233:
	tstl d2
	jeq L249
	tstl a2
	jeq L249
	movel a2@(8),d1
	cmpl _void_type_node,d1
	jeq L249
	movel _this_function,a0
	movel a0@(56),a0
	movel a0@(64),a0
	cmpw #34,a0@
	jne L249
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2,sp@-
	jbsr _expand_expr
	movel d0,a2
	jbsr _emit_queue
	jbsr _get_last_insn
	movel d0,d2
	movel a2,sp@-
	movel _this_function,a0
	movel a0@(56),a0
	movel a0@(64),sp@-
	jbsr _emit_move_insn
	movel _this_function,a0
	movel a0@(56),a0
	movel a0@(64),a2
	addw #24,sp
	cmpw #34,a2@
	jne L250
	movel a2,sp@-
	clrl sp@-
	pea 26:w
	jbsr _gen_rtx
	movel d0,sp@-
	jbsr _emit_insn
	addw #16,sp
L250:
	movel d2,sp@-
	jbsr _expand_null_return_1
	jra L218
L249:
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a3,sp@-
	jbsr _expand_expr
	jbsr _emit_queue
	movel _this_function,a0
	movel a0@(56),a0
	movel a0@(64),a2
	addw #16,sp
	cmpw #34,a2@
	jne L252
	movel a2,sp@-
	clrl sp@-
	pea 26:w
	jbsr _gen_rtx
	movel d0,sp@-
	jbsr _emit_insn
	addw #16,sp
L252:
	jbsr _expand_null_return
L218:
	moveml a6@(-12),#0xc04
	unlk a6
	rts
	.even
.globl _drop_through_at_end_p
_drop_through_at_end_p:
	link a6,#0
	jbsr _get_last_insn
	movel d0,a0
	tstl a0
	jeq L257
L258:
	cmpw #18,a0@
	jne L257
	movel a0@(8),a0
	tstl a0
	jne L258
L257:
	clrl d0
	tstl a0
	jeq L259
	cmpw #16,a0@
	jeq L259
	moveq #1,d0
L259:
	unlk a6
	rts
	.even
_tail_recursion_args:
	link a6,#0
	moveml #0x3e38,sp@-
	movel a6@(8),d6
	movel a6@(12),d5
	movel d6,a3
	movel d5,a2
	clrl d3
	tstl a3
	jeq L263
L268:
	tstl a2
	jeq L263
	movel a3@(20),a0
	movel a0@(8),d1
	cmpl a2@(8),d1
	jne L270
	movel a2@(64),a0
	cmpw #34,a0@
	jne L270
	moveq #26,d1
	cmpl a2@(28),d1
	jeq L270
	movel a3@(4),a3
	movel a2@(4),a2
	addql #1,d3
	tstl a3
	jne L268
L263:
	tstl a3
	jne L270
	tstl a2
	jeq L269
L270:
	clrl d0
	jra L261
L269:
	movel d3,d0
	asll #2,d0
	addql #1,d0
	moveq #-2,d1
	andl d1,d0
	subl d0,sp
	movel sp,a4
	movel d6,a3
	clrl d3
	tstl a3
	jeq L294
L274:
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a3@(20),sp@-
	jbsr _expand_expr
	movel d0,a4@(d3:l:4)
	addw #16,sp
	movel a3@(4),a3
	addql #1,d3
	tstl a3
	jne L274
L294:
	movel d6,a3
	clrl d3
	tstl a3
	jeq L293
L284:
	clrl d4
	movel d5,a2
	clrl d2
	cmpl d2,d3
	jle L279
L282:
	movel a4@(d3:l:4),sp@-
	movel a2@(64),sp@-
	jbsr _reg_mentioned_p
	addqw #8,sp
	tstl d0
	jeq L280
	moveq #1,d4
	jra L279
L280:
	movel a2@(4),a2
	addql #1,d2
	cmpl d2,d3
	jgt L282
L279:
	tstl d4
	jeq L277
	movel a4@(d3:l:4),sp@-
	jbsr _copy_to_reg
	movel d0,a4@(d3:l:4)
	addqw #4,sp
L277:
	movel a3@(4),a3
	addql #1,d3
	tstl a3
	jne L284
L293:
	movel d5,a2
	movel d6,a3
	clrl d3
	tstl a2
	jeq L291
	clrl d2
L290:
	movel a4@(d3:l:4),a0
	moveb a0@(2),d2
	cmpl a2@(28),d2
	jne L288
	movel a0,sp@-
	movel a2@(64),sp@-
	jbsr _emit_move_insn
	addqw #8,sp
	jra L287
L288:
	movel a3@(20),a0
	movel a0@(8),a0
	bfextu a0@(14){#4:#1},d1
	movel d1,sp@-
	movel a4@(d3:l:4),sp@-
	movel a2@(64),sp@-
	jbsr _convert_move
	addw #12,sp
L287:
	movel a2@(4),a2
	movel a3@(4),a3
	addql #1,d3
	tstl a2
	jne L290
L291:
	moveq #1,d0
L261:
	moveml a6@(-32),#0x1c7c
	unlk a6
	rts
	.even
.globl _expand_start_bindings
_expand_start_bindings:
	link a6,#0
	moveml #0x2020,sp@-
	pea 40:w
	jbsr _xmalloc
	movel d0,a2
	pea -2:w
	clrl sp@-
	jbsr _emit_note
	movel d0,d2
	movel _block_stack,a2@(4)
	movel _nesting_stack,a2@
	addql #1,_nesting_depth
	movel _nesting_depth,a2@(8)
	clrl a2@(16)
	clrl a2@(28)
	addw #12,sp
	tstl _block_stack
	jeq L297
	movel _block_stack,a0
	movel a0@(32),sp@-
	movel a0@(28),sp@-
	clrl sp@-
	jbsr _tree_cons
	addw #12,sp
	jra L298
L297:
	clrl d0
L298:
	movel d0,a2@(32)
	clrl a2@(36)
	movel _stack_block_stack,a2@(24)
	movel d2,a2@(20)
	tstl a6@(8)
	jeq L299
	jbsr _gen_label_rtx
	jra L300
L299:
	clrl d0
L300:
	movel d0,a2@(12)
	movel a2,_block_stack
	movel a2,_nesting_stack
	moveml a6@(-8),#0x404
	unlk a6
	rts
	.even
.globl _use_variable
_use_variable:
	link a6,#0
	movel a6@(8),a0
	cmpw #34,a0@
	jne L302
	movel a0,sp@-
	jra L305
L302:
	cmpw #37,a0@
	jne L303
	movel a0@(4),a1
	cmpw #34,a1@
	jne L303
	cmpl _frame_pointer_rtx,a1
	jeq L303
	cmpl _arg_pointer_rtx,a1
	jeq L303
	movel a1,sp@-
L305:
	clrl sp@-
	pea 26:w
	jbsr _gen_rtx
	movel d0,sp@-
	jbsr _emit_insn
L303:
	unlk a6
	rts
	.even
_use_variable_after:
	link a6,#0
	movel a6@(8),a0
	movel a6@(12),d0
	cmpw #34,a0@
	jne L307
	movel d0,sp@-
	movel a0,sp@-
	jra L310
L307:
	cmpw #37,a0@
	jne L308
	movel a0@(4),a1
	cmpw #34,a1@
	jne L308
	cmpl _frame_pointer_rtx,a1
	jeq L308
	cmpl _arg_pointer_rtx,a1
	jeq L308
	movel d0,sp@-
	movel a1,sp@-
L310:
	clrl sp@-
	pea 26:w
	jbsr _gen_rtx
	addw #12,sp
	movel d0,sp@-
	jbsr _emit_insn_after
L308:
	unlk a6
	rts
LC10:
	.ascii "unused variable `%s'\0"
	.even
.globl _expand_end_bindings
_expand_end_bindings:
	link a6,#0
	moveml #0x3030,sp@-
	movel a6@(8),d3
	movel a6@(16),d2
	movel _block_stack,a3
	tstl _warn_unused
	jeq L312
	movel d3,a2
	tstl a2
	jeq L312
L317:
	btst #0,a2@(14)
	jne L315
	cmpb #43,a2@(12)
	jne L315
	pea LC10
	movel a2,sp@-
	jbsr _warning_with_decl
	addqw #8,sp
L315:
	movel a2@(4),a2
	tstl a2
	jne L317
L312:
	tstl a6@(12)
	jeq L318
	pea -3:w
	clrl sp@-
	jbsr _emit_note
	addqw #8,sp
	jra L319
L318:
	movel a3@(20),a0
	moveq #-1,d1
	movel d1,a0@(20)
L319:
	tstl a3@(12)
	jeq L320
	jbsr _do_pending_stack_adjust
	movel a3@(12),sp@-
	jbsr _emit_label
	addqw #4,sp
L320:
	tstl d2
	jne L322
	tstl a3@(16)
	jne L322
	tstl a3@(28)
	jeq L321
L322:
	movel a3@(36),a2
	tstl a2
	jeq L321
L327:
	movel a2@(4),a0
	orb #8,a0@(13)
	movel a2@(4),a0
	btst #6,a0@(14)
	jeq L325
	pea LC1
	movel a0,sp@-
	jbsr _error_with_decl
	addqw #8,sp
L325:
	movel a2@,a2
	tstl a2
	jne L327
L321:
	tstl a3@(16)
	jne L329
	tstl a3@(28)
	jeq L328
L329:
	clrl sp@-
	movel a3@(28),sp@-
	jbsr _expand_cleanups
	addqw #8,sp
	tstl a3@(16)
	jeq L330
	jbsr _do_pending_stack_adjust
	movel a3@(16),sp@-
	movel _stack_pointer_rtx,sp@-
	jbsr _emit_move_insn
	addqw #8,sp
L330:
	movel d2,sp@-
	movel a3@(20),sp@-
	movel a3@(28),sp@-
	movel a3@(16),sp@-
	movel a3,sp@-
	jbsr _fixup_gotos
	addw #20,sp
L328:
	tstl _obey_regdecls
	jeq L331
	movel d3,a2
	tstl a2
	jeq L331
L336:
	movel a2@(64),d0
	cmpb #43,a2@(12)
	jne L334
	tstl d0
	jeq L334
	movel d0,sp@-
	jbsr _use_variable
	addqw #4,sp
L334:
	movel a2@(4),a2
	tstl a2
	jne L336
L331:
	movel a3@(24),_stack_block_stack
	movel _nesting_stack,a0
	movel a0@(8),d2
L340:
	movel _block_stack,a0
	movel a0@(4),_block_stack
	movel a0@,_nesting_stack
	movel a0@(8),_nesting_depth
	movel a0,sp@-
	jbsr _free
	addqw #4,sp
	cmpl _nesting_depth,d2
	jlt L340
	moveml a6@(-16),#0xc0c
	unlk a6
	rts
	.even
.globl _expand_decl
_expand_decl:
	link a6,#0
	moveml #0x3038,sp@-
	movel a6@(8),a2
	movel a6@(12),d2
	movel _block_stack,a3
	jeq L347
	movel a3@(28),sp@-
	movel d2,sp@-
	movel a2,sp@-
	jbsr _temp_tree_cons
	movel d0,a3@(28)
	movel a3,_stack_block_stack
	addw #12,sp
L347:
	tstl a2
	jne L348
	tstl d2
	jne L346
	jbsr _abort
	jra L346
L348:
	movel a2@(8),a4
	cmpb #43,a2@(12)
	jne L346
	btst #5,a2@(13)
	jne L346
	tstb a2@(13)
	jlt L346
	cmpl _error_mark_node,a4
	jne L353
	movel _const0_rtx,sp@-
	pea 26:w
	pea 37:w
	jbsr _gen_rtx
	movel d0,a2@(64)
	addw #12,sp
	jra L354
L353:
	tstl a2@(24)
	jne L355
	tstl a2@(60)
	jne L356
	clrl sp@-
	movel a2@(28),sp@-
	jbsr _assign_stack_local
	movel d0,a2@(64)
	addqw #8,sp
	jra L354
L356:
	pea 4:w
	jbsr _gen_reg_rtx
	movel d0,sp@-
	pea 26:w
	pea 37:w
	jbsr _gen_rtx
	movel d0,a2@(64)
	addw #16,sp
	jra L354
L355:
	moveq #26,d3
	cmpl a2@(28),d3
	jeq L359
	tstl _flag_float_store
	jeq L360
	cmpb #6,a4@(12)
	jeq L359
L360:
	btst #4,a2@(13)
	jne L359
	btst #6,a2@(14)
	jne L359
	btst #5,a2@(14)
	jne L361
	tstl _obey_regdecls
	jne L359
L361:
	movel a2@(28),sp@-
	jbsr _gen_reg_rtx
	movel d0,a2@(64)
	addqw #4,sp
	cmpb #11,a4@(12)
	jne L362
	movel d0,sp@-
	jbsr _mark_reg_pointer
	addqw #4,sp
L362:
	movel a2@(64),a0
	orb #16,a0@(3)
	jra L354
L359:
	movel a2@(24),a0
	btst #1,a0@(13)
	jeq L364
	clrl d2
	tstl a2@(64)
	jeq L365
	movel a2@(64),a0
	cmpw #37,a0@
	jne L367
	movel a0@(4),a0
	cmpw #34,a0@
	jeq L366
L367:
	jbsr _abort
L366:
	movel a2@(64),a0
	movel a0@(4),d2
L365:
	movel a2@(24),a0
	clrl d0
	moveb a2@(32),d0
	mulsl a0@(16),d0
	addql #7,d0
	jpl L368
	addql #7,d0
L368:
	asrl #3,d0
	movel d0,sp@-
	movel a2@(28),sp@-
	jbsr _assign_stack_local
	movel d0,a0
	movel a0,a2@(64)
	addqw #8,sp
	tstl d2
	jeq L369
	movel d2,sp@-
	movel a0@(4),sp@-
	jbsr _force_operand
	movel d0,sp@-
	movel d2,sp@-
	jbsr _emit_move_insn
	addw #16,sp
L369:
	movel a2@(64),a1
	clrl d0
	movel a2@(8),a0
	cmpb #16,a0@(12)
	jeq L371
	cmpb #19,a0@(12)
	jeq L371
	cmpb #20,a0@(12)
	jne L370
L371:
	moveq #1,d0
L370:
	bfins d0,a1@(3){#4:#1}
	jra L354
L364:
	moveq #1,d3
	movel d3,_frame_pointer_needed
	tstl a3@(16)
	jne L373
	jbsr _do_pending_stack_adjust
	movel _stack_pointer_rtx,sp@-
	jbsr _copy_to_reg
	movel d0,a3@(16)
	movel a3,_stack_block_stack
	addqw #4,sp
L373:
	clrl sp@-
	clrl sp@-
	clrl sp@-
	pea 8:w
	clrl d0
	moveb a2@(32),d0
	movel d0,sp@-
	movel a2@(24),sp@-
	jbsr _convert_units
	addw #12,sp
	movel d0,sp@-
	jbsr _expand_expr
	movel d0,d1
	moveb a2@(32),d0
	andb #15,d0
	addw #16,sp
	jeq L374
	movel d1,sp@-
	jbsr _round_push
	movel d0,d1
	addqw #4,sp
L374:
	movel d1,sp@-
	jbsr _anti_adjust_stack
	movel _stack_pointer_rtx,sp@-
	jbsr _copy_to_reg
	movel d0,sp@-
	movel a2@(28),sp@-
	pea 37:w
	jbsr _gen_rtx
	movel d0,a2@(64)
	addw #20,sp
L354:
	btst #4,a2@(13)
	jeq L375
	movel a2@(64),a0
	orb #16,a0@(3)
L375:
	btst #2,a2@(13)
	jeq L376
	movel a2@(64),a0
	orb #32,a0@(3)
L376:
	tstl _obey_regdecls
	jeq L346
	movel a2@(64),sp@-
	jbsr _use_variable
L346:
	moveml a6@(-20),#0x1c0c
	unlk a6
	rts
	.even
.globl _expand_decl_init
_expand_decl_init:
	link a6,#0
	movel a2,sp@-
	movel a6@(8),a2
	btst #5,a2@(13)
	jne L378
	movel a2@(60),d1
	cmpl _error_mark_node,d1
	jne L380
	movel a2@(8),a0
	clrl d0
	moveb a0@(12),d0
	moveq #5,d1
	cmpl d0,d1
	jeq L382
	moveq #6,d1
	cmpl d0,d1
	jeq L382
	moveq #8,d1
	cmpl d0,d1
	jeq L382
	moveq #11,d1
	cmpl d0,d1
	jne L385
L382:
	clrl sp@-
	clrl sp@-
	movel _integer_zero_node,sp@-
	movel a2@(8),sp@-
	jbsr _convert
	addqw #8,sp
	movel d0,sp@-
	movel a2,sp@-
	jbsr _expand_assignment
	addw #16,sp
	jra L385
L380:
	tstl a2@(60)
	jeq L378
	movel a2@(60),a0
	cmpb #3,a0@(12)
	jeq L378
	movel a2@(20),sp@-
	movel a2@(16),sp@-
	jbsr _emit_line_note
	clrl sp@-
	clrl sp@-
	movel a2@(60),sp@-
	movel a2,sp@-
	jbsr _expand_assignment
L385:
	jbsr _emit_queue
L378:
	movel a6@(-4),a2
	unlk a6
	rts
	.even
.globl _expand_anon_union_decl
_expand_anon_union_decl:
	link a6,#0
	moveml #0x383c,sp@-
	movel a6@(8),a2
	movel a6@(12),d4
	movel a6@(16),a3
	movel _block_stack,a5
	movel d4,sp@-
	movel a2,sp@-
	jbsr _expand_decl
	movel a2@(64),a4
	addqw #8,sp
	tstl a3
	jeq L393
	andl #255,d2
L392:
	movel a3@(20),a2
	movel a3@(16),d3
	cmpb #26,a4@(2)
	jeq L389
	clrl sp@-
	movel a4,sp@-
	movel a2@(8),a0
	moveb a0@(28),d2
	movel d2,sp@-
	pea 35:w
	jbsr _gen_rtx
	addw #16,sp
	jra L390
L389:
	movel a4,d0
L390:
	movel d0,a2@(64)
	tstl d4
	jeq L391
	movel a5@(28),sp@-
	movel d3,sp@-
	movel a2,sp@-
	jbsr _temp_tree_cons
	movel d0,a5@(28)
	addw #12,sp
L391:
	movel a3@(4),a3
	tstl a3
	jne L392
L393:
	moveml a6@(-28),#0x3c1c
	unlk a6
	rts
	.even
_expand_cleanups:
	link a6,#0
	moveml #0x2020,sp@-
	movel a6@(12),d2
	movel a6@(8),a2
	tstl a2
	jeq L403
L402:
	tstl d2
	jeq L399
	cmpl a2@(16),d2
	jeq L397
L399:
	movel a2@(20),a0
	cmpb #3,a0@(12)
	jne L400
	movel d2,sp@-
	movel a0,sp@-
	jbsr _expand_cleanups
	addqw #8,sp
	jra L397
L400:
	clrl sp@-
	clrl sp@-
	movel _const0_rtx,sp@-
	movel a2@(20),sp@-
	jbsr _expand_expr
	addw #16,sp
L397:
	movel a2@(4),a2
	tstl a2
	jne L402
L403:
	moveml a6@(-8),#0x404
	unlk a6
	rts
	.even
_fixup_cleanups:
	link a6,#0
	moveml #0x2038,sp@-
	movel a6@(12),a2
	lea _get_last_insn,a4
	jbsr a4@
	movel d0,a3
	clrl sp@-
	movel a6@(8),sp@-
	jbsr _expand_cleanups
	jbsr a4@
	movel d0,d2
	movel a2@,sp@-
	movel d2,sp@-
	movel a3@(12),sp@-
	jbsr _reorder_insns
	movel d2,a2@
	moveml a6@(-16),#0x1c04
	unlk a6
	rts
	.even
.globl _move_cleanups_up
_move_cleanups_up:
	link a6,#0
	moveml #0x30,sp@-
	movel _block_stack,a2
	movel a2@(4),a3
	movel a3@(28),sp@-
	movel a2@(28),sp@-
	jbsr _chainon
	movel d0,a3@(28)
	clrl a2@(28)
	moveml a6@(-8),#0xc00
	unlk a6
	rts
	.even
.globl _expand_start_case
_expand_start_case:
	link a6,#0
	movel a2,sp@-
	pea 40:w
	jbsr _xmalloc
	movel d0,a2
	movel _case_stack,a2@(4)
	movel _nesting_stack,a2@
	addql #1,_nesting_depth
	movel _nesting_depth,a2@(8)
	addqw #4,sp
	tstl a6@(8)
	jeq L407
	jbsr _gen_label_rtx
	jra L408
L407:
	clrl d0
L408:
	movel d0,a2@(12)
	clrl a2@(20)
	movel a6@(12),a2@(28)
	movel a6@(16),a2@(32)
	clrl a2@(24)
	clrw a2@(36)
	movel a2,_case_stack
	movel a2,_nesting_stack
	jbsr _do_pending_stack_adjust
	jbsr _get_last_insn
	movel d0,a0
	cmpw #18,a0@
	jeq L409
	pea -1:w
	clrl sp@-
	jbsr _emit_note
	addqw #8,sp
L409:
	jbsr _get_last_insn
	movel d0,a2@(16)
	movel a6@(-4),a2
	unlk a6
	rts
	.even
.globl _expand_start_case_dummy
_expand_start_case_dummy:
	link a6,#0
	pea 40:w
	jbsr _xmalloc
	movel d0,a0
	movel _case_stack,a0@(4)
	movel _nesting_stack,a0@
	addql #1,_nesting_depth
	movel _nesting_depth,a0@(8)
	clrl a0@(12)
	clrl a0@(20)
	clrl a0@(16)
	clrl a0@(32)
	clrl a0@(24)
	clrw a0@(36)
	movel a0,_case_stack
	movel a0,_nesting_stack
	unlk a6
	rts
	.even
.globl _expand_end_case_dummy
_expand_end_case_dummy:
	link a6,#0
	movel d2,sp@-
	movel _nesting_stack,a0
	movel a0@(8),d2
L415:
	movel _case_stack,a0
	movel a0@(4),_case_stack
	movel a0@,_nesting_stack
	movel a0@(8),_nesting_depth
	movel a0,sp@-
	jbsr _free
	addqw #4,sp
	cmpl _nesting_depth,d2
	jlt L415
	movel a6@(-4),d2
	unlk a6
	rts
	.even
.globl _pushcase
_pushcase:
	link a6,#0
	moveml #0x3830,sp@-
	movel a6@(8),d2
	movel a6@(12),d4
	tstl _case_stack
	jeq L420
	movel _case_stack,a0
	tstl a0@(16)
	jne L419
L420:
	moveq #1,d0
	jra L418
L419:
	movel _case_stack,a0
	movel a0@(28),a1
	movel a1@(8),d3
	movel a0@(32),d0
	cmpl _error_mark_node,d3
	jeq L434
	tstl d2
	jeq L422
	movel d2,sp@-
	movel d0,sp@-
	jbsr _convert
	movel d0,d2
	addqw #8,sp
L422:
	tstl d2
	jeq L423
	movel d3,sp@-
	movel d2,sp@-
	jbsr _int_fits_type_p
	addqw #8,sp
	tstl d0
	jne L423
	moveq #3,d0
	jra L418
L423:
	tstl d2
	jne L424
	movel _case_stack,a0
	tstl a0@(24)
	jne L435
	movel _case_stack,a0
	movel d4,a0@(24)
	jra L426
L424:
	moveq #20,d1
	addl _case_stack,d1
	movel d1,a3
	tstl a3@
	jeq L428
L430:
	movel d2,sp@-
	movel a3@,a0
	movel a0@(16),sp@-
	jbsr _tree_int_cst_lt
	addqw #8,sp
	tstl d0
	jeq L428
	movel a3@,a3
	addqw #4,a3
	tstl a3@
	jne L430
L428:
	tstl a3@
	jeq L431
	movel a3@,a0
	movel a0@(12),sp@-
	movel d2,sp@-
	jbsr _tree_int_cst_lt
	addqw #8,sp
	tstl d0
	jne L431
L435:
	moveq #2,d0
	jra L418
L431:
	pea 28:w
	jbsr _oballoc
	movel d0,a2
	clrl a2@
	movel a3@,a2@(4)
	movel d2,sp@-
	jbsr _copy_node
	movel d0,a2@(12)
	movel d0,a2@(16)
	movel d4,a2@(24)
	clrl a2@(20)
	movel a2,a3@
	addqw #8,sp
L426:
	movel d4,sp@-
	jbsr _expand_label
L434:
	clrl d0
L418:
	moveml a6@(-20),#0xc1c
	unlk a6
	rts
	.even
.globl _pushcase_range
_pushcase_range:
	link a6,#0
	moveml #0x3e38,sp@-
	movel a6@(8),d2
	movel a6@(12),d3
	movel a6@(16),d6
	tstl _case_stack
	jeq L438
	movel _case_stack,a0
	tstl a0@(16)
	jne L437
L438:
	moveq #1,d0
	jra L436
L437:
	movel _case_stack,a0
	movel a0@(28),a1
	movel a1@(8),d4
	movel a0@(32),d5
	cmpl _error_mark_node,d4
	jeq L453
	tstl d2
	jeq L440
	movel d2,sp@-
	movel d5,sp@-
	jbsr _convert
	movel d0,d2
	addqw #8,sp
L440:
	tstl d3
	jeq L441
	movel d3,sp@-
	movel d5,sp@-
	jbsr _convert
	movel d0,d3
	addqw #8,sp
L441:
	tstl d2
	jeq L442
	movel d4,sp@-
	movel d2,sp@-
	jbsr _int_fits_type_p
	addqw #8,sp
	tstl d0
	jeq L454
L442:
	tstl d3
	jeq L443
	movel d4,sp@-
	movel d3,sp@-
	jbsr _int_fits_type_p
	addqw #8,sp
	tstl d0
	jne L443
L454:
	moveq #3,d0
	jra L436
L443:
	movel d2,sp@-
	movel d3,sp@-
	jbsr _tree_int_cst_lt
	addqw #8,sp
	tstl d0
	jeq L444
	moveq #4,d0
	jra L436
L444:
	movel d3,sp@-
	movel d2,sp@-
	jbsr _tree_int_cst_equal
	addqw #8,sp
	tstl d0
	jeq L445
	movel d6,sp@-
	movel d2,sp@-
	jbsr _pushcase
	jra L436
L445:
	moveq #20,d1
	addl _case_stack,d1
	movel d1,a4
	tstl a4@
	jeq L447
L449:
	movel d2,sp@-
	movel a4@,a0
	movel a0@(16),sp@-
	jbsr _tree_int_cst_lt
	addqw #8,sp
	tstl d0
	jeq L447
	movel a4@,a4
	addqw #4,a4
	tstl a4@
	jne L449
L447:
	tstl a4@
	jeq L450
	movel a4@,a0
	movel a0@(12),sp@-
	movel d3,sp@-
	jbsr _tree_int_cst_lt
	addqw #8,sp
	tstl d0
	jne L450
	moveq #2,d0
	jra L436
L450:
	pea 28:w
	jbsr _oballoc
	movel d0,a2
	clrl a2@
	movel a4@,a2@(4)
	movel d2,sp@-
	lea _copy_node,a3
	jbsr a3@
	movel d0,a2@(12)
	movel d3,sp@-
	jbsr a3@
	movel d0,a2@(16)
	movel d6,a2@(24)
	clrl a2@(20)
	movel a2,a4@
	movel d6,sp@-
	jbsr _expand_label
	moveq #36,d1
	addl _case_stack,d1
	movel d1,a0
	addqw #1,a0@
L453:
	clrl d0
L436:
	moveml a6@(-32),#0x1c7c
	unlk a6
	rts
LC11:
	.ascii "enumerated value `%s' not handled in switch\0"
LC12:
	.ascii "case value `%d' not in enumerated type `%s'\0"
	.even
.globl _check_for_full_enumeration_handling
_check_for_full_enumeration_handling:
	link a6,#0
	moveml #0x38,sp@-
	movel _case_stack,a0
	movel a0@(28),a0
	cmpb #35,a0@(12)
	jeq L455
	movel a0@(20),a4
	movel a4@(8),a0
	movel a0@(16),a3
	tstl a3
	jeq L480
L467:
	movel _case_stack,a0
	movel a0@(20),a2
	tstl a2
	jeq L462
L464:
	movel a3@(20),sp@-
	movel a2@(16),sp@-
	jbsr _tree_int_cst_lt
	addqw #8,sp
	tstl d0
	jeq L462
	movel a2@(4),a2
	tstl a2
	jne L464
L462:
	tstl a2
	jeq L466
	movel a3@(20),sp@-
	movel a2@(12),sp@-
	jbsr _tree_int_cst_equal
	addqw #8,sp
	tstl d0
	jne L460
L466:
	movel a3@(16),a0
	movel a0@(20),sp@-
	pea LC11
	jbsr _warning
	addqw #8,sp
L460:
	movel a3@(4),a3
	tstl a3
	jne L467
L480:
	movel _case_stack,a0
	movel a0@(20),a2
	tstl a2
	jeq L455
L476:
	movel a4@(8),a0
	movel a0@(16),a3
	tstl a3
	jeq L472
L474:
	movel a3@(20),sp@-
	movel a2@(12),sp@-
	jbsr _tree_int_cst_equal
	addqw #8,sp
	tstl d0
	jne L472
	movel a3@(4),a3
	tstl a3
	jne L474
L472:
	tstl a3
	jne L470
	movel a4@(8),a0
	movel a0@(48),a0
	movel a0@(36),a0
	movel a0@(20),sp@-
	movel a2@(12),a0
	movel a0@(16),sp@-
	pea LC12
	jbsr _warning
	addw #12,sp
L470:
	movel a2@(4),a2
	tstl a2
	jne L476
L455:
	moveml a6@(-12),#0x1c00
	unlk a6
	rts
	.even
.globl _expand_end_case
_expand_end_case:
	link a6,#-12
	moveml #0x3f3c,sp@-
	jbsr _gen_label_rtx
	movel d0,d6
	movel _case_stack,a6@(-8)
	movel a6@(-8),a1
	movel a1@(28),a5
	jbsr _do_pending_stack_adjust
	movel a5@(8),d7
	cmpl _error_mark_node,d7
	jeq L482
	movel a6@(-8),a1
	tstl a1@(24)
	jne L483
	movel a6@(8),a1
	movel a1@(8),a0
	cmpb #8,a0@(12)
	jne L483
	tstl _warn_switch
	jeq L483
	jbsr _check_for_full_enumeration_handling
L483:
	movel a6@(-8),a1
	tstl a1@(24)
	jne L484
	clrl sp@-
	clrl sp@-
	pea 40:w
	jbsr _build_decl
	movel a6@(-8),a1
	movel d0,a1@(24)
	movel d0,sp@-
	jbsr _expand_label
	addw #16,sp
L484:
	movel a6@(-8),a1
	movel a1@(24),sp@-
	jbsr _label_rtx
	movel d0,d5
	jbsr _get_last_insn
	movel d0,a6@(-12)
	movel a6@(-8),a1
	movel a1@(20),sp@-
	jbsr _group_case_nodes
	subl a4,a4
	movel a6@(-8),a1
	movel a1@(20),a3
	addqw #8,sp
	tstl a3
	jeq L541
L497:
	movel a3@(12),a0
	cmpb #35,a0@(12)
	jeq L488
	jbsr _abort
L488:
	movel a3@(16),a0
	cmpb #35,a0@(12)
	jeq L489
	jbsr _abort
L489:
	movel a3@(12),sp@-
	movel a5@(8),sp@-
	lea _convert,a2
	jbsr a2@
	movel d0,a3@(12)
	movel a3@(16),sp@-
	movel a5@(8),sp@-
	jbsr a2@
	movel d0,a3@(16)
	addqw #1,a4
	addw #16,sp
	moveq #1,d7
	cmpl a4,d7
	jne L490
	movel a3@(12),d3
	movel d0,d2
	jra L491
L490:
	movel a3@(12),a0
	movel d3,a1
	movel a0@(20),d7
	cmpl a1@(20),d7
	jlt L493
	jne L492
	movel a0@(16),d7
	cmpl a1@(16),d7
	jcc L492
L493:
	movel a3@(12),d3
L492:
	movel a3@(16),a0
	movel d2,a1
	movel a1@(20),d7
	cmpl a0@(20),d7
	jlt L495
	movel a1@(20),d7
	cmpl a0@(20),d7
	jne L491
	movel a1@(16),d7
	cmpl a0@(16),d7
	jcc L491
L495:
	movel a3@(16),d2
L491:
	movel a3@(16),sp@-
	movel a3@(12),sp@-
	jbsr _tree_int_cst_equal
	addqw #8,sp
	tstl d0
	jne L487
	addqw #1,a4
L487:
	movel a3@(4),a3
	tstl a3
	jne L497
L541:
	tstl a4
	jeq L498
	movel d3,sp@-
	movel d2,sp@-
	pea 64:w
	jbsr _combine
	movel d0,a6@(-4)
	addw #12,sp
L498:
	tstl a4
	jeq L500
	movel a5@(8),a0
	tstb a0@(12)
	jne L499
L500:
	clrl sp@-
	clrl sp@-
	movel _const0_rtx,sp@-
	movel a5,sp@-
	jbsr _expand_expr
	jbsr _emit_queue
	movel d5,sp@-
	jbsr _emit_jump
	addw #20,sp
	jra L501
L499:
	movel a6@(-4),a1
	tstl a1@(20)
	jne L503
	moveq #3,d7
	cmpl a4,d7
	jge L503
	lea a4@(a4:l:4),a1
	movel a1,d0
	asll #1,d0
	movel a6@(-4),a1
	cmpl a1@(16),d0
	jcs L503
	cmpb #35,a5@(12)
	jne L502
L503:
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a5,sp@-
	jbsr _expand_expr
	movel d0,a3
	jbsr _emit_queue
	jbsr _do_pending_stack_adjust
	clrl sp@-
	movel a3,sp@-
	jbsr _protect_from_queue
	movel d0,a3
	addw #24,sp
	cmpw #37,a3@
	jne L504
	movel a3,sp@-
	jbsr _copy_to_reg
	movel d0,a3
	addqw #4,sp
L504:
	cmpw #30,a3@
	jeq L506
	cmpb #35,a5@(12)
	jne L505
L506:
	cmpb #35,a5@(12)
	jeq L507
	clrl sp@-
	movel a3@(4),sp@-
	jbsr _build_int_2
	movel d0,a5
	movel a5,sp@-
	movel a5@(8),sp@-
	jbsr _convert
	movel d0,a5
	addw #16,sp
L507:
	movel a6@(-8),a1
	movel a1@(20),a3
	tstl a3
	jeq L509
L512:
	movel a3@(12),sp@-
	movel a5,sp@-
	lea _tree_int_cst_lt,a2
	jbsr a2@
	addqw #8,sp
	tstl d0
	jne L510
	movel a5,sp@-
	movel a3@(16),sp@-
	jbsr a2@
	addqw #8,sp
	tstl d0
	jeq L509
L510:
	movel a3@(4),a3
	tstl a3
	jne L512
L509:
	tstl a3
	jeq L513
	movel a3@(24),sp@-
	jbsr _label_rtx
	movel d0,sp@-
	jbsr _emit_jump
	addqw #8,sp
	jra L501
L513:
	movel d5,sp@-
	jbsr _emit_jump
	addqw #4,sp
	jra L501
L505:
	clrl sp@-
	movel a6@(-8),a1
	pea a1@(20)
	jbsr _balance_case_nodes
	movel a5@(8),a0
	bfextu a0@(14){#4:#1},d7
	movel d7,sp@-
	movel d5,sp@-
	movel a6@(-8),a1
	movel a1@(20),sp@-
	movel a3,sp@-
	jbsr _emit_case_nodes
	movel d5,sp@-
	jbsr _emit_jump_if_reachable
	addw #28,sp
	jra L501
L502:
	movel a5@(8),a0
	cmpb #6,a0@(28)
	jne L517
	movel d3,sp@-
	movel a5,sp@-
	movel a0,sp@-
	pea 64:w
	jbsr _build
	movel d0,a5
	movel _integer_zero_node,d3
	addw #16,sp
L517:
	movel a5@(8),a0
	cmpb #4,a0@(28)
	jeq L518
	movel a5,sp@-
	clrl sp@-
	movel _mode_size+16,d7
	asll #3,d7
	movel d7,sp@-
	jbsr _type_for_size
	addqw #8,sp
	movel d0,sp@-
	jbsr _convert
	movel d0,a5
	addqw #8,sp
L518:
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a5,sp@-
	lea _expand_expr,a2
	jbsr a2@
	movel d0,a3
	jbsr _emit_queue
	clrl sp@-
	movel a3,sp@-
	jbsr _protect_from_queue
	movel d0,a3
	jbsr _do_pending_stack_adjust
	movel d5,sp@-
	movel d6,sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a6@(-4),sp@-
	jbsr a2@
	addw #16,sp
	movel d0,sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel d3,sp@-
	jbsr a2@
	addw #16,sp
	movel d0,sp@-
	movel a3,sp@-
	jbsr _gen_casesi
	movel d0,sp@-
	jbsr _emit_jump_insn
	movel a6@(-4),a1
	movel a1@(16),d4
	addql #1,d4
	movel d4,d0
	asll #2,d0
	addw #48,sp
	movel d0,d1
	addql #1,d1
	moveq #-2,d7
	andl d7,d1
	subl d1,sp
	movel sp,a2
	movel d0,sp@-
	clrl sp@-
	movel a2,sp@-
	jbsr _memset
	movel a6@(-8),a1
	movel a1@(20),a3
	addw #12,sp
	tstl a3
	jeq L539
L525:
	movel a3@(12),a0
	movel d3,a1
	movel a0@(16),d2
	subl a1@(16),d2
	jra L522
L524:
	movel a3@(24),sp@-
	jbsr _label_rtx
	movel d0,sp@-
	pea 4:w
	pea 38:w
	jbsr _gen_rtx
	movel d0,a2@(d2:l:4)
	addql #1,d2
	addw #16,sp
L522:
	movel d3,a1
	movel d2,d0
	addl a1@(16),d0
	movel a3@(16),a0
	cmpl a0@(16),d0
	jle L524
	movel a3@(4),a3
	tstl a3
	jne L525
L539:
	clrl d2
	cmpl d2,d4
	jle L538
L530:
	tstl a2@(d2:l:4)
	jne L528
	movel d5,sp@-
	pea 4:w
	pea 38:w
	jbsr _gen_rtx
	movel d0,a2@(d2:l:4)
	addw #12,sp
L528:
	addql #1,d2
	cmpl d2,d4
	jgt L530
L538:
	movel d6,sp@-
	jbsr _emit_label
	movel a2,sp@-
	movel d4,sp@-
	jbsr _gen_rtvec_v
	movel d0,sp@-
	movel d6,sp@-
	pea 4:w
	pea 38:w
	lea _gen_rtx,a2
	jbsr a2@
	addw #12,sp
	movel d0,sp@-
	pea 2:w
	pea 24:w
	jbsr a2@
	movel d0,sp@-
	jbsr _emit_jump_insn
	addw #32,sp
	jbsr _emit_barrier
L501:
	movel a6@(-8),a1
	movel a1@(16),sp@-
	jbsr _get_last_insn
	movel d0,sp@-
	movel a6@(-12),a1
	movel a1@(12),sp@-
	jbsr _reorder_insns
	addw #12,sp
L482:
	movel a6@(-8),a1
	tstl a1@(12)
	jeq L531
	movel a1@(12),sp@-
	jbsr _emit_label
	addqw #4,sp
L531:
	movel _nesting_stack,a0
	movel a0@(8),d2
L535:
	movel _case_stack,a0
	movel a0@(4),_case_stack
	movel a0@,_nesting_stack
	movel a0@(8),_nesting_depth
	movel a0,sp@-
	jbsr _free
	addqw #4,sp
	cmpl _nesting_depth,d2
	jlt L535
	moveml a6@(-52),#0x3cfc
	unlk a6
	rts
	.even
_do_jump_if_equal:
	link a6,#0
	movel d2,sp@-
	movel a6@(8),a1
	movel a6@(12),a0
	movel a6@(16),d2
	cmpw #30,a1@
	jne L543
	cmpw #30,a0@
	jne L543
	movel a1@(4),d1
	cmpl a0@(4),d1
	jne L545
	movel d2,sp@-
	jbsr _emit_jump
	jra L545
L543:
	clrl sp@-
	movel a6@(20),sp@-
	clrl sp@-
	movel a0,sp@-
	movel a1,sp@-
	jbsr _emit_cmp_insn
	movel d2,sp@-
	jbsr _gen_beq
	movel d0,sp@-
	jbsr _emit_jump_insn
L545:
	movel a6@(-4),d2
	unlk a6
	rts
	.even
_group_case_nodes:
	link a6,#0
	moveml #0x2030,sp@-
	movel a6@(8),a3
	tstl a3
	jeq L553
L552:
	movel a3@(24),sp@-
	jbsr _label_rtx
	movel d0,sp@-
	jbsr _next_real_insn
	movel d0,d2
	movel a3,a2
	addqw #8,sp
	jra L549
L551:
	movel a2@(24),sp@-
	jbsr _label_rtx
	movel d0,sp@-
	jbsr _next_real_insn
	addqw #8,sp
	cmpl d0,d2
	jne L550
	clrl sp@-
	pea 1:w
	jbsr _build_int_2
	movel d0,sp@-
	movel a3@(16),sp@-
	pea 63:w
	jbsr _combine
	movel d0,sp@-
	movel a2@(12),sp@-
	jbsr _tree_int_cst_equal
	addw #28,sp
	tstl d0
	jeq L550
	movel a2@(16),a3@(16)
L549:
	movel a2@(4),a2
	tstl a2
	jne L551
L550:
	movel a2,a3@(4)
	movel a2,a3
	tstl a3
	jne L552
L553:
	moveml a6@(-12),#0xc04
	unlk a6
	rts
	.even
_balance_case_nodes:
	link a6,#0
	moveml #0x383c,sp@-
	movel a6@(8),a5
	movel a6@(12),d4
	movel a5@,a3
	tstl a3
	jeq L555
	clrl d2
	subl a4,a4
	tstl a3
	jeq L574
L559:
	movel a3@(16),sp@-
	movel a3@(12),sp@-
	jbsr _tree_int_cst_equal
	addqw #8,sp
	tstl d0
	jne L558
	addqw #1,a4
L558:
	addql #1,d2
	movel a3@(4),a3
	tstl a3
	jne L559
L574:
	moveq #2,d1
	cmpl d2,d1
	jge L560
	movel a5,a2
	movel a5@,d3
	moveq #3,d1
	cmpl d2,d1
	jne L561
	movel a2@,a2
	addqw #4,a2
	jra L562
L561:
	lea a4@(1,d2:l),a1
	movel a1,d2
	jge L563
	addql #1,d2
L563:
	asrl #1,d2
L564:
	movel a2@,a0
	movel a0@(16),sp@-
	movel a0@(12),sp@-
	jbsr _tree_int_cst_equal
	addqw #8,sp
	tstl d0
	jne L566
	subql #1,d2
L566:
	subql #1,d2
	tstl d2
	jle L562
	movel a2@,a2
	addqw #4,a2
	jra L564
L562:
	movel a2@,a3
	movel a3,a5@
	clrl a2@
	movel d4,a3@(8)
	movel d3,a3@
	movel a3,sp@-
	movel a3,sp@-
	lea _balance_case_nodes,a2
	jbsr a2@
	movel a3,sp@-
	pea a3@(4)
	jbsr a2@
	jra L555
L560:
	movel a5@,a3
	movel d4,a3@(8)
	tstl a3@(4)
	jeq L555
L572:
	movel a3@(4),a0
	movel a3,a0@(8)
	movel a3@(4),a3
	tstl a3@(4)
	jne L572
L555:
	moveml a6@(-28),#0x3c1c
	unlk a6
	rts
	.even
_node_has_low_bound:
	link a6,#0
	moveml #0x2030,sp@-
	movel a6@(8),a3
	tstl a3@
	jeq L576
	clrl sp@-
	pea 1:w
	jbsr _build_int_2
	movel d0,sp@-
	movel a3@(12),sp@-
	pea 64:w
	jbsr _combine
	movel d0,d2
	movel a3@(12),sp@-
	movel d2,sp@-
	jbsr _tree_int_cst_lt
	addw #28,sp
	tstl d0
	jeq L576
	movel a3@(8),a2
	tstl a2
	jeq L576
L583:
	movel a2@(16),sp@-
	movel d2,sp@-
	jbsr _tree_int_cst_equal
	addqw #8,sp
	tstl d0
	jeq L581
	moveq #1,d0
	jra L575
L581:
	tstl a3@
	jne L576
	movel a2@(8),a2
	tstl a2
	jne L583
L576:
	clrl d0
L575:
	moveml a6@(-12),#0xc04
	unlk a6
	rts
	.even
_node_has_high_bound:
	link a6,#0
	moveml #0x2030,sp@-
	movel a6@(8),a3
	tstl a3@(4)
	jne L586
	clrl sp@-
	pea 1:w
	jbsr _build_int_2
	movel d0,sp@-
	movel a3@(16),sp@-
	pea 63:w
	jbsr _combine
	movel d0,d2
	movel d2,sp@-
	movel a3@(16),sp@-
	jbsr _tree_int_cst_lt
	addw #28,sp
	tstl d0
	jeq L586
	movel a3@(8),a2
	tstl a2
	jeq L586
L593:
	movel a2@(12),sp@-
	movel d2,sp@-
	jbsr _tree_int_cst_equal
	addqw #8,sp
	tstl d0
	jeq L591
	moveq #1,d0
	jra L585
L591:
	tstl a3@(4)
	jne L586
	movel a2@(8),a2
	tstl a2
	jne L593
L586:
	clrl d0
L585:
	moveml a6@(-12),#0xc04
	unlk a6
	rts
	.even
_node_is_bounded:
	link a6,#0
	moveml #0x2020,sp@-
	movel a6@(8),a2
	tstl a2@
	jne L597
	tstl a2@(4)
	jeq L596
L597:
	clrl d0
	jra L595
L596:
	clrl d2
	movel a2,sp@-
	jbsr _node_has_low_bound
	addqw #4,sp
	tstl d0
	jeq L598
	movel a2,sp@-
	jbsr _node_has_high_bound
	tstl d0
	jeq L598
	moveq #1,d2
L598:
	movel d2,d0
L595:
	moveml a6@(-8),#0x404
	unlk a6
	rts
	.even
_emit_jump_if_reachable:
	link a6,#0
	jbsr _get_last_insn
	movel d0,a0
	cmpw #16,a0@
	jeq L600
	movel a6@(8),sp@-
	jbsr _emit_jump
L600:
	unlk a6
	rts
	.even
_emit_case_nodes:
	link a6,#0
	moveml #0x3c3c,sp@-
	movel a6@(8),d2
	movel a6@(12),a2
	movel a6@(16),d4
	movel a6@(20),d3
	jeq L602
	lea _gen_bgtu,a3
	jra L603
L602:
	lea _gen_bgt,a3
L603:
	tstl d3
	jeq L604
	lea _gen_bgeu,a4
	jra L605
L604:
	lea _gen_bge,a4
L605:
	tstl d3
	jeq L606
	lea _gen_bltu,a5
	jra L607
L606:
	lea _gen_blt,a5
L607:
	tstl d3
	jeq L608
	movel #_gen_bleu,d5
	jra L609
L608:
	movel #_gen_ble,d5
L609:
	tstl a2@(20)
	jeq L610
	movel d4,sp@-
	jbsr _emit_jump_if_reachable
	movel a2@(20),sp@-
	jbsr _expand_label
	addqw #8,sp
L610:
	movel a2@(16),sp@-
	movel a2@(12),sp@-
	jbsr _tree_int_cst_equal
	addqw #8,sp
	tstl d0
	jeq L611
	movel d3,sp@-
	movel a2@(24),sp@-
	jbsr _label_rtx
	addqw #4,sp
	movel d0,sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2@(12),sp@-
	lea _expand_expr,a4
	jbsr a4@
	addw #16,sp
	movel d0,sp@-
	movel d2,sp@-
	jbsr _do_jump_if_equal
	addw #16,sp
	tstl a2@(4)
	jeq L612
	tstl a2@
	jeq L613
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2@(16),sp@-
	jbsr a4@
	addw #16,sp
	movel d0,sp@-
	movel d2,sp@-
	jbsr _emit_cmp_insn
	movel a2@(4),sp@-
	lea _node_is_bounded,a4
	jbsr a4@
	addw #24,sp
	tstl d0
	jeq L614
	movel a2@(4),a0
	movel a0@(24),sp@-
	jbsr _label_rtx
	movel d0,sp@-
	jbsr a3@
	movel d0,sp@-
	jbsr _emit_jump_insn
	movel a2@,sp@-
	jbsr a4@
	addw #16,sp
	tstl d0
	jeq L643
	movel a2@,a0
	movel a0@(24),sp@-
	jbsr _label_rtx
	jra L648
L614:
	movel a2@,sp@-
	jbsr _node_is_bounded
	addqw #4,sp
	tstl d0
	jeq L618
	movel a2@,a0
	movel a0@(24),sp@-
	jbsr _label_rtx
	movel d0,sp@-
	jbsr a5@
	movel d0,sp@-
	jbsr _emit_jump_insn
	addw #12,sp
	jra L619
L618:
	clrl sp@-
	clrl sp@-
	pea 40:w
	jbsr _build_decl
	movel a2@(4),a0
	movel d0,a0@(20)
	movel a2@(4),a0
	movel a0@(20),sp@-
	jbsr _label_rtx
	movel d0,sp@-
	jbsr a3@
	movel d0,sp@-
	jbsr _emit_jump_insn
	movel d3,sp@-
	movel d4,sp@-
	movel a2@,sp@-
	movel d2,sp@-
	jbsr _emit_case_nodes
	addw #40,sp
L619:
	movel d3,sp@-
	movel d4,sp@-
	movel a2@(4),sp@-
	jra L649
L613:
	movel a2@(4),a0
	tstl a0@(4)
	jeq L621
	movel a2,sp@-
	jbsr _node_has_low_bound
	addqw #4,sp
	tstl d0
	jne L621
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2@(16),sp@-
	jbsr _expand_expr
	addw #16,sp
	movel d0,sp@-
	movel d2,sp@-
	jbsr _emit_cmp_insn
	movel d4,sp@-
	jbsr a5@
	movel d0,sp@-
	jbsr _emit_jump_insn
	addw #28,sp
L621:
	movel a2@(4),sp@-
	jbsr _node_is_bounded
	addqw #4,sp
	tstl d0
	jeq L622
	movel a2@(4),a0
	movel a0@(24),sp@-
	jbsr _label_rtx
	jra L648
L622:
	movel d3,sp@-
	movel d4,sp@-
	movel a2@(4),sp@-
	jra L649
L612:
	tstl a2@
	jeq L628
	movel a2@,sp@-
	jbsr _node_is_bounded
	addqw #4,sp
	tstl d0
	jeq L643
	movel a2@,a0
	movel a0@(24),sp@-
	jbsr _label_rtx
	jra L648
L611:
	tstl a2@(4)
	jeq L629
	tstl a2@
	jeq L630
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2@(16),sp@-
	jbsr _expand_expr
	addw #16,sp
	movel d0,sp@-
	movel d2,sp@-
	jbsr _emit_cmp_insn
	movel a2@(4),sp@-
	jbsr _node_is_bounded
	addw #24,sp
	tstl d0
	jeq L631
	movel a2@(4),a0
	movel a0@(24),sp@-
	jbsr _label_rtx
	movel d0,sp@-
	jbsr a3@
	movel d0,sp@-
	jbsr _emit_jump_insn
	addw #12,sp
	jra L632
L631:
	clrl sp@-
	clrl sp@-
	pea 40:w
	jbsr _build_decl
	movel a2@(4),a0
	movel d0,a0@(20)
	movel a2@(4),a0
	movel a0@(20),sp@-
	jbsr _label_rtx
	movel d0,sp@-
	jbsr a3@
	movel d0,sp@-
	jbsr _emit_jump_insn
	addw #24,sp
L632:
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2@(12),sp@-
	jbsr _expand_expr
	addw #16,sp
	movel d0,sp@-
	movel d2,sp@-
	jbsr _emit_cmp_insn
	movel a2@(24),sp@-
	lea _label_rtx,a3
	jbsr a3@
	movel d0,sp@-
	jbsr a4@
	movel d0,sp@-
	jbsr _emit_jump_insn
	addw #32,sp
	movel a2@,sp@-
	jbsr _node_is_bounded
	addqw #4,sp
	tstl d0
	jeq L633
	movel a2@,a0
	movel a0@(24),sp@-
	jbsr a3@
	movel d0,sp@-
	jbsr _emit_jump
	addqw #8,sp
	jra L634
L633:
	movel d3,sp@-
	movel d4,sp@-
	movel a2@,sp@-
	movel d2,sp@-
	jbsr _emit_case_nodes
	addw #16,sp
L634:
	movel a2@(4),a0
	tstl a0@(20)
	jeq L628
	movel d3,sp@-
	movel d4,sp@-
	movel a0,sp@-
	jra L649
L630:
	movel a2,sp@-
	jbsr _node_has_low_bound
	addqw #4,sp
	tstl d0
	jne L637
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2@(12),sp@-
	jbsr _expand_expr
	addw #16,sp
	movel d0,sp@-
	movel d2,sp@-
	jbsr _emit_cmp_insn
	movel d4,sp@-
	jbsr a5@
	movel d0,sp@-
	jbsr _emit_jump_insn
	addw #28,sp
L637:
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2@(16),sp@-
	jbsr _expand_expr
	addw #16,sp
	movel d0,sp@-
	movel d2,sp@-
	jbsr _emit_cmp_insn
	movel a2@(24),sp@-
	lea _label_rtx,a3
	jbsr a3@
	movel d0,sp@-
	movel d5,a1
	jbsr a1@
	movel d0,sp@-
	jbsr _emit_jump_insn
	addw #32,sp
	movel a2@(4),sp@-
	jbsr _node_is_bounded
	addqw #4,sp
	tstl d0
	jeq L638
	movel a2@(4),a0
	jra L650
L638:
	movel d3,sp@-
	movel d4,sp@-
	movel a2@(4),sp@-
	jra L649
L629:
	tstl a2@
	jeq L641
	movel a2,sp@-
	jbsr _node_has_high_bound
	addqw #4,sp
	tstl d0
	jne L642
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2@(16),sp@-
	jbsr _expand_expr
	addw #16,sp
	movel d0,sp@-
	movel d2,sp@-
	jbsr _emit_cmp_insn
	movel d4,sp@-
	jbsr a3@
	movel d0,sp@-
	jbsr _emit_jump_insn
	addw #28,sp
L642:
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2@(12),sp@-
	jbsr _expand_expr
	addw #16,sp
	movel d0,sp@-
	movel d2,sp@-
	jbsr _emit_cmp_insn
	movel a2@(24),sp@-
	lea _label_rtx,a3
	jbsr a3@
	movel d0,sp@-
	jbsr a4@
	movel d0,sp@-
	jbsr _emit_jump_insn
	addw #32,sp
	movel a2@,sp@-
	jbsr _node_is_bounded
	addqw #4,sp
	tstl d0
	jeq L643
	movel a2@,a0
L650:
	movel a0@(24),sp@-
	jbsr a3@
L648:
	movel d0,sp@-
	jbsr _emit_jump
	jra L628
L643:
	movel d3,sp@-
	movel d4,sp@-
	movel a2@,sp@-
L649:
	movel d2,sp@-
	jbsr _emit_case_nodes
	jra L628
L641:
	movel a2,sp@-
	jbsr _node_has_high_bound
	addqw #4,sp
	tstl d0
	jne L646
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2@(16),sp@-
	jbsr _expand_expr
	addw #16,sp
	movel d0,sp@-
	movel d2,sp@-
	jbsr _emit_cmp_insn
	movel d4,sp@-
	jbsr a3@
	movel d0,sp@-
	jbsr _emit_jump_insn
	addw #28,sp
L646:
	movel a2,sp@-
	jbsr _node_has_low_bound
	addqw #4,sp
	tstl d0
	jne L628
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2@(12),sp@-
	jbsr _expand_expr
	addw #16,sp
	movel d0,sp@-
	movel d2,sp@-
	jbsr _emit_cmp_insn
	movel a2@(24),sp@-
	jbsr _label_rtx
	movel d0,sp@-
	jbsr a4@
	movel d0,sp@-
	jbsr _emit_jump_insn
L628:
	moveml a6@(-32),#0x3c3c
	unlk a6
	rts
	.even
.globl _get_frame_size
_get_frame_size:
	link a6,#0
	movel _frame_offset,d0
	negl d0
	unlk a6
	rts
	.even
.globl _assign_stack_local
_assign_stack_local:
	link a6,#0
	moveml #0x3820,sp@-
	movel a6@(8),d3
	movel a6@(12),d0
	clrl d1
	moveq #1,d4
	movel d4,_frame_pointer_needed
	addql #1,d0
	jpl L653
	addql #1,d0
L653:
	moveq #-2,d4
	andl d4,d0
	moveq #26,d4
	cmpl d3,d4
	jeq L654
	lea _mode_size,a0
	movel d0,d1
	subl a0@(d3:l:4),d1
L654:
	subl d0,_frame_offset
	addl _frame_offset,d1
	movel d1,sp@-
	clrl sp@-
	pea 30:w
	lea _gen_rtx,a2
	jbsr a2@
	movel d0,sp@-
	movel _frame_pointer_rtx,sp@-
	pea 4:w
	pea 44:w
	jbsr a2@
	movel d0,d2
	movel d2,sp@-
	movel d3,sp@-
	jbsr _memory_address_p
	addw #36,sp
	tstl d0
	jne L655
	moveq #1,d4
	movel d4,_invalid_stack_slot
L655:
	movel d2,sp@-
	movel d3,sp@-
	pea 37:w
	lea _gen_rtx,a2
	jbsr a2@
	movel d0,d2
	movel _stack_slot_list,sp@-
	movel d2,sp@-
	clrl sp@-
	pea 2:w
	jbsr a2@
	movel d0,_stack_slot_list
	movel d2,d0
	moveml a6@(-16),#0x41c
	unlk a6
	rts
	.even
.globl _put_var_into_stack
_put_var_into_stack:
	link a6,#0
	moveml #0x30,sp@-
	movel a6@(8),a3
	movel a3@(64),a2
	tstl a2
	jeq L656
	cmpw #34,a2@
	jne L656
	movel a2,sp@-
	jbsr _parm_stack_loc
	movel d0,a0
	addqw #4,sp
	tstl a0
	jne L659
	clrl d0
	moveb a2@(2),d0
	lea _mode_size,a0
	movel a0@(d0:l:4),sp@-
	movel d0,sp@-
	jbsr _assign_stack_local
	movel d0,a0
	addqw #8,sp
L659:
	movel a0@(4),a2@(4)
	andb #239,a2@(3)
	movew #37,a2@
	clrl d0
	movel a3@(8),a0
	cmpb #16,a0@(12)
	jeq L661
	cmpb #19,a0@(12)
	jeq L661
	cmpb #20,a0@(12)
	jne L660
L661:
	moveq #1,d0
L660:
	bfins d0,a2@(3){#4:#1}
	movel a2,sp@-
	jbsr _fixup_var_refs
L656:
	moveml a6@(-8),#0xc00
	unlk a6
	rts
	.even
_fixup_var_refs:
	link a6,#0
	moveml #0x3020,sp@-
	movel a6@(8),d3
	movel _sequence_stack,a2
	tstl a2
	seq d0
	moveq #1,d1
	andl d1,d0
	movel d0,sp@-
	jbsr _get_insns
	movel d0,sp@-
	movel d3,sp@-
	jbsr _fixup_var_refs_insns
	addw #12,sp
	tstl a2
	jeq L673
L666:
	movel a2@(4),sp@-
	jbsr _push_to_sequence
	movel a2@(8),a0
	addqw #4,sp
	tstl a0@(8)
	seq d0
	moveq #1,d1
	andl d1,d0
	movel d0,sp@-
	movel a2@(4),sp@-
	movel d3,sp@-
	jbsr _fixup_var_refs_insns
	jbsr _end_sequence
	addw #12,sp
	movel a2@(8),a0
	movel a0@(8),a2
	tstl a2
	jne L666
L673:
	movel _rtl_expr_chain,a2
	tstl a2
	jeq L672
L671:
	movel a2@(20),a0
	movel a0@(20),d2
	cmpl _const0_rtx,d2
	jeq L669
	tstl d2
	jeq L669
	movel d2,sp@-
	jbsr _push_to_sequence
	clrl sp@-
	movel d2,sp@-
	movel d3,sp@-
	jbsr _fixup_var_refs_insns
	jbsr _end_sequence
	addw #16,sp
L669:
	movel a2@(4),a2
	tstl a2
	jne L671
L672:
	moveml a6@(-12),#0x40c
	unlk a6
	rts
	.even
_fixup_var_refs_insns:
	link a6,#0
	moveml #0x3038,sp@-
	movel a6@(8),d2
	movel a6@(12),a3
	movel a6@(16),d3
	tstl a3
	jeq L689
L687:
	movel a3@(12),a4
	cmpw #13,a3@
	jeq L678
	cmpw #15,a3@
	jeq L678
	cmpw #14,a3@
	jne L677
L678:
	tstl d3
	jeq L679
	movel a3@(16),a0
	cmpw #25,a0@
	jne L679
	cmpl a0@(4),d2
	jne L679
	movel d2,sp@-
	movel a0@(8),sp@-
	jbsr _rtx_equal_p
	addqw #8,sp
	tstl d0
	jeq L679
	movel a3,sp@-
	jbsr _delete_insn
	movel d0,a4
	addqw #4,sp
	cmpl _last_parm_insn,a3
	jne L681
	movel a4@(8),_last_parm_insn
	jra L681
L679:
	movel a3,sp@-
	movel a3@(16),sp@-
	movel d2,sp@-
	jbsr _fixup_var_refs_1
	addw #12,sp
L681:
	movel a3@(28),a2
	tstl a2
	jeq L677
L686:
	cmpw #3,a2@
	jeq L684
	movel a3,sp@-
	movel a2@(4),sp@-
	jbsr _walk_fixup_memory_subreg
	movel d0,a2@(4)
	addqw #8,sp
L684:
	movel a2@(8),a2
	tstl a2
	jne L686
L677:
	movel a4,a3
	tstl a3
	jne L687
L689:
	moveml a6@(-20),#0x1c0c
	unlk a6
	rts
	.even
_fixup_var_refs_1:
	link a6,#-4
	moveml #0x3e3c,sp@-
	movel a6@(8),d5
	movel a6@(12),a3
	movel a6@(16),d4
	clrl d6
	movew a3@,d6
	moveq #-25,d0
	addl d6,d0
	moveq #65,d1
	cmpl d1,d0
	jhi L691
LI739:
	movew pc@(L739-LI739-2:b,d0:l:2),d1
	jmp pc@(2,d1:w)
L739:
	.word L710-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L751-L739
	.word L751-L739
	.word L751-L739
	.word L751-L739
	.word L751-L739
	.word L704-L739
	.word L691-L739
	.word L692-L739
	.word L751-L739
	.word L751-L739
	.word L751-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L691-L739
	.word L704-L739
	.word L704-L739
L692:
	cmpl d5,a3
	jne L691
	movel d4,sp@-
	movel a3,sp@-
	jbsr _fixup_stack_1
	movel d0,a3
	clrl d0
	moveb a3@(2),d0
	movel d0,sp@-
	jbsr _gen_reg_rtx
	movel d0,a2
	jra L709
L704:
	movel a3,a2
L705:
	cmpw #35,a2@
	jeq L707
	cmpw #89,a2@
	jeq L707
	cmpw #90,a2@
	jne L706
L707:
	movel a2@(4),a2
	jra L705
L706:
	cmpl a2,d5
	jne L691
	movel d4,sp@-
	movel a3,sp@-
	jbsr _fixup_stack_1
	movel d0,a3
	clrl d0
	moveb a3@(2),d0
	movel d0,sp@-
	jbsr _gen_reg_rtx
	movel d0,a2
	addw #12,sp
	cmpw #35,a3@
	jne L709
	movel d4,sp@-
	movel a3,sp@-
	jbsr _fixup_memory_subreg
	movel d0,a3
	addqw #8,sp
L709:
	movel d4,sp@-
	movel a3,sp@-
	movel a2,sp@-
	jbsr _gen_move_insn
	addqw #8,sp
	movel d0,sp@-
	jbsr _emit_insn_before
	movel a2,d0
	jra L690
L710:
	movel a3@(4),a0
	cmpw #89,a0@
	jeq L712
	cmpw #90,a0@
	jne L711
L712:
	clrl sp@-
	movel d4,sp@-
	movel a3,sp@-
	jbsr _optimize_bit_field
	addw #12,sp
L711:
	movel a3@(8),a0
	cmpw #89,a0@
	jeq L714
	cmpw #90,a0@
	jne L713
L714:
	clrl sp@-
	movel d4,sp@-
	movel a3,sp@-
	jbsr _optimize_bit_field
	addw #12,sp
L713:
	movel a3@(4),a2
	movel a3@(8),a5
	movel a2,a4
	movel a5,a6@(-4)
L715:
	cmpw #35,a2@
	jeq L717
	cmpw #36,a2@
	jeq L717
	cmpw #89,a2@
	jeq L717
	cmpw #90,a2@
	jne L716
L717:
	movel a2@(4),a2
	jra L715
L716:
L718:
	cmpw #35,a5@
	jeq L720
	cmpw #89,a5@
	jeq L720
	cmpw #90,a5@
	jne L719
L720:
	movel a5@(4),a5
	jra L718
L719:
	cmpl a5,d5
	jeq L721
	cmpl a2,d5
	jne L691
L721:
	cmpw #89,a4@
	jeq L723
	cmpw #90,a4@
	jne L722
L723:
	movel a4@(4),a0
	cmpw #35,a0@
	jne L722
	cmpl a0@(4),d5
	jne L722
	movel d4,sp@-
	movel a0,sp@-
	jbsr _fixup_memory_subreg
	movel d0,a4@(4)
	addqw #8,sp
L722:
	movel a6@(-4),a1
	cmpw #89,a1@
	jeq L725
	cmpw #90,a1@
	jne L724
L725:
	movel a6@(-4),a1
	movel a1@(4),a0
	cmpw #35,a0@
	jne L724
	cmpl a0@(4),d5
	jne L724
	movel d4,sp@-
	movel a0,sp@-
	jbsr _fixup_memory_subreg
	movel a6@(-4),a1
	movel d0,a1@(4)
	addqw #8,sp
L724:
	cmpw #89,a4@
	jeq L727
	cmpw #90,a4@
	jne L726
L727:
	movel a4@(4),a0
	cmpw #37,a0@
	jne L726
	cmpb #1,a0@(2)
	jeq L726
	movel a0,sp@-
	jbsr _copy_rtx
	movel d0,a0
	movel a0,a4@(4)
	moveb #1,a0@(2)
	addqw #4,sp
L726:
	movel a6@(-4),a1
	cmpw #89,a1@
	jeq L729
	cmpw #90,a1@
	jne L728
L729:
	movel a6@(-4),a1
	movel a1@(4),a0
	cmpw #37,a0@
	jne L728
	cmpb #1,a0@(2)
	jeq L728
	movel a0,sp@-
	jbsr _copy_rtx
	movel d0,a0
	movel a6@(-4),a1
	movel a0,a1@(4)
	moveb #1,a0@(2)
	addqw #4,sp
L728:
	cmpl a2,d5
	jne L730
	movel a3@(4),a0
	cmpw #36,a0@
	jne L730
	movel a0@(4),a3@(4)
L730:
	movel a3@(8),a4
	cmpw #34,a4@
	jeq L732
	movel a3@(4),a0
	cmpw #34,a0@
	jeq L732
	cmpw #35,a4@
	jne L733
	movel a4@(4),a0
	cmpw #34,a0@
	jeq L732
L733:
	movel a3@(4),a0
	cmpw #35,a0@
	jne L731
	movel a0@(4),a0
	cmpw #34,a0@
	jne L731
L732:
	cmpl a5,d5
	jne L734
	movel a3@(8),a0
	cmpw #35,a0@
	jne L734
	movel d4,sp@-
	movel a0,sp@-
	jbsr _fixup_memory_subreg
	movel d0,a3@(8)
	addqw #8,sp
L734:
	cmpl a2,d5
	jne L735
	movel a3@(4),a0
	cmpw #35,a0@
	jne L735
	movel d4,sp@-
	movel a0,sp@-
	jbsr _fixup_memory_subreg
	movel d0,a3@(4)
	addqw #8,sp
L735:
	movel d4,sp@-
	movel a3,sp@-
	jbsr _fixup_stack_1
	jra L690
L731:
	cmpl a2,d5
	jne L691
	movel a3@(4),a2
	cmpw #36,a2@
	jne L737
	movel a2@(4),a2
L737:
	cmpw #35,a2@
	jne L738
	movel d4,sp@-
	movel a2,sp@-
	jbsr _fixup_memory_subreg
	movel d0,a2
	addqw #8,sp
L738:
	movel d4,sp@-
	movel a2,sp@-
	jbsr _fixup_stack_1
	movel d0,d3
	clrl d0
	moveb a2@(2),d0
	movel d0,sp@-
	jbsr _gen_reg_rtx
	movel d0,d2
	movel d4,sp@-
	movel d2,sp@-
	movel d3,sp@-
	jbsr _gen_move_insn
	addqw #8,sp
	movel d0,sp@-
	jbsr _emit_insn_after
	movel d2,a3@(4)
	addw #20,sp
L691:
	lea _rtx_format,a0
	movel a0@(d6:l:4),a2
	lea _rtx_length,a0
	movel a0@(d6:l:4),d3
	jra L743
L750:
	cmpb #101,a2@(d3:l)
	jne L744
	movel d4,sp@-
	movel a3@(4,d3:l:4),sp@-
	movel d5,sp@-
	jbsr _fixup_var_refs_1
	movel d0,a3@(4,d3:l:4)
	addw #12,sp
L744:
	cmpb #69,a2@(d3:l)
	jne L743
	clrl d2
	jra L746
L749:
	movel d4,sp@-
	movel a3@(4,d3:l:4),a0
	movel a0@(4,d2:l:4),sp@-
	movel d5,sp@-
	jbsr _fixup_var_refs_1
	movel a3@(4,d3:l:4),a0
	movel d0,a0@(4,d2:l:4)
	addw #12,sp
	addql #1,d2
L746:
	movel a3@(4,d3:l:4),a0
	cmpl a0@,d2
	jcs L749
L743:
	subql #1,d3
	jpl L750
L751:
	movel a3,d0
L690:
	moveml a6@(-40),#0x3c7c
	unlk a6
	rts
	.even
_fixup_memory_subreg:
	link a6,#0
	moveml #0x3c20,sp@-
	movel a6@(8),a2
	movel a2@(8),d1
	asll #2,d1
	movel a2@(4),a0
	movel a0@(4),d4
	clrl d3
	moveb a2@(2),d3
	clrl d0
	moveb a0@(2),d0
	lea _mode_size,a0
	moveq #4,d5
	cmpl a0@(d0:l:4),d5
	jge L753
	moveq #4,d2
	jra L754
L753:
	movel a2@(4),a0
	clrl d0
	moveb a0@(2),d0
	lea _mode_size,a0
	movel a0@(d0:l:4),d2
L754:
	lea _mode_size,a0
	moveq #4,d5
	cmpl a0@(d3:l:4),d5
	jge L755
	moveq #4,d0
	jra L756
L755:
	lea _mode_size,a0
	movel a0@(d3:l:4),d0
L756:
	movel d2,a0
	subl d0,a0
	pea a0@(d1:l)
	movel d4,sp@-
	jbsr _plus_constant
	movel d0,d4
	movel d4,sp@-
	movel d3,sp@-
	jbsr _memory_address_p
	addw #16,sp
	tstl d0
	jeq L757
	movel d4,sp@-
	movel d3,sp@-
	movel a2@(4),sp@-
	jbsr _change_address
	jra L752
L757:
	jbsr _start_sequence
	movel d0,d2
	movel d4,sp@-
	movel d3,sp@-
	movel a2@(4),sp@-
	jbsr _change_address
	movel d0,d3
	movel a6@(12),sp@-
	jbsr _gen_sequence
	movel d0,sp@-
	jbsr _emit_insn_before
	movel d2,sp@-
	jbsr _end_sequence
	movel d3,d0
L752:
	moveml a6@(-20),#0x43c
	unlk a6
	rts
	.even
_walk_fixup_memory_subreg:
	link a6,#0
	moveml #0x3830,sp@-
	movel a6@(8),a2
	movel a6@(12),d4
	tstl a2
	jne L759
	clrl d0
	jra L758
L759:
	clrl d0
	movew a2@,d0
	moveq #35,d1
	cmpl d0,d1
	jne L760
	movel a2@(4),a0
	cmpw #37,a0@
	jne L760
	movel d4,sp@-
	movel a2,sp@-
	jbsr _fixup_memory_subreg
	jra L758
L760:
	lea _rtx_format,a0
	movel a0@(d0:l:4),a3
	lea _rtx_length,a0
	movel a0@(d0:l:4),d3
	jra L763
L770:
	cmpb #101,a3@(d3:l)
	jne L764
	movel d4,sp@-
	movel a2@(4,d3:l:4),sp@-
	jbsr _walk_fixup_memory_subreg
	movel d0,a2@(4,d3:l:4)
	addqw #8,sp
L764:
	cmpb #69,a3@(d3:l)
	jne L763
	clrl d2
	jra L766
L769:
	movel d4,sp@-
	movel a2@(4,d3:l:4),a0
	movel a0@(4,d2:l:4),sp@-
	jbsr _walk_fixup_memory_subreg
	movel a2@(4,d3:l:4),a0
	movel d0,a0@(4,d2:l:4)
	addqw #8,sp
	addql #1,d2
L766:
	movel a2@(4,d3:l:4),a0
	cmpl a0@,d2
	jcs L769
L763:
	subql #1,d3
	jpl L770
	movel a2,d0
L758:
	moveml a6@(-20),#0xc1c
	unlk a6
	rts
	.even
_fixup_stack_1:
	link a6,#0
	moveml #0x3830,sp@-
	movel a6@(8),a3
	movel a6@(12),d4
	clrl d0
	movew a3@,d0
	moveq #37,d1
	cmpl d0,d1
	jne L773
	movel a3@(4),a2
	cmpw #44,a2@
	jne L786
	movel a2@(4),d1
	cmpl _frame_pointer_rtx,d1
	jne L786
	movel a2@(8),a0
	cmpw #30,a0@
	jne L786
	movel a2,sp@-
	clrl d0
	moveb a3@(2),d0
	movel d0,sp@-
	jbsr _memory_address_p
	addqw #8,sp
	tstl d0
	jne L786
	clrl d0
	moveb a2@(2),d0
	movel d0,sp@-
	jbsr _gen_reg_rtx
	movel d0,d2
	movel d4,sp@-
	movel a2,sp@-
	movel d2,sp@-
	jbsr _gen_move_insn
	addqw #8,sp
	movel d0,sp@-
	jbsr _emit_insn_before
	movel d2,sp@-
	clrl sp@-
	movel a3,sp@-
	jbsr _change_address
	jra L772
L773:
	lea _rtx_format,a0
	movel a0@(d0:l:4),a2
	lea _rtx_length,a0
	movel a0@(d0:l:4),d3
	jra L778
L785:
	cmpb #101,a2@(d3:l)
	jne L779
	movel d4,sp@-
	movel a3@(4,d3:l:4),sp@-
	jbsr _fixup_stack_1
	movel d0,a3@(4,d3:l:4)
	addqw #8,sp
L779:
	cmpb #69,a2@(d3:l)
	jne L778
	clrl d2
	jra L781
L784:
	movel d4,sp@-
	movel a3@(4,d3:l:4),a0
	movel a0@(4,d2:l:4),sp@-
	jbsr _fixup_stack_1
	movel a3@(4,d3:l:4),a0
	movel d0,a0@(4,d2:l:4)
	addqw #8,sp
	addql #1,d2
L781:
	movel a3@(4,d3:l:4),a0
	cmpl a0@,d2
	jcs L784
L778:
	subql #1,d3
	jpl L785
L786:
	movel a3,d0
L772:
	moveml a6@(-20),#0xc1c
	unlk a6
	rts
	.even
_optimize_bit_field:
	link a6,#0
	moveml #0x383c,sp@-
	movel a6@(16),a3
	movel a6@(8),a1
	movel a1@(4),a0
	cmpw #89,a0@
	jeq L789
	cmpw #90,a0@
	jne L788
L789:
	movel a6@(8),a1
	movel a1@(4),a2
	moveq #1,d3
	jra L790
L788:
	movel a6@(8),a1
	movel a1@(8),a2
	clrl d3
L790:
	movel a2@(8),a4
	cmpw #30,a4@
	jne L791
	movel a2@(12),a0
	cmpw #30,a0@
	jne L791
	lea _mode_size+4,a0
	movel a0@,d0
	asll #3,d0
	cmpl a4@(4),d0
	jeq L792
	movel a0@(4),d0
	asll #3,d0
	cmpl a4@(4),d0
	jne L791
L792:
	movel a2@(12),a0
	movel a2@(8),a1
	movel a0@(4),d1
	divsll a1@(4),d0:d1
	tstl d0
	jne L791
	subl a5,a5
	movel a2@(4),a0
	cmpw #37,a0@
	jeq L824
	movel a2@(4),a0
	cmpw #34,a0@
	jne L795
	tstl a3
	jne L825
L795:
	movel a2@(4),a0
	cmpw #35,a0@
	jne L797
	movel a0@(4),a0
	cmpw #37,a0@
	jne L797
L824:
	movel a0,a5
	jra L794
L797:
	movel a2@(4),a0
	cmpw #35,a0@
	jne L794
	tstl a3
	jeq L794
	movel a0@(4),a0
	cmpw #34,a0@
	jne L794
L825:
	movel a0@(4),d0
	movel a3@(d0:l:4),a5
L794:
	tstl a5
	jeq L791
	movel a5@(4),sp@-
	jbsr _mode_dependent_address_p
	addqw #4,sp
	tstl d0
	jne L791
	movel a5@(4),sp@-
	clrl d0
	moveb a2@(2),d0
	movel d0,sp@-
	clrl sp@-
	jbsr _offsetable_address_p
	addw #12,sp
	tstl d0
	jeq L791
	movel a2@(12),a0
	movel _mode_size+4,d0
	asll #3,d0
	movel a0@(4),d2
	divsl d0,d2
	movel a2@(4),a0
	cmpw #35,a0@
	jne L801
	movel a0@(8),d0
	asll #2,d0
	addl d0,d2
	clrl d0
	moveb a0@(2),d0
	lea _mode_size,a0
	moveq #4,d4
	cmpl a0@(d0:l:4),d4
	jge L802
	moveq #4,d1
	jra L803
L802:
	movel a2@(4),a0
	clrl d0
	moveb a0@(2),d0
	lea _mode_size,a0
	movel a0@(d0:l:4),d1
L803:
	clrl d0
	moveb a5@(2),d0
	lea _mode_size,a0
	moveq #4,d4
	cmpl a0@(d0:l:4),d4
	jge L804
	moveq #4,d0
	jra L805
L804:
	clrl d0
	moveb a5@(2),d0
	lea _mode_size,a0
	movel a0@(d0:l:4),d0
L805:
	subl d1,d0
	negl d0
	subl d0,d2
L801:
	movel a5@(4),sp@-
	movel a2@(8),a0
	movel _mode_size+4,d0
	asll #3,d0
	cmpl a0@(4),d0
	jne L806
	moveq #1,d0
	jra L807
L806:
	moveq #2,d0
L807:
	movel d0,sp@-
	pea 37:w
	jbsr _gen_rtx
	movel d0,a5
	addw #12,sp
	tstl d3
	jeq L808
	movel d2,sp@-
	movel a5,sp@-
	jbsr _adj_offsetable_operand
	movel a6@(8),a1
	movel d0,a1@(4)
	movel a1@(8),a0
	addqw #8,sp
	cmpw #38,a0@
	jeq L809
	cmpw #39,a0@
	jeq L809
	cmpw #30,a0@
	jeq L809
	cmpw #32,a0@
	jeq L809
	cmpw #35,a0@
	jne L811
L812:
	tstl a0@(8)
	jne L811
	movel a0@(4),a0
	cmpw #35,a0@
	jeq L812
L811:
	moveb a0@(2),d4
	cmpb a5@(2),d4
	jeq L813
	movel a6@(8),a1
	movel a1@(8),sp@-
	clrl d0
	moveb a5@(2),d0
	movel d0,sp@-
	jbsr _gen_lowpart
	movel d0,a0
L813:
	movel a6@(8),a1
	movel a0,a1@(8)
	jra L816
L809:
	movel a6@(8),a1
	movel a1@(8),a0
	tstb a0@(2)
	jeq L816
	moveb a0@(2),d4
	cmpb a5@(2),d4
	jeq L816
	jbsr _abort
	jra L816
L808:
	movel a6@(8),a1
	movel a1@(4),a4
	cmpw #35,a4@
	jne L818
L819:
	tstl a4@(8)
	jne L818
	movel a4@(4),a4
	cmpw #35,a4@
	jeq L819
L818:
	movel a6@(8),a1
	movel a4,a1@(4)
	movel d2,sp@-
	movel a5,sp@-
	jbsr _adj_offsetable_operand
	movel d0,a5
	addqw #8,sp
	moveb a4@(2),d4
	cmpb a5@(2),d4
	jne L820
	movel a6@(8),a1
	movel a5,a1@(8)
	jra L816
L820:
	lea _get_last_insn,a3
	jbsr a3@
	movel d0,a2
	clrl d0
	moveb a4@(2),d0
	movel d0,sp@-
	jbsr _gen_reg_rtx
	movel d0,d2
	movel a6@(8),a1
	movel a1@(8),a0
	addqw #4,sp
	cmpw #90,a0@
	seq d0
	moveq #1,d4
	andl d4,d0
	movel d0,sp@-
	movel a5,sp@-
	movel d2,sp@-
	jbsr _convert_move
	movel a6@(12),a1
	movel a1@(8),sp@-
	jbsr a3@
	movel d0,sp@-
	movel a2@(12),sp@-
	jbsr _reorder_insns
	movel a6@(8),a1
	movel d2,a1@(8)
L816:
	movel a6@(12),a1
	moveq #-1,d4
	movel d4,a1@(20)
L791:
	moveml a6@(-28),#0x3c1c
	unlk a6
	rts
	.even
.globl _max_parm_reg_num
_max_parm_reg_num:
	link a6,#0
	movel _max_parm_reg,d0
	unlk a6
	rts
	.even
.globl _get_first_nonparm_insn
_get_first_nonparm_insn:
	link a6,#0
	tstl _last_parm_insn
	jeq L828
	movel _last_parm_insn,a0
	movel a0@(12),d0
	jra L827
L828:
	jbsr _get_insns
L827:
	unlk a6
	rts
	.even
_parm_stack_loc:
	link a6,#0
	movel a6@(8),a0
	movel a0@(4),d1
	cmpl _max_parm_reg,d1
	jge L830
	movel a0@(4),d0
	movel _parm_reg_stack_loc,a0
	movel a0@(d0:l:4),d0
	jra L829
L830:
	clrl d0
L829:
	unlk a6
	rts
LC13:
	.ascii "__builtin_va_alist\0"
	.even
_assign_parms:
	link a6,#-44
	moveml #0x3f3c,sp@-
	moveq #8,d6
	movel d6,a6@(-20)
	movel a6@(8),a1
	movel a1@(8),a2
	movel a1@(52),sp@-
	jbsr _list_length
	moveq #56,d6
	addl d6,d0
	movel d0,a6@(-24)
	clrl d2
	addqw #4,sp
	movel a6@(8),a1
	tstl a1@(52)
	jeq L834
	movel a1@(52),a0
	tstl a0@(36)
	jeq L834
	pea LC13
	movel a0@(36),a0
	movel a0@(20),sp@-
	jbsr _strcmp
	addqw #8,sp
	tstl d0
	jeq L833
L834:
	tstl a2@(16)
	jeq L832
	movel a2@(16),sp@-
	jbsr _tree_last
	movel d0,a0
	addqw #4,sp
	movel a0@(20),d6
	cmpl _void_type_node,d6
	jeq L832
L833:
	moveq #1,d2
L832:
	movel d2,a6@(-28)
	clrl a6@(-16)
	clrl a6@(-12)
	movel a6@(8),a1
	movel a1@(56),a0
	moveq #26,d6
	cmpl a0@(28),d6
	jne L835
	movel _struct_value_incoming_rtx,a0
	cmpw #37,a0@
	jne L835
	movel _mode_size+16,d6
	addl d6,a6@(-16)
L835:
	movel a6@(-24),d2
	asll #2,d2
	movel d2,sp@-
	jbsr _oballoc
	movel d0,_parm_reg_stack_loc
	movel d2,sp@-
	clrl sp@-
	movel d0,sp@-
	jbsr _memset
	clrl a6@(-8)
	movel a6@(8),a1
	movel a1@(52),a6@(-4)
	addw #16,sp
	jeq L946
	andl #255,d4
	andl #255,d7
L945:
	clrl d0
	movel a6@(-4),a1
	movel a1@(8),a0
	cmpb #16,a0@(12)
	jeq L840
	cmpb #19,a0@(12)
	jeq L840
	cmpb #20,a0@(12)
	jne L839
L840:
	moveq #1,d0
L839:
	movel d0,a6@(-32)
	movel a6@(-4),a1
	moveq #-1,d6
	movel d6,a1@(44)
	movel a1@(8),d6
	cmpl _error_mark_node,d6
	jeq L842
	cmpb #44,a1@(12)
	jne L842
	tstl a1@(52)
	jne L841
L842:
	movel _const0_rtx,sp@-
	pea 26:w
	pea 37:w
	jbsr _gen_rtx
	movel a6@(-4),a1
	movel d0,a1@(64)
	orb #1,a1@(14)
	addw #12,sp
	jra L838
L841:
	movel a6@(-4),a1
	movel a1@(52),a2
	moveb a2@(28),d4
	movel a1@(8),a0
	moveb a0@(28),d7
	movel a6@(-16),a6@(-40)
	movel a6@(-12),a6@(-36)
	movel a6@(-20),d6
	addl a6@(-16),d6
	movel d6,a6@(-40)
	moveq #26,d6
	cmpl d4,d6
	jne L845
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2,sp@-
	lea _size_in_bytes,a3
	jbsr a3@
	addqw #4,sp
	movel d0,sp@-
	lea _expand_expr,a2
	jbsr a2@
	movel d0,a0
	addw #16,sp
	cmpw #30,a0@
	jne L843
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a6@(-4),a1
	movel a1@(52),sp@-
	jbsr a3@
	addqw #4,sp
	movel d0,sp@-
	jbsr a2@
	movel d0,a0
	addw #16,sp
	btst #5,_target_flags+3
	jeq L847
	moveq #16,d0
	jra L848
L847:
	moveq #32,d0
L848:
	tstl d0
	jge L849
	addql #7,d0
L849:
	asrl #3,d0
	cmpl a0@(4),d0
	jgt L846
	jra L843
L845:
	lea _mode_size,a1
	movel a1@(d4:l:4),d1
	asll #3,d1
	btst #5,_target_flags+3
	jeq L850
	moveq #16,d0
	jra L851
L850:
	moveq #32,d0
L851:
	cmpl d1,d0
	jle L843
L846:
	moveq #2,d6
	jra L947
L843:
	moveq #1,d6
L947:
	movel d6,a6@(-44)
	moveq #2,d6
	cmpl a6@(-44),d6
	jne L852
	moveq #26,d6
	cmpl d4,d6
	jeq L853
	lea _mode_size,a1
	movel a1@(d4:l:4),d1
	asll #3,d1
	btst #5,_target_flags+3
	jeq L855
	moveq #16,d0
	jra L856
L855:
	moveq #32,d0
L856:
	divsll d0,d0:d1
	tstl d0
	jeq L852
	lea _mode_size,a1
	movel a1@(d4:l:4),d0
	asll #3,d0
	btst #5,_target_flags+3
	jeq L857
	movew #16,a0
	jra L858
L857:
	movew #32,a0
L858:
	lea a0@(-1,d0:l),a1
	movel a1,d1
	btst #5,_target_flags+3
	jeq L859
	moveq #16,d0
	jra L860
L859:
	moveq #32,d0
L860:
	divsl d0,d1
	btst #5,_target_flags+3
	jeq L861
	moveq #16,d0
	jra L862
L861:
	moveq #32,d0
L862:
	mulsl d1,d0
	jpl L863
	addql #7,d0
L863:
	asrl #3,d0
	lea _mode_size,a1
	subl a1@(d4:l:4),d0
	addl d0,a6@(-40)
	jra L852
L853:
	movel a6@(-4),a1
	movel a1@(52),sp@-
	jbsr _size_in_bytes
	movel d0,d2
	addqw #4,sp
	btst #5,_target_flags+3
	jeq L865
	moveq #16,d0
	jra L866
L865:
	moveq #32,d0
L866:
	movel d0,sp@-
	pea 8:w
	movel d2,sp@-
	jbsr _convert_units
	movel d0,d1
	pea 8:w
	btst #5,_target_flags+3
	jeq L867
	moveq #16,d0
	jra L868
L867:
	moveq #32,d0
L868:
	movel d0,sp@-
	movel d1,sp@-
	jbsr _convert_units
	movel d0,a0
	addw #24,sp
	cmpb #35,a0@(12)
	jne L869
	movel a0@(16),d6
	addl d6,a6@(-40)
	jra L870
L869:
	tstl a6@(-36)
	jne L871
	movel a0,a6@(-36)
	jra L870
L871:
	movel a0,sp@-
	movel a6@(-36),sp@-
	pea 63:w
	jbsr _genop
	movel d0,a6@(-36)
	addw #12,sp
L870:
	movel d2,a0
	cmpb #35,a0@(12)
	jne L873
	movel a0@(16),d6
	subl d6,a6@(-40)
	jra L852
L873:
	tstl a6@(-36)
	jne L875
	movel a0,sp@-
	movel _integer_zero_node,sp@-
	jra L948
L875:
	movel a0,sp@-
	movel a6@(-36),sp@-
L948:
	pea 64:w
	jbsr _genop
	movel d0,a6@(-36)
	addw #12,sp
L852:
	tstl a6@(-36)
	jne L877
	movel a6@(-40),sp@-
	clrl sp@-
	pea 30:w
	jbsr _gen_rtx
	addw #12,sp
	jra L949
L877:
	movel a6@(-40),sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a6@(-36),sp@-
	jbsr _expand_expr
	addw #16,sp
	movel d0,sp@-
	jbsr _plus_constant
	addqw #8,sp
L949:
	movel d0,d3
	movel d3,sp@-
	movel _arg_pointer_rtx,sp@-
	pea 4:w
	pea 44:w
	lea _gen_rtx,a2
	jbsr a2@
	movel d0,sp@-
	movel d4,sp@-
	jbsr _memory_address
	movel d0,sp@-
	movel d4,sp@-
	pea 37:w
	jbsr a2@
	movel d0,a3
	movel a6@(-32),d6
	bfins d6,a3@(3){#4:#1}
	subl a5,a5
	movel a6@(-4),a1
	movel a1@(8),a0
	movel a0@(24),a0
	addw #36,sp
	cmpb #35,a0@(12)
	jeq L880
	tstl a6@(-36)
	jeq L879
L880:
	btst #4,_target_flags+3
	jeq L881
	moveq #7,d6
	cmpl a6@(-8),d6
	jlt L881
	movel a6@(-8),d0
	jge L883
	addql #3,d0
L883:
	asrl #2,d0
	movel d0,sp@-
	movel d4,sp@-
	pea 34:w
	jbsr _gen_rtx
	addw #12,sp
	movel d0,a5
	jra L879
L881:
	subl a5,a5
L879:
	btst #4,_target_flags+3
	jeq L884
	moveq #7,d6
	cmpl a6@(-8),d6
	jlt L884
	moveq #26,d6
	cmpl d4,d6
	jne L886
	movel a6@(-4),a1
	movel a1@(52),sp@-
	jbsr _int_size_in_bytes
	addqw #4,sp
	jra L887
L886:
	lea _mode_size,a1
	movel a1@(d4:l:4),d0
L887:
	addl a6@(-8),d0
	moveq #8,d6
	cmpl d0,d6
	jge L884
	movel a6@(-8),d0
	jge L888
	addql #3,d0
L888:
	asrl #2,d0
	moveq #2,d1
	subl d0,d1
	jra L885
L884:
	clrl d1
L885:
	movel a6@(-4),a1
	tstl a1@(4)
	jne L889
	tstl a6@(-28)
	jeq L889
	tstl a5
	jeq L889
	cmpb #26,a5@(2)
	jne L890
	clrl d0
	moveb a5@(2),d0
	lea _mode_size,a1
	movel a1@(d0:l:4),d1
	jge L891
	addql #3,d1
L891:
	asrl #2,d1
	jra L889
L890:
	movel a6@(-4),a1
	movel a1@(52),sp@-
	jbsr _int_size_in_bytes
	movel d0,d1
	jge L893
	addql #3,d1
L893:
	asrl #2,d1
	addqw #4,sp
L889:
	tstl d1
	jle L894
	movel d1,d2
	asll #2,d2
	btst #5,_target_flags+3
	jeq L895
	moveq #16,d0
	jra L896
L895:
	moveq #32,d0
L896:
	tstl d0
	jge L897
	addql #7,d0
L897:
	asrl #3,d0
	movel d2,a1
	lea a1@(-1,d0:l),a4
	movel a4,d2
	btst #5,_target_flags+3
	jeq L898
	moveq #16,d0
	jra L899
L898:
	moveq #32,d0
L899:
	tstl d0
	jge L900
	addql #7,d0
L900:
	asrl #3,d0
	divsl d0,d2
	btst #5,_target_flags+3
	jeq L901
	moveq #16,d0
	jra L902
L901:
	moveq #32,d0
L902:
	tstl d0
	jge L903
	addql #7,d0
L903:
	asrl #3,d0
	mulsl d0,d2
	movel d2,_current_function_pretend_args_size
	movel d1,d2
	jra L904
L906:
	movel d2,d6
	addl a5@(4),d6
	movel d6,sp@-
	pea 4:w
	pea 34:w
	lea _gen_rtx,a2
	jbsr a2@
	movel d0,sp@-
	movel d2,d6
	mulsl _mode_size+16,d6
	movel d6,sp@-
	movel a3@(4),sp@-
	jbsr _plus_constant
	addqw #8,sp
	movel d0,sp@-
	pea 4:w
	pea 37:w
	jbsr a2@
	addw #12,sp
	movel d0,sp@-
	jbsr _emit_move_insn
	addw #20,sp
L904:
	subql #1,d2
	jpl L906
	movel a3,a5
L894:
	tstl a5
	jne L907
	movel a3,a5
L907:
	cmpl a5,a3
	jne L908
	movel a6@(-4),a1
	movel a6@(-40),d6
	asll #3,d6
	movel d6,a1@(44)
L908:
	cmpl a5,a3
	jne L909
	movel a6@(-4),a1
	movel a1@(52),sp@-
	jbsr _size_in_bytes
	movel d0,d1
	addqw #4,sp
	tstl a6@(-44)
	jeq L910
	btst #5,_target_flags+3
	jeq L911
	moveq #16,d0
	jra L912
L911:
	moveq #32,d0
L912:
	movel d0,sp@-
	pea 8:w
	movel d1,sp@-
	jbsr _convert_units
	movel d0,d1
	pea 8:w
	btst #5,_target_flags+3
	jeq L913
	moveq #16,d0
	jra L914
L913:
	moveq #32,d0
L914:
	movel d0,sp@-
	movel d1,sp@-
	jbsr _convert_units
	movel d0,d1
	addw #24,sp
L910:
	movel d1,a0
	cmpb #35,a0@(12)
	jne L915
	movel a0@(16),d6
	addl d6,a6@(-16)
	jra L919
L915:
	tstl a6@(-12)
	jne L917
	movel a0,a6@(-12)
	jra L919
L917:
	movel a0,sp@-
	movel a6@(-12),sp@-
	pea 63:w
	jbsr _genop
	movel d0,a6@(-12)
	addw #12,sp
	jra L919
L909:
	subl a3,a3
L919:
	moveq #26,d6
	cmpl d7,d6
	jeq L920
	cmpl d7,d4
	jeq L920
	tstl a3
	jeq L920
	lea _mode_size,a1
	moveq #3,d6
	cmpl a1@(d7:l:4),d6
	jlt L921
	movel a1@(d4:l:4),d0
	subl a1@(d7:l:4),d0
	addl a6@(-40),d0
	movel d0,a6@(-40)
	tstl a6@(-36)
	jne L922
	movel d0,sp@-
	clrl sp@-
	pea 30:w
	jbsr _gen_rtx
	addw #12,sp
	jra L950
L922:
	movel a6@(-40),sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a6@(-36),sp@-
	jbsr _expand_expr
	addw #16,sp
	movel d0,sp@-
	jbsr _plus_constant
	addqw #8,sp
L950:
	movel d0,d3
L921:
	movel d3,sp@-
	movel _arg_pointer_rtx,sp@-
	pea 4:w
	pea 44:w
	lea _gen_rtx,a2
	jbsr a2@
	movel d0,sp@-
	movel d7,sp@-
	jbsr _memory_address
	movel d0,sp@-
	movel d7,sp@-
	pea 37:w
	jbsr a2@
	movel d0,a3
	movel a6@(-32),d6
	bfins d6,a3@(3){#4:#1}
	addw #36,sp
L920:
	moveq #26,d6
	cmpl d7,d6
	jne L924
	cmpw #34,a5@
	jne L925
	tstl a3
	jne L926
	movel a6@(-4),a1
	movel a1@(8),sp@-
	jbsr _int_size_in_bytes
	movel d0,sp@-
	clrl d0
	moveb a5@(2),d0
	movel d0,sp@-
	jbsr _assign_stack_local
	movel d0,a3
	addw #12,sp
L926:
	movel a6@(-4),a1
	movel a1@(8),sp@-
	jbsr _int_size_in_bytes
	tstl d0
	jge L927
	addql #3,d0
L927:
	asrl #2,d0
	movel d0,sp@-
	movel a3,sp@-
	movel a5@(4),sp@-
	jbsr _move_block_from_reg
	addw #16,sp
L925:
	movel a6@(-4),a1
	movel a3,a1@(64)
	jra L928
L924:
	tstl _obey_regdecls
	jeq L930
	movel a6@(-4),a1
	btst #5,a1@(14)
	jne L930
	movel a6@(8),a1
	btst #1,a1@(14)
	jeq L929
L930:
	movel a6@(-4),a1
	btst #6,a1@(14)
	jne L929
	btst #4,a1@(13)
	jne L929
	tstl _flag_float_store
	jeq L931
	movel a1@(8),a0
	cmpb #6,a0@(12)
	jeq L929
L931:
	movel d7,sp@-
	jbsr _gen_reg_rtx
	movel d0,a6@(-44)
	movel d0,a1
	orb #16,a1@(3)
	movel a6@(-4),a1
	movel d0,a1@(64)
	addqw #4,sp
	movel d0,a1
	moveb a1@(2),d6
	cmpb a5@(2),d6
	jeq L932
	clrl sp@-
	movel a5,sp@-
	movel a6@(-44),sp@-
	jbsr _convert_move
	addw #12,sp
	jra L933
L932:
	movel a5,sp@-
	movel a6@(-44),sp@-
	jbsr _emit_move_insn
	addqw #8,sp
L933:
	movel a6@(-44),a1
	movel a1@(4),d6
	cmpl a6@(-24),d6
	jlt L934
	movel a1@(4),d6
	addql #5,d6
	movel d6,a6@(-24)
	movel d6,d3
	asll #2,d3
	movel d3,sp@-
	jbsr _oballoc
	movel d0,d2
	movel d3,sp@-
	movel _parm_reg_stack_loc,sp@-
	movel d2,sp@-
	jbsr _memcpy
	movel d2,_parm_reg_stack_loc
	addw #16,sp
L934:
	movel a6@(-44),a1
	movel a1@(4),d0
	movel _parm_reg_stack_loc,a0
	movel a3,a0@(d0:l:4)
	cmpl d7,d4
	jne L935
	cmpw #37,a5@
	jne L935
	tstl a6@(-36)
	jne L935
	lea _get_last_insn,a3
	jbsr a3@
	movel d0,a2
	jbsr a3@
	movel d0,a0
	movel a0@(28),sp@-
	movel a5,sp@-
	pea 3:w
	pea 2:w
	jbsr _gen_rtx
	movel d0,a2@(28)
	addw #16,sp
L935:
	movel a6@(-4),a1
	movel a1@(8),a0
	cmpb #11,a0@(12)
	jne L928
	movel a6@(-44),sp@-
	jbsr _mark_reg_pointer
	addqw #4,sp
	jra L928
L929:
	cmpl d4,d7
	jeq L938
	clrl sp@-
	movel a5,sp@-
	movel d7,sp@-
	jbsr _convert_to_mode
	movel d0,a5
	addw #12,sp
L938:
	cmpl a5,a3
	jeq L939
	tstl a3
	jne L940
	clrl d0
	moveb a5@(2),d0
	lea _mode_size,a1
	movel a1@(d0:l:4),sp@-
	movel d0,sp@-
	jbsr _assign_stack_local
	movel d0,a3
	addqw #8,sp
L940:
	movel a5,sp@-
	movel a3,sp@-
	jbsr _emit_move_insn
	addqw #8,sp
L939:
	movel a6@(-4),a1
	movel a3,a1@(64)
	moveq #1,d6
	movel d6,_frame_pointer_needed
L928:
	movel a6@(-4),a1
	btst #4,a1@(13)
	jeq L941
	movel a1@(64),a0
	orb #16,a0@(3)
L941:
	movel a6@(-4),a1
	btst #2,a1@(13)
	jeq L942
	movel a1@(64),a0
	orb #32,a0@(3)
L942:
	moveq #26,d6
	cmpl d4,d6
	jeq L943
	lea _mode_size,a1
	movel a1@(d4:l:4),d0
	jra L951
L943:
	movel a6@(-4),a1
	movel a1@(52),sp@-
	jbsr _int_size_in_bytes
	addqw #4,sp
L951:
	addql #3,d0
	moveq #-4,d6
	andl d6,d0
	addl d0,a6@(-8)
L838:
	movel a6@(-4),a1
	movel a1@(4),a6@(-4)
	jne L945
L946:
	jbsr _max_reg_num
	movel d0,_max_parm_reg
	jbsr _get_last_insn
	movel d0,_last_parm_insn
	movel a6@(-16),_current_function_args_size
	moveml a6@(-84),#0x3cfc
	unlk a6
	rts
	.even
.globl _get_structure_value_addr
_get_structure_value_addr:
	link a6,#0
	movel a2,sp@-
	movel a6@(8),a2
	cmpw #30,a2@
	jeq L953
	jbsr _abort
L953:
	movel a2@(4),d0
	addql #1,d0
	jpl L954
	addql #1,d0
L954:
	moveq #-2,d1
	andl d1,d0
	cmpl _max_structure_value_size,d0
	jle L955
	movel d0,_max_structure_value_size
	movel d0,sp@-
	pea 26:w
	jbsr _assign_stack_local
	movel d0,a0
	movel a0,_structure_value
	cmpw #37,a0@
	jne L955
	movel a0@(4),_structure_value
L955:
	movel _structure_value,d0
	movel a6@(-4),a2
	unlk a6
	rts
LC14:
	.ascii "`%s' may be used uninitialized in this function\0"
LC15:
	.ascii "variable `%s' may be clobbered by `longjmp'\0"
	.even
.globl _uninitialized_vars_warning
_uninitialized_vars_warning:
	link a6,#0
	moveml #0x30,sp@-
	movel a6@(8),a3
	movel a3@(28),a2
	tstl a2
	jeq L969
L963:
	cmpb #43,a2@(12)
	jne L961
	movel a2@(8),a0
	cmpb #19,a0@(12)
	jeq L961
	cmpb #20,a0@(12)
	jeq L961
	cmpb #16,a0@(12)
	jeq L961
	movel a2@(64),a0
	cmpw #34,a0@
	jne L961
	movel a0@(4),sp@-
	jbsr _regno_uninitialized
	addqw #4,sp
	tstl d0
	jeq L961
	pea LC14
	movel a2,sp@-
	jbsr _warning_with_decl
	addqw #8,sp
L961:
	cmpb #43,a2@(12)
	jne L960
	movel a2@(64),a0
	cmpw #34,a0@
	jne L960
	movel a0@(4),sp@-
	jbsr _regno_clobbered_at_setjmp
	addqw #4,sp
	tstl d0
	jeq L960
	pea LC15
	movel a2,sp@-
	jbsr _warning_with_decl
	addqw #8,sp
L960:
	movel a2@(4),a2
	tstl a2
	jne L963
L969:
	movel a3@(24),a2
	tstl a2
	jeq L968
L967:
	movel a2,sp@-
	jbsr _uninitialized_vars_warning
	addqw #4,sp
	movel a2@(4),a2
	tstl a2
	jne L967
L968:
	moveml a6@(-8),#0xc00
	unlk a6
	rts
	.even
.globl _setjmp_protect
_setjmp_protect:
	link a6,#0
	moveml #0x30,sp@-
	movel a6@(8),a3
	movel a3@(28),a2
	tstl a2
	jeq L982
L976:
	cmpb #43,a2@(12)
	jeq L975
	cmpb #44,a2@(12)
	jne L973
L975:
	tstl a2@(64)
	jeq L973
	movel a2@(64),a0
	cmpw #34,a0@
	jne L973
	btst #5,a2@(14)
	jne L973
	movel a2,sp@-
	jbsr _put_var_into_stack
	addqw #4,sp
L973:
	movel a2@(4),a2
	tstl a2
	jne L976
L982:
	movel a3@(24),a2
	tstl a2
	jeq L981
L980:
	movel a2,sp@-
	jbsr _setjmp_protect
	addqw #4,sp
	movel a2@(4),a2
	tstl a2
	jne L980
L981:
	moveml a6@(-8),#0xc00
	unlk a6
	rts
	.even
.globl _expand_function_start
_expand_function_start:
	link a6,#0
	moveml #0x2020,sp@-
	movel a6@(8),a2
	movel a2,_this_function
	tstl _optimize
	seq d0
	moveq #1,d1
	andl d1,d0
	movel d0,_cse_not_expected
	tstl _flag_omit_frame_pointer
	seq d0
	moveq #1,d1
	andl d1,d0
	movel d0,_frame_pointer_needed
	clrl _goto_fixup_chain
	clrl _stack_slot_list
	clrl _invalid_stack_slot
	movel _write_symbols,sp@-
	jbsr _init_emit
	jbsr _init_expr
	jbsr _init_const_rtx_hash_table
	clrl d2
	addqw #4,sp
	btst #3,_target_flags+3
	jeq L984
	movel a2@(8),a0
	cmpb #1,a0@(12)
	jeq L984
	tstl a0@(16)
	jeq L985
	movel a0@(16),sp@-
	jbsr _tree_last
	movel d0,a0
	addqw #4,sp
	movel a0@(20),d1
	cmpl _void_type_node,d1
	jne L984
L985:
	moveq #1,d2
L984:
	movel d2,_current_function_pops_args
	movel a2@(36),a0
	movel a0@(20),_current_function_name
	clrl d0
	movel _current_function_decl,a0
	tstl a0@(40)
	jeq L986
	movel a0@(40),a0
	cmpb #28,a0@(12)
	jne L986
	moveq #1,d0
L986:
	movel d0,_current_function_needs_context
	clrl _current_function_calls_setjmp
	clrl _current_function_returns_pcc_struct
	clrl _current_function_returns_struct
	clrl _max_structure_value_size
	clrl _structure_value
	clrl _block_stack
	clrl _loop_stack
	clrl _case_stack
	clrl _cond_stack
	clrl _nesting_stack
	clrl _nesting_depth
	clrl _tail_recursion_label
	clrl _frame_offset
	clrl _save_expr_regs
	clrl _rtl_expr_chain
	addql #1,_immediate_size_expand
	jbsr _init_pending_stack_adjust
	jbsr _clear_current_args_size
	clrl _current_function_pretend_args_size
	movel a2@(20),sp@-
	movel a2@(16),sp@-
	jbsr _emit_line_note
	pea -1:w
	clrl sp@-
	jbsr _emit_note
	movel a2,sp@-
	jbsr _assign_parms
	movel a2@(56),a0
	addw #20,sp
	moveq #26,d1
	cmpl a0@(28),d1
	jeq L988
	tstl _flag_pcc_struct_return
	jeq L987
	movel a0@(8),a0
	cmpb #19,a0@(12)
	jeq L988
	cmpb #20,a0@(12)
	jne L987
L988:
	tstl _flag_pcc_struct_return
	jeq L989
	movel a2@(56),a0
	movel a0@(8),sp@-
	jbsr _int_size_in_bytes
	movel d0,sp@-
	jbsr _assemble_static_space
	movel d0,d2
	moveq #1,d1
	movel d1,_current_function_returns_pcc_struct
	addqw #8,sp
	jra L990
L989:
	pea 4:w
	jbsr _gen_reg_rtx
	movel d0,d2
	movel _struct_value_incoming_rtx,sp@-
	movel d2,sp@-
	jbsr _emit_move_insn
	moveq #1,d1
	movel d1,_current_function_returns_struct
	addw #12,sp
L990:
	movel d2,sp@-
	movel a2@(56),a0
	movel a0@(28),sp@-
	pea 37:w
	jra L1006
L987:
	clrl sp@-
	movel a2@(56),a0
	movel a0@(8),a0
	clrl d0
	moveb a0@(28),d0
	movel d0,sp@-
	pea 34:w
L1006:
	jbsr _gen_rtx
	movel a2@(56),a0
	movel d0,a0@(64)
	addw #12,sp
	movel a2@(56),a0
	movel a0@(64),a0
	cmpw #34,a0@
	jne L993
	orb #2,a0@(3)
L993:
	jbsr _gen_label_rtx
	movel d0,_return_label
	tstl _obey_regdecls
	jeq L995
	jbsr _get_last_insn
	movel d0,_parm_birth_insn
	moveq #56,d2
	cmpl _max_parm_reg,d2
	jge L995
L999:
	movel _regno_reg_rtx,a0
	movel a0@(d2:l:4),sp@-
	jbsr _use_variable
	addqw #4,sp
	addql #1,d2
	cmpl _max_parm_reg,d2
	jlt L999
L995:
	jbsr _get_last_insn
	movel d0,_tail_recursion_reentry
	jbsr _get_pending_sizes
	movel d0,a2
	tstl a2
	jeq L1004
L1003:
	clrl sp@-
	clrl sp@-
	clrl sp@-
	movel a2@(20),sp@-
	jbsr _expand_expr
	addw #16,sp
	movel a2@(4),a2
	tstl a2
	jne L1003
L1004:
	moveml a6@(-8),#0x404
	unlk a6
	rts
	.even
.globl _expand_function_end
_expand_function_end:
	link a6,#0
	moveml #0x3020,sp@-
	tstl _sequence_stack
	jeq L1027
L1010:
	clrl sp@-
	jbsr _end_sequence
	addqw #4,sp
	tstl _sequence_stack
	jne L1010
L1027:
	subql #1,_immediate_size_expand
	tstl _current_function_returns_struct
	jeq L1011
	movel _current_function_decl,a0
	movel a0@(56),a1
	movel a1@(64),a2
	movel a2@(4),d2
	movel a1@(8),d0
	movel a0,sp@-
	movel d0,sp@-
	jbsr _build_pointer_type
	addqw #4,sp
	movel d0,sp@-
	jbsr _hard_function_value
	movel d2,sp@-
	movel d0,sp@-
	jbsr _emit_move_insn
	addw #16,sp
L1011:
	tstl _obey_regdecls
	jeq L1012
	moveq #56,d2
	cmpl _max_parm_reg,d2
	jge L1026
L1016:
	movel _regno_reg_rtx,a0
	movel a0@(d2:l:4),sp@-
	jbsr _use_variable
	addqw #4,sp
	addql #1,d2
	cmpl _max_parm_reg,d2
	jlt L1016
L1026:
	movel _save_expr_regs,a2
	tstl a2
	jeq L1012
L1020:
	movel a2@(4),sp@-
	jbsr _use_variable
	movel _parm_birth_insn,sp@-
	movel a2@(4),sp@-
	jbsr _use_variable_after
	addw #12,sp
	movel a2@(8),a2
	tstl a2
	jne L1020
L1012:
	jbsr _clear_pending_stack_adjust
	jbsr _do_pending_stack_adjust
	pea -6:w
	clrl sp@-
	jbsr _emit_note
	movel a6@(12),sp@-
	movel a6@(8),sp@-
	jbsr _emit_line_note_force
	addw #16,sp
	movel _return_label,sp@-
	jbsr _emit_label
	addqw #4,sp
	tstl _current_function_returns_pcc_struct
	jeq L1023
	movel _current_function_decl,a0
	movel a0@(56),a1
	movel a1@(64),a2
	movel a2@(4),d2
	movel a1@(8),d0
	movel a0,sp@-
	movel d0,sp@-
	jbsr _build_pointer_type
	addqw #4,sp
	movel d0,sp@-
	jbsr _hard_function_value
	movel d0,d3
	movel d2,sp@-
	movel d3,sp@-
	jbsr _emit_move_insn
	movel d3,sp@-
	jbsr _use_variable
	addw #20,sp
L1023:
	clrl sp@-
	jbsr _get_insns
	movel d0,sp@-
	clrl sp@-
	clrl sp@-
	clrl sp@-
	jbsr _fixup_gotos
	moveml a6@(-12),#0x40c
	unlk a6
	rts
.lcomm _structure_value,4
.lcomm _max_structure_value_size,4
.lcomm _parm_reg_stack_loc,4
.lcomm _max_parm_reg,4
.comm _expr_stmts_for_value,4
.lcomm _goto_fixup_chain,4
.comm _nesting_depth,4
.comm _nesting_stack,4
.comm _case_stack,4
.comm _loop_stack,4
.comm _cond_stack,4
.comm _stack_block_stack,4
.comm _block_stack,4
.lcomm _last_parm_insn,4
.lcomm _rtl_expr_chain,4
.lcomm _last_expr_value,4
.lcomm _last_expr_type,4
.lcomm _tail_recursion_reentry,4
.lcomm _tail_recursion_label,4
.lcomm _invalid_stack_slot,4
.lcomm _frame_offset,4
.lcomm _this_function,4
.lcomm _parm_birth_insn,4
.comm _emit_lineno,4
.comm _emit_filename,4
.comm _stack_slot_list,4
.comm _return_label,4
.comm _current_function_name,4
.comm _current_function_pretend_args_size,4
.comm _current_function_args_size,4
.comm _current_function_needs_context,4
.comm _current_function_returns_pcc_struct,4
.comm _current_function_returns_struct,4
.comm _current_function_pops_args,4
.comm _save_expr_regs,4
.comm _current_function_calls_setjmp,4
