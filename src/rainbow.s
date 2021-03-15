	include "hardware/custom.i"

	xdef	_rainbow

	section	.text

_rainbow	; d0 = delay
	move.l	d2,-(sp)
	move.w	#$fff,d1
.loop	move.w	d1,$dff000+color
	move.w	d0,d2
	beq.b	.skip
.wait	tst.b	$bfe001
	dbf	d2,.wait
.skip	dbf	d1,.loop
	move.l	(sp)+,d2
	rts
