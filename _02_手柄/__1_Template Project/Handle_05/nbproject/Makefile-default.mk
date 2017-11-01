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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Handle_05.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Handle_05.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=_01_USER/main.c _01_USER/My_Delay.c _01_USER/Key.c _01_USER/My_USART.c _01_USER/My_Timer.c _01_USER/GPIO.c _01_USER/TM1640.c _01_USER/My_ADC.c _01_USER/Run.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_01_USER/main.p1 ${OBJECTDIR}/_01_USER/My_Delay.p1 ${OBJECTDIR}/_01_USER/Key.p1 ${OBJECTDIR}/_01_USER/My_USART.p1 ${OBJECTDIR}/_01_USER/My_Timer.p1 ${OBJECTDIR}/_01_USER/GPIO.p1 ${OBJECTDIR}/_01_USER/TM1640.p1 ${OBJECTDIR}/_01_USER/My_ADC.p1 ${OBJECTDIR}/_01_USER/Run.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_01_USER/main.p1.d ${OBJECTDIR}/_01_USER/My_Delay.p1.d ${OBJECTDIR}/_01_USER/Key.p1.d ${OBJECTDIR}/_01_USER/My_USART.p1.d ${OBJECTDIR}/_01_USER/My_Timer.p1.d ${OBJECTDIR}/_01_USER/GPIO.p1.d ${OBJECTDIR}/_01_USER/TM1640.p1.d ${OBJECTDIR}/_01_USER/My_ADC.p1.d ${OBJECTDIR}/_01_USER/Run.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_01_USER/main.p1 ${OBJECTDIR}/_01_USER/My_Delay.p1 ${OBJECTDIR}/_01_USER/Key.p1 ${OBJECTDIR}/_01_USER/My_USART.p1 ${OBJECTDIR}/_01_USER/My_Timer.p1 ${OBJECTDIR}/_01_USER/GPIO.p1 ${OBJECTDIR}/_01_USER/TM1640.p1 ${OBJECTDIR}/_01_USER/My_ADC.p1 ${OBJECTDIR}/_01_USER/Run.p1

# Source Files
SOURCEFILES=_01_USER/main.c _01_USER/My_Delay.c _01_USER/Key.c _01_USER/My_USART.c _01_USER/My_Timer.c _01_USER/GPIO.c _01_USER/TM1640.c _01_USER/My_ADC.c _01_USER/Run.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Handle_05.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F67K22
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_01_USER/main.p1: _01_USER/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/main.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/main.p1  _01_USER/main.c 
	@-${MV} ${OBJECTDIR}/_01_USER/main.d ${OBJECTDIR}/_01_USER/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/My_Delay.p1: _01_USER/My_Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/My_Delay.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/My_Delay.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/My_Delay.p1  _01_USER/My_Delay.c 
	@-${MV} ${OBJECTDIR}/_01_USER/My_Delay.d ${OBJECTDIR}/_01_USER/My_Delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/My_Delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/Key.p1: _01_USER/Key.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/Key.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/Key.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/Key.p1  _01_USER/Key.c 
	@-${MV} ${OBJECTDIR}/_01_USER/Key.d ${OBJECTDIR}/_01_USER/Key.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/Key.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/My_USART.p1: _01_USER/My_USART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/My_USART.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/My_USART.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/My_USART.p1  _01_USER/My_USART.c 
	@-${MV} ${OBJECTDIR}/_01_USER/My_USART.d ${OBJECTDIR}/_01_USER/My_USART.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/My_USART.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/My_Timer.p1: _01_USER/My_Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/My_Timer.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/My_Timer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/My_Timer.p1  _01_USER/My_Timer.c 
	@-${MV} ${OBJECTDIR}/_01_USER/My_Timer.d ${OBJECTDIR}/_01_USER/My_Timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/My_Timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/GPIO.p1: _01_USER/GPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/GPIO.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/GPIO.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/GPIO.p1  _01_USER/GPIO.c 
	@-${MV} ${OBJECTDIR}/_01_USER/GPIO.d ${OBJECTDIR}/_01_USER/GPIO.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/GPIO.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/TM1640.p1: _01_USER/TM1640.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/TM1640.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/TM1640.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/TM1640.p1  _01_USER/TM1640.c 
	@-${MV} ${OBJECTDIR}/_01_USER/TM1640.d ${OBJECTDIR}/_01_USER/TM1640.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/TM1640.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/My_ADC.p1: _01_USER/My_ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/My_ADC.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/My_ADC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/My_ADC.p1  _01_USER/My_ADC.c 
	@-${MV} ${OBJECTDIR}/_01_USER/My_ADC.d ${OBJECTDIR}/_01_USER/My_ADC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/My_ADC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/Run.p1: _01_USER/Run.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/Run.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/Run.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/Run.p1  _01_USER/Run.c 
	@-${MV} ${OBJECTDIR}/_01_USER/Run.d ${OBJECTDIR}/_01_USER/Run.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/Run.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_01_USER/main.p1: _01_USER/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/main.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/main.p1  _01_USER/main.c 
	@-${MV} ${OBJECTDIR}/_01_USER/main.d ${OBJECTDIR}/_01_USER/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/My_Delay.p1: _01_USER/My_Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/My_Delay.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/My_Delay.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/My_Delay.p1  _01_USER/My_Delay.c 
	@-${MV} ${OBJECTDIR}/_01_USER/My_Delay.d ${OBJECTDIR}/_01_USER/My_Delay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/My_Delay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/Key.p1: _01_USER/Key.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/Key.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/Key.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/Key.p1  _01_USER/Key.c 
	@-${MV} ${OBJECTDIR}/_01_USER/Key.d ${OBJECTDIR}/_01_USER/Key.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/Key.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/My_USART.p1: _01_USER/My_USART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/My_USART.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/My_USART.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/My_USART.p1  _01_USER/My_USART.c 
	@-${MV} ${OBJECTDIR}/_01_USER/My_USART.d ${OBJECTDIR}/_01_USER/My_USART.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/My_USART.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/My_Timer.p1: _01_USER/My_Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/My_Timer.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/My_Timer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/My_Timer.p1  _01_USER/My_Timer.c 
	@-${MV} ${OBJECTDIR}/_01_USER/My_Timer.d ${OBJECTDIR}/_01_USER/My_Timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/My_Timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/GPIO.p1: _01_USER/GPIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/GPIO.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/GPIO.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/GPIO.p1  _01_USER/GPIO.c 
	@-${MV} ${OBJECTDIR}/_01_USER/GPIO.d ${OBJECTDIR}/_01_USER/GPIO.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/GPIO.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/TM1640.p1: _01_USER/TM1640.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/TM1640.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/TM1640.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/TM1640.p1  _01_USER/TM1640.c 
	@-${MV} ${OBJECTDIR}/_01_USER/TM1640.d ${OBJECTDIR}/_01_USER/TM1640.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/TM1640.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/My_ADC.p1: _01_USER/My_ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/My_ADC.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/My_ADC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/My_ADC.p1  _01_USER/My_ADC.c 
	@-${MV} ${OBJECTDIR}/_01_USER/My_ADC.d ${OBJECTDIR}/_01_USER/My_ADC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/My_ADC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_01_USER/Run.p1: _01_USER/Run.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_01_USER" 
	@${RM} ${OBJECTDIR}/_01_USER/Run.p1.d 
	@${RM} ${OBJECTDIR}/_01_USER/Run.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s" 每leanp1    -o${OBJECTDIR}/_01_USER/Run.p1  _01_USER/Run.c 
	@-${MV} ${OBJECTDIR}/_01_USER/Run.d ${OBJECTDIR}/_01_USER/Run.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_01_USER/Run.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Handle_05.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  F:/Program\ Files\ (x86)/Microchip/xc8/v1.34/lib/pic18-plib-c18-18f67k22.lpp  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/Handle_05.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"       --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/Handle_05.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    "F:\Program Files (x86)\Microchip\xc8\v1.34\lib\pic18-plib-c18-18f67k22.lpp" 
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/Handle_05.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Handle_05.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  F:/Program\ Files\ (x86)/Microchip/xc8/v1.34/lib/pic18-plib-c18-18f67k22.lpp 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/Handle_05.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/plib" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include/legacy" -I"F:/Program Files (x86)/Microchip/xc8/v1.34/include" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/Handle_05.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    "F:\Program Files (x86)\Microchip\xc8\v1.34\lib\pic18-plib-c18-18f67k22.lpp" 
	
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
