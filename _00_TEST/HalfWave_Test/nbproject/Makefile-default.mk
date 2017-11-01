#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/HalfWave_Test.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/HalfWave_Test.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=nbproject/private/gpio.c nbproject/private/ADC.c nbproject/private/triac.c nbproject/private/message.c nbproject/private/parameter.c nbproject/private/KeyState.c nbproject/private/delay.c nbproject/private/timer.c nbproject/private/pic18f67xx_it.c nbproject/private/main.c nbproject/private/hal_Usart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/nbproject/private/gpio.p1 ${OBJECTDIR}/nbproject/private/ADC.p1 ${OBJECTDIR}/nbproject/private/triac.p1 ${OBJECTDIR}/nbproject/private/message.p1 ${OBJECTDIR}/nbproject/private/parameter.p1 ${OBJECTDIR}/nbproject/private/KeyState.p1 ${OBJECTDIR}/nbproject/private/delay.p1 ${OBJECTDIR}/nbproject/private/timer.p1 ${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1 ${OBJECTDIR}/nbproject/private/main.p1 ${OBJECTDIR}/nbproject/private/hal_Usart.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/nbproject/private/gpio.p1.d ${OBJECTDIR}/nbproject/private/ADC.p1.d ${OBJECTDIR}/nbproject/private/triac.p1.d ${OBJECTDIR}/nbproject/private/message.p1.d ${OBJECTDIR}/nbproject/private/parameter.p1.d ${OBJECTDIR}/nbproject/private/KeyState.p1.d ${OBJECTDIR}/nbproject/private/delay.p1.d ${OBJECTDIR}/nbproject/private/timer.p1.d ${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1.d ${OBJECTDIR}/nbproject/private/main.p1.d ${OBJECTDIR}/nbproject/private/hal_Usart.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/nbproject/private/gpio.p1 ${OBJECTDIR}/nbproject/private/ADC.p1 ${OBJECTDIR}/nbproject/private/triac.p1 ${OBJECTDIR}/nbproject/private/message.p1 ${OBJECTDIR}/nbproject/private/parameter.p1 ${OBJECTDIR}/nbproject/private/KeyState.p1 ${OBJECTDIR}/nbproject/private/delay.p1 ${OBJECTDIR}/nbproject/private/timer.p1 ${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1 ${OBJECTDIR}/nbproject/private/main.p1 ${OBJECTDIR}/nbproject/private/hal_Usart.p1

# Source Files
SOURCEFILES=nbproject/private/gpio.c nbproject/private/ADC.c nbproject/private/triac.c nbproject/private/message.c nbproject/private/parameter.c nbproject/private/KeyState.c nbproject/private/delay.c nbproject/private/timer.c nbproject/private/pic18f67xx_it.c nbproject/private/main.c nbproject/private/hal_Usart.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/HalfWave_Test.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F67K22
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/nbproject/private/gpio.p1: nbproject/private/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/gpio.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/gpio.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/gpio.p1  nbproject/private/gpio.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/gpio.d ${OBJECTDIR}/nbproject/private/gpio.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/gpio.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/ADC.p1: nbproject/private/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/ADC.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/ADC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/ADC.p1  nbproject/private/ADC.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/ADC.d ${OBJECTDIR}/nbproject/private/ADC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/ADC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/triac.p1: nbproject/private/triac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/triac.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/triac.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/triac.p1  nbproject/private/triac.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/triac.d ${OBJECTDIR}/nbproject/private/triac.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/triac.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/message.p1: nbproject/private/message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/message.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/message.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/message.p1  nbproject/private/message.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/message.d ${OBJECTDIR}/nbproject/private/message.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/message.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/parameter.p1: nbproject/private/parameter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/parameter.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/parameter.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/parameter.p1  nbproject/private/parameter.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/parameter.d ${OBJECTDIR}/nbproject/private/parameter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/parameter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/KeyState.p1: nbproject/private/KeyState.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/KeyState.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/KeyState.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/KeyState.p1  nbproject/private/KeyState.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/KeyState.d ${OBJECTDIR}/nbproject/private/KeyState.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/KeyState.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/delay.p1: nbproject/private/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/delay.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/delay.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/delay.p1  nbproject/private/delay.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/delay.d ${OBJECTDIR}/nbproject/private/delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/timer.p1: nbproject/private/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/timer.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/timer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/timer.p1  nbproject/private/timer.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/timer.d ${OBJECTDIR}/nbproject/private/timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1: nbproject/private/pic18f67xx_it.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1  nbproject/private/pic18f67xx_it.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/pic18f67xx_it.d ${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/main.p1: nbproject/private/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/main.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/main.p1  nbproject/private/main.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/main.d ${OBJECTDIR}/nbproject/private/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/hal_Usart.p1: nbproject/private/hal_Usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/hal_Usart.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/hal_Usart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/hal_Usart.p1  nbproject/private/hal_Usart.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/hal_Usart.d ${OBJECTDIR}/nbproject/private/hal_Usart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/hal_Usart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/nbproject/private/gpio.p1: nbproject/private/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/gpio.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/gpio.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/gpio.p1  nbproject/private/gpio.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/gpio.d ${OBJECTDIR}/nbproject/private/gpio.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/gpio.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/ADC.p1: nbproject/private/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/ADC.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/ADC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/ADC.p1  nbproject/private/ADC.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/ADC.d ${OBJECTDIR}/nbproject/private/ADC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/ADC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/triac.p1: nbproject/private/triac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/triac.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/triac.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/triac.p1  nbproject/private/triac.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/triac.d ${OBJECTDIR}/nbproject/private/triac.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/triac.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/message.p1: nbproject/private/message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/message.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/message.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/message.p1  nbproject/private/message.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/message.d ${OBJECTDIR}/nbproject/private/message.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/message.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/parameter.p1: nbproject/private/parameter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/parameter.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/parameter.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/parameter.p1  nbproject/private/parameter.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/parameter.d ${OBJECTDIR}/nbproject/private/parameter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/parameter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/KeyState.p1: nbproject/private/KeyState.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/KeyState.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/KeyState.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/KeyState.p1  nbproject/private/KeyState.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/KeyState.d ${OBJECTDIR}/nbproject/private/KeyState.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/KeyState.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/delay.p1: nbproject/private/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/delay.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/delay.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/delay.p1  nbproject/private/delay.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/delay.d ${OBJECTDIR}/nbproject/private/delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/timer.p1: nbproject/private/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/timer.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/timer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/timer.p1  nbproject/private/timer.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/timer.d ${OBJECTDIR}/nbproject/private/timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1: nbproject/private/pic18f67xx_it.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1  nbproject/private/pic18f67xx_it.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/pic18f67xx_it.d ${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/pic18f67xx_it.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/main.p1: nbproject/private/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/main.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/main.p1  nbproject/private/main.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/main.d ${OBJECTDIR}/nbproject/private/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/nbproject/private/hal_Usart.p1: nbproject/private/hal_Usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/nbproject/private" 
	@${RM} ${OBJECTDIR}/nbproject/private/hal_Usart.p1.d 
	@${RM} ${OBJECTDIR}/nbproject/private/hal_Usart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/nbproject/private/hal_Usart.p1  nbproject/private/hal_Usart.c 
	@-${MV} ${OBJECTDIR}/nbproject/private/hal_Usart.d ${OBJECTDIR}/nbproject/private/hal_Usart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/nbproject/private/hal_Usart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/HalfWave_Test.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/HalfWave_Test.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"       --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/HalfWave_Test.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/HalfWave_Test.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/HalfWave_Test.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/HalfWave_Test.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/HalfWave_Test.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
