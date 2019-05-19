// Copyright 2016 The Charon Platform Authors.
// All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <charon/base>
#include <charon/mvm>
#include <list>

using namespace charon;

static std::mutex mtx;
static std::list<mvm::data *> * s_container = new std::list<mvm::data *>;

void mvm::container::init()
{

}

void mvm::container::push(mvm::data * data)
{
  std::unique_lock<std::mutex> lck(mtx);
  s_container->push_back(data);
}

void mvm::container::back(mvm::data * data)
{
  std::unique_lock<std::mutex> lck(mtx);
  s_container->push_back(data);
}

mvm::data * mvm::container::pop()
{
  std::unique_lock<std::mutex> lck(mtx);
  mvm::data * data = s_container->front();
  s_container->pop_front();
  return data;
}

bool mvm::container::empty()
{
  std::unique_lock<std::mutex> lck(mtx);
  return s_container->empty();
}
