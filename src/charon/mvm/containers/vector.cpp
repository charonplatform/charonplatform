// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <charon/base>
#include <charon/mvm>
#include <vector>

using namespace charon;

static std::mutex mtx;
static std::vector<mvm::data *> * s_container = new std::vector<mvm::data *>;

void mvm::container::init()
{
  s_container->reserve(100);
}

void mvm::container::push(mvm::data * data)
{
  std::unique_lock<std::mutex> lck(mtx);
  s_container->push_back(data);
}

void mvm::container::back(mvm::data * data)
{
  std::unique_lock<std::mutex> lck(mtx);
  s_container->insert(s_container->begin(), data);
}

mvm::data * mvm::container::pop()
{
  std::unique_lock<std::mutex> lck(mtx);
  mvm::data * data = s_container->back();
  s_container->pop_back();
  return data;
}

bool mvm::container::empty()
{
  std::unique_lock<std::mutex> lck(mtx);
  return s_container->empty();
}
