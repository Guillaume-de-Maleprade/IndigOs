#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=i586-pc-elf-gcc
CCC=g++
CXX=g++
FC=gfortran
AS=nasm

# Macros
CND_PLATFORM=MinGW_ELF-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/0-Noyau_Start.o \
	${OBJECTDIR}/1-NOYAU_MAIN.o \
	${OBJECTDIR}/CALLBACK_EXCEPTION.o \
	${OBJECTDIR}/CALLBACK_IRQ.o \
	${OBJECTDIR}/DELAY.o \
	${OBJECTDIR}/Descripteurs.o \
	${OBJECTDIR}/EXCEPTION.o \
	${OBJECTDIR}/Ecran.o \
	${OBJECTDIR}/HARD_8042_Clavier.o \
	${OBJECTDIR}/HARD_8253_Timer.o \
	${OBJECTDIR}/INIT_IDT.o \
	${OBJECTDIR}/IRQ.o \
	${OBJECTDIR}/Init_GDT.o \
	${OBJECTDIR}/Outils.o \
	${OBJECTDIR}/PIC_8259A.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=-f elf

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/noyau.jlv.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/noyau.jlv.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	i586-pc-elf-ld -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/noyau.jlv ${OBJECTFILES} ${LDLIBSOPTIONS} -Ttext=0x100000 --entry=_start --oformat i586-pc-elf -Tdata=0x200000 -Map=Noyau.map

${OBJECTDIR}/0-Noyau_Start.o: 0-Noyau_Start.asm
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/0-Noyau_Start.o 0-Noyau_Start.asm

${OBJECTDIR}/1-NOYAU_MAIN.o: 1-NOYAU_MAIN.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/1-NOYAU_MAIN.o 1-NOYAU_MAIN.c

${OBJECTDIR}/CALLBACK_EXCEPTION.o: CALLBACK_EXCEPTION.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CALLBACK_EXCEPTION.o CALLBACK_EXCEPTION.c

${OBJECTDIR}/CALLBACK_IRQ.o: CALLBACK_IRQ.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CALLBACK_IRQ.o CALLBACK_IRQ.c

${OBJECTDIR}/DELAY.o: DELAY.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DELAY.o DELAY.c

${OBJECTDIR}/Descripteurs.o: Descripteurs.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Descripteurs.o Descripteurs.c

${OBJECTDIR}/EXCEPTION.o: EXCEPTION.asm
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/EXCEPTION.o EXCEPTION.asm

${OBJECTDIR}/Ecran.o: Ecran.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ecran.o Ecran.c

${OBJECTDIR}/HARD_8042_Clavier.o: HARD_8042_Clavier.asm
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/HARD_8042_Clavier.o HARD_8042_Clavier.asm

${OBJECTDIR}/HARD_8253_Timer.o: HARD_8253_Timer.asm
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/HARD_8253_Timer.o HARD_8253_Timer.asm

${OBJECTDIR}/INIT_IDT.o: INIT_IDT.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/INIT_IDT.o INIT_IDT.c

${OBJECTDIR}/IRQ.o: IRQ.asm
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/IRQ.o IRQ.asm

${OBJECTDIR}/Init_GDT.o: Init_GDT.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Init_GDT.o Init_GDT.c

${OBJECTDIR}/Outils.o: Outils.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Outils.o Outils.c

${OBJECTDIR}/PIC_8259A.o: PIC_8259A.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PIC_8259A.o PIC_8259A.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
