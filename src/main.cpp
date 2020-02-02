#include <iostream>
#include <string>
#include "mqtt_client.hpp"

////////////////////////////////////////////////////////////////////////////////
// MAIN LOOP
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
  mqtt_client client("dummy_client_id");
  client.publish("test_topic", "test_msg");
  while (std::tolower(std::cin.get()) != 'q');
  return 0;
}
