#pragma once


#define ulong unsigned long
#define ulonglong unsigned long long
#define longlong long long
#define ULONG unsigned long
#define ULONGLONG unsigned long long
#define ushort unsigned short
#define USHORT unsigned short
#define uchar unsigned char
#define UCHAR unsigned char


typedef struct _UNICODE_STRING
{
	unsigned short Length;
	unsigned short MaxLength;
	unsigned long Pad;
	wchar_t* Buffer;
}UNICODE_STRING;



//Size 0x128
struct _SYSTEM_MODULE
{
	ulonglong Pad0;//at 0x0
	ulonglong Pad1;//at 0x8
	void* ImageBase;//at 0x10
	ulong SizeOfImage;//at 0x18
	ulong Flags;//at 0x1C
	ushort Index;//at 0x20
	ushort bUserMode;//at 0x22,0 kernelmodule,sameas Index user
	ushort LoadCount;//at 0x24
	ushort BaseNameOffset;//at 0x26
	unsigned char FullDllName[0x100];//at 0x28
};



struct _SYSTEM_MODULE_LIST
{
	ulong NumberOfModules;
	ulong Pad;
	_SYSTEM_MODULE Module[1];
};





//Size 0x140
struct _SYSTEM_MODULE_EX
{
	ushort Size;//at 0x0
	ushort Pad0;//at 0x2
	ulong Pad1;//at 0x4
	ulonglong Pad2;//at 0x8
	ulonglong AlwaysZero;//at 0x10
	void* ImageBase;//at 0x18
	ulong SizeOfImage;//at 0x20
	ulong Flags;//at 0x24
	ushort Index;//at 0x28
	ushort bUserMode;//at 0x2A,0 kernelmodule,sameas Index user
	ushort LoadCount;//at 0x2C
	ushort BaseNameOffset;//at 0x2E
	unsigned char FullDllName[0x100];//at 0x30
	ulong CheckSum;//at 0x130
	ulong PadZero0;//at 0x134
	ulonglong PadZero1;//at 0x138
};


struct _CLIENT_ID
{
	ulonglong UniqueProcess;
	ulonglong UniqueThread;
};

//------------------------------------------------------------------------

//Size 0x50
struct _SYSTEM_THREAD_INFORMATION
{
	ulonglong ApcTime;//at 0x0
	ulonglong UserTime;//at 0x8
	ulonglong CreateTime;//at 0x10
	ulong WaitTime;//at 0x18
	ulong Pad;//at 0x1C
	ulonglong StartAddress;//at 0x20
	_CLIENT_ID CID;//at 0x28
	ulong Priority;//at 0x38
	ulong BasePriority;//at 0x3C
	ulong ContextSwitches;//at 0x40
	ulong ThreadState;//at 0x44
	ulong WaitReason;//at 0x48
	ulong Pad1;//at 0x4C
};

//size 0x88
struct _SYSTEM_THREAD_INFORMATION_EX
{
	ulonglong ApcTime;//at 0x0
	ulonglong UserTime;//at 0x8
	ulonglong CreateTime;//at 0x10
	ulong WaitTime;//at 0x18
	ulong Pad;//at 0x1C
	ulonglong StartAddress;//at 0x20
	_CLIENT_ID CID;//at 0x28
	ulong Priority;//at 0x38
	ulong BasePriority;//at 0x3C
	ulong ContextSwitches;//at 0x40
	ulong ThreadState;//at 0x44
	ulong WaitReason;//at 0x48
	ulong Pad1;//at 0x4C
	ulonglong StackBase;//at 0x50
	ulonglong StackLimit;//at 0x58
	ulonglong Win32StartAddress;//at 0x60
	ulonglong Teb;//at 0x68
	ulonglong Zero0;//at 0x70
	ulonglong Zero1;//at 0x78
	ulonglong Zero2;//at 0x80

};

typedef struct _SYSTEM_PROCESS_INFORMATION {
  ULONG                   NextEntryOffset; //at 0x0
  ULONG                   NumberOfThreads; //at 0x4
  ULONGLONG					WorkingSetPrivateSize;//at 0x8
  ULONG HardFaultCount; //at 0x10
  ULONG					ActiveThreadsHighWatermark;//at 0x14
  ULONGLONG				CycleTime;//at 0x18
  ULONGLONG           CreateTime; //at 0x20
  ULONGLONG           UserTime;//at 0x28
  ULONGLONG           KernelTime;//at 0x30
  _UNICODE_STRING          ImageName;//at 0x38
  ULONG               BasePriority; //at 0x48
  ULONG PAD0;//at 0x4C
  ULONGLONG                  UniqueProcessId;//at 0x50
  ULONGLONG                  InheritedFromUniqueProcessId;//at 0x58
  ULONG HandleCount;//at 0x60
  ULONG SessionId;//at 0x64
  ULONGLONG UniqueProcessId_;//at 0x68
  ULONGLONG       PeakVirtualSize;//at 0x70
  ULONGLONG		  VirtualSize;//at 0x78
  ULONG			PageFaultCount;//at 0x80
  ULONG PAD1;//at 0x84
  ULONGLONG PeakWorkingSetSize;//at 0x88
  ULONGLONG WorkingSetSize;	   //at 0x90
  ULONGLONG ProcessQuotaPeak_1; //at 0x98
  ULONGLONG ProcessQuotaUsage_1;//at 0xA0
  ULONGLONG ProcessQuotaPeak_0; //at 0xA8
  ULONGLONG ProcessQuotaUsage_0;//at 0xB0
  ULONGLONG CommitCharge;//at 0xB8
  ULONGLONG CommitChargePeak;//at 0xC0
  ULONGLONG CommitCharge_;//at 0xC8
  ULONGLONG ReadOperationCount;//at 0xD0
  ULONGLONG WriteOperationCount;//at 0xD8
  ULONGLONG OtherOperationCount;//at 0xE0
  ULONGLONG ReadTransferCount;//at 0xE8
  ULONGLONG WriteTransferCount;//at 0xF0
  ULONGLONG OtherTransferCount;//at 0xF8
  _SYSTEM_THREAD_INFORMATION           Threads[1];//at 0x100
} SYSTEM_PROCESS_INFORMATION;


typedef struct _SYSTEM_PROCESS_INFORMATION_EX {
  ULONG                   NextEntryOffset; //at 0x0
  ULONG                   NumberOfThreads; //at 0x4
  ULONGLONG					WorkingSetPrivateSize;//at 0x8
  ULONG HardFaultCount; //at 0x10
  ULONG					ActiveThreadsHighWatermark;//at 0x14
  ULONGLONG				CycleTime;//at 0x18
  ULONGLONG           CreateTime; //at 0x20
  ULONGLONG           UserTime;//at 0x28
  ULONGLONG           KernelTime;//at 0x30
  _UNICODE_STRING          ImageName;//at 0x38
  ULONG               BasePriority; //at 0x48
  ULONG PAD0;//at 0x4C
  ULONGLONG                  UniqueProcessId;//at 0x50
  ULONGLONG                  InheritedFromUniqueProcessId;//at 0x58
  ULONG HandleCount;//at 0x60
  ULONG SessionId;//at 0x64
  ULONGLONG UniqueProcessId_;//at 0x68
  ULONGLONG       PeakVirtualSize;//at 0x70
  ULONGLONG		  VirtualSize;//at 0x78
  ULONG			PageFaultCount;//at 0x80
  ULONG PAD1;//at 0x84
  ULONGLONG PeakWorkingSetSize;//at 0x88
  ULONGLONG WorkingSetSize;	   //at 0x90
  ULONGLONG ProcessQuotaPeak_1; //at 0x98
  ULONGLONG ProcessQuotaUsage_1;//at 0xA0
  ULONGLONG ProcessQuotaPeak_0; //at 0xA8
  ULONGLONG ProcessQuotaUsage_0;//at 0xB0
  ULONGLONG CommitCharge;//at 0xB8
  ULONGLONG CommitChargePeak;//at 0xC0
  ULONGLONG CommitCharge_;//at 0xC8
  ULONGLONG ReadOperationCount;//at 0xD0
  ULONGLONG WriteOperationCount;//at 0xD8
  ULONGLONG OtherOperationCount;//at 0xE0
  ULONGLONG ReadTransferCount;//at 0xE8
  ULONGLONG WriteTransferCount;//at 0xF0
  ULONGLONG OtherTransferCount;//at 0xF8
  _SYSTEM_THREAD_INFORMATION_EX           Threads[1];//at 0x100
} _SYSTEM_PROCESS_INFORMATION_EX;
//----------------------
struct _SESSION_PROCESS_INFO
{
	ulong SessionId;//at 0x0
	ulong OutputBufferLength;//at 0x4
	_SYSTEM_PROCESS_INFORMATION* OutputBuffer;//at 0x8
};


//------------------------

//size 0x18
struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO
{
	USHORT 	UniqueProcessId;//at 0x0
	USHORT 	CreatorBackTraceIndex;//at 0x2
	UCHAR 	ObjectTypeIndex;//at 0x4
	UCHAR 	HandleAttributes;//at 0x5
	USHORT 	HandleValue;//at 0x6
	PVOID 	Object;//at 0x8
	ULONG 	GrantedAccess;//at 0x10
	ULONG 	Pad;//at 0x14
};


//Size at least 0x20
struct _SYSTEM_HANDLE_TABLE
{
	ulong Count;//at 0x0
	ulong Pad;//at 0x4
	_SYSTEM_HANDLE_TABLE_ENTRY_INFO Entry[1];//multiple
};



//------------------------

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX
{
	  void* Object;
	  ulonglong UniqueProcessId;
	  HANDLE HandleValue;
	  ulong GrantedAccess;
	  ushort CreatorBackTraceIndex;
	  ushort ObjectTypeIndex;
	  ulong HandleAttributes;
	  ulong Reserved;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO_EX;
  
typedef struct _SYSTEM_HANDLE_INFORMATION_EX
{
  ulonglong NumberOfHandles;
  ulonglong Reserved;
  SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX Handles[1];
} SYSTEM_HANDLE_INFORMATION_EX, *PSYSTEM_HANDLE_INFORMATION_EX;


//------------------------
//size 0x50	
struct _SYSTEM_OBJECT_INFORMATION_OBJECT
{
	ulong Offset;//at 0x0
	ulong Pad0;//at 0x4
	void* pObject;//at 0x8
	ulonglong CreatorUniqueProcess;//at 0x10, taken from _OBJECT_HEADER_CREATOR_INFO
	ushort CreatorBackTraceIndex;//at 0x18, taken from _OBJECT_HEADER_CREATOR_INFO
	ushort Flags;//at 0x1A, taken from _OBJECT_HEADER
	ulong PointerCount;//at 0x1C, taken from _OBJECT_HEADER
	ulong HandleCount;//at 0x20, taken from _OBJECT_HEADER
	ulong PagedPoolCharge;//at 0x24, taken from _OBJECT_HEADER or _OBJECT_TYPE
	ulong NonPagedPoolCharge;//at 0x28, taken from _OBJECT_HEADER or _OBJECT_TYPE
	ulong Pad1;//at 0x2C
	ulonglong ExclusiveProcessId;//at 0x30, taken from _OBJECT_HEADER_PROCESS_INFO
	void* pSecurityDescriptor;//at 0x38, taken from _OBJECT_HEADER
	_UNICODE_STRING Name;//at 0x40
};


//size at least 0x40
struct _SYSTEM_OBJECT_INFORMATION 
{
	ulong NextOffset;//at 0x0
	ulong TotalNumberOfObjects;//at 0x4, taken from _OBJECT_TYPE
	ulong TotalNumberOfHandles;//at 0x8, taken from _OBJECT_TYPE
	ulong Index;//at 0xC, TypeIndex into ObTypeIndexTable, taken from _OBJECT_TYPE
	ulong InvalidAttributes;//at 0x10, taken from _OBJECT_TYPE
	_GENERIC_MAPPING GenericMapping;//at 0x14, taken from _OBJECT_TYPE
	ulong ValidAccessMask;//at 0x24, taken from _OBJECT_TYPE
	ulong PoolType;//at 0x28, taken from _OBJECT_TYPE
	ulong bSecurityRequired;//at 0x2C, taken from _OBJECT_TYPE
	_UNICODE_STRING Name;//at 0x30, taken from _OBJECT_TYPE
	//wide char here
};

//------------------------
typedef struct _SYSTEM_BIGPOOL_ENTRY 
{
	union
	{
		PVOID VirtualAddress;
		ULONG_PTR NonPaged : 1;
	};
	ulonglong SizeInBytes;
	union 
	{
		uchar Tag[4];
		ulong TagUlong;
	};
} SYSTEM_BIGPOOL_ENTRY, *PSYSTEM_BIGPOOL_ENTRY;


typedef struct _SYSTEM_BIGPOOL_INFORMATION
{
	ulong Count;
	SYSTEM_BIGPOOL_ENTRY AllocatedInfo[1];
} SYSTEM_BIGPOOL_INFORMATION, *PSYSTEM_BIGPOOL_INFORMATION;

//------------------------

struct _BIGPOOL_SESSION_INFO_INPUT
{
	ulong SessionId;
	ulong InfoSize;
	void* pInfo;
};


typedef struct _SESSION_BIGPOOL_INFORMATION
{
	ulong NextOffset;
	ulong Pad;
	ulong SessionId;
	ulong Count;
	SYSTEM_BIGPOOL_ENTRY AllocatedInfo[1];
} SESSION_BIGPOOL_INFORMATION, *PSESSION_BIGPOOL_INFORMATION;

//------------------------

#define PROCESS_HANDLE_TRACING_MAX_STACKS 16


typedef struct _PROCESS_HANDLE_TRACING_ENTRY
{
	HANDLE Handle;
	_CLIENT_ID ClientId;
	ULONG Type;
	void* Stacks[PROCESS_HANDLE_TRACING_MAX_STACKS];
} PROCESS_HANDLE_TRACING_ENTRY, *PPROCESS_HANDLE_TRACING_ENTRY;

typedef struct _PROCESS_HANDLE_TRACING_QUERY {
	HANDLE Handle;
	ULONG  TotalTraces;
	PROCESS_HANDLE_TRACING_ENTRY HandleTrace[1];
} PROCESS_HANDLE_TRACING_QUERY, *PPROCESS_HANDLE_TRACING_QUERY;


typedef struct _PROCESS_HANDLE_TRACING_ENABLE {
	ULONG Flags;
} PROCESS_HANDLE_TRACING_ENABLE, *PPROCESS_HANDLE_TRACING_ENABLE;


//------------------------
typedef struct _PSAPI_WS_WATCH_INFORMATION {
  ulonglong FaultingPc;
  ulonglong FaultingVa;
} PSAPI_WS_WATCH_INFORMATION, *PPSAPI_WS_WATCH_INFORMATION;
//------------------------

#define STATUS_UNSUCCESSFUL		0xC0000001
#define STATUS_NOT_IMPLEMENTED		   0xC0000002
#define STATUS_INVALID_INFO_CLASS 0xC0000003
#define STATUS_INFO_LENGTH_MISMATCH    0xC0000004

#define STATUS_INVALID_PARAMETER   0xC000000D
#define STATUS_ACCESS_DENIED 0xC0000022
#define STATUS_BUFFER_TOO_SMALL 0xC0000023


#define SystemProcessInformation 0x5
#define SystemLocksInformation 0xC
#define SystemHandleInformation 0x10
#define SystemObjectInformation 0x11
#define SystemModuleInformation 0xB
#define SystemLoadedModuleInformation 0xB
#define SystemModuleInformationEx 0x4D
#define SystemSessionProcessInformation 0x35
#define SystemExtendedProcessInformation 0x39
#define SystemExtendedHandleInformation 0x40
#define SystemBigPoolInformation 0x42
#define SystemSessionBigPoolInformation 0x7D
#define SystemMemoryListInformation 80

#define ProcessHandleTracing 0x20
#define ProcessWorkingSetWatch 0xF
#define ProcessWorkingSetWatchEx 0x2A

extern "C"
{
	int ZwQuerySystemInformation(int InfoClass,void* OutputBuffer,ulong OutputBufferLength,ulong* pReturnedLength);

	int ZwSetInformationProcess(HANDLE ProcessHandle, 
							ulonglong ProcessInformationClass,  
							void* ProcessInformation, 
							ulonglong ProcessInformationLength);

	int ZwQueryInformationProcess(HANDLE ProcessHandle,
						ulonglong ProcessInformationClass,
						void* ProcessInformation,
						ulonglong ProcessInformationLength,
						ulonglong* ReturnLength );

	int ZwClose(HANDLE Handle);

}


void DumpHex(const void* data, size_t size);


void Leak0();
void Leak1();
void Leak2();
void Leak3();
void Leak4();
void Leak5();
void Leak6();
void Leak7();
void Leak8();
void Leak9();

void LeakA();
void LeakB();
void LeakC();
void LeakD();