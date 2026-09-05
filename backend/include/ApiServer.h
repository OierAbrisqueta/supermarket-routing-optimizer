#ifndef ROUTINGOPTIMIZER_APISERVER_H
#define ROUTINGOPTIMIZER_APISERVER_H

#pragma once
#include "ThreadPool.h"
#include <httplib.h>

class ApiServer {
public:
    ApiServer(int port, size_t threadCount, const std::string& dbPath);

    void start();
    void stop();

private:
    void setupRoutes();

    void handleCalculateRoute(const httplib::Request& request, httplib::Response& response);

    int port;
    httplib::Server srv;
    ThreadPool pool;
};

#endif //ROUTINGOPTIMIZER_APISERVER_H