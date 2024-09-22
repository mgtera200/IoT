#!/bin/bash


MQTT_PORT=1883            
MQTT_TOPIC="laptop/battery"  



INTERVAL=3


get_battery_info() {
 
  BATTERY_PERCENTAGE=$(cat /sys/class/power_supply/BAT0/capacity)
  
  
  BATTERY_STATUS=$(cat /sys/class/power_supply/BAT0/status)

  
  PAYLOAD="percentage:$BATTERY_PERCENTAGE,status:$BATTERY_STATUS"

  
  mosquitto_pub -t "$MQTT_TOPIC" -m "$PAYLOAD"

  echo "Published battery info: $PAYLOAD"
}


while true; do
  get_battery_info
  sleep $INTERVAL
done

