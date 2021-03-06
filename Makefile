################################### Include Directories ########################################
ZUMOLIB 			= ./ZumoBot.cydsn/ZumoLibrary
FREERTOSINC 		= ./FreeRTOS/Source/include
FREERTOSARMCM3 		= ./FreeRTOS/Source/portable/GCC/ARM_CM3
MQTTCLIENTSOURCE 	= ./paho.mqtt.embedded-c/MQTTClient-C/src
MQTTPACKETSOURCE 	= ./paho.mqtt.embedded-c/MQTTPacket/src
MQTTFREERTOS 		= ./paho.mqtt.embedded-c/MQTTClient-C/src/FreeRTOS
GENSOURCEPSOC		= ./ZumoBot.cydsn/Generated_Source/PSoC5/
#################################################################################################

######################################## defines ################################################
DEBUG 	= DEBUG
MQTT_T	= MQTT_TASK
MQTT_H  = MQTTCLIENT_PLATFORM_HEADER=MQTTFreeRTOS.h 
#################################################################################################

CC       := clang
FORMAT   := clang-format
CFLAGS   = -Wall -fsyntax-only -I$(ZUMOLIB) -I$(FREERTOSINC) -I$(FREERTOSARMCM3) -I$(MQTTCLIENTSOURCE) -I$(MQTTFREERTOS) -I$(MQTTPACKETSOURCE) -I$(GENSOURCEPSOC) -D$(DEBUG) -D$(MQTT_T) -D$(MQTT_H)
FFLAGS   := -i
SOURCE   = $(wildcard ./upload/*.c) $(wildcard ./upload/*.cpp)
TARGET   = PSOC

all: $(TARGET)

$(TARGET):
	$(FORMAT) $(FFLAGS) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) $(LDFLAGS)

