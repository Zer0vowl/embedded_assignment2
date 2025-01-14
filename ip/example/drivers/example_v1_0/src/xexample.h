// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XEXAMPLE_H
#define XEXAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xexample_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Axi_cpu_BaseAddress;
} XExample_Config;
#endif

typedef struct {
    u64 Axi_cpu_BaseAddress;
    u32 IsReady;
} XExample;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XExample_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XExample_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XExample_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XExample_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XExample_Initialize(XExample *InstancePtr, u16 DeviceId);
XExample_Config* XExample_LookupConfig(u16 DeviceId);
int XExample_CfgInitialize(XExample *InstancePtr, XExample_Config *ConfigPtr);
#else
int XExample_Initialize(XExample *InstancePtr, const char* InstanceName);
int XExample_Release(XExample *InstancePtr);
#endif

void XExample_Start(XExample *InstancePtr);
u32 XExample_IsDone(XExample *InstancePtr);
u32 XExample_IsIdle(XExample *InstancePtr);
u32 XExample_IsReady(XExample *InstancePtr);
void XExample_EnableAutoRestart(XExample *InstancePtr);
void XExample_DisableAutoRestart(XExample *InstancePtr);

u32 XExample_Get_in1_BaseAddress(XExample *InstancePtr);
u32 XExample_Get_in1_HighAddress(XExample *InstancePtr);
u32 XExample_Get_in1_TotalBytes(XExample *InstancePtr);
u32 XExample_Get_in1_BitWidth(XExample *InstancePtr);
u32 XExample_Get_in1_Depth(XExample *InstancePtr);
u32 XExample_Write_in1_Words(XExample *InstancePtr, int offset, word_type *data, int length);
u32 XExample_Read_in1_Words(XExample *InstancePtr, int offset, word_type *data, int length);
u32 XExample_Write_in1_Bytes(XExample *InstancePtr, int offset, char *data, int length);
u32 XExample_Read_in1_Bytes(XExample *InstancePtr, int offset, char *data, int length);
u32 XExample_Get_in2_BaseAddress(XExample *InstancePtr);
u32 XExample_Get_in2_HighAddress(XExample *InstancePtr);
u32 XExample_Get_in2_TotalBytes(XExample *InstancePtr);
u32 XExample_Get_in2_BitWidth(XExample *InstancePtr);
u32 XExample_Get_in2_Depth(XExample *InstancePtr);
u32 XExample_Write_in2_Words(XExample *InstancePtr, int offset, word_type *data, int length);
u32 XExample_Read_in2_Words(XExample *InstancePtr, int offset, word_type *data, int length);
u32 XExample_Write_in2_Bytes(XExample *InstancePtr, int offset, char *data, int length);
u32 XExample_Read_in2_Bytes(XExample *InstancePtr, int offset, char *data, int length);
u32 XExample_Get_out_r_BaseAddress(XExample *InstancePtr);
u32 XExample_Get_out_r_HighAddress(XExample *InstancePtr);
u32 XExample_Get_out_r_TotalBytes(XExample *InstancePtr);
u32 XExample_Get_out_r_BitWidth(XExample *InstancePtr);
u32 XExample_Get_out_r_Depth(XExample *InstancePtr);
u32 XExample_Write_out_r_Words(XExample *InstancePtr, int offset, word_type *data, int length);
u32 XExample_Read_out_r_Words(XExample *InstancePtr, int offset, word_type *data, int length);
u32 XExample_Write_out_r_Bytes(XExample *InstancePtr, int offset, char *data, int length);
u32 XExample_Read_out_r_Bytes(XExample *InstancePtr, int offset, char *data, int length);

void XExample_InterruptGlobalEnable(XExample *InstancePtr);
void XExample_InterruptGlobalDisable(XExample *InstancePtr);
void XExample_InterruptEnable(XExample *InstancePtr, u32 Mask);
void XExample_InterruptDisable(XExample *InstancePtr, u32 Mask);
void XExample_InterruptClear(XExample *InstancePtr, u32 Mask);
u32 XExample_InterruptGetEnabled(XExample *InstancePtr);
u32 XExample_InterruptGetStatus(XExample *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
