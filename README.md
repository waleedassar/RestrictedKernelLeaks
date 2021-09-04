# RestrictedKernelLeaks

List of KASLR bypass techniques in Windows 10 kernel.


1) ZwQuerySystemInformation/SystemModuleInformation

2) ZwQuerySystemInformation/SystemModuleInformationEx

3) ZwQuerySystemInformation/SystemProcessInformation

4) ZwQuerySystemInformation/SystemExtendedProcessInformation

5) ZwQuerySystemInformation/SystemSessionProcessInformation

6) ZwQuerySystemInformation/SystemLocksInformation

7) ZwQuerySystemInformation/SystemHandleInformation

8) ZwQuerySystemInformation/SystemExtendedHandleInformation

9) ZwQuerySystemInformation/SystemObjectInformation

10) ZwQuerySystemInformation/SystemBigPoolInformation

11) ZwQuerySystemInformation/SystemSessionBigPoolInformation

12) ZwQueryInformationProcess/ProcessHandleTracing

13) ZwQueryInformationProcess/ProcessWorkingSetWatch

14) ZwQueryInformationProcess/ProcessWorkingSetWatchEx


N.B. These techniques are only valid from outside the sandbox.

