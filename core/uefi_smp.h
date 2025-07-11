#define EFI_MP_SERVICES_PROTOCOL_GUID \
    { 0x3fdda605, 0xa76e, 0x4f46, { 0xad, 0x29, 0x12, 0xf4, 0x6b, 0x2a, 0x60, 0x6a } }

typedef int (*efi_mp_startup_this_ap)(
    void *This,
    void (*Procedure)(void *),
    int ProcessorNumber,
    void *WaitEvent,
    int TimeoutInMicroseconds,
    void *ProcedureArgument,
    int *Finished
);

typedef int (*efi_mp_whoami)(
    void *This,
    int *ProcessorNumber
);

typedef int (*efi_mp_get_number_of_processors)(
    void *This,
    unsigned long *NumberOfProcessors,
    unsigned long *NumberOfEnabledProcessors
);

typedef struct {
    efi_mp_get_number_of_processors GetNumberOfProcessors;
    void* GetProcessorInfo;
    void* StartupAllAPs;
    efi_mp_startup_this_ap StartupThisAP;
    void* SwitchBSP;
    void* EnableDisableAP;
    efi_mp_whoami WhoAmI;    
} efi_mp_services_t;