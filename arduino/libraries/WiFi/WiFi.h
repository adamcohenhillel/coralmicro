/*
 * Copyright 2022 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WiFi_h
#define WiFi_h

#include <Arduino.h>

#include <cstdint>
#include <memory>
#include <vector>

#include "libs/base/wifi.h"

// Common encryption types for networks.
enum encryption_type {
  ENC_TYPE_WEP = 5,
  ENC_TYPE_TKIP = 2,
  ENC_TYPE_CCMP = 4,
  ENC_TYPE_NONE = 7,
  ENC_TYPE_UNKNOWN = 9,
  ENC_TYPE_AUTO = 8
};

// Status codes for Wi-Fi.
enum wl_status_t {
  WL_NO_SHIELD = 255,
  WL_IDLE_STATUS = 0,
  WL_NO_SSID_AVAIL,
  WL_SCAN_COMPLETED,
  WL_CONNECTED,
  WL_CONNECT_FAILED,
  WL_CONNECTION_LOST,
  WL_DISCONNECTED
};

namespace coralmicro {
namespace arduino {

// Allows for scanning for and associating with a Wi-Fi network.
// Connection is initiated with the `begin` functions,
// which connect to a specified access point.
// Scanning can be executed via `scanNetworks` and the results
// can be retrieved with the SSID/RSSI/encryptionType methods that
// accept `networkItem`.
// You should not initialize this object yourself, instead include `WiFi.h` and
// use the global `WiFi` instance.
class WiFiClass {
 public:
  // Connects to an open Wi-Fi network.
  //
  // @param ssid The SSID to connect to.
  // @returns WL_CONNECTED on success; WL_CONNECT_FAILED otherwise.
  int begin(const char* ssid);

  // Connects to a Wi-Fi network using a passphrase.
  //
  // @param ssid The SSID to connect to.
  // @param passphrase The passphrase used to connect to the network.
  // @returns WL_CONNECTED on success; WL_CONNECT_FAILED otherwise.
  int begin(const char* ssid, const char* passphrase);

  // Disconnects from the associated Wi-Fi network.
  //
  // @returns WL_DISCONNECTED on success.
  int disconnect();

  // Retrieves the SSID of the associated Wi-Fi network.
  //
  // @returns SSID if the device is connected to a network, empty string
  // otherwise.
  char* SSID();

  // Retrieves the SSID of the `networkItem`-th scan result.
  //
  // @returns SSID of the scan result.
  char* SSID(uint8_t networkItem);

  // Retrieves the BSSID of the access point.
  //
  // @param bssid Pointer to memory where BSSID will be stored.
  // @returns Address of BSSID on success; nullptr otherwise.
  uint8_t* BSSID(uint8_t* bssid);

  // Retrieves the RSSI of the associated Wi-Fi network.
  //
  // @returns RSSI if the device is connected to a network, INT_MIN otherwise.
  int32_t RSSI();

  // Retrieves the RSSI of the `networkItem`-th scan result.
  //
  // @returns RSSI of the scan result.
  int32_t RSSI(uint8_t networkItem);

  // Retrieves the encryption type of the associated Wi-Fi network.
  //
  // @returns Value from `enum encryption_type` representing the network
  // security.
  uint8_t encryptionType();

  // Retrieves the encryption type of the `networkItem`-th scan result.
  //
  // @returns `encryption_type` representing the network security.
  uint8_t encryptionType(uint8_t networkItem);

  // Scans for nearby Wi-Fi networks.
  //
  // @returns The number of networks discovered.
  int8_t scanNetworks();

  // Retrieves the status of the Wi-Fi connection.
  //
  // @returns `wl_status_type` representing the connection status.
  uint8_t status();

  // Retrieves the MAC address of the Wi-Fi module.
  //
  // @param bssid Pointer to memory where the MAC will be stored.
  // @returns Address of MAC on success; nullptr otherwise.
  uint8_t* macAddress(uint8_t* mac);

  // Retrieves the board's wifi ip address.
  // @returns The wifi ip address of the board.
  IPAddress localIP();

 private:
  std::unique_ptr<char[]> ssid_ = nullptr;
  std::vector<WIFIScanResult_t> scan_results_;
  wl_status_t network_status_ = WL_DISCONNECTED;
};

}  // namespace arduino
}  // namespace coralmicro

extern coralmicro::arduino::WiFiClass WiFi;

#endif  // WiFi_h
