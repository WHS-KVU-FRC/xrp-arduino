#ifndef _XRPENCODER_H_
#define _XRPENCODER_H_

#include "Arduino.h"

namespace xrp {
class XRPEncoder {
 public:
  XRPEncoder(int channelA, int channelB);
 private:
  int channelA;
  int channelB;
};
} // namespace xrp

#endif