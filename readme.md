Oprema:

1. STM32F407VG
2. Dodatno napajanje: baterija 9 [V]
3. senzor nivoa (4x) // korištena 2
4. motor SG90 (2x)
5. DC motor
6. Relej
7. Potenciometar 10k (2x)
8. LCD 1602

Funkcionalnost:
Sistem se sastoji iz dva rezervoara i posude za miješanje tečnosti. Prvo ćemo provjeriti da li u rezervoarima ima tečnosti, ako ima, ući ćemo u while petlju, a ako nema, kod se neće dalje izvršavati (ovaj dio programa trenutno nije realizovan). Kada smo ustanovili da u rezervoarima imamo tečnost, prvo će se otvoriti prvi ventil (pokreće se prvi servo motor) dok drugi ventil ostaje
zatvoren. Kada voda u posudi za miješanje dostigne prvi nivo (promijeni se prvi flag), zatvara se prvi ventil (vraćamo prvi servo motor u početni položaj) a drugi ventil se otvara (pokrećemo drugi servo motor). Sada ćemo sačekati da voda u posudi dosegne drugi nivo. Kada voda dostigne drugi nivo (promijeni se drugi flag) dolazi do zatvaranja drugog ventila. Sada u posudi imamo dovoljno
tečnosti i moguće je miješanje. Za pokretanje je korišten DC motor. Pritiskom na taster koji se nalazi na ploči okida relej i pokreće motor koji je spojen na eksterno napajanje (baterija od 9 V). Motor je pokrenut dok držimo taster. Kada pustimo taster
motor prestaje sa kretanjem, tj. mješanje se obustavlja.
