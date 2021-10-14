#pragma once

/**
 * modules/common/apollo_app.h
 */

#include <csignal>
#include <string>

#include "status.h"

namespace apollo {
namespace common {

class ApolloApp {
  public:
    /**
     * @brief module name. It is used to uniquely identify the app.
     */
    virtual std::string Name() const = 0;

    /**
     * @brief this is the entry point of an Apollo App. It initializes the app,
     * starts the app, and stop the app when the ros has shutdown.
     */
    virtual int Spin();

    /**
     * The default destructor.
     */
    virtual ~ApolloApp() = default;

  protected:
    /**
     * @brief The module initialization function. This is the first function being
     * called when the App starts. Usually this function loads the configurations,
     * subscribe the data from sensors or other modules.
     * @return Status initialization status
     */
    virtual apollo::common::Status Init() = 0;

    /**
     * @brief The module start function. Apollo app usually triggered to execute
     * in two ways: 1. Triggered by upstream messages, or 2. Triggered by timer.
     * If an app is triggered by upstream messages, the Start() function usually
     * register a call back function that will be called when an upstream message
     * is received. If an app is triggered by timer, the Start() function usually
     * register a timer callback function.
     * @return Status start status
     */
    virtual apollo::common::Status Start() = 0;

    /**
     * @brief The module stop function. This function will be called when
     * after ros::shutdown() has finished. In the default APOLLO_MAIN macro,
     * ros::shutdown() is called when SIGINT is received.
     */
    virtual void Stop() = 0;
};

void apollo_app_sigint_handler(int signal_num);

}  // namespace common
}  // namespace apollo

#define APOLLO_MAIN(APP)                                           \
    int main(int argc, char** argv) {                              \
        signal(SIGINT, apollo::common::apollo_app_sigint_handler); \
        APP apollo_app_;                                           \
        apollo_app_.Spin();                                        \
        return 0;                                                  \
    }
