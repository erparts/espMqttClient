/*
Copyright (c) 2022 Bert Melis. All rights reserved.

Parts are based on the original work of Marvin Roger:
https://github.com/marvinroger/async-mqtt-client

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#pragma once

#include <functional>

#include "Packets/Packet.h"

namespace espMqttClientTypes {

enum class DisconnectReason : int8_t {
  TCP_DISCONNECTED = 0,
  MQTT_UNACCEPTABLE_PROTOCOL_VERSION = 1,
  MQTT_IDENTIFIER_REJECTED = 2,
  MQTT_SERVER_UNAVAILABLE = 3,
  MQTT_MALFORMED_CREDENTIALS = 4,
  MQTT_NOT_AUTHORIZED = 5
};

enum class Error : uint8_t {
  MAX_RETRIES = 0,
  OUT_OF_MEMORY = 1
};

struct MessageProperties {
  uint8_t qos;
  bool dup;
  bool retain;
  uint16_t packetId;
};

typedef std::function<void(bool sessionPresent)> OnConnectCallback;
typedef std::function<void(DisconnectReason reason)> OnDisconnectCallback;
typedef std::function<void(uint16_t packetId, uint8_t qos)> OnSubscribeCallback;
typedef std::function<void(uint16_t packetId)> OnUnsubscribeCallback;
typedef std::function<void(const MessageProperties& properties, const char* topic, const uint8_t* payload, size_t len, size_t index, size_t total)> OnMessageCallback;
typedef std::function<void(uint16_t packetId)> OnPublishCallback;
typedef std::function<void(uint16_t packetId, Error error)> OnErrorCallback;

}  // end namespace espMqttClientTypes
