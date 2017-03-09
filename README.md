# Automation
Home automation and monitoring based on MQTT and ESP8266. There are a series of nodes, which can function as a producer or consumer of messages (or both). Right now, there are three types of node:

* Temperature sensor nodes, which have a small temperature sensor and broadcast the reading every few seconds (a PCB exists for these).
* Switcher nodes, which contain a relay to switch stuff on and off (a PCB exists for low-voltage switching)
* Message board nodes, which contain an LED matrix display so that output can be communicated to the real world.

These nodes each connect to an MQTT broker, which could be something like Mosquitto running on a Raspberry Pi. There's then some glue logic that needs to exist (e.g. NodeRed) that allows the whole system to respond to changes on the inputs. Some work is requred to get all this working, and this is left as an exercise for the student. 
