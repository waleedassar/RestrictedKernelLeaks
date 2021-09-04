#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "Header.h"



//SystemModuleInformation
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void Leak0()
{
	ulong Size = 0x1000;
	void* p = VirtualAlloc(0,Size,MEM_COMMIT,PAGE_READWRITE);
	if(p)
	{
		ulong ReturnedLength = 0;
		int ret = ZwQuerySystemInformation(SystemModuleInformation,p,Size,&ReturnedLength);
		printf("ZwQuerySystemInformation, ret: %X\r\n",ret);
		while(ret == STATUS_INFO_LENGTH_MISMATCH)
		{
			VirtualFree(p,0,MEM_RELEASE);
			Size += Size;
			p = VirtualAlloc(0,Size,MEM_COMMIT,PAGE_READWRITE);
			if(p)
			{
				ret = ZwQuerySystemInformation(SystemModuleInformation,p,Size,&ReturnedLength);
				printf("ZwQuerySystemInformation, ret: %X\r\n",ret);
			}
			else
			{
				printf("Error allocating memory\r\n");
				return;
			}
		}

		_SYSTEM_MODULE_LIST* pModList = (_SYSTEM_MODULE_LIST*)p;
		ulong NumModules = pModList->NumberOfModules;
		printf("Number Of Modules: %X\r\n",NumModules);

		if(NumModules)
		{
			_SYSTEM_MODULE* pCurrentMod = & pModList->Module[0];
			ulong i = 0;
			while(i<NumModules)
			{
				printf("Full Name: %s\r\n",pCurrentMod->FullDllName);

				printf("Pad0: %I64X\r\n",pCurrentMod->Pad0);
				printf("Pad1: %I64X\r\n",pCurrentMod->Pad1);
				printf("ImageBase: %I64X\r\n",pCurrentMod->ImageBase);
				printf("SizeOfImage: %X\r\n",pCurrentMod->SizeOfImage);
				printf("Flags: %X\r\n",pCurrentMod->Flags);
				printf("Index: %X\r\n",pCurrentMod->Index);
				printf("bUserMode: %X\r\n",pCurrentMod->bUserMode);
				printf("LoadCount: %X\r\n",pCurrentMod->LoadCount);
				
				printf("BaseNameOffset: %X\r\n",pCurrentMod->BaseNameOffset);

				printf("----------------------\r\n");

				pCurrentMod += 1;
				i++;
			}
		}

		VirtualFree(p,0,MEM_RELEASE);
	}
	return;
}



//-----------------------------



//SystemModuleInformationEx
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void Leak1()
{
	ulong Size = 0x1000;
	void* p = VirtualAlloc(0,Size,MEM_COMMIT,PAGE_READWRITE);
	ulong ReturnedLength = 0;

	if(p)
	{
		int ret = ZwQuerySystemInformation(SystemModuleInformationEx,p,Size,&ReturnedLength);
		printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",ret,ReturnedLength);


		if(ret == STATUS_INFO_LENGTH_MISMATCH)
		{
			VirtualFree(p,0,MEM_RELEASE);
			Size  = ReturnedLength;
			p = VirtualAlloc(0,Size,MEM_COMMIT,PAGE_READWRITE);
			if(p)
			{
				ret = ZwQuerySystemInformation(SystemModuleInformationEx,p,Size,&ReturnedLength);
				printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",ret,ReturnedLength);
			}
			else
			{
				printf("Error allocating memory\r\n");
				return;
			}
		}



		
		_SYSTEM_MODULE_EX* pMods = (_SYSTEM_MODULE_EX*)p;
		ulong SizeRead = 0;
		ulong NumModules = 0;

		while( (SizeRead+sizeof(_SYSTEM_MODULE_EX)) <= ReturnedLength)
		{
				printf("Full Name: %s\r\n",pMods->FullDllName);


				

				printf("Pad0: %I64X\r\n",pMods->Pad0);
				printf("Pad1: %I64X\r\n",pMods->Pad1);
				printf("Pad2: %I64X\r\n",pMods->Pad2);
				printf("AlwaysZero: %I64X\r\n",pMods->AlwaysZero);
				printf("ImageBase: %I64X\r\n",pMods->ImageBase);
				printf("SizeOfImage: %I64X\r\n",pMods->SizeOfImage);
				printf("Flags: %I64X\r\n",pMods->Flags);

				printf("Index: %I64X\r\n",pMods->Index);
				printf("bUserMode: %I64X\r\n",pMods->bUserMode);
				printf("LoadCount: %I64X\r\n",pMods->LoadCount);
				printf("BaseNameOffset: %I64X\r\n",pMods->BaseNameOffset);

				printf("CheckSum: %I64X\r\n",pMods->CheckSum);
				printf("PadZero0: %I64X\r\n",pMods->PadZero0);
				printf("PadZero1: %I64X\r\n",pMods->PadZero1);
				


				printf("----------------------\r\n");

				NumModules++;
				pMods++;
			    SizeRead += sizeof(_SYSTEM_MODULE_EX);
		}
		//printf("%X\r\n",SizeRead);
		//printf("%X\r\n",NumModules);
		//printf("%X\r\n",ReturnedLength);
		VirtualFree(p,0,MEM_RELEASE);
	}

	return;
}



//------------------


//SystemProcessInformation
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void Leak2()
{
	ulong Size = 0x1000;
	void* p = VirtualAlloc(0,Size,MEM_COMMIT,PAGE_READWRITE);
	ulong ReturnedLength = 0;

	if(p)
	{
		int ret = ZwQuerySystemInformation(SystemProcessInformation,p,Size,&ReturnedLength);
		printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",ret,ReturnedLength);


		if(ret == STATUS_INFO_LENGTH_MISMATCH)
		{
			VirtualFree(p,0,MEM_RELEASE);
			Size  = ReturnedLength;
			p = VirtualAlloc(0,Size,MEM_COMMIT,PAGE_READWRITE);
			if(p)
			{
				ret = ZwQuerySystemInformation(SystemProcessInformation,p,Size,&ReturnedLength);
				printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",ret,ReturnedLength);
			}
			else
			{
				printf("Error allocating memory\r\n");
				return;
			}
		}



	_SYSTEM_PROCESS_INFORMATION* pSysInfo = (_SYSTEM_PROCESS_INFORMATION*)p;
	unsigned long Offset = 0;
	while(Offset < ReturnedLength)
	{
		printf("Offset: %X\r\n",Offset);
		printf("ReturnedLength: %X\r\n",ReturnedLength);


		wprintf(L"Image Name: %s\r\n",pSysInfo->ImageName.Buffer);

		wprintf(L"Image Name / Length: %X\r\n",pSysInfo->ImageName.Length);
		wprintf(L"Image Name / MaxLength: %X\r\n",pSysInfo->ImageName.MaxLength);
		wprintf(L"Image Name / Pad: %X\r\n",pSysInfo->ImageName.Pad);
		wprintf(L"Image Name: %s\r\n",pSysInfo->ImageName.Buffer);

		printf("UniqueProcessId: %I64X\r\n",pSysInfo->UniqueProcessId);
		printf("UniqueProcessId_: %I64X\r\n",pSysInfo->UniqueProcessId_);
		printf("InheritedFromUniqueProcessId: %I64X\r\n",pSysInfo->InheritedFromUniqueProcessId);
		printf("NumberOfThreads: %I64X\r\n",pSysInfo->NumberOfThreads);
		printf("WorkingSetPrivateSize: %I64X\r\n",pSysInfo->WorkingSetPrivateSize);

		printf("HardFaultCount: %I64X\r\n",pSysInfo->HardFaultCount);
		printf("ActiveThreadsHighWatermark: %I64X\r\n",pSysInfo->ActiveThreadsHighWatermark);
		printf("CycleTime: %I64X\r\n",pSysInfo->CycleTime);
		printf("CreateTime: %I64X\r\n",pSysInfo->CreateTime);
		printf("UserTime: %I64X\r\n",pSysInfo->UserTime);
		printf("KernelTime: %I64X\r\n",pSysInfo->KernelTime);

		

		printf("BasePriority: %I64X\r\n",pSysInfo->BasePriority);
		printf("PAD0: %I64X\r\n",pSysInfo->PAD0);
		printf("HandleCount: %I64X\r\n",pSysInfo->HandleCount);
		printf("SessionId: %I64X\r\n",pSysInfo->SessionId);
		printf("PeakVirtualSize: %I64X\r\n",pSysInfo->PeakVirtualSize);
		printf("VirtualSize: %I64X\r\n",pSysInfo->VirtualSize);
		printf("PageFaultCount: %I64X\r\n",pSysInfo->PageFaultCount);
		printf("PAD1: %I64X\r\n",pSysInfo->PAD1);
		printf("PeakWorkingSetSize: %I64X\r\n",pSysInfo->PeakWorkingSetSize);
		printf("WorkingSetSize: %I64X\r\n",pSysInfo->WorkingSetSize);


		printf("ProcessQuotaPeak_1: %I64X\r\n",pSysInfo->ProcessQuotaPeak_1);
		printf("ProcessQuotaUsage_1: %I64X\r\n",pSysInfo->ProcessQuotaUsage_1);
		printf("ProcessQuotaPeak_0: %I64X\r\n",pSysInfo->ProcessQuotaPeak_0);
		printf("ProcessQuotaUsage_0: %I64X\r\n",pSysInfo->ProcessQuotaUsage_0);
		printf("CommitCharge: %I64X\r\n",pSysInfo->CommitCharge);
		printf("CommitChargePeak: %I64X\r\n",pSysInfo->CommitChargePeak);
		printf("CommitCharge_: %I64X\r\n",pSysInfo->CommitCharge_);

		printf("ReadOperationCount: %I64X\r\n",pSysInfo->ReadOperationCount);
		printf("WriteOperationCount: %I64X\r\n",pSysInfo->WriteOperationCount);
		printf("OtherOperationCount: %I64X\r\n",pSysInfo->OtherOperationCount);
		printf("ReadTransferCount: %I64X\r\n",pSysInfo->ReadTransferCount);
		printf("WriteTransferCount: %I64X\r\n",pSysInfo->WriteTransferCount);
		printf("OtherTransferCount: %I64X\r\n",pSysInfo->OtherTransferCount);
		

		ulong NumThread = pSysInfo->NumberOfThreads;
		_SYSTEM_THREAD_INFORMATION* pThreadInfo = & (pSysInfo->Threads[0]);

		for(ulong i = 0 ; i < NumThread ; i++,pThreadInfo++)
		{
			printf("----- Thread Info ------\r\n");
			printf("PID: %I64X, TID: %I64X\r\n",pThreadInfo->CID.UniqueProcess,pThreadInfo->CID.UniqueThread);

			printf("ApcTime: %I64X\r\n",pThreadInfo->ApcTime);
			printf("UserTime: %I64X\r\n",pThreadInfo->UserTime);
			printf("CreateTime: %I64X\r\n",pThreadInfo->CreateTime);
			printf("WaitTime: %I64X\r\n",pThreadInfo->WaitTime);
			printf("Pad: %I64X\r\n",pThreadInfo->Pad);
			printf("StartAddress: %I64X\r\n",pThreadInfo->StartAddress);
			printf("Priority: %I64X\r\n",pThreadInfo->Priority);
			printf("BasePriority: %I64X\r\n",pThreadInfo->BasePriority);
			printf("ContextSwitches: %I64X\r\n",pThreadInfo->ContextSwitches);
			printf("ThreadState: %I64X\r\n",pThreadInfo->ThreadState);
			printf("WaitReason: %I64X\r\n",pThreadInfo->WaitReason);
			printf("Pad1: %I64X\r\n",pThreadInfo->Pad1);
		}



		Offset = pSysInfo->NextEntryOffset;
		pSysInfo = (_SYSTEM_PROCESS_INFORMATION*) (((char*)pSysInfo) + Offset);
		
		//printf("Press any key to continue\r\n");
		//getchar();

		if(Offset == 0)
		{
			printf("Done\r\n");
			break;
		}

		//getchar();
	}




		//printf("%X\r\n",SizeRead);
		//printf("%X\r\n",NumModules);
		//printf("%X\r\n",ReturnedLength);
		VirtualFree(p,0,MEM_RELEASE);
	}

	return;
}


//----------------------


//SystemExtendedProcessInformation
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void Leak3()
{
	ulong Size = 0x1000;
	void* p = VirtualAlloc(0,Size,MEM_COMMIT,PAGE_READWRITE);
	ulong ReturnedLength = 0;

	if(p)
	{
		int ret = ZwQuerySystemInformation(SystemExtendedProcessInformation,p,Size,&ReturnedLength);
		printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",ret,ReturnedLength);


		if(ret == STATUS_INFO_LENGTH_MISMATCH)
		{
			VirtualFree(p,0,MEM_RELEASE);
			Size  = ReturnedLength;
			p = VirtualAlloc(0,Size,MEM_COMMIT,PAGE_READWRITE);
			if(p)
			{
				ret = ZwQuerySystemInformation(SystemExtendedProcessInformation,p,Size,&ReturnedLength);
				printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",ret,ReturnedLength);
			}
			else
			{
				printf("Error allocating memory\r\n");
				return;
			}
		}



		







	_SYSTEM_PROCESS_INFORMATION_EX* pSysInfo = (_SYSTEM_PROCESS_INFORMATION_EX*)p;
	unsigned long Offset = 0;
	while(Offset < ReturnedLength)
	{
		printf("Offset: %X\r\n",Offset);
		printf("ReturnedLength: %X\r\n",ReturnedLength);


		wprintf(L"Image Name: %s\r\n",pSysInfo->ImageName.Buffer);

		wprintf(L"Image Name / Length: %X\r\n",pSysInfo->ImageName.Length);
		wprintf(L"Image Name / MaxLength: %X\r\n",pSysInfo->ImageName.MaxLength);
		wprintf(L"Image Name / Pad: %X\r\n",pSysInfo->ImageName.Pad);
		wprintf(L"Image Name: %s\r\n",pSysInfo->ImageName.Buffer);

		printf("UniqueProcessId: %I64X\r\n",pSysInfo->UniqueProcessId);
		printf("UniqueProcessId_: %I64X\r\n",pSysInfo->UniqueProcessId_);
		printf("InheritedFromUniqueProcessId: %I64X\r\n",pSysInfo->InheritedFromUniqueProcessId);
		printf("NumberOfThreads: %I64X\r\n",pSysInfo->NumberOfThreads);
		printf("WorkingSetPrivateSize: %I64X\r\n",pSysInfo->WorkingSetPrivateSize);

		printf("HardFaultCount: %I64X\r\n",pSysInfo->HardFaultCount);
		printf("ActiveThreadsHighWatermark: %I64X\r\n",pSysInfo->ActiveThreadsHighWatermark);
		printf("CycleTime: %I64X\r\n",pSysInfo->CycleTime);
		printf("CreateTime: %I64X\r\n",pSysInfo->CreateTime);
		printf("UserTime: %I64X\r\n",pSysInfo->UserTime);
		printf("KernelTime: %I64X\r\n",pSysInfo->KernelTime);

		

		printf("BasePriority: %I64X\r\n",pSysInfo->BasePriority);
		printf("PAD0: %I64X\r\n",pSysInfo->PAD0);
		printf("HandleCount: %I64X\r\n",pSysInfo->HandleCount);
		printf("SessionId: %I64X\r\n",pSysInfo->SessionId);
		printf("PeakVirtualSize: %I64X\r\n",pSysInfo->PeakVirtualSize);
		printf("VirtualSize: %I64X\r\n",pSysInfo->VirtualSize);
		printf("PageFaultCount: %I64X\r\n",pSysInfo->PageFaultCount);
		printf("PAD1: %I64X\r\n",pSysInfo->PAD1);
		printf("PeakWorkingSetSize: %I64X\r\n",pSysInfo->PeakWorkingSetSize);
		printf("WorkingSetSize: %I64X\r\n",pSysInfo->WorkingSetSize);


		printf("ProcessQuotaPeak_1: %I64X\r\n",pSysInfo->ProcessQuotaPeak_1);
		printf("ProcessQuotaUsage_1: %I64X\r\n",pSysInfo->ProcessQuotaUsage_1);
		printf("ProcessQuotaPeak_0: %I64X\r\n",pSysInfo->ProcessQuotaPeak_0);
		printf("ProcessQuotaUsage_0: %I64X\r\n",pSysInfo->ProcessQuotaUsage_0);
		printf("CommitCharge: %I64X\r\n",pSysInfo->CommitCharge);
		printf("CommitChargePeak: %I64X\r\n",pSysInfo->CommitChargePeak);
		printf("CommitCharge_: %I64X\r\n",pSysInfo->CommitCharge_);

		printf("ReadOperationCount: %I64X\r\n",pSysInfo->ReadOperationCount);
		printf("WriteOperationCount: %I64X\r\n",pSysInfo->WriteOperationCount);
		printf("OtherOperationCount: %I64X\r\n",pSysInfo->OtherOperationCount);
		printf("ReadTransferCount: %I64X\r\n",pSysInfo->ReadTransferCount);
		printf("WriteTransferCount: %I64X\r\n",pSysInfo->WriteTransferCount);
		printf("OtherTransferCount: %I64X\r\n",pSysInfo->OtherTransferCount);
		

		
		ulong NumThread = pSysInfo->NumberOfThreads;
		_SYSTEM_THREAD_INFORMATION_EX* pThreadInfo = & (pSysInfo->Threads[0]);

		for(ulong i = 0 ; i < NumThread ; i++,pThreadInfo++)
		{
			printf("----- Thread Info ------\r\n");
			printf("PID: %I64X, TID: %I64X\r\n",pThreadInfo->CID.UniqueProcess,pThreadInfo->CID.UniqueThread);

			printf("ApcTime: %I64X\r\n",pThreadInfo->ApcTime);
			printf("UserTime: %I64X\r\n",pThreadInfo->UserTime);
			printf("CreateTime: %I64X\r\n",pThreadInfo->CreateTime);
			printf("WaitTime: %I64X\r\n",pThreadInfo->WaitTime);
			printf("Pad: %I64X\r\n",pThreadInfo->Pad);
			printf("StartAddress: %I64X\r\n",pThreadInfo->StartAddress);
			printf("Priority: %I64X\r\n",pThreadInfo->Priority);
			printf("BasePriority: %I64X\r\n",pThreadInfo->BasePriority);
			printf("ContextSwitches: %I64X\r\n",pThreadInfo->ContextSwitches);
			printf("ThreadState: %I64X\r\n",pThreadInfo->ThreadState);
			printf("WaitReason: %I64X\r\n",pThreadInfo->WaitReason);
			printf("Pad1: %I64X\r\n",pThreadInfo->Pad1);

			printf("StackBase: %I64X\r\n",pThreadInfo->StackBase);
			printf("StackLimit: %I64X\r\n",pThreadInfo->StackLimit);
			printf("Win32StartAddress: %I64X\r\n",pThreadInfo->Win32StartAddress);
			printf("Teb: %I64X\r\n",pThreadInfo->Teb);
			printf("Zero0: %I64X\r\n",pThreadInfo->Zero0);
			printf("Zero1: %I64X\r\n",pThreadInfo->Zero1);
			printf("Zero2: %I64X\r\n",pThreadInfo->Zero2);
		}
		


		Offset = pSysInfo->NextEntryOffset;
		pSysInfo = (_SYSTEM_PROCESS_INFORMATION_EX*) (((char*)pSysInfo) + Offset);
		
		//printf("Press any key to continue\r\n");
		//getchar();

		if(Offset == 0)
		{
			printf("Done\r\n");
			break;
		}

		//getchar();
	}




		//printf("%X\r\n",SizeRead);
		//printf("%X\r\n",NumModules);
		//printf("%X\r\n",ReturnedLength);
		VirtualFree(p,0,MEM_RELEASE);
	}

	return;
}


//--------------
//SystemSessionProcessInformation
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void Leak4()
{

	unsigned long MaxSession = 5;//you can change
	for(ulong s = 0; s< MaxSession;s++)
	{
		printf("Session: %X\r\n",s);

		_SESSION_PROCESS_INFO Sess = {0};
		Sess.SessionId = s;



		ulong Size = 0x1000;
		void* p = VirtualAlloc(0,Size,MEM_COMMIT,PAGE_READWRITE);
		ulong ReturnedLength = 0;

		if(!p)
		{
			printf("Error allocating memory, Session: %X\r\n",s);
			return;
		}
		else
		{
			Sess.OutputBuffer = (_SYSTEM_PROCESS_INFORMATION*)p;
			Sess.OutputBufferLength = Size;

			int ret = ZwQuerySystemInformation(SystemSessionProcessInformation,&Sess,0x10,&ReturnedLength);
			printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",ret,ReturnedLength);


			if(ret == STATUS_INFO_LENGTH_MISMATCH)
			{
				Sess.OutputBuffer = 0;
				Sess.OutputBufferLength = 0;

				VirtualFree(p,0,MEM_RELEASE);

				Size  = ReturnedLength;

				p = VirtualAlloc(0,Size,MEM_COMMIT,PAGE_READWRITE);
				if(p)
				{
					Sess.OutputBuffer = (_SYSTEM_PROCESS_INFORMATION*)p;
					Sess.OutputBufferLength = Size;

					ret = ZwQuerySystemInformation(SystemSessionProcessInformation,&Sess,0x10,&ReturnedLength);
					printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",ret,ReturnedLength);
				}
				else
				{
					printf("Error allocating memory, Session: %X\r\n",s);
					return;
				}
			}


			if(ReturnedLength == 0)
			{
				printf("Warning: Non-existing session\r\n");
			}
			else
			{
				_SYSTEM_PROCESS_INFORMATION* pSysInfo = (_SYSTEM_PROCESS_INFORMATION*)p;
				unsigned long Offset = 0;

				while(Offset < ReturnedLength)
				{
							printf("Offset: %X\r\n",Offset);
							printf("ReturnedLength: %X\r\n",ReturnedLength);


							wprintf(L"Image Name: %s\r\n",pSysInfo->ImageName.Buffer);

							wprintf(L"Image Name / Length: %X\r\n",pSysInfo->ImageName.Length);
							wprintf(L"Image Name / MaxLength: %X\r\n",pSysInfo->ImageName.MaxLength);
							wprintf(L"Image Name / Pad: %X\r\n",pSysInfo->ImageName.Pad);
							wprintf(L"Image Name: %s\r\n",pSysInfo->ImageName.Buffer);

							printf("UniqueProcessId: %I64X\r\n",pSysInfo->UniqueProcessId);
							printf("UniqueProcessId_: %I64X\r\n",pSysInfo->UniqueProcessId_);
							printf("InheritedFromUniqueProcessId: %I64X\r\n",pSysInfo->InheritedFromUniqueProcessId);
							printf("NumberOfThreads: %I64X\r\n",pSysInfo->NumberOfThreads);
							printf("WorkingSetPrivateSize: %I64X\r\n",pSysInfo->WorkingSetPrivateSize);

							printf("HardFaultCount: %I64X\r\n",pSysInfo->HardFaultCount);
							printf("ActiveThreadsHighWatermark: %I64X\r\n",pSysInfo->ActiveThreadsHighWatermark);
							printf("CycleTime: %I64X\r\n",pSysInfo->CycleTime);
							printf("CreateTime: %I64X\r\n",pSysInfo->CreateTime);
							printf("UserTime: %I64X\r\n",pSysInfo->UserTime);
							printf("KernelTime: %I64X\r\n",pSysInfo->KernelTime);

		

							printf("BasePriority: %I64X\r\n",pSysInfo->BasePriority);
							printf("PAD0: %I64X\r\n",pSysInfo->PAD0);
							printf("HandleCount: %I64X\r\n",pSysInfo->HandleCount);
							printf("SessionId: %I64X\r\n",pSysInfo->SessionId);
							printf("PeakVirtualSize: %I64X\r\n",pSysInfo->PeakVirtualSize);
							printf("VirtualSize: %I64X\r\n",pSysInfo->VirtualSize);
							printf("PageFaultCount: %I64X\r\n",pSysInfo->PageFaultCount);
							printf("PAD1: %I64X\r\n",pSysInfo->PAD1);
							printf("PeakWorkingSetSize: %I64X\r\n",pSysInfo->PeakWorkingSetSize);
							printf("WorkingSetSize: %I64X\r\n",pSysInfo->WorkingSetSize);


							printf("ProcessQuotaPeak_1: %I64X\r\n",pSysInfo->ProcessQuotaPeak_1);
							printf("ProcessQuotaUsage_1: %I64X\r\n",pSysInfo->ProcessQuotaUsage_1);
							printf("ProcessQuotaPeak_0: %I64X\r\n",pSysInfo->ProcessQuotaPeak_0);
							printf("ProcessQuotaUsage_0: %I64X\r\n",pSysInfo->ProcessQuotaUsage_0);
							printf("CommitCharge: %I64X\r\n",pSysInfo->CommitCharge);
							printf("CommitChargePeak: %I64X\r\n",pSysInfo->CommitChargePeak);
							printf("CommitCharge_: %I64X\r\n",pSysInfo->CommitCharge_);

							printf("ReadOperationCount: %I64X\r\n",pSysInfo->ReadOperationCount);
							printf("WriteOperationCount: %I64X\r\n",pSysInfo->WriteOperationCount);
							printf("OtherOperationCount: %I64X\r\n",pSysInfo->OtherOperationCount);
							printf("ReadTransferCount: %I64X\r\n",pSysInfo->ReadTransferCount);
							printf("WriteTransferCount: %I64X\r\n",pSysInfo->WriteTransferCount);
							printf("OtherTransferCount: %I64X\r\n",pSysInfo->OtherTransferCount);
		

		
							ulong NumThread = pSysInfo->NumberOfThreads;
							_SYSTEM_THREAD_INFORMATION* pThreadInfo = & (pSysInfo->Threads[0]);

							for(ulong i = 0 ; i < NumThread ; i++,pThreadInfo++)
							{
								printf("----- Thread Info ------\r\n");
								printf("PID: %I64X, TID: %I64X\r\n",pThreadInfo->CID.UniqueProcess,pThreadInfo->CID.UniqueThread);

								printf("ApcTime: %I64X\r\n",pThreadInfo->ApcTime);
								printf("UserTime: %I64X\r\n",pThreadInfo->UserTime);
								printf("CreateTime: %I64X\r\n",pThreadInfo->CreateTime);
								printf("WaitTime: %I64X\r\n",pThreadInfo->WaitTime);
								printf("Pad: %I64X\r\n",pThreadInfo->Pad);
								printf("StartAddress: %I64X\r\n",pThreadInfo->StartAddress);
								printf("Priority: %I64X\r\n",pThreadInfo->Priority);
								printf("BasePriority: %I64X\r\n",pThreadInfo->BasePriority);
								printf("ContextSwitches: %I64X\r\n",pThreadInfo->ContextSwitches);
								printf("ThreadState: %I64X\r\n",pThreadInfo->ThreadState);
								printf("WaitReason: %I64X\r\n",pThreadInfo->WaitReason);
								printf("Pad1: %I64X\r\n",pThreadInfo->Pad1);

							}

							Offset = pSysInfo->NextEntryOffset;
							pSysInfo = (_SYSTEM_PROCESS_INFORMATION*) (((char*)pSysInfo) + Offset);

							if(Offset == 0)
							{
								printf("Done\r\n");
								break;
							}


							//getchar();
				}
			}

		
			//printf("Press any key to continue enumerating next session processes\r\n");
			//getchar();


			VirtualFree(p,0,MEM_RELEASE);


		}


		
	}

	return;
}
//--------------
//SystemLocksInformation
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void Leak5()
{
	ulong Result = 0;
	void* p = VirtualAlloc(0,0x2000,MEM_COMMIT,PAGE_READWRITE);

	int R = ZwQuerySystemInformation(SystemLocksInformation,p,0x2000,&Result);
	wprintf(L"NtQuerySystemInformation, ret: %X, ResultLength: %X\r\n",R,Result);

	if(R < 0)
	{
		if(VirtualFree(p,0x2000,MEM_DECOMMIT))
		{
			p = VirtualAlloc(0,Result,MEM_COMMIT,PAGE_READWRITE);
			if(p)
			{
				ulong ResultX = 0;

				R = ZwQuerySystemInformation(SystemLocksInformation,p,Result,&ResultX);
				wprintf(L"NtQuerySystemInformation, ret: %X, ResultLength: %X\r\n",R,ResultX);
				ulong NumChunks = *(ulong*)p;
				wprintf(L"Number of Chunks: %X\r\n",NumChunks);
				//return 0;
				ulonglong* pLeak = (ulonglong*)( ((char*)p) + 0x8);
				for(int i=0;i<NumChunks;i++)
				{
					//if(!*pLeak) break;
					wprintf(L"Leaked address: %I64X\r\n",*pLeak);
					pLeak = (ulonglong*)(((char*)pLeak)+0x30);
				}
				VirtualFree(p,Result,MEM_DECOMMIT);
			}
		}
	}
	return;
}

//------------

//SystemHandleInformation
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void Leak6()
{
	bool bX = false;

	ulong  ResultY = 0;
	ulonglong Dummy[8];
	int retY = ZwQuerySystemInformation(SystemHandleInformation,&Dummy[0],0x20,&ResultY);
	wprintf(L"ZwQuerySystemInformation, ret: %X, ResultLength: %X\r\n",retY,ResultY);

	ulong SizeToAlloc = ResultY * 2;

	if(retY == 0xC0000004)
	{

			_SYSTEM_HANDLE_TABLE* pHandles = (_SYSTEM_HANDLE_TABLE*)VirtualAlloc(0,SizeToAlloc,MEM_COMMIT,PAGE_READWRITE);
			memset(pHandles,0,SizeToAlloc);

			if(pHandles)
			{
				ulong Tid;
				ulong ResultYY = 0;
				retY = ZwQuerySystemInformation(SystemHandleInformation,pHandles,SizeToAlloc,&ResultYY);
				wprintf(L"ZwQuerySystemInformation, ret: %X, ResultLength: %X\r\n",retY,ResultYY);
				if(retY >= 0 )
				{
					unsigned long Count = pHandles->Count;
					_SYSTEM_HANDLE_TABLE_ENTRY_INFO* pENtryInfo = & pHandles->Entry[0];
					int i = 0;
					while(i<Count)
					{
						wprintf(L"PID: %X, Handle: %X, HandleAttributes: %X, GrantedAccess: %X, ObjectTypeIndex: %X, Object Address: %I64X\r\n",
							pENtryInfo->UniqueProcessId,
							pENtryInfo->HandleValue,
							pENtryInfo->HandleAttributes,
							pENtryInfo->GrantedAccess,
							pENtryInfo->ObjectTypeIndex,
							pENtryInfo->Object);

						pENtryInfo++;
						i++;
					}
				}
			}
			VirtualFree(pHandles,SizeToAlloc,MEM_DECOMMIT);
	}
	return;
}


//-----------------

//SystemExtendedHandleInformation
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void Leak7()
{
	int retY = 0;
	ulong ReturnedLength = 0;



	ulong SizeToAlloc = 0x1000;
	void* p = VirtualAlloc(0,SizeToAlloc,MEM_COMMIT,PAGE_READWRITE);

	if(p)
	{
		retY = ZwQuerySystemInformation(SystemExtendedHandleInformation,p,SizeToAlloc,&ReturnedLength);
		printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",retY,ReturnedLength);


		while(retY == STATUS_INFO_LENGTH_MISMATCH)
		{
			VirtualFree(p,0,MEM_RELEASE);
			SizeToAlloc  = ReturnedLength;
			p = VirtualAlloc(0,SizeToAlloc,MEM_COMMIT,PAGE_READWRITE);
			if(p)
			{
				retY = ZwQuerySystemInformation(SystemExtendedHandleInformation,p,SizeToAlloc,&ReturnedLength);
				printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",retY,ReturnedLength);
			}
			else
			{
				printf("Error allocating memory\r\n");
				return;
			}
		}

	}

	if(retY != STATUS_INFO_LENGTH_MISMATCH)
	{
			_SYSTEM_HANDLE_INFORMATION_EX* pHandles = (_SYSTEM_HANDLE_INFORMATION_EX*)p;
			if(pHandles)
			{
				ulonglong Count = pHandles->NumberOfHandles;
				SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX* pENtryInfo = & pHandles->Handles[0];




				ulonglong i = 0;
				while(i < Count)
				{
					wprintf(L"Object: %I64X, UniqueProcessId: %I64X, HandleValue: %I64X, GrantedAccess: %X, CreatorBackTraceIndex: %X, ObjectTypeIndex: %X, HandleAttributes: %X, Reserved: %I64X\r\n",
							pENtryInfo->Object,
							pENtryInfo->UniqueProcessId,
							pENtryInfo->HandleValue,
							pENtryInfo->GrantedAccess,
							pENtryInfo->CreatorBackTraceIndex,
							pENtryInfo->ObjectTypeIndex,
							pENtryInfo->HandleAttributes,
							pENtryInfo->Reserved);

					pENtryInfo++;
					i++;
				}
			}
	}



	if(p) VirtualFree(p,0,MEM_RELEASE);
	return;
}
//-------------
//SystemObjectInformation
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
//requires "Maintain a list of objects for each type" in gflags
void Leak8()
{
	int retY = 0;
	ulong ReturnedLength = 0;



	ulong SizeToAlloc = 0x800000; //0x1000;
	void* p = VirtualAlloc(0,SizeToAlloc,MEM_COMMIT,PAGE_READWRITE);

	if(p)
	{
		retY = ZwQuerySystemInformation(SystemObjectInformation,p,SizeToAlloc,&ReturnedLength);
		printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",retY,ReturnedLength);

		printf("Please wait a moment.\r\n");

		while(retY == STATUS_INFO_LENGTH_MISMATCH)
		{
			VirtualFree(p,0,MEM_RELEASE);
			SizeToAlloc  = ReturnedLength;
			SizeToAlloc += 0x100000;

			p = VirtualAlloc(0,SizeToAlloc,MEM_COMMIT,PAGE_READWRITE);
			if(p)
			{
				retY = ZwQuerySystemInformation(SystemObjectInformation,p,SizeToAlloc,&ReturnedLength);
				//printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",retY,ReturnedLength);
			}
			else
			{
				printf("Error allocating memory\r\n");
				return;
			}
		}

	}

	printf("%I64X have been allocated.\r\n",ReturnedLength);

	if(retY != STATUS_INFO_LENGTH_MISMATCH)
	{
			_SYSTEM_OBJECT_INFORMATION* pTypes = (_SYSTEM_OBJECT_INFORMATION*)p;


			if(pTypes)
			{
				ulong var_Offset = 0;
				do
				{
					var_Offset = pTypes->NextOffset;
					printf("NextOffset: %X\r\n",var_Offset);

					
					if(var_Offset >= ReturnedLength)
					{
						printf("Corrupt output.\r\n");
						ExitProcess(0);
					}
					

					printf("TotalNumberOfObjects: %X\r\n",pTypes->TotalNumberOfObjects);
					printf("TotalNumberOfHandles: %X\r\n",pTypes->TotalNumberOfHandles);
					printf("TypeIndex: %X\r\n",pTypes->Index);
					printf("InvalidAttributes: %X\r\n",pTypes->InvalidAttributes);
					
					printf("GenericMapping/GenericAll: %X\r\n",pTypes->GenericMapping.GenericAll);
					printf("GenericMapping/GenericExecute: %X\r\n",pTypes->GenericMapping.GenericExecute);
					printf("GenericMapping/GenericRead: %X\r\n",pTypes->GenericMapping.GenericRead);
					printf("GenericMapping/GenericWrite: %X\r\n",pTypes->GenericMapping.GenericWrite);

					printf("ValidAccessMask: %X\r\n",pTypes->ValidAccessMask);
					printf("PoolType: %X\r\n",pTypes->PoolType);
					printf("bSecurityRequired: %X\r\n",pTypes->bSecurityRequired);
					

					printf("Name/Length: %X\r\n",pTypes->Name.Length);
					printf("Name/MaxLength: %X\r\n",pTypes->Name.MaxLength);
					printf("Name/Pad: %X\r\n",pTypes->Name.Pad);

					ulonglong NameBuffer = (ulonglong)(pTypes->Name.Buffer);
					wprintf(L"TypeName: %s\r\n",pTypes->Name.Buffer);

					

					NameBuffer += pTypes->Name.MaxLength;
					if(NameBuffer & 0x7)
					{
						NameBuffer += 7;
						NameBuffer &= (~7);
					}
					//----------------------------------------------------------
					//Now start enumerating each object within the current type.
					_SYSTEM_OBJECT_INFORMATION_OBJECT* pSingleObject = 
					(_SYSTEM_OBJECT_INFORMATION_OBJECT*) (  (uchar*)NameBuffer);
					
					do
					{
						printf(">>>>>>>>>>>>>>>>>>>\r\n");
						wprintf(L"Name: %s\r\n",pSingleObject->Name.Buffer);
						printf("pObject: %I64X\r\n",pSingleObject->pObject);
						printf("pSecurityDescriptor: %I64X\r\n",pSingleObject->pSecurityDescriptor);
						
						if(pSingleObject->Offset == 0)
						{

						}
						else
						{
							pSingleObject = 
							(_SYSTEM_OBJECT_INFORMATION_OBJECT*)(((uchar*)p) + pSingleObject->Offset);
						}
					}while(pSingleObject->Offset);

					pTypes = (_SYSTEM_OBJECT_INFORMATION*)(((uchar*)p) + var_Offset);
				}while(var_Offset);
			}
	}



	if(p) VirtualFree(p,0,MEM_RELEASE);
	return;
}

//------------------

//SystemBigPoolInformation
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void Leak9()
{
	int retY = 0;

	ulong ReturnedLength = 0;

	ulong SizeToAlloc = 0x1000;
	void* p = VirtualAlloc(0,SizeToAlloc,MEM_COMMIT,PAGE_READWRITE);

	if(p)
	{
		retY = ZwQuerySystemInformation(SystemBigPoolInformation,p,SizeToAlloc,&ReturnedLength);
		printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",retY,ReturnedLength);

		while(retY == STATUS_INFO_LENGTH_MISMATCH)
		{
			VirtualFree(p,0,MEM_RELEASE);
			SizeToAlloc  = ReturnedLength;
			

			p = VirtualAlloc(0,SizeToAlloc,MEM_COMMIT,PAGE_READWRITE);
			if(p)
			{
				retY = ZwQuerySystemInformation(SystemBigPoolInformation,p,SizeToAlloc,&ReturnedLength);
				//printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",retY,ReturnedLength);
			}
			else
			{
				printf("Error allocating memory\r\n");
				return;
			}
		}

	}

	printf("%I64X have been allocated.\r\n",ReturnedLength);

	if(retY != STATUS_INFO_LENGTH_MISMATCH)
	{
		_SYSTEM_BIGPOOL_INFORMATION* pBigPool = (_SYSTEM_BIGPOOL_INFORMATION*)p;

		ulonglong count = pBigPool->Count;

		ulonglong i = 0;
		while(i < count)
		{
			_SYSTEM_BIGPOOL_ENTRY* pEntry = &pBigPool->AllocatedInfo[i];

			ulonglong VA = (ulonglong)(pEntry->VirtualAddress);
			if(VA & 0x1)
			{
				VA &= (~1);
			}
			printf("VirtualAddress: %I64X\r\n",VA);

			printf("SizeInBytes: %X\r\n",pEntry->SizeInBytes);

			printf("Tag: %s\r\n",&pEntry->Tag[0]);
			i++;
		}
	}



	if(p) VirtualFree(p,0,MEM_RELEASE);
	return;
}

//---------------------

//SystemSessionBigPoolInformation
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void LeakA()
{
	int retY = 0;
	_BIGPOOL_SESSION_INFO_INPUT SessionInput = {0};
	SessionInput.SessionId = -1;
	
	ulong ReturnedLength = 0;
	retY = ZwQuerySystemInformation(SystemSessionBigPoolInformation,
							&SessionInput,
							sizeof(_BIGPOOL_SESSION_INFO_INPUT),
							&ReturnedLength);
	printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",retY,ReturnedLength);

	ulong SizeToAlloc = ReturnedLength;
	void* p = VirtualAlloc(0,SizeToAlloc,MEM_COMMIT,PAGE_READWRITE);
	if(!p) return;

	SessionInput.InfoSize = SizeToAlloc;
	SessionInput.pInfo = p;
	SessionInput.SessionId = -1;

	retY = ZwQuerySystemInformation(SystemSessionBigPoolInformation,
							&SessionInput,
							sizeof(_BIGPOOL_SESSION_INFO_INPUT),
							&ReturnedLength);
	printf("ZwQuerySystemInformation, ret: %X, ReturnedLength: %X\r\n",retY,ReturnedLength);

	if(retY != STATUS_INFO_LENGTH_MISMATCH)
	{
		ulong NextOffset = 0;
		

		do
		{
			_SESSION_BIGPOOL_INFORMATION* pBigPool = (_SESSION_BIGPOOL_INFORMATION*) (((uchar*)p) + NextOffset);

			NextOffset = pBigPool->NextOffset;

			printf("Session Id: %X\r\n",pBigPool->SessionId);

			ulonglong count = pBigPool->Count;
			ulonglong i = 0;
			_SYSTEM_BIGPOOL_ENTRY* pEntry = &pBigPool->AllocatedInfo[i];
			while(i < count)
			{
				pEntry = &pBigPool->AllocatedInfo[i];

				ulonglong VA = (ulonglong)(pEntry->VirtualAddress);
				if(VA & 0x1)
				{
					VA &= (~1);
				}
				printf("VirtualAddress: %I64X\r\n",VA);

				printf("SizeInBytes: %X\r\n",pEntry->SizeInBytes);

				printf("Tag: %s\r\n",&pEntry->Tag[0]);
				i++;
			}

			printf("-----------------------------\r\n");
		}while(NextOffset);
	}



	if(p) VirtualFree(p,0,MEM_RELEASE);
	return;
}

//-------------
//ProcessHandleTracing
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void LeakB()
{



	_PROCESS_HANDLE_TRACING_ENABLE Set = {0};
	int ret = ZwSetInformationProcess(GetCurrentProcess(),ProcessHandleTracing,&Set,sizeof(Set));
	printf("ZwSetInformationProcess, ret: %X\r\n",ret);

	if(ret >= 0)
	{
		ulonglong SzToAlloc = 0x5000;
		void* p = VirtualAlloc(0,SzToAlloc,MEM_COMMIT,PAGE_READWRITE);
		if(p)
		{
			HANDLE hTestHandle = CreateEvent(0,FALSE,FALSE,0);
			ZwClose(hTestHandle);

			_PROCESS_HANDLE_TRACING_QUERY* pQuery = 
			(_PROCESS_HANDLE_TRACING_QUERY*)p;

			pQuery->Handle = hTestHandle;

			ulonglong retLength = 0;

			ret = ZwQueryInformationProcess(GetCurrentProcess(),
										ProcessHandleTracing,
										pQuery,
										SzToAlloc,
										&retLength);
			printf("ZwQueryInformationProcess, ret: %X\r\n",ret);

			if(ret >= 0)
			{
				printf("Handle: %I64X\r\n",pQuery->Handle);
				printf("%X\r\n",pQuery->TotalTraces);

				ulonglong var_TotalTraces = pQuery->TotalTraces;

				ulonglong i = 0;
				while(i < var_TotalTraces)
				{
					PROCESS_HANDLE_TRACING_ENTRY* pEntry = &pQuery->HandleTrace[i];

					printf(">>Handle: %I64X\r\n",pEntry->Handle);
					printf(">>ClientId/ProcessId: %I64X\r\n",pEntry->ClientId.UniqueProcess);
					printf(">>ClientId/ThreadId: %I64X\r\n",pEntry->ClientId.UniqueThread);
					printf(">>Type: %I64X\r\n",pEntry->Type);

					for(ulong ii=0;ii<PROCESS_HANDLE_TRACING_MAX_STACKS;ii++)
					{
						printf(">>S: %I64X\r\n",pEntry->Stacks[ii]);
					}

					printf("-------------------------\r\n");
					i++;
				}
			}


			VirtualFree(p,0,MEM_RELEASE);
		}
	}
}


//------------------
//ProcessWorkingSetWatch
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void LeakC()
{
	void* p = VirtualAlloc(0,0x10000,MEM_COMMIT,PAGE_READWRITE);
	if(p)
	{
		ulonglong RetLen = 0;
		int retValue = ZwSetInformationProcess(GetCurrentProcess(),ProcessWorkingSetWatch,0,0);
		printf("ZwSetInformationProcess, ret: %X\r\n",retValue);

		printf("Please close the popup.\r\n");

		//FindWindow(L"test",L"test");
		MessageBox(0,L"Close me",L"Close me",0);
		
		retValue =	ZwQueryInformationProcess(GetCurrentProcess(),ProcessWorkingSetWatch,p,0x10000,&RetLen);
		printf("ZwQueryInformationProcess, ret: %X, RetLen: %I64X\r\n",retValue,RetLen);

		_PSAPI_WS_WATCH_INFORMATION* pWatch = (_PSAPI_WS_WATCH_INFORMATION*)p;
		ulong Num = RetLen / sizeof(_PSAPI_WS_WATCH_INFORMATION);

		while(Num)
		{
			if(   ( pWatch->FaultingPc & 0x8000000000000000 ) || ( pWatch->FaultingVa & 0x8000000000000000 ) )
			{
				printf("FaultingPc: %I64X\r\n",pWatch->FaultingPc);
				printf("FaultingVa: %I64X\r\n",pWatch->FaultingVa);
				printf("-----------------\r\n");
			}

			pWatch++;
			Num--;
		}

		VirtualFree(p,0,MEM_RELEASE);
	}
}


//-----------------

//ProcessWorkingSetWatch
//Guarded by ExIsRestrictedCaller
//Inaccessible from the Sandbox
void LeakD()
{
	void* p = VirtualAlloc(0,0x10000,MEM_COMMIT,PAGE_READWRITE);
	if(p)
	{
		ulonglong RetLen = 0;
		int retValue = ZwSetInformationProcess(GetCurrentProcess(),ProcessWorkingSetWatch,0,0);
		printf("ZwSetInformationProcess, ret: %X\r\n",retValue);
			

		printf("Please close the popup.\r\n");

		//FindWindow(L"test",L"test");
		MessageBox(0,L"Close me",L"Close me",0);
		
		retValue =	ZwQueryInformationProcess(GetCurrentProcess(),ProcessWorkingSetWatchEx,p,0x10000,&RetLen);
		printf("ZwQueryInformationProcess, ret: %X, RetLen: %I64X\r\n",retValue,RetLen);

		_PSAPI_WS_WATCH_INFORMATION* pWatch = (_PSAPI_WS_WATCH_INFORMATION*)p;
		ulong Num = RetLen / sizeof(_PSAPI_WS_WATCH_INFORMATION);

		while(Num)
		{
			if(   ( pWatch->FaultingPc & 0x8000000000000000 ) || ( pWatch->FaultingVa & 0x8000000000000000 ) )
			{
				printf("FaultingPc: %I64X\r\n",pWatch->FaultingPc);
				printf("FaultingVa: %I64X\r\n",pWatch->FaultingVa);
				printf("-----------------\r\n");
			}

			pWatch++;
			Num--;
		}

		VirtualFree(p,0,MEM_RELEASE);
	}
}