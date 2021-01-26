#include "util.h"
#include "rifrap.h"

int main(int argc, char *argv[]) {
	int status;
	uint8_t idps[16];
	const char *exdata_path = argv[2];
	const char *rifrap_file = argv[3];
	const char *out_path = argv[4];
	char *rifrap_file_ext;

	printf("Welcome to riffraff. Used to convert rif to rap files and vice versa\n");

	if (argc != 5) {
		printf("Invalid number of arguments\n");
		printf("First argument is path to idps_key (16 bytes)\n");
		printf("Second argument is path to where act.dat is located\n");
		printf("Third argument is path to rif/rap file\n");
		printf("Fourth argument is the path where the generated rap is stored\n");

		return -1;
	}

	status = read_file(argv[1], idps, 16);
	if (status != 0) {
		printf("Failed to parse idps_key: error %d\n", status);
		return status;
	}
	printf("IDPS key is: ");
	for (int i = 0; i < 16; i++) {
		printf("%x", idps[i]);
	}
	printf("\n");

	printf("Exdata path is: %s\n", exdata_path);

	if (strlen(rifrap_file) < 4) {
		printf("rif/rap file is too short: %s\n", rifrap_file);
		return -1;
	}

	rifrap_file_ext = strrchr(rifrap_file, '.');
	if (rifrap_file_ext == NULL) {
		printf("Could not find file extension. Only .rif or .rap files are supported\n");
		return -1;
	}

	if (strcmp(rifrap_file_ext, ".rif") == 0) {
		printf("Rif file detected: %s. Will generate rap\n", rifrap_file);
		status = rif2rap(idps, exdata_path, rifrap_file, out_path);
		if (status == 0) {
			printf("Failed to create rap file\n");
			return -1;
		}
		printf("Rap file created in dir %s\n", out_path);
	} else if (strcmp(rifrap_file_ext, ".rap") == 0) {
		printf("Rap file detected: %s. Will generate rif\n", rifrap_file);
		status = rap2rif(idps, exdata_path, rifrap_file, out_path);
		if (status == 0) {
			printf("Failed to create rif file\n");
			return -1;
		}
		printf("Rif file created in dir %s\n", out_path);

	} else {
		printf("Failed to detect neither a .rif or .rap file: %s\n", rifrap_file);
		return -1;
	}

	return 0;
}
