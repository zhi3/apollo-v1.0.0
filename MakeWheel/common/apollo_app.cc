#include "apollo_app.h"

#include <iostream>

namespace apollo {
namespace common {

int ApolloApp::Spin() {
    auto status = Init();
    if (!status.ok()) {
        std::cerr << "Init failed: " << status << std::endl;
        return -1;
    }

    status = Start();
    if (!status.ok()) {
        std::cerr << "Start failed: " << status << std::endl;
        return -2;
    }

    std::cout << "... Spinning ...." << std::endl;
    std::cout << "... Spinning ...." << std::endl;

    Stop();
    std::cout << Name() << " exited." << std::endl;
    return 0;
}

void apollo_app_sigint_handler(int signal_num) {
    std::cout << "Received signal: " << signal_num;
    if (signal_num != SIGINT) {
        return;
    }
    bool static is_stopping = false;
    if (is_stopping) {
        return;
    }
    is_stopping = true;
    std::cout << "running ros::shutdown()" << std::endl;
}

}  // namespace common
}  // namespace apollo
