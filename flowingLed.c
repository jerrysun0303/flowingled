#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LED0_PATH "/sys/class/leds/led0/brightness"
#define LED1_PATH "/sys/class/leds/led1/brightness"

void write_brightness(const char *path, int brightness) {
  int fd = open(path, O_WRONLY);
  if (fd == -1)
    return;
  char buffer[10];
  snprintf(buffer, sizeof(buffer), "%d", brightness);
  if (write(fd, buffer, strlen(buffer)) < 0)     return;

  close(fd);
}

int main() {
  while (1) {
    printf("Green: off  Red: on\n");
    write_brightness(LED0_PATH, 0);
    write_brightness(LED1_PATH, 0);
    sleep(1);

    printf("Green: on   Red: off\n");
    write_brightness(LED0_PATH, 255);
    write_brightness(LED1_PATH, 255);
    sleep(1);
  }
  return 0;
}