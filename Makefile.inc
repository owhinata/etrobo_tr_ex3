mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
	Walker.o \
	LineTracer.o \
	Scenario.o \
	ScenarioTracer.o \
	RandomWalker.o \
	LineMonitor.o \
	Starter.o \
	SimpleTimer.o \
	Diagnostics.o \
	Control.o \
	etrobo_control.grpc.pb.o \
	etrobo_control.pb.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION
	ifeq ($(TARGET),raspi_gcc)
		APPL_LIBS += -lhiredis -lprotobuf -lgrpc++ -lpthread\
									-Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
									-ldl
	endif

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIRS += $(mkfile_path)app $(mkfile_path)unit

INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)unit
