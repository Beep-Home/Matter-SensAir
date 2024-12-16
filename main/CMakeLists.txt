idf_component_register(SRC_DIRS           "." "components"
                       PRIV_INCLUDE_DIRS  "." "${ESP_MATTER_PATH}/examples/common/utils"
                       REQUIRES           esp_matter espressif__led_strip utkumaden__esp-idf-bmx280 driver)

set_property(TARGET ${COMPONENT_LIB} PROPERTY CXX_STANDARD 17)
target_compile_options(${COMPONENT_LIB} PRIVATE "-DCHIP_HAVE_CONFIG_H")
