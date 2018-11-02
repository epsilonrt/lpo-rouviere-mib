# How to build ?

This subagent can control 3 leds and read 3 push buttons connected to the GPIO of a Pi board.

**`snmpd` must be installed with configuration files in ../etc/snmp and started.**

## Install LPO-ROUVIERE-MIB

		$ mkdir -p ~/.snmp/mibs && cp ../LPO-ROUVIERE-MIB.txt ~/.snmp/mibs/
		$ sudo service snmpd restart

Verify with :

		$ snmptranslate -M+. -mLPO-ROUVIERE-MIB -Tp -IR lpoRouviereMIB
			+--lpoRouviereMIB(52900)
				 |
				 +--lprMIBObjects(1)
				 |  |
				 |  +--lprSnmpTutorial(1)
				 |  |  |
				 |  |  +--lprSnmpTutorialLeds(1)
				 |  |  |  |
				 |  |  |  +-- -RW- Integer32 led1(1)
				 |  |  |  |        Range: 0..1
				 |  |  |  +-- -RW- Integer32 led2(2)
				 |  |  |  |        Range: 0..1
				 |  |  |  +-- -RW- Integer32 led3(3)
				 |  |  |           Range: 0..1
				 |  |  |
				 |  |  +--lprSnmpTutorialButtons(2)
				 |  |     |
				 |  |     +-- -R-- Integer32 sw1(1)
				 |  |     |        Range: 0..1
				 |  |     +-- -R-- Integer32 sw2(2)
				 |  |     |        Range: 0..1
				 |  |     +-- -R-- Integer32 sw3(3)
				 |  |              Range: 0..1
				 |  |
				 |  +--lprPointCast(2)
				 |     |
				 |     +--lprPointCastCoils(1)
				 |     |  |
				 |     |  +-- -RW- Integer32 coil1(1)
				 |     |  |        Range: 0..1
				 |     |  +-- -RW- Integer32 coil2(2)
				 |     |  |        Range: 0..1
				 |     |  +-- -RW- Integer32 coil3(3)
				 |     |           Range: 0..1
				 |     |
				 |     +--lprPointCastDiscreteInputs(2)
				 |     |
				 |     +--lprPointCastInputRegisters(3)
				 |
				 +--lprMIBConformance(2)

## Build `piduino-agent` with `net-snmp-config`

		$ net-snmp-config --compile-subagent --cflags "$(pkg-config --cflags piduino)" --ldflags "$(pkg-config --libs piduino)" piduino-agent lprSnmpTutorial.c

You can also compile with codelite !

## Test `piduino-agent`

		$ sudo ./piduino-agent -f -Lo -DlprSnmpTutorial -x  tcp:localhost:705

if you have compiled with codelite, the command is:

		$ sudo Debug/piduino-agent

* Reads leds

    $ snmpwalk -v1 -cepsilonrt localhost LPO-ROUVIERE-MIB::lprSnmpTutorialLeds
      LPO-ROUVIERE-MIB::led1.0 = INTEGER: 0
      LPO-ROUVIERE-MIB::led2.0 = INTEGER: 0
      LPO-ROUVIERE-MIB::led3.0 = INTEGER: 0

* Reads buttons

    $ snmpwalk -v1 -cepsilonrt localhost LPO-ROUVIERE-MIB::lprSnmpTutorialButtons
      LPO-ROUVIERE-MIB::led1.0 = INTEGER: 0
      LPO-ROUVIERE-MIB::led2.0 = INTEGER: 0
      LPO-ROUVIERE-MIB::led3.0 = INTEGER: 0


* Set led1

    $ snmpset -v1 -cepsilonrt localhost LPO-ROUVIERE-MIB::led1.0 i 1
      LPO-ROUVIERE-MIB::led1.0 = INTEGER: 1

* Clear led1

    $ snmpset -v1 -cepsilonrt localhost LPO-ROUVIERE-MIB::led1.0 i 0
      LPO-ROUVIERE-MIB::led1.0 = INTEGER: 0

* remote access

    $ snmpwalk -v1 -cepsilonrt n12 LPO-ROUVIERE-MIB::lprSnmpTutorialButtons
    $ snmpset -v1 -cepsilonrt n12 LPO-ROUVIERE-MIB::led1.0 i 1
    $ snmpset -v1 -cepsilonrt n12 LPO-ROUVIERE-MIB::led1.0 i 0
