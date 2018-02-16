# Stepper-Motor-Controller
Using an arduino, it is fairly simply to design a circuit with a H-bridge and have full control over the stepper motor by controlling the four pins.
This arduino code encodes the four steps required to make a stepper motor go forwards, backwards, at any speed of the loop.

This design is part of a larger project to create an automated battery capacity testing machine. One stepper motor will push batteries
out of a stack, onto discharge contacts. The arduino will log how long the battery discharges for at a constant current. Then another
stepper motor from behind will push the discharged battery into another stack. The arduino will store capacity of each battery in an
array, so we know array[0] is the battery at the bottom of the discharged stack. I will then physically write the capacity on each
battery to know if it is good or bad, so that I can put the good ones into a pack together for my electric bicycle build.
