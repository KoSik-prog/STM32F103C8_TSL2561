<h1 align="center">TSL2561/GY-2561 Simple Library for STM32</h1>

- HAL library uses
- without sensor inetrrupt handling

<h2>How to use:</h2>

<h3>INIT:</h3>

    #define TSL2561_ADDRESS (0x39 << 1) // sensor address
    uint8_t ret = tsl2561_init(&hi2c2, TSL2561_ADDRESS, TSL2561_INTEG_101);

<h3>READ:</h3>

    float light = tsl2561_readLux();

## :memo: License ##
This project is licensed under the MIT License. For more details, please refer to the [LICENSE](LICENSE.md) file.

<br/>
<p align="center">Made by <a href="https://github.com/kosik-prog/" target="_blank">KoSik</a><p/>
<br/>
<a href="#top">Back to top</a>