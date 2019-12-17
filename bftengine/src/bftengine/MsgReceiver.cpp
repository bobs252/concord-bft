// Concord
//
// Copyright (c) 2019 VMware, Inc. All Rights Reserved.
//
// This product is licensed to you under the Apache 2.0 license (the "License").  You may not use this product except in
// compliance with the Apache 2.0 License.
//
// This product may include a number of subcomponents with separate copyright notices and license terms. Your use of
// these subcomponents is subject to the terms and conditions of the sub-component's license, as noted in the LICENSE
// file.

#include "MsgReceiver.hpp"
#include "messages/MessageBase.hpp"
#include "ReplicaConfig.hpp"
#include <cstring>

namespace bftEngine::impl {

using namespace std;

MsgReceiver::MsgReceiver(std::shared_ptr<IncomingMsgsStorage> &storage) : incomingMsgsStorage_(storage) {}

void MsgReceiver::onNewMessage(const NodeNum sourceNode, const char *const message, const size_t messageLength) {
  if (messageLength > ReplicaConfigSingleton::GetInstance().GetMaxExternalMessageSize()) return;
  if (messageLength < sizeof(MessageBase::Header)) return;

  auto *msgBody = (MessageBase::Header *)std::malloc(messageLength);
  memcpy(msgBody, message, messageLength);

  auto node = (uint16_t)sourceNode;  // TODO(GG): make sure that this casting is okay

  std::unique_ptr<MessageBase> pMsg(new MessageBase(node, msgBody, messageLength, true));

  incomingMsgsStorage_->pushExternalMsg(std::move(pMsg));
}

void MsgReceiver::onConnectionStatusChanged(const NodeNum node, const ConnectionStatus newStatus) {}

}  // namespace bftEngine::impl