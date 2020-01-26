#ifndef MQTT_CLIENT_HPP
#define MQTT_CLIENT_HPP

#include <string>
#include "mqtt/async_client.h"

class mqtt_client {
  private:
    class callback : public virtual mqtt::callback,	public virtual mqtt::iaction_listener {
      private:
        mqtt::async_client& cli_;
        mqtt::connect_options& connOpts_;

        void on_failure(const mqtt::token& tok) override;
        void on_success(const mqtt::token& tok) override {}
        void connected(const std::string& cause) override;
        void connection_lost(const std::string& cause) override;
        void message_arrived(mqtt::const_message_ptr msg) override;
        void delivery_complete(mqtt::delivery_token_ptr token) override {}
      public:
        callback(mqtt::async_client& cli, mqtt::connect_options& connOpts)
          : cli_(cli), connOpts_(connOpts) {}
    };

    mqtt::async_client* client;
    callback* cb;
  public:
    mqtt_client(std::string client_id);
    mqtt_client(std::string client_id, std::string host_url);
    void publish(std::string topic, std::string message, uint8_t qos = 1);
    ~mqtt_client();
};

#endif