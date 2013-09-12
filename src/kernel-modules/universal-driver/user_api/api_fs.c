#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <niagara_api.h>

//please, chose one of two:
//#define PREFIX "/proc/niagara/"
#define PREFIX "/sys/devices/virtual/niagara/"

#define error(fmt, args ...) do { fprintf(stderr, fmt ":%m\n", ## args); exit(EXIT_FAILURE); } while (0)

static FILE *niagara_attribute_open(int card, int segment, const char *name, const char *mode)
{
	char fname[256];
	FILE *f;

	snprintf(fname, sizeof(fname), PREFIX "%X/%X/%s", card, segment, name);
	f = fopen(fname, mode);
	if (f) return f;
	snprintf(fname, sizeof(fname), PREFIX "%X/%s", card, name);
	f = fopen(fname, mode);
	if (f) return f;
	snprintf(fname, sizeof(fname), PREFIX "%s", name);
	f = fopen(fname, mode);
	return f;
}

int NiagaraGetAttribute(int card, int segment, const char *name, unsigned *value)
{
	FILE *f = niagara_attribute_open(card, segment, name, "r");

	if (f == NULL) error("Can't open %s in %s", name, PREFIX);
	if (fscanf(f, "%X", value) != 1) {
		fclose(f); error("Can't read %s", name);
	}
	fclose(f);
	return 0;
}
int NiagaraSetAttribute(int card, int segment, const char *name, unsigned value)
{
	FILE *f = niagara_attribute_open(card, segment, name, "w");

	if (f == NULL) error("Can't open %s in %s", name, PREFIX);
	fprintf(f, "%X\n", value);
	fclose(f);
	return 0;
}

int NiagaraGetCardName(int card, char *name, size_t namesize)
{
	FILE *f = niagara_attribute_open(card, 0, "name", "r");
	char *nptr;

	if (f == NULL) error("Can't open \"name\" in %s%X", PREFIX, card);
	fgets(name, namesize, f);
	fclose(f);
	nptr = strrchr(name, '\n');
	if (nptr) *nptr = 0;
	return 0;
}
