// 20130303
#define NIAGARA_VERSION_MAJOR 0
#define NIAGARA_VERSION_MINOR 5
#define NIAGARA_VERSION_BUILD 2
#define NIAGARA_VERSION ((NIAGARA_VERSION_MAJOR << 16) | (NIAGARA_VERSION_MINOR << 8) | NIAGARA_VERSION_BUILD)

int NiagaraGetAttribute(int card, int segment, const char *attribute, unsigned *value);
int NiagaraSetAttribute(int card, int segment, const char *attribute, unsigned value);

int NiagaraGetCardName(int card, char *name, size_t namesize);
