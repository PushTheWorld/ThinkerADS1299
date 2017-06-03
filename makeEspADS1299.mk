# Thinker ADS1299 Make Files
PROJECT_NAME = ThinkerADS1299
FILE_NAME = $(PROJECT_NAME)
LIBARAIES_DIR = $(HOME)/Documents/Arduino/libraries
SKETCH = $(LIBARAIES_DIR)/$(PROJECT_NAME)/$(FILE_NAME).ino
OPENBCI_WIFI_DIR = $(LIBARAIES_DIR)/OpenBCI_Wifi

UPLOAD_PORT = /dev/cu.usbserial-A104JV88
ESP_ROOT = $(HOME)/esp8266
ESP_LIBS = $(ESP_ROOT)/libraries

LIBS = $(ESP_LIBS)/SPI $(LIBARAIES_DIR)/ADS1299

# EXCLUDE_DIRS = $(LIBARAIES_DIR)/ArduinoJson/test $(LIBARAIES_DIR)/ArduinoJson/fuzzing $(LIBARAIES_DIR)/WebSockets/examples

include $(HOME)/makeEspArduino/makeEspArduino.mk
