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
	${OBJECTDIR}/1-Main.o \
	${OBJECTDIR}/Clavier.o \
	${OBJECTDIR}/Ecran.o \
	${OBJECTDIR}/Outils.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/2-boot-grub-mini.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/2-boot-grub-mini.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/2-boot-grub-mini ${OBJECTFILES} ${LDLIBSOPTIONS} -Ttext=0x100000 --entry=_start --oformat i586-pc-elf

${OBJECTDIR}/0-Noyau_Start.o: 0-Noyau_Start.asm
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/0-Noyau_Start.o 0-Noyau_Start.asm

${OBJECTDIR}/1-Main.o: 1-Main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/1-Main.o 1-Main.c

${OBJECTDIR}/Clavier.o: Clavier.s
	${MKDIR} -p ${OBJECTDIR}
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/Clavier.o Clavier.s

${OBJECTDIR}/Ecran.o: Ecran.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ecran.o Ecran.c

${OBJECTDIR}/Outils.o: Outils.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Outils.o Outils.c

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
