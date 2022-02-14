#include <x86_64/drivers/acpi.hpp>
#include <x86_64/printhex.hpp>

int memcmp2(const char *s1, const char *s2, int n) {
    int index = 0;
    while (s1[index] && s2[index] && s1[index] == s2[index] && n--)
        index++;

    if (n == 0)
        return 0;
    else
        return s1[index] - s2[index];
}

namespace firefly::drivers::acpi {
    // uint8_t find_sing(char *p) {
    //     if(p[0] == 'R'
    //     && p[1] == 'S'
    //     && p[2] == 'D'
    //     && p[3] == ' '
    //     && p[4] == 'P'
    //     && p[5] == 'T'
    //     && p[6] == 'R'
    //     && p[7] == ' ') {
    //         return true;
    //     } else {
    //         return false;
    //     }
    //}
    RSDPDescriptor20 *find_acpi() {
        //we know that acpi exists in the system because we have checked before finding it
        char *memrange0[2] = {(char*)0x40E, (char*)0xFFF};
        char *memrange1[2] = {(char*)0x000E0000, (char*)0x000FFFFF};

        void *ret;
        
        const char RSDPTR[8] = {'R', 'S', 'D', ' ', 'P', 'T', 'R', ' '};

        //firstly find RSDP in mem range 0
        uint8_t status[2] = {0, 0};
        int i = 0;
        while(status[0] == 0 || status[0] == 3){
            if(memcmp2((char*)memrange0[0]+i, RSDPTR, 8) != 0) {i++;}
            if(memcmp2((char*)memrange0[0]+i, RSDPTR, 8) == 0){
                status[0] = 1;
                ret = (char*)memrange0[0]+i;

                //validate rsdp
                //RSDPDescriptor *r = (RSDPDescriptor *)ret;
                if(((RSDPDescriptor *)ret)->Revision == 0){
                    printf("Using ACPI v1.0\n");
                } else if (((RSDPDescriptor20 *)ret)->firstPart.Revision == 2){
                    printf("Using ACPI v2.0+\n");
                } else {
                    status[0] = 2;
                }
                printf("OEMID: %s\n", ((RSDPDescriptor20 *)ret)->firstPart.OEMID);
            }

            if(memrange0[0] + i == memrange0[1]) status[0] = 2; //we have found nothing
        }
        
        if(status[0] != 1){
            //try to find in mem range 1
            i = 0;
            while(status[1] == 0 || status[1] == 3){
                //printf("%d ", memcmp2((char*)memrange1[0]+i, "RSD PTR ", 8));
                if(memcmp2((char*)memrange1[0]+i, RSDPTR, 8) != 0) i++;
                if(memcmp2((char*)memrange1[0]+i, RSDPTR, 8) == 0){
                    status[1] = 1;
                    ret = (char*)memrange1[0]+i;
                    //RSDPDescriptor *r = (RSDPDescriptor *)ret;
                    if(((RSDPDescriptor *)ret)->Revision == 0){
                    printf("Using ACPI v1.0\n");
                    } else if (((RSDPDescriptor20 *)ret)->firstPart.Revision == 2){
                        printf("Using ACPI v2.0+\n");
                    } else {
                        status[1] = 2;
                    }
                    printf("OEMID: %s\n", ((RSDPDescriptor20 *)ret)->firstPart.OEMID);
                }

                if(memrange1[0] + i == memrange1[1]) status[1] = 2; //we have found nothing
            }
        }
        //printf("status0: %d | status1: %d\n", status[0], status[1]);
        if(status[0] == 1 || status[1] == 1){
            firefly::kernel::print_ramdata(((char*)ret) - 64, 512);
            return (RSDPDescriptor20 *)ret;
        }
        printf("RSDP not found!\n");
        return nullptr;
    }
    void init();
    ACPITable parse_table(RSDPDescriptor20 *r) {
        ACPITable a;
        bool isfadtfound = false;
        if(r->firstPart.Revision == 0){
            a.which_to_use = 0;
            a.Outdated = (RSDT *)((void *)(uintptr_t)r->firstPart.RsdtAddress);
            a.New = nullptr;
            int entries = (a.Outdated->h.Length - sizeof(a.Outdated->h)) / 4;
            for(int i = 0; i < entries; i++){
                ACPISDTHeader *h = (ACPISDTHeader *)((void *)((uintptr_t)a.Outdated->PointerToOtherSDT[i]));
                const char FACPS[4] = {'F', 'A', 'C', 'P'} ;
                if(memcmp2(h->Signature, FACPS, 4) == 0) {
                    a.FADTable = (FADT *)((void *)h);
                    isfadtfound = true;
                } else {
                    if(!isfadtfound){
                        printf("FADT not found!\n");
                        a.FADTable = nullptr;
                    }
                }
            }
        }
        if(r->firstPart.Revision >= 2){
            a.which_to_use = 1;
            a.New = (XSDT *)((void *)r->XsdtAddress);
            a.Outdated = nullptr;
            a.FADTable = nullptr;
        }
        return a;
    }
}