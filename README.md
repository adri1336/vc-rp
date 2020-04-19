# Vice City Roleplay (SA-MP 0.3.DL)
Servidor de SA-MP en la ciudad de Vice City creado sin base.

## Dependencias
SA-MP 0.3.DL-R1 server (https://archive.org/download/sa-mp-0.3.dl/samp03DL_svr_R1_win32.zip)
Pawn Compiler 3.10.8 (https://github.com/pawn-lang/compiler/releases/tag/v3.10.8)
sscanf 2.8.2 (https://github.com/maddinat0r/sscanf/releases/tag/v2.8.2)
GPS (https://github.com/kristoisberg/samp-gps-plugin/releases/tag/1.4.0)
Streamer 2.9.4 (https://github.com/samp-incognito/samp-streamer-plugin/releases/tag/v2.9.4)
MySQL R41-4 (https://github.com/pBlueG/SA-MP-MySQL/releases/tag/R41-4)
Pawn.Regex 1.1.2 (https://github.com/urShadow/Pawn.Regex/releases/tag/1.1.2)
samp-mysql-yinline-include v1.0.1 (https://github.com/maddinat0r/samp-mysql-yinline-include/releases/tag/v1.0.1)

## Instalación rapida
1. Instala las dependencias
2. Copia los includes de la carpeta *includes* a tu compilador de Pawn
2. Crea las bases de datos con el archivo *schemas/databases.sql*
3. Importa cada archivo *.sql* de la carpeta *schemas* a su base de datos correspondiente
4. Compila *filterscripts/maps.pwn* y *gamemodes/main.pwn*
4. Configura *server.cfg* si es necesario
5. Abre *samp-server.exe*

## Gamemode
*(main.pwn)*
- Comenta la línea **#define LOCAL_HOST** para habilitar el modo producción
- Redefine **#define MAX_PLAYERS 50** según el máximo de slots de su servidor
- Redefine **#define SAVE_ACCOUNTS_TIME** si es necesario, es el intervalo de tiempo de guardado de las cuentas online, por defecto es de **5 minutos**
- **Las radios no funcionan debido a que dependen de un servidor, puedes activarlas usando tu propio servidor, para ello:**
	- Redefine **#define RADIO_URL** del archivo *gamemodes/server/radios/header.inc*


### Ignora los siguientes warnings de compilación
```
gamemodes\main.pwn(48) : warning 218: old style prototypes used with optional semicolumns
gamemodes\player/pstats/funcs.inc(167) : warning 213: tag mismatch: expected tag none ("_"), but found "Float"
gamemodes\player/label_render/funcs.inc(82) : warning 213: tag mismatch: expected tag none ("_"), but found "Float"
gamemodes\player/label_render/funcs.inc(83) : warning 213: tag mismatch: expected tag none ("_"), but found "Float"
```

