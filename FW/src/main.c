#include "main.h"

void _setup_gpio_output(uint gpio)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, true);
    gpio_put(gpio, true);
}

void _setup_gpio_input(uint gpio)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, false);
}

void _gpio_put_od(uint gpio, bool level)
{
    if(level)
    {
        gpio_set_dir(gpio, GPIO_IN);
        //gpio_pull_up(gpio);
        gpio_put(gpio, 1);
        gpio_disable_pulls(gpio);
    }
    else
    {
        gpio_set_dir(gpio, GPIO_OUT);
        gpio_disable_pulls(gpio);
        gpio_put(gpio, 0);
    }
}

button_remap_s user_map = {
    .dpad_up = MAPCODE_DUP,
    .dpad_down = MAPCODE_DDOWN,
    .dpad_left = MAPCODE_DLEFT,
    .dpad_right = MAPCODE_DRIGHT,

    .button_a = MAPCODE_B_A,
    .button_b = MAPCODE_B_B,
    .button_x = MAPCODE_B_X,
    .button_y = MAPCODE_B_Y,

    .trigger_l = MAPCODE_T_ZL,
    .trigger_r = MAPCODE_T_ZR,
    .trigger_zl = MAPCODE_T_L,
    .trigger_zr = MAPCODE_T_R,

    .button_plus = MAPCODE_B_PLUS,
    .button_minus = MAPCODE_B_MINUS,
    .button_stick_left = MAPCODE_B_STICKL,
    .button_stick_right = MAPCODE_B_STICKR,
};

void cb_hoja_hardware_setup()
{
    _setup_gpio_output(GPIO_DLEFT_3);
    _setup_gpio_output(GPIO_DUP_3);
    _setup_gpio_output(GPIO_DRIGHT_3);
    _setup_gpio_output(GPIO_DDOWN_3);
    _setup_gpio_output(GPIO_SELECT_3);
    _setup_gpio_output(GPIO_START_3);
    _setup_gpio_output(GPIO_B_3);
    _setup_gpio_output(GPIO_A_3);

    _setup_gpio_input(GPIO_DLEFT);
    _setup_gpio_input(GPIO_DUP);
    _setup_gpio_input(GPIO_DRIGHT);
    _setup_gpio_input(GPIO_DDOWN);
    _setup_gpio_input(GPIO_SELECT);
    _setup_gpio_input(GPIO_START);
    _setup_gpio_input(GPIO_B);
    _setup_gpio_input(GPIO_A);
}

void cb_hoja_read_buttons(button_data_s *data)
{
    // Keypad version
    gpio_put(PGPIO_SCAN_A, false);
    sleep_us(5);
    data->button_a  = !gpio_get(PGPIO_PUSH_C);

    data->button_b  = !gpio_get(PGPIO_PUSH_D);
    data->button_x  = !gpio_get(PGPIO_PUSH_A);
    data->button_y  = !gpio_get(PGPIO_PUSH_B);
    gpio_put(PGPIO_SCAN_A, true);

    gpio_put(PGPIO_SCAN_B, false);
    sleep_us(5);
    data->dpad_left     = !gpio_get(PGPIO_PUSH_D);
    data->dpad_right    = !gpio_get(PGPIO_PUSH_C);
    data->dpad_down     = !gpio_get(PGPIO_PUSH_B);
    data->dpad_up       = !gpio_get(PGPIO_PUSH_A);
    gpio_put(PGPIO_SCAN_B, true);

    gpio_put(PGPIO_SCAN_C, false);
    sleep_us(5);
    data->trigger_l       = !gpio_get(PGPIO_PUSH_C);
    data->trigger_r       = !gpio_get(PGPIO_PUSH_B);
    data->button_plus     = !gpio_get(PGPIO_PUSH_A);
    //
    gpio_put(PGPIO_SCAN_C, true);

    data->button_minus =!gpio_get(PGPIO_BUTTON_PWRSELECT);
    data->button_shipping = data->button_minus;

    if(data->button_minus && data->trigger_r)
    {
        data->button_minus = false;
        data->trigger_r = false;
        data->button_home = true;
    }
    else data->button_home = false;

    if(data->button_minus && data->trigger_l)
    {
        data->button_minus = false;
        data->trigger_l = false;
        data->button_capture = true;
    }
    else data->button_capture = false;
    
    data->button_sync       = data->button_plus;

}

void cb_hoja_read_analog(a_data_s *data)
{
    // Convert data
    data->lx = 2048;
    data->ly = 2048;
    data->rx = 2048;
    data->ry = 2048;
}

void cb_hoja_task_1_hook(uint32_t timestamp)
{
    //app_rumble_task(timestamp);
}

int main()
{
    stdio_init_all();
    sleep_ms(100);

    printf("SuperGamepad+ Started.\n");

    cb_hoja_hardware_setup();

    gpio_init(PGPIO_ESP_EN);
    cb_hoja_set_bluetooth_enabled(false);

    gpio_init(PGPIO_BUTTON_USB_EN);
    gpio_set_dir(PGPIO_BUTTON_USB_EN, GPIO_OUT);
    gpio_put(PGPIO_BUTTON_USB_EN, 0);

    gpio_init(PGPIO_BUTTON_USB_SEL);
    gpio_set_dir(PGPIO_BUTTON_USB_SEL, GPIO_OUT);
    gpio_put(PGPIO_BUTTON_USB_SEL, 0);

    button_data_s tmp = {0};
    cb_hoja_read_buttons(&tmp);

    hoja_config_t _config = {
        .input_method   = INPUT_METHOD_AUTO,
        .input_mode     = INPUT_MODE_LOAD,
    };

    if(tmp.button_plus && tmp.trigger_l)
    {
        reset_usb_boot(0, 0);
    }
    else if (tmp.button_plus && tmp.trigger_r)
    {
        _config.input_method    = INPUT_METHOD_BLUETOOTH;
        _config.input_mode      = INPUT_MODE_BASEBANDUPDATE;
    }
    
    hoja_init(&_config);
}
