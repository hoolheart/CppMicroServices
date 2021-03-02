/*=============================================================================

 Library: CppMicroServices

 Copyright (c) The CppMicroServices developers. See the COPYRIGHT
 file at the top-level directory of this distribution and at
 https://github.com/CppMicroServices/CppMicroServices/COPYRIGHT .

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 =============================================================================*/

#ifndef __CPPMICROSERVICES_SCRIMPL_CONFIGURATIONNOTIFIER_HPP__
#define __CPPMICROSERVICES_SCRIMPL_CONFIGURATIONNOTIFIER_HPP__

#include "../SCRLogger.hpp"
#include "cppmicroservices/cm/ConfigurationListener.hpp"
#include "ConcurrencyUtil.hpp"

namespace cppmicroservices {
namespace scrimpl {

/** ConfigChangeNotification
     * This class is used by ConfigurationListener to notify ComponentConfigurationImpl
     * about changes to Configuration Objects.
     */
struct ConfigChangeNotification final
{
  ConfigChangeNotification(
    const std::string pid,
    std::shared_ptr<cppmicroservices::AnyMap> properties,
    const cppmicroservices::service::cm::ConfigurationEventType evt)
    : pid(std::move(pid))
    , newProperties(properties)
    , event(std::move(evt))
  {}

  const std::string pid;
  const cppmicroservices::service::cm::ConfigurationEventType event;
  std::shared_ptr<cppmicroservices::AnyMap> newProperties;
};

class ConfigurationNotifier final 
{

public:
  /**
   * @throws std::invalid_argument exception if any of the params is a nullptr 
   */
  ConfigurationNotifier(
    const cppmicroservices::BundleContext context,
    std::shared_ptr<cppmicroservices::logservice::LogService> logger);
  
  ConfigurationNotifier(const ConfigurationNotifier&) = delete;
  ConfigurationNotifier(ConfigurationNotifier&&) = delete;
  ConfigurationNotifier& operator=(const ConfigurationNotifier&) = delete;
  ConfigurationNotifier& operator=(ConfigurationNotifier&&) = delete;
  ~ConfigurationNotifier() = default;

  /**
   * @throws std::bad_alloc exception if memory cannot be allocated
   */
  cppmicroservices::ListenerTokenId RegisterListener(
    const std::string& pid,
    std::function<void(const ConfigChangeNotification&)> notify);

  void UnregisterListener(const std::string& pid,
    const cppmicroservices::ListenerTokenId token) noexcept;
  
  bool AnyListenersForPid(const std::string& pid) noexcept;
    
  void NotifyAllListeners(
    const std::string& pid,
    const cppmicroservices::service::cm::ConfigurationEventType type,
    const std::shared_ptr<cppmicroservices::AnyMap> properties);

private:
  using TokenMap =
    std::unordered_map<ListenerTokenId,
                       std::function<void(const ConfigChangeNotification&)>>;

  cppmicroservices::scrimpl::Guarded<
    std::unordered_map<std::string, std::shared_ptr<TokenMap>>>
    listenersMap;

  std::atomic<cppmicroservices::ListenerTokenId>
    tokenCounter; ///< used to
                  ///generate unique
                  ///tokens for
                  ///listeners

  cppmicroservices::BundleContext bundleContext;
  std::shared_ptr<cppmicroservices::logservice::LogService> logger;
};

} // namespace scrimpl
} // namespace cppmicroservices
#endif //__CPPMICROSERVICES_SCRIMPL_CONFIGURATIONNOTIFIER_HPP__