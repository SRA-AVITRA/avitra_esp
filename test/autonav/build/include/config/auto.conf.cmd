deps_config := \
	/home/shweta/esp/esp-idf/components/app_trace/Kconfig \
	/home/shweta/esp/esp-idf/components/aws_iot/Kconfig \
	/home/shweta/esp/esp-idf/components/bt/Kconfig \
	/home/shweta/esp/esp-idf/components/driver/Kconfig \
	/home/shweta/esp/esp-idf/components/efuse/Kconfig \
	/home/shweta/esp/esp-idf/components/esp32/Kconfig \
	/home/shweta/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/shweta/esp/esp-idf/components/esp_event/Kconfig \
	/home/shweta/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/shweta/esp/esp-idf/components/esp_http_server/Kconfig \
	/home/shweta/esp/esp-idf/components/esp_https_ota/Kconfig \
	/home/shweta/esp/esp-idf/components/espcoredump/Kconfig \
	/home/shweta/esp/esp-idf/components/ethernet/Kconfig \
	/home/shweta/esp/esp-idf/components/fatfs/Kconfig \
	/home/shweta/esp/esp-idf/components/freemodbus/Kconfig \
	/home/shweta/esp/esp-idf/components/freertos/Kconfig \
	/home/shweta/esp/esp-idf/components/heap/Kconfig \
	/home/shweta/esp/esp-idf/components/libsodium/Kconfig \
	/home/shweta/esp/esp-idf/components/log/Kconfig \
	/home/shweta/esp/esp-idf/components/lwip/Kconfig \
	/home/shweta/esp/esp-idf/components/mbedtls/Kconfig \
	/home/shweta/esp/esp-idf/components/mdns/Kconfig \
	/home/shweta/esp/esp-idf/components/mqtt/Kconfig \
	/home/shweta/esp/esp-idf/components/nvs_flash/Kconfig \
	/home/shweta/esp/esp-idf/components/openssl/Kconfig \
	/home/shweta/esp/esp-idf/components/pthread/Kconfig \
	/home/shweta/esp/esp-idf/components/rosserial_esp32/Kconfig \
	/home/shweta/esp/esp-idf/components/spi_flash/Kconfig \
	/home/shweta/esp/esp-idf/components/spiffs/Kconfig \
	/home/shweta/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/shweta/esp/esp-idf/components/unity/Kconfig \
	/home/shweta/esp/esp-idf/components/vfs/Kconfig \
	/home/shweta/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/shweta/esp/esp-idf/components/wifi_provisioning/Kconfig \
	/home/shweta/esp/esp-idf/components/app_update/Kconfig.projbuild \
	/home/shweta/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/shweta/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/shweta/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/shweta/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_TARGET)" "esp32"
include/config/auto.conf: FORCE
endif
ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
