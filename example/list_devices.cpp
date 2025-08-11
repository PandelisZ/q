/*=============================================================================
   Copyright (c) 2014-2024 Joel de Guzman. All rights reserved.

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#include <q_io/audio_device.hpp>
#include <q_io/midi_device.hpp>
#include <print>
#include <string>

namespace q = cycfi::q;

int main()
{
   std::println("================================================================================");
   std::println("Available Audio Devices: ");
   for (auto const& device : q::audio_device::list())
   {
      std::println("id: {}", device.id());
      std::println("name: \"{}\"", device.name());
      std::println("number of input channels: {}", device.input_channels());
      std::println("number of output channels: {}", device.output_channels());
   }

   std::println("================================================================================");
   std::println("Available MIDI Devices: ");
   for (auto const& device : q::midi_device::list())
   {
      std::println("id: {}", device.id());
      std::println("name: \"{}\"", device.name());
      std::println("number of inputs: {}", device.num_inputs());
      std::println("number of outputs: {}", device.num_outputs());
   }
   return 0;
}

