#include "stm32l4r5xx.h"

constexpr uint32_t LED2 = 7;
constexpr uint32_t LED3 = 14;

void wait(int32_t factor) {
  for (volatile int i = 0; i < (factor * 50000); i++) {
    __asm__("nop");
  }
}

void enable_port_b() {
  // Enable GPIO clock
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
}

void enable_pwr() {
  // Enable power registers
  RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
  (void)RCC->APB1ENR1;
}

void set_sysclk_1mhz() {
  // MSIRANGE should only be written while MSI is ready
  while ((RCC->CR & RCC_CR_MSIRDY) == 0) {
  }

  RCC->CR = (RCC->CR & ~RCC_CR_MSIRANGE) | RCC_CR_MSIRANGE_4 | RCC_CR_MSIRGSEL;
}

void enable_status_led() {

  // clear mode bits and set to output mode (01)
  GPIOB->MODER &= ~(3u << (LED2 << 1));
  GPIOB->MODER |= (1 << (LED2 << 1));

  // turn LED on
  GPIOB->ODR |= 1 << LED2;

  // clear mode bits and set to output mode (01)
  GPIOB->MODER &= ~(3u << (LED3 << 1));
  GPIOB->MODER |= (1 << (LED3 << 1));

  // turn LED on
  GPIOB->ODR |= 1 << LED3;
}

// enter low power run mode by setting LPR bit
void enter_lpr() {
  PWR->CR1 |= PWR_CR1_LPR;

  // wait until lpr mode is started
  while ((PWR->SR2 & PWR_SR2_REGLPF) == 0) {
  }
}

// exit low power run mode by clearing LPR bit
void exit_lpr() {
  PWR->CR1 &= ~PWR_CR1_LPR;

  // wait until lpr mode is exited
  while ((PWR->SR2 & PWR_SR2_REGLPF) != 0) {
  }
}

void led_toggle(uint32_t bit) { GPIOB->ODR ^= 1 << bit; }
void led_off(uint32_t bit) { GPIOB->ODR &= ~(1 << bit); }
void led_on(uint32_t bit) { GPIOB->ODR |= 1 << bit; }

[[noreturn]] inline void run() {
  led_off(LED3);
  // variable to inspect in debugger
  int counter = 0;
  while (true) {
    led_toggle(LED2);
    counter++;
    wait(1);
  }
}

[[noreturn]] inline void run_lpr() {
  int counter = 0;
  auto led = LED3;
  led_off(LED3);
  led_off(LED2);
  constexpr int factor = 1;
  bool lpr = false;
  while (true) {

    led_toggle(led);
    counter++;
    wait(factor);

    if (counter % 5 == 0) {
      led_off(led);
      if (!lpr) {
        led = LED2;
        enter_lpr();
      } else {
        led = LED3;
        exit_lpr();
      }
      lpr = !lpr;
    }
  }
}

int main() {
  enable_pwr();
  set_sysclk_1mhz();
  enable_port_b();
  enable_status_led();

  // run();
  run_lpr();
}
