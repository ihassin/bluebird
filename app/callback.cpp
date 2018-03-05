#include <fstream>
#include <unistd.h>

#ifndef PIPERI_H
#include "piperi.h"
#endif

#ifndef CALLBACK_H_
#include "callback.h"
#endif

#ifndef UTIL_H_
#include "util.h"
#endif

#undef DEBUG
#undef ERROR
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

static log4cpp::Category& mainLog = log4cpp::Category::getInstance(std::string("main"));

/****************************************************************************************
*/
Callback::Callback()
{
  _subscribed = false;
  Temp1Chr = 0;
  _prepare_gpio17();
}

/****************************************************************************************
 * add your console hciconfig preambul to setup hci before BTLE is starting
*/
bool Callback::initHciDevice(int devid, const char* devn)
{
  return true;
}

/****************************************************************************************
*/
bool Callback::onSpin(IServer* ps, uint16_t notyUuid)
{
  if(kbhit() && (getchar() == 'q')) {
    return false;
  }

  if(_subscribed)
  {
    if(notyUuid==TimeChr->get_handle()) {
      _send_value(TimeChr);
    } else {
      if(notyUuid==Temp1Chr->get_handle()) {
        _send_value(Temp1Chr);
      }
    }
  }
  return true;
}

/****************************************************************************************
*/
void Callback::onServicesDiscovered(std::vector<IHandler*>& els)
{
  mainLog.info("Callback::onServicesDiscovered");
}

/****************************************************************************************
*/
/// remote reads pc characteristics
void Callback::onReadRequest(IHandler* pc)
{
  mainLog.info("Callback::onReadRequest: %d", pc->get_16uid());
  _send_value(pc);
}

/****************************************************************************************
*/
int Callback::onSubscribesNotify(IHandler* pc, bool b)
{
  mainLog.info("Callback::onSubscribesNotify: %d:%d", pc->get_16uid(), (int) b);

  _subscribed = b;
  return 0 ;
}

/****************************************************************************************
*/
void Callback::onIndicate(IHandler* pc)
{
  if(is_tracing(kTraceCallback)) TRACE("my_proc event:  onIndicate:" <<  std::hex<< pc->get_16uid() << std::dec);
  _send_value(pc);
}

/****************************************************************************************
*/
void Callback::onWriteRequest(IHandler* pc)
{
  std::string     ret;
  const uint8_t*  value = pc->get_value();
  char            by[4];
  int             i=0;

  for(;i<pc->get_length();i++)
  {
    ::sprintf(by,"%02X:",value[i]);
    ret.append(by);
  }
  mainLog.info("Callback::onWriteRequest: %d:<%s>", pc->get_16uid(), ret.c_str());

  if(pc->get_16uid() == UID_GPIO)
  {
    if(::access("/sys/class/leds/led0/trigger",0)==0)
    {
      if(value[0]==0) {
          system("echo 0 >/sys/class/leds/led0/brightness");
      } else {
          system("echo 1 >/sys/class/leds/led0/brightness");
      }
    }
  }
}

/****************************************************************************************
*/
//descriptor chnaged of the charact
void Callback::onWriteDescriptor(IHandler* pc, IHandler* pd)
{
  char buff[256];
  sprintf(buff, "Callback::onWriteDescriptor: %d", int(*((int*)(pd->get_value()))));
  mainLog.info(buff);
}

/****************************************************************************************
*/
void Callback::onAdvertized(bool onoff)
{
  mainLog.info("Callback::onAdvertized");
}

/****************************************************************************************
*/
void Callback::onDeviceStatus(bool onoff)
{
  mainLog.info("Callback::onDeviceStatus");
  if(onoff==false)
  {
    _subscribed = false;
  }
}

/****************************************************************************************
*/
void Callback::onStatus(const HciDev* device)
{
  if(device == 0)
  {
    _subscribed = false;
    mainLog.info("Callback::onStatus: Disconnected");
  }
  else
  {
    mainLog.info("Callback::onStatus:acceptedConnection: %s:%s", device->_mac, device->_name);
  }
}

/****************************************************************************************
*/
void Callback::_prepare_gpio17()
{
  if(::access("/sys/class/gpio/export/",0)==0)
  {
    system ("chmod 777 /sys/class/gpio/export");
    system ("echo 17 > /sys/class/gpio/export");
    system ("sync");
    if(::access("/sys/class/gpio/gpio17/",0)==0)
      system ("chmod 777 /sys/class/gpio/gpio17/*");
    system ("sync");
  }
}

/****************************************************************************************
*/
const char *Callback::_get_time()
{
  mainLog.info("Callback::_get_time");

  time_t secs = time(0);
  struct tm *local = localtime(&secs);
  sprintf(_some, "%02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec);
  return _some;
}

/****************************************************************************************
*/
float Callback::_get_temp()
{
  mainLog.info("Callback::_get_temp");

  float ftamp=0.0;

  if(::access("/opt/vc/bin/vcgencmd",0)==0)
  {
    ::system("/opt/vc/bin/vcgencmd measure_temp > /tmp/bunget");
    std::ifstream ifs("/tmp/bunget");
    std::string temp( (std::istreambuf_iterator<char>(ifs) ),(std::istreambuf_iterator<char>()));
    temp = temp.substr(5);
    ftamp =::atof(temp.c_str());
  }
  return ftamp;
}

/****************************************************************************************
*/
const char *Callback::_get_temp_s()
{
  mainLog.info("Callback::_get_temp_s");
  
  if(::access("/opt/vc/bin/vcgencmd",0)==0)
  {
    ::system("/opt/vc/bin/vcgencmd measure_temp > /tmp/bunget");
    std::ifstream ifs("/tmp/bunget");
    std::string temp( (std::istreambuf_iterator<char>(ifs) ),(std::istreambuf_iterator<char>()));
    ::strcpy(_some,temp.c_str());
  }
  return _some;
}

/****************************************************************************************
*/
uint8_t Callback::_get_gpio()
{
  mainLog.info("Callback::_get_gpio");

  if(::access("/sys/class/gpio/gpio17/value",0)==0)
  {
    std::ifstream ifs("/sys/class/gpio/gpio17/value");
    std::string temp( (std::istreambuf_iterator<char>(ifs) ),(std::istreambuf_iterator<char>()));
    return uint8_t(::atoi(temp.c_str()));
  }

  return 0;
}

/****************************************************************************************
*/
void Callback::_send_value(IHandler* pc)
{
  mainLog.info("Callback::_send_value");

  uint16_t uid = pc->get_16uid();
  switch(uid)
  {
    case  UID_GPIO:
      {
          uint8_t gp = _get_gpio();
          // pc->put_value((uint8_t*)&gp,1);
          GattRw(pc).write(gp);
      }
      break;
    case  UID_TIME:
      {
          const char* t = _get_time();
          pc->put_value((uint8_t*)t,::strlen(t));
      }
      break;
    case  UID_TEMP:
      {
          //float ft = _get_temp();
          //pc->put_value((uint8_t*)&ft,sizeof(float));
          const char* fts = _get_temp_s();
          pc->put_value((uint8_t*)fts,::strlen(fts));
      }
      break;
    case  0xec0e:
      {
          //float ft = _get_temp();
          //pc->put_value((uint8_t*)&ft,sizeof(float));
          //const char* fts = _get_temp_s();
          static int K=0;

          char rands[32];
          ::sprintf(rands,"%d", K++);
          pc->put_value((uint8_t*)rands,::strlen(rands));
      }
    break;
    default:
        break;
  }
}
