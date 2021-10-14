#include "apollo_app.h"
#include "status.h"

#include <iostream>

class Student : public apollo::common::ApolloApp {
  public:
    std::string Name() const override { return "Student"; }

    apollo::common::Status Init() override {
        std::cout << "Init: " << Name() << std::endl;
        return apollo::common::Status::OK();
    }

    apollo::common::Status Start() override {
        std::cout << "Start: " << Name() << std::endl;
        // return apollo::common::Status::OK();
        return apollo::common::Status(apollo::common::ErrorCode::CONTROL_INIT_ERROR,
                                      "unable to load control init configuration!");
    }

    void Stop() override { std::cout << "Stop: " << Name() << std::endl; }
};

APOLLO_MAIN(Student)
