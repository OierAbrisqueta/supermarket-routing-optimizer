#include "ApiServer.h"
#include <nlohmann/json.hpp>
#include <future>
#include "RouteEngine.h"

using json = nlohmann::json;

ApiServer::ApiServer(int port, size_t threadCount, const std::string& dbPath): port(port), pool(threadCount, dbPath) {
}

void ApiServer::start() {
    std::cout << "Starting server on port: " << port << std::endl;
    srv.listen("0.0.0.0", port);
}

void ApiServer::stop() {
    srv.stop();
}

void ApiServer::setupRoutes() {
    srv.Post("/api/route", [this](const httplib::Request& req, httplib::Response& res) {
        this->handleCalculateRoute(req, res);
    });
}

void ApiServer::handleCalculateRoute(const httplib::Request& request, httplib::Response& response) {
    try {
        json request_body = json::parse(request.body);

        int store_id = request_body.value("store_id", 1);
        int start_node = request_body.value("start_node_id", 1);
        int end_node = request_body.value("end_node_id", 5);
        std::vector<int> product_ids = request_body.value("product_ids", std::vector<int>{});

        auto promise = std::make_shared<std::promise<json>>();
        auto future = promise->get_future();

        pool.enqueueTask([store_id, start_node, end_node, product_ids, promise](Database& local_db) {
            try {
                StoreLayout layout = local_db.getStoreLayout(store_id);
                std::vector<Item> items = local_db.getItems(store_id, product_ids);
                
                RouteEngine engine(layout);
                std::vector<int> path = engine.calculateOptimalRoute(start_node, end_node, items);

                json result;
                result["status"] = "success";
                result["optimal_path"] = path;
                
                promise->set_value(result);
            } catch (const std::exception& e) {
                json err;
                err["status"] = "error";
                err["message"] = e.what();
                promise->set_value(err);
            }
        });

        json response_json = future.get();
        
        if (response_json["status"] == "error") {
            response.status = 500;
        } else {
            response.status = 200;
        }
        
        response.set_content(response_json.dump(), "application/json");

    } catch (const json::exception& e) {
        json err = {{"status", "error"}, {"message", "Invalid JSON body"}};
        response.status = 400; // Bad Request
        response.set_content(err.dump(), "application/json");
    }
}