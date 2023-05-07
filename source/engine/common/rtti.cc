#include "RTTI.h"

#include "StringPool.h"

RTTI::~RTTI() {}

void RTTI::setTypeInfo(char* i_char) {
  if (i_char)
    mTypeInfo = StringPool::getStringPool()->findString(i_char);
}

bool RTTI::isType(RTTI* i_RTTI_ptr) {
  if (i_RTTI_ptr) {
    if (mTypeInfo == i_RTTI_ptr->mTypeInfo) return true;
    return false;
  }
  return false;
}

RTTI::RTTI() {}
