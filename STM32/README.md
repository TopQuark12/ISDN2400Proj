
# Notes  

## ADC calculations  

STM32F767 characteristics:  
ADC clock = 27Mhz  
External input impedance = 50kR  
Sampling switch impedance = 6kR  
SHA capacitance (Max) = 7pF  
Expected curcuit impedance = 5kR  
Allowed error = 1/4LSB  
Needed sampling period = 111.878clk => 112clk  
12-bit conversion time = 15clk  
Sampling time = ~4.7us  