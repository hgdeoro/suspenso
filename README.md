## About Suspenso

The goal is to create a system that will give us information about the motorcycle suspension,
to be able to make changes in the suspension settings and collect data to learn about
the effects of those changes. Also, knowing if we're close to use all the travel available
in the front suspension would be good, since that's dangerous.

Is it possible to build such system with simple components? **I have no idea**.

The idea is to keep it as simple as possible. Initial approach will be to create something
closer to a "data logger", no need to see information in real time.

![Motorcycle](docs/motorcycle.png?raw=true "MVP")

## What to measure

Probably the best measurement would be height of motorcycle (front and rear)
and position/travel of suspensions (front and rear), but this is difficult. Thus, for a
**first approach**, the idea is to ignore motorcycle height (and thus ignore
changes of height produced because of the compression of the tire) and
just measure position/travel of suspension.

Also, by using accelerometers, maybe it will be possible to compare the values
read in the wheel vs the value read in the chassis, and thus create some indicator
about how much force (force? that's the right word?) the suspension absorbed.

In the future: there's lot of ideas, like tire pressure (that affects suspension),
tire temperature (IR camera?), motorcycle angle, motorcycle distance from road, etc.

### How to measure position/travel of suspension

Maybe using something like VL53L1X or VL6180X, we can measure the distance from the
motorcycle fender to the tire, and from that calculate the travel of suspension?

## UI

Not defined yet. Probably some web server running on the Raspberry Pi to show
the information received? This would be simple to implement. A laptop can be
connected con the wifi network and access some http service running in the
Raspberry Pi.

## Protection of Arduino

Not defined yet. Maybe potting with [Devcon Urethane](https://www.reddit.com/r/AskElectronics/comments/jabskm/could_i_waterproof_this_with_epoxy_resin_more_in/g8p4kwf?utm_source=share&utm_medium=web2x&context=3)?

## Schema (work in progess)

Not the final schema, but so far, I'm working on this:

![Electronics](docs/mvp_bb.png?raw=true "MVP")

## Main components

* **Raspberry Pi**: wifi access point + server to receive data from Arduinos
* **Arduinos**: sense and send data to Raspberry Pi
* **Button**: syncronize time reference in all Arduinos

## Design decision

Anything can change, but so far, these are the design decision.

* Send power to Arduino by wire, since Arduino Nano 33 IoT accepts up to 20V DC.
  * _Assumption_: changes in voltage won't affect Arduino Nano 33 IoT sensors
  * _CON_: require wires, which makes installation more difficult
  * _PRO_: much simpler building, less electronics to deal with
  * _Alternative_: we can add a battery to each Arduino to avoid using the wires.
  
* Synchronize time in Arduinos using hardware solution:
  * _Assumption_: software synchronization is much less precise.
  * _CON_: requires an extra wire, but since we're sending 2 wires to the Arduinos, this
    is not a big deal.
  * _PRO_: very precise (by using external interrumpt).
  * _PRO_: simple and safe: uses GROUND and internal pull up resistor.
  * _Alternative_: since we have network communication with Arduinos, we can try using
    NTP protocol, but probably this won't be very precise.
  * _Alternative_: no syncronization at all? This could work if every Arduino boot at the
    exact same time.
  * _Alternative_: remove button and trigger synchronization from Raspberry Pi. This is a good
    feature, but not implemented at the moment to keep it simple.

* Send data by wireless communication
  * _Assumption_: since distance between components is short, link quality and throughput will be good
  * _Assumption_: Wifi + UDP is fast and reliable, more than Bluetooth
  * _PRO_: good throughput, simple API, flexibility
  * _Alternative_: connect Arduinos to Raspberry Pi (How? Serial? RSS?)

## Planned iterations

* Suspenso v0.1:
  * Goal: as a first approach, let’s try the simplest way to send data using UDP packets.
  * [Read more](https://hgdeoro.com/2021/07/sending-data-from-arduino-part-1/)

* Suspenso v0.2:
  * Goal: let's learn about the limits of sending data points using UDP.
  * [Read more](https://hgdeoro.com/2021/07/sending-data-from-arduino-part-2/)
  * **WORK IN PROGRESS**

# Attribution

Motorcycle image from https://unsplash.com/photos/AMn5p2YX0g0

# Directories

## /sensor

Arduino sketch.

## /automation

Ansible playbooks to setup development environment: computer & Raspberry Pi. Probably this won't
work on other computers.

## /suspensopy

Python package. At the moment, scripts to facilitate running of tests.

# License

Not sure if this is the best for software + hardware project. At the moment:

GNU AFFERO GENERAL PUBLIC LICENSE
