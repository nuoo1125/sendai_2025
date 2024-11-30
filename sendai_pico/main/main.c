#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "stepper/stepper.h"

void main(){
    stepper_setup();
    stepper_slow(1,1);
}