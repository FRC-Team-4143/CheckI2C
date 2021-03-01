#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

bool CheckI2C() {
	auto fd{open("/dev/i2c-1", O_RDWR)};
	if (fd < 0) {
		auto e{errno};
		if (EACCES == e) {
			printf("Could not open the I2C bus. Access denied.\n");
			printf("Try: sudo usermod -aG i2c {username}\n");
		}
		else {
			printf("Could not open the I2C bus. Error %d.\n", e);
		}
		return false;
	}

	if (ioctl(fd, I2C_SLAVE, 0x40) < 0) {
		auto e{errno};
		if (EACCES == e) {
			printf("Could not set the I2C slave. Access denied.\n");
			printf("Try: sudo usermod -aG i2c {username}\n");
		}
		else {
			printf("Could not set the I2C slave. Error %d.\n", e);
		}
		close(fd);
		return false;
	}

	printf("Successfully opened the I2C bus.\n");
	close(fd);
	return true;
}

int main() {
	CheckI2C();
	return 0;
}
