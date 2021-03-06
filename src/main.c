/******************************************************************************
*				Skolprojekt
* Felsök och uppdatera en befintlig C-kod från C89 till C99 och optimera
* koden.
*
* Extra: Lägg till funktionalitet så som, WDT, 7seg, vector, dynamisk timer,
*	EEPROM
* Implementerat:  Watchdog, 7-segmentsdisplay, Vector, Dynamisk timer.
*******************************************************************************
* Innan så exekverade inte koden på grund av flera fel.
* Makron som var feldefinierade och andra makron som användes på fel ställen.
* Felaktiga beräkningar korrigerades
*
* Programmet var tänkt att skriva ut temperatur seriellt var 60:e sekund.
* Om knapp på PIN 13 trycktes ner så återställdes timern samtidigt som
* temperaturen skrevs ut seriellt.
* Vid varje utskrift så togglades en lysdiod för indikation av att avläsning
* har ägt rum.
*******************************************************************************
* I det uppdaterade programmet så har  delar av koden slopats då de inte
* hade något användningsområde i den uppdaterade koden.
*
* Borttagna filer: MemoryBlock.h, MemoryBlock.c, Byte.h, Byte.c	
*
* En LED har bytts ut mot två stycken 7-segments displayer som visar aktuell
* temperatur efter att en dynamisk timer aktiveras via tryckknapp på PIN 13.
* Den dynamiska timern håller upp till 10 värden som sparar tiden mellan
* varje tryckknapp. Summan av all tid divideras med det antalet tider som har
*  sparats (upp till 10 värden).
*
* Seriell överföring inaktiveras efter initieringsrutinen har gjort sitt.
* Därefter är allt styrt via avbrottsrutiner där main loop som kontinuerligt
* återställer räknaren för Watchdog-timern så länge programmet exekverar
* normalt.
******************************************************************************/

// Inkluderingsdirektiv:
#include "header.h"

/******************************************************************************
* Funktionen main utgör programmets start- och slutpunkt. Programmets globala
* variabler initieras via anrop av funktionen setup. Efter att setup-rutinen
* har körts så avaktiveras seriell överföring via funktionen disable_serial
* då temperaturen går att avläsa på 7 segmentsdisplayer.
*
* En while-loop används för att hålla programmet igång och för att återställa 
* Watchdog-timern via WD_reset så länge matningsspänning tillförs.
* Om programmet fastnar i exekvering utanför mainloop så återställs programmet.
*
* Resterande del av programmet är avbrottsgenererat.
******************************************************************************/
int main(void)
{	
	setup();
	disable_serial(true);
    while (true)
	{
	WD_reset();
	}
	return 0;
}
