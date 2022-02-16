#!/bin/bash
echo $LIGHT_RGBA_VALUE | nc 10.216.183.183 80 -w1;
