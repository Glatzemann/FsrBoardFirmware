/*
   FSR Board Firmware - Firmware for PCB doing FSR Sensor tests for
    reprap printers auto bed leveling.
    
    Copyright (C) 2015  Roland "Glatzemann" Rosenkranz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Thermistor.h"
#include "Configuration.h"
#include "Pins.h"

#include "Arduino.h"

Thermistor::Thermistor()
  : currentTemp(20.0f)
  , resistance(0)
{
  
}

void Thermistor::update(unsigned long time)
{
  currentTemp = calc(analogRead(THERMISTOR_ANALOG_PIN));
  
}

float Thermistor::getCurrentTemperature()
{
  return currentTemp;
}

long Thermistor::getRawResistance()
{
  return resistance;
}

float Thermistor::calc(int rawAdc)
{
  float vcc = 3.3f;       // only used for display purposes, if used set to the measured Vcc.
  float pad = 100000;     // balance/pad resistor value, set this to the measured resistance of your pad resistor
  float thermr = 100000;  // thermistor nominal resistance

  resistance = pad * ((1024.0 / rawAdc) - 1); 
  float temp = log(resistance); // Saving the Log(resistance) so not to calculate it 4 times later
  temp = 1 / (0.001129148 + (0.000234125 * temp) + (0.0000000876741 * temp * temp * temp));
  temp = temp - 273.15;  // Convert Kelvin to Celsius

  return temp;
}
