#include "config_server.h"

ConfigServer::ConfigServer(ControllerConfig *config) : wifi_server(80) {
    this->config = config;
}

void ConfigServer::start() {
    wifi_server.begin();
}

void ConfigServer::handle_client() {
    WiFiClient client = wifi_server.available();
    if (!client) {
        return;
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html><html>");
    client.println("<head>");
    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    client.println("</head>");

    client.println("<body>");
    client.println("<h1>E1.31 Light Controller</h1>");
    client.println("<ul>");
    client.print("<li>Global brightness: ");
    client.print(config->global_brightness);
    client.println("</li>");
    client.println("</ul>");
    client.println("</body>");
    client.println("</html>");
    client.println();
}