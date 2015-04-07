/*
** Simple utility to convert a NDS Rom to a 2SF.
** Based on EXE2PSF code, written by Neill Corlett
** Released under the terms of the GNU General Public License
**
** You need zlib to compile this.
** It's available at http://www.gzip.org/zlib/
*/

#define APP_NAME	"rom2sf"
#define APP_VER		"[2015-04-07]"
#define APP_DESC	"NDS ROM to 2SF Converter"
#define APP_AUTHOR	"loveemu <http://github.com/loveemu/rom2sf>"

#ifdef _WIN32
#define ZLIB_WINAPI
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string>
#include <sstream>
#include <map>

#include <zlib.h>

#include "rom2sf.h"
#include "nds2sf.h"
#include "cbyteio.h"
#include "cpath.h"

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#include <sys/stat.h>
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define _chdir(s)	chdir((s))
#define _mkdir(s)	mkdir((s), 0777)
#define _rmdir(s)	rmdir((s))
#endif

void printUsage(const char *cmd)
{
	const char *availableOptions[] = {
		"--help", "Show this help",
		"--psfby, --2sfby [name]", "Set creator name of 2SF",
	};

	printf("%s %s\n", APP_NAME, APP_VER);
	printf("======================\n");
	printf("\n");
	printf("%s. Created by %s.\n", APP_DESC, APP_AUTHOR);
	printf("\n");
	printf("Usage\n");
	printf("-----\n");
	printf("\n");
	printf("Syntax: `%s <NDS Files>`\n", cmd);
	printf("\n");
	printf("### Options ###\n");
	printf("\n");

	for (int i = 0; i < sizeof(availableOptions) / sizeof(availableOptions[0]); i += 2)
	{
		printf("%s\n", availableOptions[i]);
		printf("  : %s\n", availableOptions[i + 1]);
		printf("\n");
	}
}

int main(int argc, char **argv)
{
	bool result;
	int argnum;
	int argi;

	char *psfby = NULL;

	argi = 1;
	while (argi < argc && argv[argi][0] == '-')
	{
		if (strcmp(argv[argi], "--help") == 0)
		{
			printUsage(argv[0]);
			return EXIT_SUCCESS;
		}
		else if (strcmp(argv[argi], "--psfby") == 0 || strcmp(argv[argi], "--2sfby") == 0)
		{
			if (argi + 1 >= argc) {
				fprintf(stderr, "Error: Too few arguments for \"%s\"\n", argv[argi]);
				return EXIT_FAILURE;
			}

			psfby = argv[argi];
			argi++;
		}
		else
		{
			fprintf(stderr, "Error: Unknown option \"%s\"\n", argv[argi]);
			return EXIT_FAILURE;
		}
		argi++;
	}

	argnum = argc - argi;
	if (argnum == 0)
	{
		fprintf(stderr, "Error: No input files.\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "Run \"%s --help\" for help.\n", argv[0]);
		return EXIT_FAILURE;
	}

	result = true;
	for (; argi < argc; argi++)
	{
		char nds_path[PATH_MAX];
		char nds2sf_path[PATH_MAX];

		strcpy(nds_path, argv[argi]);
		strcpy(nds2sf_path, nds_path);
		path_stripext(nds2sf_path);
		strcat(nds2sf_path, ".2sf");

		std::map<std::string, std::string> tags;
		if (psfby != NULL && strcmp(psfby, "") != 0) {
			tags["2sfby"] = psfby;
		}

		if (NDS2SF::exe2sf_file(nds_path, nds2sf_path, tags)) {
			printf("Converted %s to %s\n", nds_path, nds2sf_path);
		}
		else {
			printf("Error: Unable to convert %s to %s\n", nds_path, nds2sf_path);
			result = false;
		}
	}

	return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
