#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

/* RGB LED pins */
#define RED_PIN     18
#define GREEN_PIN   19
#define BLUE_PIN    1

/* GPIO controllers */
#define RED_GPIO    DT_NODELABEL(gpiob)
#define GREEN_GPIO  DT_NODELABEL(gpiob)
#define BLUE_GPIO   DT_NODELABEL(gpiod)

static const struct device *gpiob = DEVICE_DT_GET(RED_GPIO);
static const struct device *gpiod = DEVICE_DT_GET(BLUE_GPIO);

void leds_off(void)
{
    gpio_pin_set(gpiob, RED_PIN, 1);
    gpio_pin_set(gpiob, GREEN_PIN, 1);
    gpio_pin_set(gpiod, BLUE_PIN, 1);
}

void red_on(void)
{
    leds_off();
    gpio_pin_set(gpiob, RED_PIN, 0);
}

void yellow_on(void)
{
    leds_off();

    /* Red + Green = Yellow */
    gpio_pin_set(gpiob, RED_PIN, 0);
    gpio_pin_set(gpiob, GREEN_PIN, 0);
}

void green_on(void)
{
    leds_off();
    gpio_pin_set(gpiob, GREEN_PIN, 0);
}

int main(void)
{
    if (!device_is_ready(gpiob) || !device_is_ready(gpiod)) {
        return -1;
    }

    /* Configure pins as outputs */
    gpio_pin_configure(gpiob, RED_PIN, GPIO_OUTPUT_HIGH);
    gpio_pin_configure(gpiob, GREEN_PIN, GPIO_OUTPUT_HIGH);
    gpio_pin_configure(gpiod, BLUE_PIN, GPIO_OUTPUT_HIGH);

    while (1) {

        /* RED */
        red_on();
        k_msleep(5000);

        /* GREEN */
        green_on();
        k_msleep(5000);

		/* YELLOW */
        yellow_on();
        k_msleep(2000);
    }
	
    return 0;
}