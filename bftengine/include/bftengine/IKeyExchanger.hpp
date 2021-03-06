// Concord
//
// Copyright (c) 2020 VMware, Inc. All Rights Reserved.
//
// This product is licensed to you under the Apache 2.0 license (the "License"). You may not use this product except in
// compliance with the Apache 2.0 License.
//
// This product may include a number of subcomponents with separate copyright notices and license terms. Your use of
// these subcomponents is subject to the terms and conditions of the sub-component's license, as noted in the LICENSE
// file.

#pragma once
#include <string>
#include <cstdint>

// Interface for objects that need to be notified on key rotation
class IKeyExchanger {
 public:
  virtual ~IKeyExchanger() {}
  virtual void onPublicKeyExchange(const std::string& msg, const std::uint16_t& signerIndex) = 0;
  virtual void onPrivateKeyExchange(const std::string& secretKey, const std::string& verificationKey) = 0;
};
