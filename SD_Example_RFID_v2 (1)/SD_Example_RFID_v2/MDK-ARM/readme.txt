Este proyecto visualiza el reloj en tiempo real y presenta un men�
que permite registrar la hora en un fichero en una micro-sd.

Tambi�n permite viasualizar las horas almacenadas y borrar el fichero.

El programa adem�s permite leer un lector de tarjetas RFID conectado a los mismos pines que la
tarjeta SD integrada en la Mini-DK2 utilizando los pines P0.0 como Reset y P0.1 como CS

Conexi�n del adaptador RFIR MFR522
   MFRC552_RST:    P0.0
   MFRC552_MISO:   P1.23
   MFRC552_MOSI:   P1.24
   MFRC552_SCK:    P1.20
   MFRC552_SS/SDA: P0.1
