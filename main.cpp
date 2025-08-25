#include "stm32l4r5xx.h"

constexpr uint32_t LED2 = 7;

void sleep() {
  for (volatile int i = 0; i < 400000; i++) {
    __asm__("nop");
  }
}

void enable_port_b() {
  // Enable GPIO clock
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
}

void enable_status_led() {

  // clear mode bits and set to output mode (01)
  GPIOB->MODER &= ~(3u << (LED2 << 1));
  GPIOB->MODER |= (1 << (LED2 << 1));

  // turn LED on
  GPIOB->ODR |= 1 << LED2;
}

void toggle_led(uint32_t bit) { GPIOB->ODR ^= 1 << bit; }

int main() {
  enable_port_b();
  enable_status_led();

  // variable to inspect in debugger
  int counter = 0;

  while (true) {
    toggle_led(LED2);
    counter++;
    sleep();
  }
}
