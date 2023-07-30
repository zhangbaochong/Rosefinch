#include <iostream>
#include "gtest/gtest.h"
#include "Framework/Core/Log/Log.h"

using namespace Rosefinch;

TEST(TestLog, PrintLog)
{
  LOG_DEBUG("log debug");
  LOG_INFO("log info");
  LOG_WARN("log warn");
  LOG_ERROR("log error");
  LOG_CRITICAL("log critical");
  EXIT_SUCCESS();
}

int main(int argc,char **argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}