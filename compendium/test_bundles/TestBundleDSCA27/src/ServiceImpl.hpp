#include <cppmicroservices/AnyMap.h>

#include "TestInterfaces/Interfaces.hpp"

#include <mutex>

namespace sample {
class ServiceComponentCA27 : public ::test::CAInterface
{
public:
  ServiceComponentCA27(const std::shared_ptr<cppmicroservices::AnyMap>& props)
    : properties_(*props)
  {}

  cppmicroservices::AnyMap GetProperties();
  ~ServiceComponentCA27() = default;

private:
  std::mutex propertiesLock;
  cppmicroservices::AnyMap properties_;
};
}
