#ifndef LIMIT_FLAGS_H
#define LIMIT_FLAGS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define LIMIT_FLAGS_MAX_FLAGS                   (16)
#define LIMIT_FLAGS_MAX_STRING_LENGTH           (32)
#define LIMIT_FLAGS_STRING_TERMINATION_LENGTH   (1)
#define LIMIT_FLAGS_PACKET_LENGTH               (LIMIT_FLAGS_MAX_STRING_LENGTH + LIMIT_FLAGS_STRING_TERMINATION_LENGTH)

typedef struct _LIMIT_FLAGS_PROVIDER_STRUCT
{
    U32 bit_id; // bit position of the provider's flag -- allocated by LimitFlags
    char name[LIMIT_FLAGS_MAX_STRING_LENGTH + LIMIT_FLAGS_STRING_TERMINATION_LENGTH]; // string identifier
    U32 *handle; // pointer to provider's BOOLEAN flag
} LIMIT_FLAGS_PROVIDER_STRUCT;

// this is a container for clients to retrieve defining the LimitFlags providers,
// including their allocated bit positions and name
typedef struct _LIMIT_FLAGS_PROVIDERS_STRUCT
{
    U8 num_providers;
    U16 flags;
    LIMIT_FLAGS_PROVIDER_STRUCT provider_list[LIMIT_FLAGS_MAX_FLAGS];
   
} LIMIT_FLAGS_PROVIDERS_STRUCT;


/*  ========================================================================
                                Function Prototypes
    ======================================================================== */

void Limit_Flags_Initialize();
BOOLEAN Limit_Flags_Register(char *name, void *st_ptr);
LIMIT_FLAGS_PROVIDERS_STRUCT *Limit_Flags_Get();
void Limit_Flags_Run();
void Limit_Flags_Send();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LIMIT_FLAGS_H
