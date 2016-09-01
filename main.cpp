/*
 * Copyright (C) 2016 Konstantin Kuznetsov
 * http://konst.pro/
 */
#include "site.h"

using namespace Wt;

WApplication *createApplication(const WEnvironment& env)
{
  return new Site(env);
}

int main(int argc, char **argv)
{
   return WRun(argc, argv, &createApplication);
}

