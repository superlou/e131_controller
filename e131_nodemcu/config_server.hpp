#ifndef SERVER_H_
#define SERVER_H_

#include <ESP8266WiFi.h>
#include "controller_config.hpp"

class ConfigServer {
    private:
        WiFiServer wifi_server;
        ControllerConfig *config;

    public:
        ConfigServer(ControllerConfig *config);
        void start();
        void handle_client();
};

#endif
