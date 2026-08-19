#ifndef ROUTINGOPTIMIZER_APISERVER_H
#define ROUTINGOPTIMIZER_APISERVER_H

#pragma once
#include "ThreadPool.h"
#include "Database.h"
#include <httplib.h>

class ApiServer {
public:
    ApiServer(int port, size_t threadCount, Database& db);

    void start();
    void stop();

private:
    void setupRoutes();

    void handleCalculateRoute(const httplib::Request& request, httplib::Response& response);

    int port;
    httplib::Server srv;
    ThreadPool pool;
    Database& db;
};

#endif //ROUTINGOPTIMIZER_APISERVER_H