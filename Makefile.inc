mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
	ScenarioWalker.o \
	ScenarioReader.o \
	ScenarioParams.o \
	Monitor.o \
	Uptime.o \
	LineMonitor.o \
	PoseEstimator.o \
	Detector.o \
	Starter.o \
	Timer.o \
	ColorDetector.o \
	SwitchEdgeDetector.o \
	Walker.o \
	StayInPlace.o \
	LineWalker.o \
	SampleWalker.o \
	Driver.o \
	Diagnostics.o

APPL_COBJS += \
	mjson.o \

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIRS += \
	$(mkfile_path)app \
	$(mkfile_path)monitor \
	$(mkfile_path)detector \
	$(mkfile_path)walker \
	$(mkfile_path)mjson/src

INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)monitor \
	-I$(mkfile_path)detector \
	-I$(mkfile_path)walker \
	-I$(mkfile_path)mjson/src \
