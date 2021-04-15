﻿/*
 Copyright (c) 2013, Ford Motor Company
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following
 disclaimer in the documentation and/or other materials provided with the
 distribution.

 Neither the name of the Ford Motor Company nor the names of its contributors
 may be used to endorse or promote products derived from this software
 without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SRC_COMPONENTS_POLICY_POLICY_EXTERNAL_INCLUDE_POLICY_POLICY_TYPES_H_
#define SRC_COMPONENTS_POLICY_POLICY_EXTERNAL_INCLUDE_POLICY_POLICY_TYPES_H_

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "policy/policy_table/types.h"
#include "transport_manager/common.h"
#include "utils/helpers.h"

namespace policy {

// TODO(PV): specify errors
enum PolicyErrorEnum {};

const std::string kDefaultDeviceMacAddress = "00:00:00:00:00:00";
const std::string kDefaultDeviceName = "MyDevice";
const std::string kDefaultDeviceConnectionType = "UNKNOWN";

/**
 * @brief Constants for special ids in application policies section of
 * policy table
 */
const std::string kPreDataConsentId = "pre_DataConsent";
const std::string kDefaultId = "default";
const std::string kDeviceId = "device";

/*
 *@brief Policy Services specifies Users of Updates
 * received from cloud through mobile device
 */
enum PolicyServiceTypes { SERVICE_NONE = 0, IVSU = 0x04, POLICY = 0x07 };

/*
 * @brief Status of policy table update
 */
enum PolicyTableStatus {
  StatusUpToDate = 0,
  StatusUpdatePending,
  StatusUpdateRequired,
  StatusUnknown,
  StatusProcessingSnapshot
};

enum class PTUIterationType { DefaultIteration = 0, RetryIteration };

enum class ResetRetryCountType { kResetWithStatusUpdate = 0, kResetInternally };

typedef rpc::Optional<rpc::Boolean> EncryptionRequired;

// Code generator uses String class name, so this typedef was renamed to PTSring
typedef std::string PTString;
typedef std::vector<uint8_t> BinaryMessage;
typedef std::shared_ptr<BinaryMessage> BinaryMessageSptr;

typedef std::string HMILevel;
typedef std::string Parameter;
typedef std::string RpcName;
typedef std::set<std::string> RPCParams;

typedef std::map<std::string, std::set<policy::HMILevel> > HMIPermissions;
struct ParameterPermissions
    : std::map<std::string, std::set<policy::Parameter> > {
  ParameterPermissions()
      : any_parameter_allowed(false)
      , any_parameter_disallowed_by_user(false)
      , any_parameter_disallowed_by_policy(false) {}
  bool any_parameter_allowed;
  bool any_parameter_disallowed_by_user;
  bool any_parameter_disallowed_by_policy;
};

struct RpcPermissions {
  HMIPermissions hmi_permissions;
  ParameterPermissions parameter_permissions;
  EncryptionRequired require_encryption;
};

typedef std::map<RpcName, RpcPermissions> Permissions;

/**
 * @brief Typedef for use with AllowApp request/notification
 */
typedef std::vector<std::string> PermissionsList;

/**
 * @brief Typedef for getting initial application data, e.g. nickname list
 */
typedef std::vector<std::string> StringArray;

enum PermitResult { kRpcAllowed = 0, kRpcDisallowed, kRpcUserDisallowed };

/**
 * @struct Stores result of check:
 * if HMI Level was allowed for RPC to work in
 * and list of parameters allowed for RPC if specified in PT.
 */
struct CheckPermissionResult {
  CheckPermissionResult() : hmi_level_permitted(kRpcDisallowed) {}

  PermitResult hmi_level_permitted;
  RPCParams list_of_allowed_params;
  RPCParams list_of_disallowed_params;
  RPCParams list_of_undefined_params;

  bool HasParameter(const PTString& parameter) {
    const bool is_allowed =
        helpers::in_range(list_of_allowed_params, parameter);
    const bool is_disallowed =
        helpers::in_range(list_of_disallowed_params, parameter);
    const bool is_undefined =
        helpers::in_range(list_of_undefined_params, parameter);

    return is_allowed || is_disallowed || is_undefined;
  }

  bool DisallowedInclude(const RPCParams& parameters) {
    if (parameters.empty()) {
      return false;
    }
    return std::includes(list_of_disallowed_params.begin(),
                         list_of_disallowed_params.end(),
                         parameters.begin(),
                         parameters.end());
  }

  bool IsAnyAllowed(const RPCParams& parameters) {
    if (parameters.empty()) {
      return true;
    }
    return list_of_allowed_params.end() !=
           std::find_first_of(list_of_allowed_params.begin(),
                              list_of_allowed_params.end(),
                              parameters.begin(),
                              parameters.end());
  }
};

/**
  @struct Holds Url string and optional policy app id.
  */
struct EndpointData {
  explicit EndpointData(const std::string& url_string = "")
      : app_id("default") {
    if (false == url_string.empty()) {
      url.push_back(url_string);
    }
  }
  std::vector<std::string> url;
  std::string app_id;
};

typedef std::vector<EndpointData> EndpointUrls;

/**
 * @brief Struct contains device data to be used for dialogs, generation of IDs
 */
struct DeviceParams {
  DeviceParams()
      : device_name(kDefaultDeviceName)
      , device_mac_address(kDefaultDeviceMacAddress)
      , device_connection_type(kDefaultDeviceConnectionType)
      , device_handle(0) {}

  std::string device_name;
  std::string device_mac_address;
  std::string device_connection_type;
  transport_manager::DeviceHandle device_handle;
};

/**
 * @brief User consent for device data usage
 */
enum DeviceConsent {
  kDeviceAllowed = 0,
  kDeviceDisallowed,
  kDeviceHasNoConsent
};

/**
 * @brief Struct contains parameters, which can be received during application
 * registration and should be stored in policy table
 */
struct DeviceInfo {
  DeviceInfo() : max_number_rfcom_ports(0) {}

  std::string hardware;
  std::string firmware_rev;
  std::string os;
  std::string os_ver;
  std::string carrier;
  uint32_t max_number_rfcom_ports;
  std::string connection_type;

  void AdoptDeviceType(const std::string& deviceType) {
    connection_type = "USB_serial_number";
    using namespace helpers;
    static const std::string bluetooth("BLUETOOTH");
    static const std::string wifi("WIFI");
    static const std::string webengine("WEBENGINE_WEBSOCKET");
    if (Compare<std::string, EQ, ONE>(deviceType, bluetooth, wifi)) {
      connection_type.assign("BTMAC");
    } else if (Compare<std::string, EQ, ONE>(deviceType, webengine)) {
      connection_type.assign("");
    }
  }
};

/**
 * @brief User consent for functional group
 */
enum GroupConsent { kGroupAllowed = 0, kGroupDisallowed, kGroupUndefined };

/**
 * @brief Contains user permission for RPC functional group with specific name
 * and id from DB
 */
struct FunctionalGroupPermission {
  FunctionalGroupPermission() : group_id(0), state(kGroupUndefined) {}

  bool operator==(const FunctionalGroupPermission& rhs) {
    if (this->group_id == rhs.group_id &&
        this->group_alias == rhs.group_alias &&
        this->group_name == rhs.group_name) {
      return true;
    }
    return false;
  }

  std::string group_alias;
  std::string group_name;
  int32_t group_id;
  GroupConsent state;
};

/**
 * @brief Stores data to be sent to HMI on application permissions change
 */
struct AppPermissions {
  AppPermissions(const std::string& app_id)
      : application_id(app_id)
      , isAppPermissionsRevoked(false)
      , appRevoked(false)
      , appPermissionsConsentNeeded(false)
      , appUnauthorized(false)
      , isSDLAllowed(false)
      , requestTypeChanged(false)
      , requestSubTypeChanged(false) {}

  std::string application_id;
  bool isAppPermissionsRevoked;
  std::vector<policy::FunctionalGroupPermission> appRevokedPermissions;
  bool appRevoked;
  bool appPermissionsConsentNeeded;
  bool appUnauthorized;
  bool isSDLAllowed;
  std::string priority;
  DeviceParams deviceInfo;
  bool requestTypeChanged;
  std::vector<std::string> requestType;
  bool requestSubTypeChanged;
  std::vector<std::string> requestSubType;
};

/**
 * @brief Contains parameters for user-defined consent for appication
 * functional groups on given device
 */
struct PermissionConsent {
  std::string device_id;
  std::string policy_app_id;
  std::vector<FunctionalGroupPermission> group_permissions;
  std::string consent_source;
};

/**
 * @brief Contain data for GetUserFriendyMessage response
 */
struct UserFriendlyMessage {
  std::string message_code;
  std::string tts;
  std::string label;
  std::string line1;
  std::string line2;
  std::string text_body;
};

/**
 * @brief Types of functional groups in policy table
 */
enum GroupType {
  kTypeDefault = 0,   // groups assigned to 'default' permissions section
  kTypeAllowed,       // groups allowed by user for specific application
  kTypeDisallowed,    // groups disallowed by user for specific application
  kTypeUnconsented,   // groups disallowed by default but consent may be changed
                      // by user
  kTypePreconsented,  // groups allowed for specific application without
                      // user consent by default (could be changed by user)
  kTypeGeneral,       // groups assigned to specific application
  kTypePreDataConsented,  // groups assigned to 'pre_DataConsent' permissions
                          // section
  kTypeDevice             // groups assigned to 'device' permissions section
};

/**
 * @brief Array of functional group id from DB
 */
typedef std::vector<int32_t> FunctionalGroupIDs;

/**
 * @brief Array of functional group ids sorted by types
 */
typedef std::map<GroupType, FunctionalGroupIDs> FunctionalIdType;

/**
 * @brief Array of functional group ids binded to user_consent_prompt (e.g.
 * VehicleData) and group name (e.g. VehicleData-4)
 */
typedef std::map<uint32_t, std::pair<std::string, std::string> >
    FunctionalGroupNames;

/**
 * @brief Array of device ids, which are an identifiers in policy table
 */
typedef std::vector<std::string> DeviceIds;

/**
 * @brief Counters that calculated on receiving of succesful update
 */
enum Counters { KILOMETERS, DAYS_AFTER_EPOCH };

/**
 * @struct Vehicle information
 */
struct VehicleInfo {
  std::string vehicle_make;
  std::string vehicle_model;
  std::string vehicle_year;
};

/**
 * @brief The MetaInfo information
 */
struct MetaInfo {
  std::string ccpu_version;
  std::string wers_country_code;
  std::string language;
};

/**
 * @brief The index of the application, the index of its URL
 * and the policy application id from the Endpoints vector
 * that will be sent on the next OnSystemRequest retry sequence
 */
struct RetrySequenceURL {
  uint32_t app_idx_;
  uint32_t url_idx_;
  std::string policy_app_id_;
  RetrySequenceURL(uint32_t app, uint32_t url, const std::string& app_id)
      : app_idx_(app), url_idx_(url), policy_app_id_(app_id) {}
  RetrySequenceURL() : app_idx_(0), url_idx_(0) {}
};

/**
 * @brief Index of the application, index of its URL
 * from the Endpoints vector
 */
typedef std::pair<uint32_t, uint32_t> AppIdURL;

/**
 * @brief Represents ExternalConsent entity status received from the system
 */
enum EntityStatus { kStatusOn, kStatusOff };

/**
 * @brief The ExternalConsentStatusItem struct represents external user consent
 * settings item
 */
struct ExternalConsentStatusItem {
  ExternalConsentStatusItem(const uint32_t type,
                            const uint32_t id,
                            const EntityStatus status)
      : entity_type_(type), entity_id_(id), status_(status) {}

  bool operator==(const ExternalConsentStatusItem& rhs) const {
    return (entity_type_ == rhs.entity_type_) && (entity_id_ == rhs.entity_id_);
  }

  bool operator<(const ExternalConsentStatusItem& rhs) const {
    return (entity_type_ < rhs.entity_type_) || (entity_id_ < rhs.entity_id_);
  }

  const uint32_t entity_type_;
  const uint32_t entity_id_;
  const EntityStatus status_;
};

struct ExternalConsentStatusItemSorter {
  bool operator()(const ExternalConsentStatusItem& lhs,
                  const ExternalConsentStatusItem& rhs) const {
    return (lhs.entity_type_ < rhs.entity_type_) ||
           (lhs.entity_id_ < rhs.entity_id_);
  }
};

/**
 * @brief The ApplicationPolicyActions struct contains actions which should be
 * done for some application
 */
struct ApplicationPolicyActions {
  ApplicationPolicyActions()
      : is_notify_system(false)
      , is_send_permissions_to_app(false)
      , is_consent_needed(false)
      , app_properties_changed(false) {}

  bool is_notify_system;
  bool is_send_permissions_to_app;
  bool is_consent_needed;
  bool app_properties_changed;
};

/**
 * @brief ApplicationsPoliciesActions map of actions to be done for every
 * application
 */
typedef std::map<std::string, ApplicationPolicyActions>
    ApplicationsPoliciesActions;

/**
 * @brief Customer connectivity settings status
 */
typedef std::set<ExternalConsentStatusItem, ExternalConsentStatusItemSorter>
    ExternalConsentStatus;

/**
 * @brief GroupsByExternalConsentStatus represents list of group names, which
 * has mapped ExternalConsent item (entity type + entity id) in their
 * disallowed_by_external_consent_ containers. Boolean value represents
 * whether ExternalConsent item has been found in
 * disallowed_by_external_consent_ON or in disallowed_by_external_consent_OFF
 * container
 */
typedef std::map<ExternalConsentStatusItem,
                 std::vector<std::pair<std::string, bool> > >
    GroupsByExternalConsentStatus;

/**
 * @brief GroupsNames represents groups names from policy table -> functional
 * groupings groups container
 */
typedef std::set<std::string> GroupsNames;

typedef std::string ApplicationId;
typedef std::string DeviceId;

/**
 * @brief Link of device to application
 */
typedef std::pair<policy::DeviceId, policy::ApplicationId> Link;

/**
 * @brief Collection of links
 */
typedef std::set<Link> ApplicationsLinks;

/**
 * @brief Represents possible result codes for policy table update check
 */
enum PermissionsCheckResult {
  RESULT_NO_CHANGES,
  RESULT_APP_REVOKED,
  RESULT_NICKNAME_MISMATCH,
  RESULT_PERMISSIONS_REVOKED,
  RESULT_CONSENT_NEEDED,
  RESULT_CONSENT_NOT_REQUIRED,
  RESULT_PERMISSIONS_REVOKED_AND_CONSENT_NEEDED,
  RESULT_REQUEST_TYPE_CHANGED,
  RESULT_REQUEST_SUBTYPE_CHANGED,
  RESULT_ENCRYPTION_REQUIRED_FLAG_CHANGED,
  RESULT_APP_PROPERTIES_CHANGED
};

/**
 * @brief Per application collection of results done by checking policy table
 * update
 */
typedef std::set<std::pair<std::string, PermissionsCheckResult> >
    CheckAppPolicyResults;

/**
 * @brief Index of the application, index of its URL
 * from the Endpoints vector
 */
typedef std::pair<uint32_t, uint32_t> AppIdURL;

/**
 * @brief The AppProperties struct contains application properties
 */
struct AppProperties {
  AppProperties()
      : endpoint()
      , certificate()
      , enabled(false)
      , auth_token()
      , transport_type()
      , hybrid_app_preference() {}

  AppProperties(std::string endpoint,
                std::string certificate,
                bool enabled,
                std::string auth_token,
                std::string transport_type,
                std::string hybrid_app_preference)
      : endpoint(endpoint)
      , certificate(certificate)
      , enabled(enabled)
      , auth_token(auth_token)
      , transport_type(transport_type)
      , hybrid_app_preference(hybrid_app_preference) {}

  /**
   * @brief endpoint Filled with the endpoint used to connect to the cloud
   * application.
   * @note should be absent for local applications
   */
  std::string endpoint;

  /**
   * @brief certificate Filled with the certificate used for creation
   * of a secure connection to the cloud application
   */
  std::string certificate;

  /**
   * @brief enabled Whether or not the app is enabled
   */
  bool enabled;

  /**
   * @brief auth_token Filled with the token used for authentication when
   * reconnecting to the cloud app
   */
  std::string auth_token;

  /**
   * @brief transport_type Filled with the transport type used by the
   * cloud/local application (ex. "WSS")
   */
  std::string transport_type;

  /**
   * @brief hybrid_app_preference Filled with the hybrid app preference for the
   * application set by the user
   */
  std::string hybrid_app_preference;
};

}  //  namespace policy

#endif  // SRC_COMPONENTS_POLICY_POLICY_EXTERNAL_INCLUDE_POLICY_POLICY_TYPES_H_
