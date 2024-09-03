
.macro GetPlayerParameter # parameter is PlayerData Pointer
backup

# load player data
lbz r3, 0x0A(r3)

# get rider id and rider table
lwz r24, OFST_RiderTable(rtoc)
lwz r25, 0x04(r24)
lbzx r25, r3, r25

# load param kexData
lwz r24, OFST_RiderParamTable(rtoc)
mulli r25, r25, 4
lwzx r3, r25, r24

restore
.endm


.macro branch reg, address
lis \reg, \address @h
ori \reg,\reg,\address @l
mtctr \reg
bctr
.endm

.macro branchl reg, address
lis \reg, \address @h
ori \reg,\reg,\address @l
mtctr \reg
bctrl
.endm

.macro load reg, address
lis \reg, \address @h
ori \reg, \reg, \address @l
.endm

.macro backup
mflr r0
stw r0, 0x4(r1)
stwu	r1,-0x100(r1)	# make space for 12 registers
stmw  r20,0x8(r1)
.endm

 .macro restore
lmw  r20,0x8(r1)
lwz r0, 0x104(r1)
addi	r1,r1,0x100	# release the space
mtlr r0
.endm

.macro backupall
mflr r0
stw r0, 0x4(r1)
stwu	r1,-0x100(r1)	# make space for 12 registers
stmw  r3,0x8(r1)
.endm

.macro restoreall
lmw  r3,0x8(r1)
lwz r0, 0x104(r1)
addi	r1,r1,0x100	# release the space
mtlr r0
.endm
