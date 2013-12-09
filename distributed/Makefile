################################################################################
#
# Copyright 1993-2013 NVIDIA Corporation.  All rights reserved.
#
# NOTICE TO USER:   
#
# This source code is subject to NVIDIA ownership rights under U.S. and 
# international Copyright laws.  
#
# NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE 
# CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR 
# IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH 
# REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF 
# MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.   
# IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, 
# OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS 
# OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE 
# OR PERFORMANCE OF THIS SOURCE CODE.  
#
# U.S. Government End Users.  This source code is a "commercial item" as 
# that term is defined at 48 C.F.R. 2.101 (OCT 1995), consisting  of 
# "commercial computer software" and "commercial computer software 
# documentation" as such terms are used in 48 C.F.R. 12.212 (SEPT 1995) 
# and is provided to the U.S. Government only as a commercial end item.  
# Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through 
# 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the 
# source code with only those rights set forth herein.
#
################################################################################
#
# Makefile project only supported on Mac OS X and Linux Platforms)
#
################################################################################

include ./findcudalib.mk

# Location of the CUDA Toolkit
CUDA_PATH       ?= /usr/local/cuda-5.5

# internal flags
NVCCFLAGS   := -m${OS_SIZE}
CCFLAGS     := -O3
NVCCLDFLAGS :=
LDFLAGS     :=

# Extra user flags
EXTRA_NVCCFLAGS   ?=
EXTRA_NVCCLDFLAGS ?=
EXTRA_LDFLAGS     ?=
EXTRA_CCFLAGS     ?=

# OS-specific build flags
ifneq ($(DARWIN),) 
  LDFLAGS += -Xlinker -rpath $(CUDA_PATH)/lib
  CCFLAGS += -arch $(OS_ARCH) $(STDLIB)  
else
  ifeq ($(OS_ARCH),armv7l)
    ifeq ($(abi),gnueabi)
      CCFLAGS += -mfloat-abi=softfp
    else
      # default to gnueabihf
      override abi := gnueabihf
      LDFLAGS += --dynamic-linker=/lib/ld-linux-armhf.so.3
      CCFLAGS += -mfloat-abi=hard
    endif
  endif
endif

ifeq ($(ARMv7),1)
NVCCFLAGS += -target-cpu-arch ARM
ifneq ($(TARGET_FS),) 
CCFLAGS += --sysroot=$(TARGET_FS)
LDFLAGS += --sysroot=$(TARGET_FS)
LDFLAGS += -rpath-link=$(TARGET_FS)/lib
LDFLAGS += -rpath-link=$(TARGET_FS)/usr/lib
LDFLAGS += -rpath-link=$(TARGET_FS)/usr/lib/arm-linux-$(abi)
endif
endif

# Debug build flags
ifeq ($(dbg),1)
      NVCCFLAGS += -g -G
      TARGET := debug
else
      TARGET := release
endif

ALL_CCFLAGS :=
ALL_CCFLAGS += $(NVCCFLAGS)
ALL_CCFLAGS += $(addprefix -Xcompiler ,$(CCFLAGS))
ALL_CCFLAGS += $(EXTRA_NVCCFLAGS)
ALL_CCFLAGS += $(addprefix -Xcompiler ,$(EXTRA_CCFLAGS))

ALL_LDFLAGS :=
ALL_LDFLAGS += $(ALL_CCFLAGS)
ALL_LDFLAGS += $(NVCCLDFLAGS)
ALL_LDFLAGS += $(addprefix -Xlinker ,$(LDFLAGS))
ALL_LDFLAGS += $(EXTRA_NVCCLDFLAGS)
ALL_LDFLAGS += $(addprefix -Xlinker ,$(EXTRA_LDFLAGS))

# Common includes and paths for CUDA
INCLUDES  := -I/usr/local/cuda/common/inc
LIBRARIES :=

################################################################################

# MPI check and binaries
MPICXX ?= $(shell which mpicxx)
EXEC   ?=

ifneq ($(shell uname -m | sed -e "s/i386/i686/"), ${OS_ARCH})
      $(info -----------------------------------------------------------------------------------------------)
      $(info WARNING - MPI not supported when cross compiling.)
      MPICXX :=
endif

ifeq ($(MPICXX),)
      $(info -----------------------------------------------------------------------------------------------)
      $(info WARNING - No MPI compiler found.)
      $(info -----------------------------------------------------------------------------------------------)
      $(info   CUDA Sample "Main" cannot be built without an MPI Compiler.)
      $(info   This will be a dry-run of the Makefile.)
      $(info   For more information on how to set up your environment to build and run this )
      $(info   sample, please refer the CUDA Samples documentation and release notes)
      $(info -----------------------------------------------------------------------------------------------)
      MPICXX=mpicxx
      EXEC=@echo "[@]"
endif

# CUDA code generation flags
ifneq ($(OS_ARCH),armv7l)
GENCODE_SM10    := -gencode arch=compute_10,code=sm_10
endif
GENCODE_SM20    := -gencode arch=compute_20,code=sm_20
GENCODE_SM30    := -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=\"sm_35,compute_35\"
GENCODE_FLAGS   := $(GENCODE_SM10) $(GENCODE_SM20) $(GENCODE_SM30)

LIBSIZE := 
ifeq ($(DARWIN),)
ifeq ($(OS_SIZE),64)
LIBSIZE := 64
endif
endif

LIBRARIES += -L$(CUDA_PATH)/lib${LIBSIZE} -lcudart

################################################################################

# Target rules
all: build

build: Main

#VectorAdd_cuda.o: VectorAdd.cu
#	$(EXEC) $(NVCC) $(INCLUDES) $(ALL_CCFLAGS) $(GENCODE_FLAGS) -o $@ -c $<

Main.o: Main.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

OBJReader.o: OBJReader.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

Mesh.o: Mesh.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

MeshData.o: MeshData.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

BoundingBox.o: BoundingBox.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

Face.o: Face.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

Camera.o: Camera.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

Raytracer.o: Raytracer.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

Ray.o: Ray.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

Image.o: Image.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

Triangle.o: Triangle.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

Material.o: Material.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

MTLReader.o: MTLReader.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

Utilities.o: Utilities.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

RaytracerObject.o: RaytracerObject.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

MeshBVH.o: MeshBVH.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

MeshBVHNode.o: MeshBVHNode.cpp
	$(EXEC) $(MPICXX) $(CCFLAGS) $(INCLUDES) -o $@ -c $<

Main: Main.o OBJReader.o Mesh.o MeshData.o BoundingBox.o Face.o Camera.o Raytracer.o Ray.o Image.o Triangle.o  Material.o MTLReader.o Utilities.o RaytracerObject.o MeshBVH.o MeshBVHNode.o
	$(EXEC) $(MPICXX) $(CCFLAGS) $(LDFLAGS) -o $@ $+ $(LIBRARIES)
	$(EXEC) mkdir -p ../../bin/$(OS_ARCH)/$(OSLOWER)/$(TARGET)$(if $(abi),/$(abi))
	$(EXEC) cp $@ ../../bin/$(OS_ARCH)/$(OSLOWER)/$(TARGET)$(if $(abi),/$(abi))

run: build
	$(EXEC) ./Main

clean:
	$(EXEC) rm -f Main.o OBJReader.o Mesh.o MeshData.o BoundingBox.o Face.o Camera.o Raytracer.o Ray.o Image.o Triangle.o  Material.o MTLReader.o Utilities.o RaytracerObject.o MeshBVH.o MeshBVHNode.o
	$(EXEC) rm -rf ../../bin/$(OS_ARCH)/$(OSLOWER)/$(TARGET)$(if $(abi),/$(abi))/Main

clobber: clean

