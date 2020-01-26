#include <iostream>
#include <string>
#include <unistd.h>
#include "mqtt_client.hpp"

////////////////////////////////////////////////////////////////////////////////
// MAIN LOOP
////////////////////////////////////////////////////////////////////////////////

// TODO: block thread until connection is established

int main(int argc, char* argv[]) {
  mqtt_client client("dummy_client_id");
  sleep(5);
  client.publish("test_topic", "test_msg");
  while (std::tolower(std::cin.get()) != 'q');
  return 0;
}
