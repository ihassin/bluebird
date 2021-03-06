#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <stropts.h>

#undef DEBUG
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

#ifndef PIPERI_H
#include "piperi.h"
#endif

#ifndef CALLBACK_H_
#include "callback.h"
#endif

#ifndef UTIL_H_
#include "util.h"
#endif

using namespace std;

bool __alive = true;

int main(int argc, char **argv)
{
  log4cpp::PropertyConfigurator::configure("log4cpp.properties");
  log4cpp::Category& rootLog = log4cpp::Category::getRoot();
  log4cpp::Category& mainLog = log4cpp::Category::getInstance(std::string("main"));

  if(argc==1) {
    rootLog.error("sudo bunget hcidev#, pass device id as 0,1,2.. as first argument!");
    return -1;
  }

  if(getuid()!=0) {
    rootLog.error("run under sudo credentials or setcap bunget !\n");
    return -1;
  }

  int dev = ::atoi(argv[1]);

  int srdel = 0;
  if(argc == 3) {
    srdel = atoi(argv[2]);
  }

  enable_raw_mode();
  
  try {
    BtCtx *ctx = BtCtx::instance();
    Callback callback;

    IServer *BS =  ctx->new_server(&callback, dev, "piperi", srdel, true);

    IService *ps = BS->add_service(0x123F, "piperi");

    callback.LedChr = ps->add_charact(UID_GPIO,PROPERTY_WRITE|PROPERTY_INDICATE,0, FORMAT_RAW, 1); // 1 / 0
    callback.TimeChr = ps->add_charact(UID_TIME, PROPERTY_READ|PROPERTY_NOTIFY, 0, FORMAT_RAW, 20); // we send it as string
    callback.Temp1Chr = ps->add_charact(UID_TEMP, PROPERTY_NOTIFY|PROPERTY_INDICATE, 0, FORMAT_FLOAT, FORMAT_FLOAT_LEN); // we send it as float
    
    BS->advertise(512);
    mainLog.info("Advertising");
    BS->run();
    BS->stop();
  } catch(bunget::hexecption& ex) {
    mainLog.fatal(ex.report());
  }

  disable_raw_mode();
  tcflush(0, TCIFLUSH);
  return 0;
}
