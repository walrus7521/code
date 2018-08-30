#include "limit_flags.h"
#include <string.h> // For memset()
#include <stddef.h> // For offsetof()

static LIMIT_FLAGS_PROVIDERS_STRUCT providers;
static int str_idx = 0;
static int sequencer = 0;

void Limit_Flags_Initialize()
{
    memset(providers.provider_list, 0, LIMIT_FLAGS_MAX_FLAGS * sizeof(LIMIT_FLAGS_PROVIDER_STRUCT));
    providers.num_providers = 0;
    str_idx = 0;
    sequencer = 0;

}

BOOLEAN Limit_Flags_Register(char *name, void *data_ptr)
{
    if (providers.num_providers < LIMIT_FLAGS_MAX_FLAGS)
    {
        LIMIT_FLAGS_PROVIDER_STRUCT *provider = &providers.provider_list[providers.num_providers];
        provider->bit_id = providers.num_providers;
        strncpy(provider->name, name, strlen(name));
        provider->handle = data_ptr;
        providers.num_providers++;
        printf("Limit_Flags_Register: registered %s bit %u\n", provider->name, provider->bit_id);
        return TRUE;
    }
    else
    {
        printf("Limit_Flags_Register: FAILED\n");
        return FALSE;
    }
}

LIMIT_FLAGS_PROVIDERS_STRUCT *Limit_Flags_Get()
{
    return &providers;
}

void Limit_Flags_Run()
{
    int i;
    U32 v;
    LIMIT_FLAGS_PROVIDER_STRUCT *provider;
    providers.flags = 0;
    for (i = 0; i < providers.num_providers; i++)
    {
        provider = &providers.provider_list[i];
        v = *(provider[i].handle);
        providers.flags |= (v ? 1 << provider->bit_id : 0);
    }

}

void Limit_Flags_Send()
{
    LIMIT_FLAGS_PROVIDER_STRUCT *provider;
    int crc;
    char buf[100] = {0}; // Buffer for sending the data to the display.
    memset(buf, 0, 100);

    switch (sequencer)
    {
        case 0:
            // send string
            crc = 0xdead;
            provider = &providers.provider_list[str_idx];
            sprintf(buf, "%d, %s, %d\n", provider->bit_id, provider->name, crc);
            str_idx++;
            if (str_idx >= providers.num_providers)
            {
                str_idx = 0;
            }
            serial_out(strlen(buf), buf, STREAM_DESC);
            break;
        default:
            // send data
            crc = 0xbeef;
            sprintf(buf, "%d, %d, %d\n", 0x80, providers.flags, crc);
            serial_out(strlen(buf), buf, STREAM_DESC);
            break;
    }
    sequencer++;
    if (sequencer >= 9)
    {
        sequencer = 0;
    }

}

