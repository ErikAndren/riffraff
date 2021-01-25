#include "util.h"
#include "rifrap.h"

int main(int argc, char *argv[]) {
	int status;
	uint8_t idps[16];
	const char *exdata_path = argv[2];
	const char *rif_file = argv[3];
	const char *out_path = argv[4];

	printf("Welcome to riffraff. Used to convert rif to rap files\n");

	if (argc != 5) {
		printf("Invalid number of arguments\n");
		printf("First argument is path to idps_key (16 bytes)\n");
		printf("Second argument is path to where act.dat is located\n");
		printf("Third argument is path to rif file\n");
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
	printf("Rif file is: %s\n", rif_file);
	printf("Output directory is %s\n", out_path);

	status = rif2rap(idps, exdata_path, rif_file, out_path);
	if (status == 0) {
		printf("Failed to create rap file\n");
		return -1;
	}
	printf("Rap file created in dir %s\n", out_path);
	return 0;
}
