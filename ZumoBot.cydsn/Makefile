################################### Include Directories ########################################
ZUMOLIB 			= ./projects/zumo/ZumoBot.cydsn/ZumoLibrary
FREERTOSINC 		= ./projects/zumo/FreeRTOS/Source/include
FREERTOSARMCM3 		= ./projects/zumo/FreeRTOS/Source/portable/GCC/ARM_CM3
MQTTCLIENTSOURCE 	= ./projects/zumo/paho.mqtt.embedded-c/MQTTClient-C/src
MQTTPACKETSOURCE 	= ./projects/zumo/paho.mqtt.embedded-c/MQTTPacket/src
MQTTFREERTOS 		= ./projects/zumo/paho.mqtt.embedded-c/MQTTClient-C/src/FreeRTOS
GENSOURCEPSOC		= ./projects/zumo/ZumoBot.cydsn/Generated_Source/PSoC5/
#################################################################################################

######################################## defines ################################################
DEBUG 	= DEBUG
MQTT_T	= MQTT_TASK
MQTT_H  = MQTTCLIENT_PLATFORM_HEADER=MQTTFreeRTOS.h 
#################################################################################################

CC       := clang
CFLAGS   = -Wall -fsyntax-only -I$(ZUMOLIB) -I$(FREERTOSINC) -I$(FREERTOSARMCM3) -I$(MQTTCLIENTSOURCE) -I$(MQTTFREERTOS) -I$(MQTTPACKETSOURCE) -I$(GENSOURCEPSOC) -D$(DEBUG) -D$(MQTT_T) -D$(MQTT_H)
SOURCE   = $(wildcard ./projects/zumo/upload/*.c) $(wildcard ./projects/zumo/upload/*.cpp)
TARGET   = PSOC

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SOURCE) $(LDFLAGS)
