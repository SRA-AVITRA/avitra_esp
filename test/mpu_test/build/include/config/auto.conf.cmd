deps_config := \
	/home/shanks/esp/esp-idf/components/app_trace/Kconfig \
	/home/shanks/esp/esp-idf/components/aws_iot/Kconfig \
	/home/shanks/esp/esp-idf/components/bt/Kconfig \
	/home/shanks/esp/esp-idf/components/driver/Kconfig \
	/home/shanks/esp/esp-idf/components/efuse/Kconfig \
	/home/shanks/esp/esp-idf/components/esp32/Kconfig \
	/home/shanks/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/shanks/esp/esp-idf/components/esp_event/Kconfig \
	/home/shanks/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/shanks/esp/esp-idf/components/esp_http_server/Kconfig \
	/home/shanks/esp/esp-idf/components/esp_https_ota/Kconfig \
	/home/shanks/esp/esp-idf/components/espcoredump/Kconfig \
	/home/shanks/esp/esp-idf/components/ethernet/Kconfig \
	/home/shanks/esp/esp-idf/components/fatfs/Kconfig \
	/home/shanks/esp/esp-idf/components/freemodbus/Kconfig \
	/home/shanks/esp/esp-idf/components/freertos/Kconfig \
	/home/shanks/esp/esp-idf/components/heap/Kconfig \
	/home/shanks/esp/esp-idf/components/libsodium/Kconfig \
	/home/shanks/esp/esp-idf/components/log/Kconfig \
	/home/shanks/esp/esp-idf/components/lwip/Kconfig \
	/home/shanks/esp/esp-idf/components/mbedtls/Kconfig \
	/home/shanks/esp/esp-idf/components/mdns/Kconfig \
	/home/shanks/esp/esp-idf/components/mqtt/Kconfig \
	/home/shanks/esp/esp-idf/components/nvs_flash/Kconfig \
	/home/shanks/esp/esp-idf/components/openssl/Kconfig \
	/home/shanks/esp/esp-idf/components/pthread/Kconfig \
	/home/shanks/esp/esp-idf/components/spi_flash/Kconfig \
	/home/shanks/esp/esp-idf/components/spiffs/Kconfig \
	/home/shanks/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/shanks/esp/esp-idf/components/unity/Kconfig \
	/home/shanks/esp/esp-idf/components/vfs/Kconfig \
	/home/shanks/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/shanks/esp/esp-idf/components/wifi_provisioning/Kconfig \
	/home/shanks/esp/esp-idf/components/app_update/Kconfig.projbuild \
	/home/shanks/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/shanks/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/shanks/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/shanks/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_TARGET)" "esp32"
include/config/auto.conf: FORCE
endif
ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
