lib_LIBRARIES = libvega.a

#libvega_a_CFLAGS = @VEGA_FLAGS@ 
#libvega_a_CCASFLAGS = @VEGA_FLAGS@ 


libvega_a_SOURCES = \
	./drivers/uart/uart.c \
	./drivers/uart/debug_uart.c \
	./drivers/gpio/gpio.c \
	./drivers/gpio/led.c \
	./drivers/i2c/i2c.c \
	./drivers/spi/spi.c \
	./drivers/timer/timer.c \
	./drivers/adc/adc.c \
	./drivers/interrupt/interrupt.c \
	./common/stdlib.c \
	./common/rawfloat.c \
	./common/crt.S
	
nobase_include_HEADERS = \
	./include/gpio.h \
	./include/i2c.h \
	./include/m25p80_eeprom.h \
	./include/config.h \
	./include/spi.h \
	./include/timer.h \
	./include/uart.h \
	./include/debug_uart.h \
	./include/adc.h \
	./include/interrupt.h \
	./include/led.h \
	./include/encoding.h \
	./include/stdlib.h


