/*=============================================================================
   Copyright (c) 2014-2024 Joel de Guzman. All rights reserved.

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#include <q_io/midi_stream.hpp>
#include "example.hpp"
#include <print>

namespace q = cycfi::q;
namespace midi = q::midi_1_0;

///////////////////////////////////////////////////////////////////////////////
// MIDI processor example. This simple program monitors the incoming MIDI
// stream and prints the event to std::cout. Not all events are monitored.
//
// Note: This uses the default MIDI input device. Use the PmDefaults program
// (in external/app/pmdefaults folder) to set the default MIDI input device.
///////////////////////////////////////////////////////////////////////////////

struct midi_processor : midi::processor
{
   using midi::processor::operator();

   void operator()(midi::note_on msg, std::size_t time)
   {
      std::println(
         "Note On  {{Channel: {}, Key: {}, Velocity: {}}}",
         int(msg.channel()),
         int(msg.key()),
         int(msg.velocity())
      );
   }

   void operator()(midi::note_off msg, std::size_t time)
   {
      std::println(
         "Note Off {{Channel: {}, Key: {}, Velocity: {}}}",
         int(msg.channel()),
         int(msg.key()),
         int(msg.velocity())
      );
   }

   void operator()(midi::poly_aftertouch msg, std::size_t time)
   {
      std::println(
         "Polyphonic Aftertouch {{Channel: {}, Key: {}, Pressure: {}}}",
         int(msg.channel()),
         int(msg.key()),
         int(msg.pressure())
      );
   }

   void operator()(midi::control_change msg, std::size_t time)
   {
      std::println(
         "Control Change {{Channel: {}, Controller: {}, Value: {}}}",
         int(msg.channel()),
         int(msg.controller()),
         int(msg.value())
      );
   }

   void operator()(midi::program_change msg, std::size_t time)
   {
      std::println(
         "Program Change {{Channel: {}, Preset: {}}}",
         int(msg.channel()),
         int(msg.preset())
      );
   }

   void operator()(midi::channel_aftertouch msg, std::size_t time)
   {
      std::println(
         "Channel Aftertouch {{Channel: {}, Pressure: {}}}",
         int(msg.channel()),
         int(msg.pressure())
      );
   }

   void operator()(midi::pitch_bend msg, std::size_t time)
   {
      std::println(
         "Pitch Bend             {{Channel: {}, Value: {}}}",
         int(msg.channel()),
         int(msg.value())
      );
   }
};

int main()
{
   q::midi_input_stream::set_default_device(get_midi_device());

   q::midi_input_stream stream;
   if (stream.is_valid())
   {
      while (true)
         stream.process(midi_processor{});
   }

   return 0;
}

