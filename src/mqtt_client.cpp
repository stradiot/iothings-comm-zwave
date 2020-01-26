#include <stdexcept>
#include <iostream>
#include <array>
#include "mqtt_client.hpp"

////////////////////////////////////////////////////////////////////////////////
// CONSTANTS DEFINITION
////////////////////////////////////////////////////////////////////////////////

const std::string DEF_HOST = "tcp://localhost:1883";

const char* LWT_TOPIC = "last_will";
const char* LWT_PAYLOAD = "Last will and testament.";

const int  QOS = 2;

const auto PUB_TIMEOUT = std::chrono::seconds(2);

const std::array<std::string, 1> SUB_TOPICS = { "dummy_topic" }; 

////////////////////////////////////////////////////////////////////////////////
// MQTT CLIENT CALLBACK
////////////////////////////////////////////////////////////////////////////////

void mqtt_client::callback::on_failure(const mqtt::token& tok) {
  std::cout << "Connection attempt failed" << std::endl;
  cli_.reconnect();
}

void mqtt_client::callback::connected(const std::string& cause) {
  std::cout << "\nConnection success" << std::endl;

  for(const std::string& topic : SUB_TOPICS)
    cli_.subscribe(topic, QOS); 
}

void mqtt_client::callback::connection_lost(const std::string& cause){
  std::cout << "\nConnection lost" << std::endl;
  if (!cause.empty())
    std::cout << "\tcause: " << cause << std::endl;

  std::cout << "Reconnecting..." << std::endl;
  cli_.reconnect();
}

void mqtt_client::callback::message_arrived(mqtt::const_message_ptr msg) {
  std::cout << "Message arrived" << std::endl;
  std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
  std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;
}

mqtt_client::mqtt_client(std::string client_id) {
  if (!client_id.length()) {
    throw std::invalid_argument("empty client ID specified");
  }

  mqtt::message last_will_message(LWT_TOPIC, LWT_PAYLOAD, QOS, false);
  mqtt::will_options last_will(last_will_message);

  mqtt::connect_options conn_opts;
  conn_opts.set_will(last_will);
	conn_opts.set_keep_alive_interval(20);
	conn_opts.set_clean_session(true);

	client = new mqtt::async_client(DEF_HOST, client_id);
  cb = new callback(*client, conn_opts);
	client->set_callback(*cb);

	try {
		std::cout << "Connecting to the MQTT server..." << std::flush;
		client->connect(conn_opts, nullptr, *cb);
	}
	catch (const mqtt::exception&) {
		std::cerr << "\nERROR: Unable to connect to MQTT server: '"
			<< DEF_HOST << "'" << std::endl;
	}
}

void mqtt_client::publish(std::string topic, std::string message, uint8_t qos) {
  try {
    std::cout << "\nSending message..." << std::endl;
    mqtt::message_ptr pubmsg = mqtt::make_message(topic, message, qos, false);
    mqtt::delivery_token_ptr pubtok = client->publish(pubmsg);
    pubtok->wait();
    std::cout << "  ...OK" << std::endl;
  } catch (const mqtt::exception& exc){
    std::cerr << exc.what() << std::endl;
  }
}

mqtt_client::~mqtt_client() {
	try {
		std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
		client->disconnect()->wait();
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
	}

  free(client);
  free(cb);
}
