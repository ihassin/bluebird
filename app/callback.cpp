#include <fstream>
#include <unistd.h>

#ifndef TRACE_H_
#include "trace.h"
#endif

#ifndef CALLBACK_H_
#include "callback.h"
#endif

#ifndef UTIL_H_
#include "util.h"
#endif

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
  if(is_tracing(kTraceCallback)) TRACE("my_proc event: onServicesDiscovered");
}

/****************************************************************************************
*/
/// remote reads pc characteristics
void Callback::onReadRequest(IHandler* pc)
{
  if(is_tracing(kTraceCallback)) TRACE("my_proc event:  onReadRequest:" <<  std::hex<< pc->get_16uid() << std::dec);
  _send_value(pc);
}

/****************************************************************************************
*/
int Callback::onSubscribesNotify(IHandler* pc, bool b)
{
  if(is_tracing(kTraceCallback)) TRACE("my_proc event: onSubscribesNotify:" << std::hex<< pc->get_16uid() << "="<<(int)b<< std::dec);
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
  if(is_tracing(kTraceCallback)) TRACE("my_proc event:  onWriteRequest:" <<  std::hex<< pc->get_16uid() << std::dec);
  std::string     ret;
  const uint8_t*  value = pc->get_value();
  char            by[4];
  int             i=0;

  for(;i<pc->get_length();i++)
  {
    ::sprintf(by,"%02X:",value[i]);
    ret.append(by);
  }
  if(is_tracing(kTraceCallback)) TRACE("Remote data:" << ret);
  if(pc->get_16uid() == UID_GPIO)
  {
    if(::access("/sys/class/gpio/gpio17/value",0)==0)
    {
      if(value[0]==0) {
          system("echo 0 > /sys/class/gpio/gpio17/value");
      } else {
          system("echo 1 > /sys/class/gpio/gpio17/value");
      }
    }
  }
}

/****************************************************************************************
*/
//descriptor chnaged of the charact
void Callback::onWriteDescriptor(IHandler* pc, IHandler* pd)
{
    if(is_tracing(kTraceCallback)) TRACE("my_proc event:  onWriteDescriptor:" << int(*((int*)(pd->get_value()))));
}

/****************************************************************************************
*/
void Callback::onAdvertized(bool onoff)
{
    if(is_tracing(kTraceCallback)) TRACE("my_proc event:  onAdvertized:" << onoff);
}

/****************************************************************************************
*/
void Callback::onDeviceStatus(bool onoff)
{
    if(is_tracing(kTraceCallback)) TRACE("my_proc event:  onDeviceStatus:" << onoff);
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
        if(is_tracing(kTraceCallback)) TRACE("my_proc event: disconnected");
    }
    else
    {
        if(is_tracing(kTraceCallback)) TRACE("accepted connection: " << device->_mac <<","<< device->_name);
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
    if(is_tracing(kTraceCallback)) TRACE("my_proc::_get_time");

    time_t secs = time(0);
    struct tm *local = localtime(&secs);
    sprintf(_some, "%02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec);
    return _some;
}

/****************************************************************************************
*/
float Callback::_get_temp()
{
    if(is_tracing(kTraceCallback)) TRACE("my_proc::_get_temp");

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
const char* Callback::_get_temp_s()
{
    if(is_tracing(kTraceCallback)) TRACE("my_proc::_get_temp_s");
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
    if(is_tracing(kTraceCallback)) TRACE("my_proc::_get_gpio");
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
    if(is_tracing(kTraceCallback)) TRACE("my_proc::_send_value");

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
