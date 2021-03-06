// Copyright (c) 2018-2021 Marco Wang <m.aesophor@gmail.com>. All rights reserved.
#include "CallbackManager.h"

#include <atomic>

using std::atomic;
using std::function;
using cocos2d::Scene;
using cocos2d::DelayTime;
using cocos2d::CallFunc;
using cocos2d::Sequence;

namespace vigilante {

CallbackManager* CallbackManager::getInstance() {
  static CallbackManager instance;
  return &instance;
}

CallbackManager::CallbackManager()
    : _scene(),
      _pendingCount(0) {}


void CallbackManager::runAfter(const function<void ()>& userCallback, float delay) {
  // If the specified delay is 0 second, then we can
  // simply invoke `userCallback` and return early.
  if (delay == 0) {
    userCallback();
    return;
  }

  _scene->runAction(Sequence::create(
      CallFunc::create([=]() { ++(this->_pendingCount); }),
      DelayTime::create(delay),
      CallFunc::create(userCallback),
      CallFunc::create([=]() { --(this->_pendingCount); }),
      nullptr
    )
  );
}


int CallbackManager::getPendingCount() const {
  return _pendingCount;
}

void CallbackManager::setScene(Scene* scene) {
  _scene = scene;
}

}  // namespace vigilante
