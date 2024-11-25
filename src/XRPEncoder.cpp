#include "Arduino.h"
#include "XRPEncoder.h"

// Changed code for teaching purposes

xrp::XRPEncoder::XRPEncoder(int channelA, int channelB) {
  this->channelA = channelA;
  this->channelB = channelB;
}