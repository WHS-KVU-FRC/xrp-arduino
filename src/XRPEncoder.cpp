#include "Arduino.h"
#include "XRPEncoder.h"

xrp::XRPEncoder::XRPEncoder(int channelA, int channelB) {
  this->channelA = channelA;
  this->channelB = channelB;
}