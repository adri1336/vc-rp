[connection]
MESSAGE_ERROR_WRONG_NAME_FORMAT = {ERROR}Tu nombre no cumple con el formato Nombre_Apellido.
MESSAGE_WARNING_IP = {WARNING}Tu dirección IP ha cambiado desde tu última conexión.

MESSAGE_INFO_SPAWN_NEW_USER = {SUCCESS}* Bienvenido %s, esperamos que te diviertas en el servidor, utiliza /ayuda para obtener ayuda sobre el servidor.
MESSAGE_INFO_SPAWN = {SUCCESS} * Bienvenido de nuevo %s, te vimos por última vez el %s.

MESSAGE_ERROR_INDEX = {ERROR}No se pudo cargar tu última posición debido a un error del servidor.

[register]
TEXTDRAW_GENDER = Género
TEXTDRAW_GENDER_MALE = Masculino
TEXTDRAW_GENDER_FEMALE = Femenino
TEXTDRAW_CHARACTER = Personaje
TEXTDRAW_CONTINUE = Continuar

DIALOG_REGISTER_LANG_CAPTION = Selecciona tu idioma
DIALOG_REGISTER_LANG_BODY = %s
DIALOG_REGISTER_LANG_YES = Continuar
DIALOG_REGISTER_LANG_NO = Salir

DIALOG_REGISTER_PASSWD_CAPTION = Registra tu cuenta
DIALOG_REGISTER_PASSWD_BODY_1 = Introduce una contraseña que puedas recordar para registrar tu cuenta.\n
DIALOG_REGISTER_PASSWD_BODY_2 = La contraseña debe ser segura y debe contener entre %d y %d caracteres.\n\n
DIALOG_REGISTER_PASSWD_BODY_3 = ¡No compartas tu contraseña con nadie!
DIALOG_REGISTER_PASSWD_YES = Continuar
DIALOG_REGISTER_PASSWD_NO = Salir
MESSAGE_ERROR_WRONG_REG_PASSWD = {ERROR}La contraseña no cumple con el formato indicado.

DIALOG_REGISTER_REPASSWD_CAPTION = Registra tu cuenta
DIALOG_REGISTER_REPASSWD_BODY = Vuelve a introducir tu contraseña.\nQueremos comprobar que coinciden.
DIALOG_REGISTER_REPASSWD_YES = Continuar
DIALOG_REGISTER_REPASSWD_NO = Atrás
MESSAGE_ERROR_WRONG_REG_REPASSWD = {ERROR}Las contraseñas no coinciden.

DIALOG_REGISTER_MAIL_CAPTION = Indica tu correo
DIALOG_REGISTER_MAIL_BODY = Indica tu dirección de correo electrónico.\nEstá sera el único medio para recuperar tu contraseña.
DIALOG_REGISTER_MAIL_YES = Continuar
DIALOG_REGISTER_MAIL_NO = Salir
MESSAGE_ERROR_WRONG_MAIL_FORMAT = {ERROR}Formato no válido.
MESSAGE_WARNING_EMAIL_EXISTS = {WARNING}Este correo electrónico está en uso.

MESSAGE_INFO_REGISTER = {INFO}Para continuar, haga clic en continuar.

[login]
DIALOG_LOGIN_CAPTION = Ingresar
DIALOG_LOGIN_BODY = Bienvenido de nuevo, %s.\nIngresa tu contraseña para jugar.
DIALOG_LOGIN_YES = Continuar
DIALOG_LOGIN_NO = Salir
MESSAGE_ERROR_WRONG_LOGIN = {ERROR}Contraseña incorrecta. Intento %d/%d, si fallas todos los intentos serás bloqueado por %d minutos.

[commands_control]
MESSAGE_ERROR_NOT_SPAWNED = {ERROR}Ahora no puedes usar comandos.
MESSAGE_ERROR_NOT_ALLOWED = {ERROR}No tienes permiso para usar este comando.
MESSAGE_ERROR_UNDEFINED_COMMAND = {ERROR}El comando %s no existe.

[afk]
MESSAGE_INFO_AFK_DAYS = {INFO}Estuviste en pausa durante %d días, %d horas y %d minutos.
MESSAGE_INFO_AFK_HOURS = {INFO}Estuviste en pausa durante %d horas y %d minutos.
MESSAGE_INFO_AFK_MINUTES = {INFO}Estuviste en pausa durante %d minutos y %d segundos.
MESSAGE_INFO_AFK_SECONDS = {INFO}Estuviste en pausa durante %d segundos.

[area_action_key]
GAMETEXT_INFO_CLOSED = ~r~cerrado
MESSAGE_ERROR_PROPERTY_LT_MINUTES = {ERROR}Tienes que esperar %d minutos y %d segundos para volver a hacer una visita.
MESSAGE_ERROR_PROPERTY_LT_SECONDS = {ERROR}Tienes que esperar %d segundos para volver a hacer una visita.
MESSAGE_ERROR_VINV_IN_USE = {ERROR}Hay otra persona buscando en el maletero.

[hospital]
MESSAGE_INFO_HOSPITAL_MONEY = {INFO}Fuiste llevado al hospital más cercano, el coste por los servicios médicos es de %d$.
MESSAGE_INFO_HOSPITAL = {INFO}Fuiste llevado al hospital más cercano.
MESSAGE_INFO_HOSPITAL_BED = {INFO}Puedes usar las camas del hospital para recuperarte.
MESSAGE_ERROR_BED_IN_USE = {ERROR}Esta cama está siendo usada por otra persona.
MESSAGE_INFO_BED = {INFO}Espera mientras te recuperas, para irte presiona F o ENTER.
MESSAGE_ERROR_GOOD_HEALTH = {ERROR}Tu estado es bueno, no necesitas recuperarte.
GAMETEXT_INFO_CURED = ~g~curado
MESSAGE_INFO_BED_DISTANCE = {INFO}No te levantes de la cama mientras te curas, si quieres irte presiona F o ENTER.

[disconnect_message]
MESSAGE_INFO_DISCONNECT_CRASH = {INFO}%s se ha desconectado (crash).
MESSAGE_INFO_DISCONNECT_QUIT = {INFO}%s se ha desconectado.
MESSAGE_INFO_DISCONNECT_KICK = {INFO}%s se ha desconectado (kick/ban).

[atm]
TEXTDRAW_WITHDRAW = Retirar
TEXTDRAW_DEPOSIT = Depositar
TEXTDRAW_EXIT = Salir

DIALOG_ATM_DEPOSIT_CAPTION = Depositar dinero
DIALOG_ATM_DEPOSIT_BODY = Tienes %d$ en efectivo, ¿cuánto quieres depositar?
DIALOG_ATM_DEPOSIT_YES = Depositar
DIALOG_ATM_DEPOSIT_NO = Atrás

DIALOG_ATM_WITHDRAW_CAPTION = Retirar dinero
DIALOG_ATM_WITHDRAW_BODY = Tienes %d$ en tu cuenta bancaria, ¿cuánto quieres retirar?
DIALOG_ATM_WITHDRAW_YES = Retirar
DIALOG_ATM_WITHDRAW_NO = Atrás

MESSAGE_ERROR_WRONG_FORMAT = {ERROR}Debes introducir un valor numérico entero.
MESSAGE_ERROR_NEGATIVE = {ERROR}Debes introducir un valor positivo.
MESSAGE_ERROR_NOMONEY = {ERROR}No tienes %d$ en efectivo para poder depositarlos.
MESSAGE_ERROR_NOBANKMONEY = {ERROR}No tienes %d$ en tu cuenta para poder retirarlos.
MESSAGE_ERROR_MAX_TRANSACTION = {ERROR}Los cajeros tienen un limite de %d$ por transacción.
MESSAGE_INFO_DEPOSIT = {INFO}Has depositado %d$ en tu cuenta bancaria.
MESSAGE_INFO_WITHDRAW = {INFO}Has retirado %d$ de tu cuenta bancaria.

[bank]
DIALOG_BANK_MOVEMENTS_HEADER = Fecha\tConcepto\tCantidad\n
BANK_MOVEMENT_WITHDRAW = Retirada de dinero
BANK_MOVEMENT_DEPOSIT = Ingreso de dinero
BANK_MOVEMENT_TRANSFER_TO = Enviado a:
BANK_MOVEMENT_TRANSFER_FROM = Recibido de:

DIALOG_BANK_POINT_CAPTION = Banco
DIALOG_BANK_POINT_BODY = - Retirar\n- Depositar\n- Transferir\n- Movimientos
DIALOG_BANK_POINT_YES = Continuar
DIALOG_BANK_POINT_NO = Salir

DIALOG_BANK_WITHDRAW_CAPTION = Retirar dinero
DIALOG_BANK_WITHDRAW_BODY = Tienes %d$ en tu cuenta bancaria, ¿cuánto quieres retirar?
DIALOG_BANK_WITHDRAW_YES = Retirar
DIALOG_BANK_WITHDRAW_NO = Atrás

DIALOG_BANK_DEPOSIT_CAPTION = Depositar dinero
DIALOG_BANK_DEPOSIT_BODY = Tienes %d$ en efectivo, ¿cuánto quieres depositar?
DIALOG_BANK_DEPOSIT_YES = Depositar
DIALOG_BANK_DEPOSIT_NO = Atrás

DIALOG_BANK_TRANSFER_CAPTION = Transferir dinero
DIALOG_BANK_TRANSFER_BODY = ¿Cuánto dinero quieres transferir?\nTienes %d$ en tu cuenta bancaria.
DIALOG_BANK_TRANSFER_YES = Continuar
DIALOG_BANK_TRANSFER_NO = Atrás

DIALOG_BANK_TRANSFER_NAME_CAPTION = Transferir dinero
DIALOG_BANK_TRANSFER_NAME_BODY = Vale, quieres transferir %d$.\n¿A quién quieres transferirle el dinero? Indica el nombre completo.
DIALOG_BANK_TRANSFER_NAME_YES = Continuar
DIALOG_BANK_TRANSFER_NAME_NO = Atrás
MESSAGE_ERROR_TRANSFER_WRONG_FORMAT = {ERROR}Debes introducir el nombre de la persona a la que quieres transferirle el dinero.
MESSAGE_ERROR_TRANSFER_WRONG_NAME = {ERROR}El nombre '%s' no está registrado en nuestra base de datos.

DIALOG_BANK_TRANSFER_CONFIRM_CAPTION = Transferir dinero
DIALOG_BANK_TRANSFER_CONFIRM_BODY = Beneficiario: %s\nCantidad: %d$\n\n¿Quieres realizar la transferencia?
DIALOG_BANK_TRANSFER_CONFIRM_YES = Transferir
DIALOG_BANK_TRANSFER_CONFIRM_NO = Atrás

MESSAGE_ERROR_WRONG_FORMAT = {ERROR}Debes introducir un valor numérico entero.
MESSAGE_ERROR_NEGATIVE = {ERROR}Debes introducir un valor positivo.
MESSAGE_ERROR_NOMONEY = {ERROR}No tienes %d$ en efectivo para poder depositarlos.
MESSAGE_ERROR_NOBANKMONEY = {ERROR}No tienes %d$ en tu cuenta para poder retirarlos.
MESSAGE_ERROR_MAX_TRANSACTION = {ERROR}Los cajeros tienen un limite de %d$ por transacción.
MESSAGE_INFO_DEPOSIT = {INFO}Has depositado %d$ en tu cuenta bancaria.
MESSAGE_INFO_WITHDRAW = {INFO}Has retirado %d$ de tu cuenta bancaria.
MESSAGE_INFO_TRANSFER = {INFO}Has transferido %d$ a la cuenta de %s.
MESSAGE_INFO_GOTTRANSFER = {INFO}Has recibido una tranferencia de %s de %d$.
MESSAGE_ERROR_NO_MOVEMENTS = {ERROR}No hay movimientos en tu cuenta bancaria.

[veh_shop_sunshine]
DIALOG_SELECT_OPTION_CAPTION = Concesionario
DIALOG_SELECT_OPTION_BODY = Ver catálogo de vehículos nuevos\nVender un vehículo
DIALOG_SELECT_OPTION_YES = >>
DIALOG_SELECT_OPTION_NO = Cerrar

DIALOG_SVEH_INFO_CAPTION = Comprar vehículo
DIALOG_SVEH_INFO_BODY = Vehículo: %s\nPrecio: %d$\nNivel requerido: %d\n\nVelocidad máxima: %d KM/H\nCapacidad depósito: %.0fL\nAsientos: %d\n\n¿Quieres comprar este vehículo?
DIALOG_SVEH_INFO_BODY_MPH = Vehículo: %s\nPrecio: %d$\nNivel requerido: %d\n\nVelocidad máxima: %d MPH\nCapacidad depósito: %.0fL\nAsientos: %d\n\n¿Quieres comprar este vehículo?
DIALOG_SVEH_INFO_YES = Comprar
DIALOG_SVEH_INFO_NO = Cancelar

MESSAGE_ERROR_NO_MONEY = {ERROR}Te faltan %d$ para poder comprar este vehículo.
MESSAGE_ERROR_NO_LEVEL = {ERROR}Necesitas ser al menos nivel %d para poder comprar este vehículo.
MESSAGE_ERROR_MAX_VEHS = {ERROR}No puedes tener más vehículos, el límite es de %d vehículos por jugador.
MESSAGE_ERROR_INV_SLOT = {ERROR}No tienes espacio en tu inventario para las llaves del vehículo.
MESSAGE_ERROR_NO_LICENSE = {ERROR}Necesitas la licencia de conducir para poder comprar un vehículo.

DIALOG_SELL_CONFIRM_CAPTION = Vender vehículo
DIALOG_SELL_CONFIRM_BODY = Vehículo: %s\nMatrícula: %s\nRecibirás: %d$\n¿Quieres vender este vehículo?
DIALOG_SELL_CONFIRM_YES = Vender
DIALOG_SELL_CONFIRM_NO = Cancelar

MESSAGE_ERROR_VEHICLE_SELL = {ERROR}Ahora mismo no necesitamos vehículos, vuelve otro día.
MESSAGE_ERROR_NO_VEHICLES = {ERROR}No tienes ningún vehículo.
MESSAGE_ERROR_VEHICLE_STATE = {ERROR}No puedes vender este vehículo ahora.
MESSAGE_ERROR_VEHICLE_AREA = {ERROR}El vehículo tiene que estar cerca del concesionario para poder venderlo.
GAMETEXT_INFO_VEHICLE_SOLD = ~g~vendido

DIALOG_BUY_VEHICLE_INFO_CAPTION = Vehículo de ocasión
DIALOG_BUY_VEHICLE_INFO_BODY = Vehículo: %s\nKilometraje: %.0f\nPrecio: %d$\nNivel requerido: %d
DIALOG_BUY_VEHICLE_INFO_BODY_MPH = Vehículo: %s\nMillaje: %.0f\nPrecio: %d$\nNivel requerido: %d
DIALOG_BUY_VEHICLE_INFO_YES = Comprar
DIALOG_BUY_VEHICLE_INFO_NO = Cancelar
GAMETEXT_INFO_VEHICLE_BOUGHT = ~g~comprado

[nears_players]
DIALOG_CAPTION = Jugadores cercanos
DIALOG_ME = Yo

MESSAGE_ERROR_NO_NEAR_PLAYERS = {ERROR}No hay jugadores cercanos.
MESSAGE_ERROR_SELECTED_PLAYER_GONE = {ERROR}El jugador ya no está disponible.

[inv]
TEXTDRAW_TITLE = INVENTARIO
TEXTDRAW_INV_FREE_SLOT = Espacio vacío

INV_BUTTON_TYPE_GIVE = Dar
INV_BUTTON_TYPE_MOVE = Mover
INV_BUTTON_TYPE_DELETE = Eliminar
INV_BUTTON_TYPE_VEHICLE_OPEN = Abrir
INV_BUTTON_TYPE_PDOOR_OPEN = Abrir
INV_BUTTON_TYPE_BDOOR_OPEN = Abrir
INV_BUTTON_TYPE_VEHICLE_CLOSE = Cerrar
INV_BUTTON_TYPE_PDOOR_CLOSE = Cerrar
INV_BUTTON_TYPE_BDOOR_CLOSE = Cerrar
INV_BUTTON_TYPE_VEHICLE_START = Arrancar
INV_BUTTON_TYPE_VEHICLE_STOP = Parar
INV_BUTTON_TYPE_SHOW = Enseñar
INV_BUTTON_TURN_PHONE_ON = Encender
INV_BUTTON_TOY_ATTACH = Colocar
INV_BUTTON_TOY_REMOVE = Quitar
INV_BUTTON_CONFIG_TOY = Ajustar
INV_BUTTON_WEAPON_CARRY_YES = Sacar
INV_BUTTON_WEAPON_CARRY_NO = Guardar
INV_BUTTON_TYPE_OPEN_GPS = Usar
INV_BUTTON_TYPE_OPEN_PHONE = Usar
INV_BUTTON_FOOD_EAT = Comer
INV_BUTTON_DRINK_DRINK = Beber
INV_BUTTON_TYPE_SMOKE = Fumar
INV_BUTTON_WATCH_TIME = Hora
INV_BUTTON_USE_BOOMBOX = Sacar

INV_ITEM_BANDANA = bandana
INV_ITEM_BEER = cerveza
INV_ITEM_CAP = gorra
INV_ITEM_CIGARETTE = cigarrillo
INV_ITEM_GLASSES = gafas
INV_ITEM_HELMET = casco
INV_ITEM_HOTDOG = perrito caliente
INV_ITEM_PROPERTY_KEY = llave de propiedad (%d)
INV_ITEM_PROPERTY_MASTER_KEY = llave de propiedad (%d)
INV_ITEM_PROPERTY_RENT_KEY = llave de propiedad (%d)
INV_ITEM_MASK = máscara
INV_ITEM_PHONE_NULL = teléfono
INV_ITEM_PHONE = teléfono (%s)
INV_ITEM_PIZZA = pizza
INV_ITEM_SMASK = pañuelo
INV_ITEM_SKI_MASK = pasamontañas
INV_ITEM_SODA = soda
INV_ITEM_WATCH = reloj
INV_ITEM_WATER = agua
INV_ITEM_WHISKY = whisky
INV_ITEM_HAMBURGER = hamburguesa
INV_ITEM_HAT = gorro
INV_ITEM_BRASS_KNUCKLES = puño americano
INV_ITEM_GOLF_CLUB = palo de golf
INV_ITEM_NIGHTSTICK = porra
INV_ITEM_KNIFE = cuchillo
INV_ITEM_BASEBALL_BAT = bate
INV_ITEM_SHOVEL = pala
INV_ITEM_POOL_CUE = taco
INV_ITEM_KATANA = katana
INV_ITEM_CHAINSAW = motosierra
INV_ITEM_PURPLE_DILDO = consolador morado
INV_ITEM_DILDO = consolador
INV_ITEM_VIBRATOR = vibrador
INV_ITEM_SILVER_VIBRATOR = vibrador plateado
INV_ITEM_FLOWERS = flores
INV_ITEM_CANE = bastón
INV_ITEM_GRENADE = granada
INV_ITEM_TEAR_GAS = gas lacrimógeno
INV_ITEM_MOLOTOV_COCKTAIL = cóctel mólotov
INV_ITEM_45COLT = pistola
INV_ITEM_SILENCED_45COLT = pistola silenciada
INV_ITEM_DESERT_EAGLE = desert eagle
INV_ITEM_SHOTGUN = escopeta
INV_ITEM_SAWNOFF_SHOTGUN = escopeta recortada
INV_ITEM_COMBAT_SHOTGUN = escopeta de combate
INV_ITEM_UZI = uzi
INV_ITEM_MP5 = mp5
INV_ITEM_AK_47 = ak-47
INV_ITEM_M4 = m4
INV_ITEM_TEC_9 = tec-9
INV_ITEM_COUNTRY_RIFLE = rifle
INV_ITEM_SNIPER_RIFLE = francotirador
INV_ITEM_RPG = lanzacohetes
INV_ITEM_HS_ROCKET = lanzacohetes teledirigido
INV_ITEM_FLAMETHROWER = lanzallamas
INV_ITEM_MINIGUN = minigun
INV_ITEM_SATCHEL_CHARGE = carga explosiva
INV_ITEM_DETONATOR = detonador
INV_ITEM_SPRAYCAN = bote de spray
INV_ITEM_FIRE_EXTINGUISHER = extintor
INV_ITEM_CAMERA = cámara
INV_ITEM_PARACHUTE = paracaídas
INV_ITEM_VEHICLE_KEY = llave de %s (VEH-%05d)
INV_ITEM_VEHICLE_MASTER_KEY = llave de %s (VEH-%05d)
INV_ITEM_VEHICLE_RENT_KEY = llave de %s (VEH-%05d)
INV_ITEM_BUSINESS_KEY = llave de negocio (%d)
INV_ITEM_BUSINESS_MASTER_KEY = llave de negocio (%d)
INV_ITEM_DRIVER_LICENSE = licencia de conducir
INV_ITEM_CHARACTER_ID = identificación
INV_ITEM_GPS = GPS
INV_ITEM_GUN_LICENSE = licencia de armas
INV_ITEM_BOOMBOX = boombox

DIALOG_DELETE_ITEM_CAPTION = Eliminar objeto
DIALOG_DELETE_ITEM_BODY = ¿Estás seguro de que quieres eliminar este objeto de tu inventario?\nEsta opción es irreversible.
DIALOG_DELETE_ITEM_YES = Eliminar
DIALOG_DELETE_ITEM_NO = Cancelar

DIALOG_DELETE_ITEM_AMOUNT_CAPTION = Eliminar objeto
DIALOG_DELETE_ITEM_AMOUNT_BODY = {FFFFFF}¿Cuántos quieres eliminar?, tienes {CCFF00}%d.
DIALOG_DELETE_ITEM_AMOUNT_YES = Eliminar
DIALOG_DELETE_ITEM_AMOUNT_NO = Cancelar

DIALOG_GIVE_ITEM_AMOUNT_CAPTION = Dar objeto
DIALOG_GIVE_ITEM_AMOUNT_BODY = {FFFFFF}¿Cuántos quieres dar?, tienes {CCFF00}%d.
DIALOG_GIVE_ITEM_AMOUNT_YES = Dar
DIALOG_GIVE_ITEM_AMOUNT_NO = Cancelar

MESSAGE_ERROR_INVALID_AMOUNT = {ERROR}Cantidad no válida.

GAMETEXT_INFO_ITEM_DELETE = ~r~eliminado

DIALOG_GIVE_ITEM_CAPTION = Inventario
DIALOG_GIVE_ITEM_BODY = De: %s (%d)\nObjeto: %s\nCantidad: %d
DIALOG_GIVE_ITEM_YES = Aceptar
DIALOG_GIVE_ITEM_NO = Rechazar
MESSAGE_ERROR_GIVE_DISCONNECTED = {ERROR}El jugador se ha desconectado.
MESSAGE_ERROR_GIVE_PLAYER_AFK = {ERROR}El jugador está pausado.
MESSAGE_ERROR_SELECTED_PLAYER_GONE = {ERROR}El jugador ya no está disponible.
MESSAGE_ERROR_GIVE_ERROR_PLAYER = {ERROR}No se pudo completar la acción, es probable que no tengas espacio en tu inventario.
MESSAGE_ERROR_GIVE_ERROR = {ERROR}No se pudo completar la acción, es probable que la persona no tenga espacio en su inventario.
MESSAGE_ERROR_GIVE_ERROR_ID = {ERROR}Error, el objeto ha cambiado.
MESSAGE_INFO_GIVE_WAIT = {INFO}Espera hasta que %s acepte o rechaze el trato.
MESSAGE_INFO_GIVE_PLAYER = {INFO}%s te ha dado '%s'.
MESSAGE_INFO_GIVE = {INFO}Le has dado '%s' a %s.
MESSAGE_INFO_GIVE_REJECT = {INFO}%s ha rechazado el trato.
MESSAGE_INFO_MOVE = {INFO}Selecciona ahora la posición a donde quieres mover este objeto.

MESSAGE_ERROR_PLAYER_INV_DISABLED = {ERROR}Este jugador está haciendo un trato con otro jugador.
MESSAGE_ERROR_INV_DISABLED = {ERROR}No puedes abrir el inventario hasta que termines el trato con %s (%d).
MESSAGE_ERROR_NO_SIGNAL = {ERROR}No hay señal GPS.

MESSAGE_ERROR_NO_FUEL = {ERROR}El vehículo no tiene gasolina.
GAMETEXT_INFO_VEHICLE_OPENED = ~g~abierto
GAMETEXT_INFO_VEHICLE_CLOSED = ~r~cerrado
GAMETEXT_INFO_VEHICLE_STARTED = ~g~encendido
GAMETEXT_INFO_VEHICLE_STOPPED = ~r~apagado

MESSAGE_ERROR_NO_MONEY = {ERROR}No tienes %d$ para poder llevarte tu vehículo.
DIALOG_VEHICLE_POUND_CAPTION = Vehículo
DIALOG_VEHICLE_POUND_BODY = Tu vehículo está en el depósito municipal.\nDebes pagar %d$ para poder llevarte tu vehículo.
DIALOG_VEHICLE_POUND_YES = Pagar
DIALOG_VEHICLE_POUND_NO = Cancelar

MESSAGE_INFO_ITEM_SHOWN = {INFO}Le has mostrado tu %s a %s.
MESSAGE_INFO_ITEM_SHOW = {INFO}%s te muestra su %s.
DIALOG_SHOW_ITEM_CAPTION = Inventario
DIALOG_SHOW_ITEM_BODY = %s de %s\n%s
DIALOG_SHOW_ITEM_YES = Cerrar

GAMETEXT_INFO_DOOR_OPENED = ~g~abierta
GAMETEXT_INFO_DOOR_CLOSED = ~r~cerrada

MESSAGE_ERROR_TOYS_FULL = {ERROR}No te puedes colocar mas accesorios.
MESSAGE_ERROR_TOY_NOT_ATTACHED = {ERROR}El accesorio no está colocado.

MESSAGE_ERROR_WEAPON_MAX = {ERROR}Solo puedes llevar %d armas en mano, guarda alguna primero.

MESSAGE_ERROR_FOOD_LIMIT = {ERROR}Espera a terminar de comer para comer de nuevo.
MESSAGE_ERROR_FOOD_VOMIT = {ERROR}Ya has comido demasiado, espera un tiempo.
MESSAGE_ERROR_DRINK_LIMIT = {ERROR}Espera a terminar de beber para beber de nuevo.
MESSAGE_ERROR_DRINK = {ERROR}No tienes sed.

MESSAGE_ERROR_VINV = {ERROR}No tienes espacio en tu maletero para este objeto.

DIALOG_MOVE_ITEM_TO_VINV_CAPTION = Mover al maletero
DIALOG_MOVE_ITEM_TO_VINV_BODY = {FFFFFF}¿Cuántos quieres mover?, tienes {CCFF00}%d.
DIALOG_MOVE_ITEM_TO_VINV_YES = Mover
DIALOG_MOVE_ITEM_TO_VINV_NO = Cancelar

[vehicle_funcs]
MESSAGE_ERROR_NO_VEHICLE_ACCESS = {ERROR}No tienes las llaves de este vehículo.
MESSAGE_ERROR_PLAYER_NOT_IN_VEHICLE = {ERROR}Este jugador no está en el vehículo o no está conectado.
MESSAGE_ERROR_KICK_SYNTAX = {ERROR}La sintaxis del comando es: /echar <jugadorID/Nombre>.
MESSAGE_ERROR_POSITION = {ERROR}No estás en el lugar adecuado.

MESSAGE_ERROR_NO_DRIVING = {ERROR}No estás conduciendo ningún vehículo.
MESSAGE_ERROR_INVALID_VEHICLE_ID = {ERROR}No estás cerca o dentro de un vehículo.
MESSAGE_ERROR_NO_DOORS = {ERROR}Este vehículo no tiene cerradura.
MESSAGE_ERROR_NO_ENGINE = {ERROR}Este vehículo no tiene motor.
MESSAGE_ERROR_NO_KEY = {ERROR}No tienes las llaves de este vehículo.
MESSAGE_ERROR_NO_ACCESS = {ERROR}No tienes acceso a este vehículo.
MESSAGE_ERROR_NO_FUEL = {ERROR}El vehículo no tiene gasolina.
MESSAGE_ERROR_NO_RADIO = {ERROR}Este vehículo no tiene radio.
GAMETEXT_INFO_VEHICLE_OPENED = ~g~abierto
GAMETEXT_INFO_VEHICLE_CLOSED = ~r~cerrado
GAMETEXT_INFO_VEHICLE_STARTED = ~g~encendido
GAMETEXT_INFO_VEHICLE_STOPPED = ~r~apagado
GAMETEXT_INFO_VEHICLE_LIGHTS_ON = ~g~luces encendidas
GAMETEXT_INFO_VEHICLE_LIGHTS_OFF = ~r~luces apagadas
GAMETEXT_INFO_NO_FUEL = ~r~sin gasolina

DIALOG_VEHICLE_POUND_CAPTION = Vehículo
DIALOG_VEHICLE_POUND_BODY = Tu vehículo está en el depósito municipal.\nDebes pagar %d$ para poder llevarte tu vehículo.
DIALOG_VEHICLE_POUND_YES = Pagar
DIALOG_VEHICLE_POUND_NO = Cancelar
MESSAGE_ERROR_NO_MONEY = {ERROR}No tienes %d$ para poder llevarte tu vehículo.

[gas_station]
MESSAGE_ERROR_ENGINE_ON = {ERROR}Apaga el motor del vehículo.
MESSAGE_ERROR_MAX_FUEL = {ERROR}La gasolina está al máximo.
MESSAGE_ERROR_NO_MONEY = {ERROR}No tienes dinero suficiente.
MESSAGE_INFO_FUEL = {INFO}Espera mientras se llena la gasolina o arranca y vete.
GAMETEXT_INFO_FUELING = ~y~llenando_~p~%.0fL/%.0fL
GAMETEXT_INFO_FUELED = ~g~lleno_~p~%.0fL/%.0fL

[vc_mdlpreview]
MESSAGE_ERROR_DB_ERROR = {ERROR}No se puede cargar, problema de base de datos (vc_map).
MESSAGE_INFO_QUIT = {INFO}Vuelve a usar el mismo comando para salir de este modo.
MESSAGE_INFO_FILTER_ON = {INFO}Filtro activado, ahora se pasará a los que sean de tipo null.
MESSAGE_INFO_FILTER_OFF = {INFO}Filtro desactivado, ahora se pasará de objeto normalmente.

DIALOG_MODELID_CAPTION = Indica el modelid
DIALOG_MODELID_BODY = Introduce el modelid:
DIALOG_MODELID_YES = Ir
DIALOG_MODELID_NO = Cerrar
MESSAGE_ERROR_WRONG_MODELID_FORMAT = {ERROR}Formato de modelid no válido.
MESSAGE_ERROR_NO_MODELID_FOUND = {ERROR}No se ha encontrado el modelid en la db.

DIALOG_OBJECT_TYPE_CAPTION = Selecciona el tipo de objeto
DIALOG_OBJECT_TYPE_BODY = %s
DIALOG_OBJECT_TYPE_YES = Establecer
DIALOG_OBJECT_TYPE_NO = Cancelar

[driving_school]
TEST_1_QUESTION = ¿Por donde debe circular un vehículo?
TEST_1_VALID_ANSWER = 1
TEST_1_1_ANSWER = Por el carril derecho de la calzada
TEST_1_2_ANSWER = Por el carril izquierdo de la calzada
TEST_1_3_ANSWER = Por la acera

TEST_2_QUESTION = ¿Qué debe hacer ante un semáforo de color rojo?
TEST_2_VALID_ANSWER = 3
TEST_2_1_ANSWER = Continuar con mi viaje
TEST_2_2_ANSWER = Destruir el semáforo
TEST_2_3_ANSWER = Detenerme y continuar cuando esté verde

TEST_3_QUESTION = Si un policía le indica que se detenga, ¿qué debe hacer?
TEST_3_VALID_ANSWER = 2
TEST_3_1_ANSWER = Atropellarlo y continuar
TEST_3_2_ANSWER = Obedecer las instrucciones del agente
TEST_3_3_ANSWER = Ignorarlo y acelerar

TEST_4_QUESTION = ¿Puedes conducir bajo los efectos del alcohol?
TEST_4_VALID_ANSWER = 3
TEST_4_1_ANSWER = Sí, sin problemas
TEST_4_2_ANSWER = No, salvo que sea necesario
TEST_4_3_ANSWER = No, en ningún caso

TEST_5_QUESTION = ¿Donde debes estacionar tu vehículo?
TEST_5_VALID_ANSWER = 2
TEST_5_1_ANSWER = En la calzada
TEST_5_2_ANSWER = En un estacionamiento
TEST_5_3_ANSWER = En la acera

TEXTDRAW_CANCEL_1_MESSAGE = Tienes ~y~%d ~w~segundos para volver al vehículo antes de que se cancele la prueba.
TEXTDRAW_CANCEL_2_MESSAGE = ~r~Se ha cancelado la prueba porque has abandonado el vehículo.
TEXTDRAW_CANCEL_3_MESSAGE = ~r~Se ha cancelado la prueba porque el vehículo ha quedado destruido.
TEXTDRAW_CANCEL_4_MESSAGE = ~r~Se ha cancelado la prueba porque has superado el límite de velocidad.

TEXTDRAW_SPEED_LIMIT = Límite de velocidad actual: %s%d KM/H\n~w~Siguiente límite de velocidad: %s%d KM/H
TEXTDRAW_SPEED_LIMIT_MPH = Límite de velocidad actual: %s%d MPH\n~w~Siguiente límite de velocidad: %s%d MPH

MESSAGE_ERROR_INV_SLOT = {ERROR}No tienes espacio en tu inventario para almacenar la licencia.
MESSAGE_ERROR_HAVE_LICENSE = {ERROR}Ya tienes licencia de conducir.
MESSAGE_ERROR_NO_MONEY = {ERROR}No tienes dinero suficiente para pagar la licencia.

DIALOG_LICENSE_INFO_CAPTION = Exámen teórico
DIALOG_LICENSE_INFO_BODY_1 = Realizar el exámen tiene un coste de %d$.\n
DIALOG_LICENSE_INFO_BODY_2 = Si apruebas tendrás que realizar una prueba práctica para obtener la licencia.\n
DIALOG_LICENSE_INFO_BODY_3 = Si suspendes tendrás que volver a repetir el examen.
DIALOG_LICENSE_INFO_YES = Empezar
DIALOG_LICENSE_INFO_NO = Salir

MESSAGE_ERROR_LICENSE_TEST = {ERROR}No has superado la prueba.
GAMETEXT_INFO_LICENSE_TEST = ~g~prueba superada
GAMETEXT_INFO_LICENSE_PASSED = ~g~licencia obtenida

MESSAGE_INFO_VEHICLE_LICENSE = {INFO}Sube al vehículo para continuar con la prueba práctica

[chat]
MESSAGE_CHAT = {CHAT}%s dice: %s
MESSAGE_CHAT_DRUNK = {CHAT}%s dice (ebrio): %s
MESSAGE_CHAT_PHONE = {CHAT}%s dice (teléfono): %s

[actions]
MESSAGE_ACTION_OPEN_VEHICLE = {ACTION}* %s abre el vehículo (%s)
MESSAGE_ACTION_CLOSE_VEHICLE = {ACTION}* %s cierra el vehículo (%s)
MESSAGE_ACTION_START_VEHICLE = {ACTION}* %s arranca el vehículo (%s)
MESSAGE_ACTION_STOP_VEHICLE = {ACTION}* %s para el vehículo (%s)
MESSAGE_ACTION_INV_GIVE = {ACTION}* %s le da su %s a %s
MESSAGE_ACTION_INV_SHOW = {ACTION}* %s le muestra su %s a %s
MESSAGE_ACTION_INV_DELETE = {ACTION}* %s tira su %s
MESSAGE_ACTION_INV_DELETE_AMOUNT = {ACTION}* %s tira su %s (%d)
MESSAGE_ACTION_HOSPITAL_BED = {ACTION}* %s se tumba en la cama
MESSAGE_ACTION_ATM_WITHDRAW = {ACTION}* %s saca dinero del cajero
MESSAGE_ACTION_ATM_DEPOSIT = {ACTION}* %s ingresa dinero en el cajero
MESSAGE_ACTION_LIGHTS_VEHICLE_ON = {ACTION}* %s enciende las luces del vehículo (%s)
MESSAGE_ACTION_LIGHTS_VEHICLE_OFF = {ACTION}* %s apaga las luces del vehículo (%s)
MESSAGE_ACTION_OPEN_PDOOR = {ACTION}* %s abre la puerta de la propiedad
MESSAGE_ACTION_CLOSE_PDOOR = {ACTION}* %s cierra la puerta de la propiedad
MESSAGE_ACTION_CARRY_WEAPON = {ACTION}* %s saca un arma (%s)
MESSAGE_ACTION_UNCARRY_WEAPON = {ACTION}* %s guarda un arma (%s)
MESSAGE_ACTION_OPEN_GPS = {ACTION}* %s usa su GPS
MESSAGE_ACTION_CLOSE_GPS = {ACTION}* %s guarda su GPS
MESSAGE_ACTION_OPEN_PHONE = {ACTION}* %s usa su teléfono
MESSAGE_ACTION_CLOSE_PHONE = {ACTION}* %s guarda su teléfono
MESSAGE_ACTION_TOY_ATTACH = {ACTION}* %s se coloca un accesorio (%s)
MESSAGE_ACTION_TOY_REMOVE = {ACTION}* %s se quita un accesorio (%s)
MESSAGE_ACTION_EAT = {ACTION}* %s come (%s)
MESSAGE_ACTION_DRINK = {ACTION}* %s bebe (%s)
MESSAGE_ACTION_CLOTHES_CHANGE = {ACTION}* %s se cambia de ropa
MESSAGE_ACTION_CLOTHES_DELETE = {ACTION}* %s tira ropa
MESSAGE_ACTION_GPS_TAXI_SHOW = {ACTION}* %s le muestra el GPS al taxista %s
MESSAGE_ACTION_WATCH = {ACTION}* %s consulta la hora en su reloj
MESSAGE_ACTION_ACTION = {ACTION}* %s %s
MESSAGE_ACTION_DO = {ADFF2F}* %s (( %s ))
MESSAGE_ACTION_BCHANNEL = {FFFFFF}%s (%d): (( %s ))
MESSAGE_ERROR_SYNTAX = {ERROR}La sintaxis no es válida.

[menu]
TEXTDRAW_PLAY = jugar
TEXTDRAW_INFO = info
TEXTDRAW_SETTINGS = ajustes
TEXTDRAW_QUIT = salir

DIALOG_SETTINGS_KM = kilómetros
DIALOG_SETTINGS_MILES = millas

DIALOG_SETTINGS_CAPTION = Ajustes
DIALOG_SETTINGS_BODY_1 = Idioma\t%s\n
DIALOG_SETTINGS_BODY_2 = Resolución de pantalla\t%d/%d\n
DIALOG_SETTINGS_BODY_3 = Cambiar personaje (skin)\n
DIALOG_SETTINGS_BODY_4 = Canal de dudas\t%d\n
DIALOG_SETTINGS_BODY_5 = Mensajes administrativos\t%d\n
DIALOG_SETTINGS_BODY_6 = Unidad de medida\t%s\n
DIALOG_SETTINGS_YES = Ajustar
DIALOG_SETTINGS_NO = Atrás

DIALOG_LANG_CAPTION = Selecciona tu idioma
DIALOG_LANG_BODY = %s
DIALOG_LANG_YES = Continuar
DIALOG_LANG_NO = Salir
GAMETEXT_INFO_LANG_CHANGED = ~g~idioma cambiado

DIALOG_AR_CAPTION = Resolución de pantalla
DIALOG_AR_BODY = Introduce tu resolución de pantalla en GTA:SA para\ncalcular tu relación de aspecto.\nPor ejemplo: 1920, 1080
DIALOG_AR_YES = Ajustar
DIALOG_AR_NO = Atrás
MESSAGE_ERROR_WRONG_FORMAT = {ERROR}Formato no válido.
GAMETEXT_INFO_AR_RESTART = reinica el juego para que los cambios surtan efecto

DIALOG_INFO_CAPTION = Información
DIALOG_INFO_BODY = Ver introducción\nAyuda
DIALOG_INFO_YES = Continuar
DIALOG_INFO_NO = Salir

[rent_vehicles]
MESSAGE_ERROR_INV_SLOT = {ERROR}No tienes espacio en tu inventario para las llaves del vehículo.
MESSAGE_ERROR_NO_LICENSE = {ERROR}Necesitas la licencia de conducir para alquilar un vehículo.
MESSAGE_ERROR_VEHICLE_RENTED = {ERROR}Ya tienes un vehículo en renta, deshazte de las llaves en tu inventario.
MESSAGE_ERROR_NO_MONEY = {ERROR}Necesitas %d$ para poder alquilar este vehículo.
MESSAGE_ERROR_NO_LEVEL = {ERROR}Necesitas ser nivel %d para poder alquilar este vehículo.

DIALOG_RENT_VEHICLE_CAPTION = Rentar vehículo
DIALOG_RENT_VEHICLE_BODY_1 = Vehículo que vas a rentar: %s\nPrecio: %d$\n\n
DIALOG_RENT_VEHICLE_BODY_2 = Podrás usar este vehículo hasta que lo abandones\npor demasiado tiempo o elimines las llaves.
DIALOG_RENT_VEHICLE_YES = Rentar
DIALOG_RENT_VEHICLE_NO = Cancelar
GAMETEXT_INFO_VEHICLE_RENTED = ~g~vehiculo alquilado

[shared_commands]
MESSAGE_ERROR_POSITION = {ERROR}No estás en el lugar adecuado.
MESSAGE_ERROR_NO_PKEYS = {ERROR}No tienes las llaves de esta propiedad.
MESSAGE_ERROR_NO_PSELL = {ERROR}Esta propiedad no está en venta.
GAMETEXT_INFO_PROPERTY_PURCHASED = ~g~propiedad comprada
GAMETEXT_INFO_DOOR_OPENED = ~g~abierta
GAMETEXT_INFO_DOOR_CLOSED = ~r~cerrada
MESSAGE_ERROR_P_INV_SLOT = {ERROR}No tienes espacio en tu inventario para las llaves de la propiedad.
MESSAGE_ERROR_P_NO_MONEY = {ERROR}No tienes dinero suficiente para poder comprar la propiedad.
MESSAGE_ERROR_P_NO_LEVEL = {ERROR}Necesitas ser nivel %d para poder comprar esta propiedad.
MESSAGE_ERROR_MAX_PROP = {ERROR}No puedes tener más propiedades, el límite es de %d propiedades por jugador.
MESSAGE_ERROR_PROPERTY_RENTED = {ERROR}Ya tienes una propiedad en renta, deshazte de las llaves en tu inventario.
MESSAGE_ERROR_PROPERTY_RENTED_DAYS = {ERROR}La propiedad ya está alquilada por el máximo de días posibles.

MESSAGE_ERROR_NO_BSELL = {ERROR}Este negocio no está en venta.
MESSAGE_ERROR_B_INV_SLOT = {ERROR}No tienes espacio en tu inventario para las llaves del negocio.
MESSAGE_ERROR_B_NO_MONEY = {ERROR}No tienes dinero suficiente para poder comprar el negocio.
MESSAGE_ERROR_B_NO_LEVEL = {ERROR}Necesitas ser nivel %d para poder comprar este negocio.
MESSAGE_ERROR_MAX_BIZZ = {ERROR}No puedes tener más negocios, el límite es de %d negocios por jugador.
GAMETEXT_INFO_BUSINESS_PURCHASED = ~g~negocio comprado
MESSAGE_ERROR_NO_BKEYS = {ERROR}No tienes las llaves de este negocio.

DIALOG_RENT_PROPERTY_CAPTION = Alquilar esta propiedad
DIALOG_RENT_PROPERTY_BODY = Precio por día: %d$\n¿Durante cuántos días quieres alquilar la propiedad?\n\nMínimo: %d día(s), máximo: %d día(s)
DIALOG_RENT_PROPERTY_YES = Alquilar
DIALOG_RENT_PROPERTY_NO = Cancelar
MESSAGE_ERROR_PRENT_DAYS = {ERROR}Cantidad de días no válida.
MESSAGE_ERROR_FORMAT = {ERROR}Formato no válido.
MESSAGE_ERROR_PRENT_NO_MONEY = {ERROR}Necesitas %d$ para alquilar esta propiedad por %d día(s).
GAMETEXT_INFO_PROPERTY_RENTED = ~g~propiedad alquilada

DIALOG_RENT_ADD_PROPERTY_CAPTION = Renovar alquiler
DIALOG_RENT_ADD_PROPERTY_BODY = El alquiler expira en %d día(s)\nPrecio por día: %d$\n¿Cuántos días quieres ampliar el alquiler?\n\nMínimo: %d día(s), máximo: %d día(s)
DIALOG_RENT_ADD_PROPERTY_YES = Ampliar
DIALOG_RENT_ADD_PROPERTY_NO = Cancelar
GAMETEXT_INFO_PROPERTY_RENT_ADD = ~g~alquiler ampliado

MESSAGE_ERROR_COMMAND = {ERROR}Ahora no puedes usar este comando.
MESSAGE_ERROR_RESPOND_CSYNTAX = {ERROR}El uso del comando es /responder [ID].
MESSAGE_ERROR_PDISCONNECTED = {ERROR}El jugador no está conectado.

MESSAGE_ERROR_NO_TAXI_REQUEST = {ERROR}Este jugador no ha solicitado un taxi o esta solicitud ya ha sido respondida.
MESSAGE_WARNING_TAXI_RESPONSE = {WARNING}El taxista %s ha respondido a tu llamada y ya está en camino.
MESSAGE_INFO_TAXI_RESPONSE = {INFO}Has avisado al cliente que vas a buscarlo.
MESSAGE_ERROR_ALREADY_TAXI_JOB = {ERROR}Estás transportando a un viajero en este momento.

[gps]
GPS_OPTION_MINIMAP = Minimapa
GPS_OPTION_LOCATION = Ubicación
GPS_OPTION_ROUTE = Ruta GPS
GPS_OPTION_CANCEL_ROUTE = Cancelar ruta
GPS_OPTION_CATEGORY_OBJECTIVES = Objetivos
GPS_OPTION_CATEGORY_PROPERTIES = Mis propiedades
GPS_OPTION_CATEGORY_BUSINESS = Mis negocios
GPS_OPTION_CATEGORY_VEHICLES = Mis vehículos

GPS_CAT_HOSPITAL = Hospitales
GPS_CAT_BANK = Bancos
GPS_CAT_POLICE = Comisarías
GPS_CAT_MECHANIC = Talleres
GPS_CAT_DRIVING_SCHOOL = Autoescuelas
GPS_CAT_JOBS = Trabajos
GPS_CAT_REAL_ESTATES = Inmobiliarias
GPS_CAT_BUSINESS = Negocios

MESSAGE_ERROR_NO_GPS = {ERROR}No tienes GPS.
MESSAGE_ERROR_NO_ROUTE = {ERROR}No hay ninguna ruta.
MESSAGE_INFO_ROUTE_CANCELED = {INFO}Ruta cancelada.
MESSAGE_ERROR_DS_ROUTE = {ERROR}No puedes cancelar esta ruta.
MESSAGE_ERROR_ROUTE_EXISTS = {ERROR}Para crear una nueva ruta cancela la actual.
MESSAGE_ERROR_NO_SIGNAL = {ERROR}No hay señal GPS.

DIALOG_CREATE_ROUTE_CAPTION = Crear una ruta
DIALOG_CREATE_ROUTE_BODY = ¿Quieres crear una ruta hasta este lugar?
DIALOG_CREATE_ROUTE_YES = Ruta
DIALOG_CREATE_ROUTE_NO = Cerrar

MESSAGE_INFO_ROUTE = {INFO}Ruta calculada.
MESSAGE_ERROR_ROUTE = {ERROR}No se puede calcular la ruta.
GAMETEXT_INFO_ROUTE_FINISH = ~g~destino alcanzado

[phone]
PHONE_NUMBER_TAXI = taxi
PHONE_1_OPTION = Encender
PHONE_2_OPTION = Agenda
PHONE_3_OPTION = Llamar
PHONE_4_OPTION = Servicios
PHONE_5_OPTION = Apagar
PHONE_6_OPTION = Seleccionar
PHONE_7_OPTION = Bloquear
PHONE_8_OPTION = Atrás
PHONE_9_OPTION = Eliminar
PHONE_10_OPTION = Añadir
PHONE_11_OPTION = Confirmar
PHONE_12_OPTION = Marcando...
PHONE_13_OPTION = Colgar (%s)
PHONE_14_OPTION = Cntstar (%s)
PHONE_15_OPTION = Fin (%d:%02d)
PHONE_16_OPTION = Colgar
PHONE_17_OPTION = Entrante...
PHONE_18_OPTION = + Añadir
PHONE_19_OPTION = Nombre\n%s
PHONE_20_OPTION = Número\n_
PHONE_21_OPTION = Número\n%d

MESSAGE_ERROR_NO_PHONE = {ERROR}No tienes teléfono.
MESSAGE_ERROR_NUMBER_NO_EXISTS = {ERROR}El teléfono %s no existe.
MESSAGE_ERROR_NUMBER_OCCUPIED = {ERROR}El teléfono %s está ocupado o fuera de cobertura.
MESSAGE_PHONE_CHAT = {PHONE}[Teléfono] %s: %s
MESSAGE_INFO_CONTACT_DELETED = {INFO}Contacto eliminado.
MESSAGE_ERROR_PB_FULL = {ERROR}Tu agenda está llena.
MESSAGE_INFO_CONTACT_ADDED = {INFO}Contacto añadido.
MESSAGE_ERROR_PB_ADD = {ERROR}Introduce un nombre y un número para añadir un contacto.
MESSAGE_ERROR_CALL_SYNTAX = {ERROR}La sintaxis del comando es /llamar [número].
MESSAGE_ERROR_NO_SIGNAL = {ERROR}No hay señal.

DIALOG_PB_CONTACT_CAPTION = Nombre del contacto
DIALOG_PB_CONTACT_BODY = Introduce el nombre del contacto\nDebe contener como máximo %d caracteres alfanuméricos
DIALOG_PB_CONTACT_YES = Confirmar
DIALOG_PB_CONTACT_NO = Cerrar
MESSAGE_ERROR_PB_NAME_FORMAT = {ERROR}El formato no es válido.

[toys]
TEXTDRAW_TOYS_TITLE = Accesorios
TOY_1_BONE = espalda
TOY_2_BONE = cabeza
TOY_3_BONE = brazo izquierdo
TOY_4_BONE = brazo derecho
TOY_5_BONE = mano izquierda
TOY_6_BONE = mano derecha
TOY_7_BONE = muslo izquierdo
TOY_8_BONE = muslo derecho
TOY_9_BONE = pie izquierdo
TOY_10_BONE= pie derecho
TOY_11_BONE = pantorrilla derecha
TOY_12_BONE = pantorrilla izquierda
TOY_13_BONE = antebrazo izquierdo
TOY_14_BONE = antebrazo derecho
TOY_15_BONE = hombro izquierdo
TOY_16_BONE = hombro derecho
TOY_17_BONE = cuello
TOY_18_BONE = boca

DIALOG_CONFIG_TOY_CAPTION = Configurar accesorio
DIALOG_CONFIG_TOY_BODY = Actualmente este accesorio está colocado en: %s\n¿Quieres cambiar la parte del cuerpo en la que se colocará el objeto?
DIALOG_CONFIG_TOY_YES = Sí
DIALOG_CONFIG_TOY_NO = No

MESSAGE_ERROR_TOY_TOO_BIG = {ERROR}El accesorio es demasiado grande.

DIALOG_TOYS_CAPTION = Accesorios
DIALOG_TOYS_BODY = {FFCCFF}|--- Colocados ---|\n%s|--- Guardados ---|\n%s
DIALOG_TOYS_YES = Opciones
DIALOG_TOYS_NO = Salir

DIALOG_TOY_ATTACHED_CAPTION = Accesorio
DIALOG_TOY_ATTACHED_BODY = Guardar\nConfigurar\nEliminar
DIALOG_TOY_ATTACHED_YES = Continuar
DIALOG_TOY_ATTACHED_NO = Salir

DIALOG_TOY_CAPTION = Accesorio
DIALOG_TOY_BODY = Colocar\nEliminar
DIALOG_TOY_YES = Continuar
DIALOG_TOY_NO = Salir

MESSAGE_ERROR_NO_WATCH = {ERROR}No tienes un reloj.

[weapons]
DIALOG_WEAPONS_CAPTION = Armas
DIALOG_WEAPONS_BODY = Arma\tMunición\n{FFCCFF}|--- En mano ---|\n%s|--- Guardadas ---|\n%s
DIALOG_WEAPONS_YES = Opciones
DIALOG_WEAPONS_NO = Salir

DIALOG_WEAPON_CARRIED_CAPTION = Arma
DIALOG_WEAPON_CARRIED_BODY = Guardar\nEliminar
DIALOG_WEAPON_CARRIED_YES = Continuar
DIALOG_WEAPON_CARRIED_NO = Salir

DIALOG_WEAPON_CAPTION = Arma
DIALOG_WEAPON_BODY = Sacar\nEliminar
DIALOG_WEAPON_YES = Continuar
DIALOG_WEAPON_NO = Salir

MESSAGE_ERROR_WEAPON_MAX = {ERROR}Solo puedes llevar %d armas en mano, guarda alguna primero.

[business]
DIALOG_DUPLICATE_KEYS_CAPTION = Duplicado de llaves
DIALOG_AMMO_CAPTION = Munición para tus armas

BUSINESS_TYPE_GENERAL_STORE = tienda general
BUSINESS_TYPE_AMMUNATION = armería
BUSINESS_TYPE_CLOTHING_STORE = tienda de ropa
BUSINESS_TYPE_RESTAURANT = restaurante
BUSINESS_TYPE_BURGER = hamburguesería
BUSINESS_TYPE_PIZZA = pizzería
BUSINESS_TYPE_DISCO = discoteca
BUSINESS_TYPE_BAR = bar
BUSINESS_TYPE_ELECTRONICS = tienda de electrónica
BUSINESS_TYPE_HARDWARE_STORE = ferretería

BUSINESS_SALE_TYPE_FOOD = comida
BUSINESS_SALE_TYPE_DRINK = bebida
BUSINESS_SALE_TYPE_CLOTHES = ropa
BUSINESS_SALE_TYPE_TOYS = accesorios
BUSINESS_SALE_TYPE_ELECTRONICS = electrónica
BUSINESS_SALE_TYPE_BAR = bar
BUSINESS_SALE_TYPE_WEAPONS = armas
BUSINESS_SALE_TYPE_AMMO = munición
BUSINESS_SALE_TYPE_ALL = comprar productos
BUSINESS_SALE_TYPE_HARDWARE = ferretería
BUSINESS_SALE_TYPE_CIGARETTES = cigarrillos

BUSINESS_PRODUCT_WINE = vino
BUSINESS_PRODUCT_SPRUNK = sprunk
BUSINESS_PRODUCT_DUPLICATE_KEYS = duplicado de llaves
BUSINESS_PRODUCT_NORMAL_AMMO = munición normal

DIALOG_BUSINESS_CATALOG_CAPTION = Productos
DIALOG_BUSINESS_CATALOG_HEADER = Producto\tPrecio\tStock\tNivel\n
DIALOG_BUSINESS_CATALOG_NO_STOCK = Sin stock
DIALOG_BUSINESS_CATALOG_NEXT_PAGE = \t{FFFFFF}Página siguiente

TEXTDRAW_BCATALOG_TITLE = ~y~PRODUCTOS
TEXTDRAW_BCATALOG_ID_DOWN = ~d~ ID
TEXTDRAW_BCATALOG_ID_UP = ~u~ ID
TEXTDRAW_BCATALOG_PRODUCT = Producto
TEXTDRAW_BCATALOG_PRICE_DOWN = ~d~ Precio
TEXTDRAW_BCATALOG_PRICE_UP = ~u~ Precio
TEXTDRAW_BCATALOG_STOCK_DOWN = ~d~ Stock
TEXTDRAW_BCATALOG_STOCK_UP = ~u~ Stock
TEXTDRAW_BCATALOG_SALES_DOWN = ~d~ Ventas
TEXTDRAW_BCATALOG_SALES_UP = ~u~ Ventas
TEXTDRAW_BCATALOG_ADD_PRODUCT = + Añadir producto

MESSAGE_ERROR_NO_PRODUCTS = {ERROR}No se venden productos.
MESSAGE_ERROR_NO_STOCK = {ERROR}No hay unidades disponibles de este producto.
MESSAGE_ERROR_LEVEL = {ERROR}Necesitas ser nivel %d para comprar este producto.
MESSAGE_ERROR_NO_MONEY = {ERROR}No tienes suficiente dinero para comprar este producto.
GAMETEXT_INFO_PRODUCT_BOUGHT = ~g~producto comprado
MESSAGE_ERROR_INV = {ERROR}No tienes espacio en tu inventario para el producto o ya tienes este producto.
MESSAGE_ERROR_CLOTHES = {ERROR}No hay más ropas disponibles para ti.
MESSAGE_ERROR_TOYS = {ERROR}No hay más accesorios disponibles para ti.
MESSAGE_ERROR_CLOTHES_ADD = {ERROR}No puedes tener más ropas.
MESSAGE_ERROR_TOY_ADD = {ERROR}No puedes tener más accesorios.
MESSAGE_ERROR_NO_MASTER_KEYS = {ERROR}No tienes ninguna llave (solo se pueden duplicar las llaves maestras).
MESSAGE_ERROR_LOCATION = {ERROR}No estás en tu negocio.
MESSAGE_ERROR_GUN_LICENSE = {ERROR}Necesitas tener licencia de armas para comprar productos de este tipo.
MESSAGE_ERROR_NO_WEAPONS = {ERROR}No tienes ninguna arma que necesite munición.

DIALOG_BUSINESS_CAPTION = Negocio
DIALOG_BUSINESS_BODY = Cambiar horario\nCaja fuerte\nRadio\nProductos
DIALOG_BUSINESS_YES = Continuar
DIALOG_BUSINESS_NO = Cerrar

DIALOG_BUSINESS_SCHEDULE_CAPTION = Horario
DIALOG_BUSINESS_SCHEDULE_BODY_1 = Horario actual: %02d:00 - %02d:00\n\n
DIALOG_BUSINESS_SCHEDULE_BODY_2 = Introduce la hora de apertura y la hora de cierre separada por un espacio\nPor ejemplo: 8 22
DIALOG_BUSINESS_SCHEDULE_YES = Cambiar
DIALOG_BUSINESS_SCHEDULE_NO = Atrás
MESSAGE_ERROR_INVALID_FORMAT = {ERROR}Formato no válido.

DIALOG_BUSINESS_MONEY_CAPTION = Caja fuerte
DIALOG_BUSINESS_MONEY_BODY = Depositar\nRetirar
DIALOG_BUSINESS_MONEY_YES = Continuar
DIALOG_BUSINESS_MONEY_NO = Atrás

DIALOG_BUSINESS_DEPOSIT_CAPTION = Caja fuerte (depositar)
DIALOG_BUSINESS_DEPOSIT_BODY = Dinero en la caja fuerte: %d$\nIntroduce la cantidad de dinero a depositar
DIALOG_BUSINESS_DEPOSIT_YES = Depositar
DIALOG_BUSINESS_DEPOSIT_NO = Cerrar
MESSAGE_ERROR_DEPOSIT_NO_MONEY = No tienes dinero suficiente.

DIALOG_BUSINESS_WITHDRAW_CAPTION = Caja fuerte (retirar)
DIALOG_BUSINESS_WITHDRAW_BODY = Dinero en la caja fuerte: %d$\nIntroduce la cantidad de dinero a retirar
DIALOG_BUSINESS_WITHDRAW_YES = Retirar
DIALOG_BUSINESS_WITHDRAW_NO = Cerrar
MESSAGE_ERROR_WITHDRAW_NO_MONEY = No hay esa cantidad de dinero en la caja fuerte.

GAMETEXT_INFO_CHANGES_SAVED = ~g~cambios aplicados

MESSAGE_ERROR_ADD_NO_PRODUCTS = {ERROR}No hay más productos disponibles para tu negocio.
DIALOG_BUSINESS_EPRODUCT_CAPTION = Modificar producto
DIALOG_BUSINESS_EPRODUCT_BODY = Precio de venta\nAñadir stock\nEliminar producto
DIALOG_BUSINESS_EPRODUCT_YES = Continuar
DIALOG_BUSINESS_EPRODUCT_NO = Cerrar

DIALOG_BP_EDIT_PRICE_CAPTION = Precio
DIALOG_BP_EDIT_PRICE_BODY = Precio de venta al público actual: %d$\nCoste del producto: %d$\n\nIntroduce el nuevo precio de venta al público:
DIALOG_BP_EDIT_PRICE_YES = Cambiar
DIALOG_BP_EDIT_PRICE_NO = Atrás
MESSAGE_ERROR_BP_EDIT_PRICE = {ERROR}El precio no es válido, introduce un precio acorde con la realidad.

DIALOG_BP_DELETE_CAPTION = Eliminar producto
DIALOG_BP_DELETE_BODY = ¿Estás seguro de que quieres eliminar este producto de tu negocio?\nEsta opción es irreversible y no recuperarás el coste de los productos.
DIALOG_BP_DELETE_YES = Eliminar
DIALOG_BP_DELETE_NO = Atrás

DIALOG_BP_ADD_STOCK_CAPTION = Añadir stock
DIALOG_BP_ADD_STOCK_BODY = Coste del producto: %d$\nIntroduce la cantidad de stock a añadir:
DIALOG_BP_ADD_STOCK_YES = Continuar
DIALOG_BP_ADD_STOCK_NO = Atrás
MESSAGE_ERROR_BP_STOCK = {ERROR}La cantidad de stock introducida no es válida.

DIALOG_BPASTOCK_CONFIRM_CAPTION = Confirmar
DIALOG_BPASTOCK_CONFIRM_BODY = Cantidad: %d\nCoste total: %d$\n\nDinero en caja fuerte: %d$
DIALOG_BPASTOCK_CONFIRM_YES = Confirmar
DIALOG_BPASTOCK_CONFIRM_NO = Cerrar
MESSAGE_ERROR_ASTOCK_NO_MONEY = {ERROR}No hay suficiente dinero en la caja fuerte de tu negocio.

DIALOG_BIZZ_BUY_AMOUNT_CAPTION = Comprar producto
DIALOG_BIZZ_BUY_AMOUNT_BODY = {FFFFFF}¿Cuántos quieres comprar?\n{FFFFFF}Puedes comprar hasta {CCFF00}%d {FFFFFF}productos.
DIALOG_BIZZ_BUY_AMOUNT_YES = Comprar
DIALOG_BIZZ_BUY_AMOUNT_NO = Cerrar
MESSAGE_ERROR_INVALID_AMOUNT = Cantidad no válida.
MESSAGE_ERROR_NO_MONEY_AMOUNT = Necesitas %d$.

[clothing]
TEXTDRAW_CHARACTER_MENU_TITLE = Personaje
TEXTDRAW_CLOTHES_MENU_TITLE = Ropas

MESSAGE_ERROR_CHAR_TIME = {ERROR}Fecha en la que podrás cambiar tu personaje: %s (%d días restantes)
DIALOG_CHAR_INFO_CAPTION = Información
DIALOG_CHAR_INFO_BODY_1 = {INFO}Solo puedes cambiar tu personaje cada {67bf4a}%d días.\n{INFO}El coste del cambio es de {67bf4a}%d$ del juego.\n\n
DIALOG_CHAR_INFO_BODY_2 = {INFO}Al cambiar tu personaje perderás todas las ropas y la configuración de los accesorios.
DIALOG_CHAR_INFO_YES = Aceptar
DIALOG_CHAR_INFO_NO = Atrás
MESSAGE_ERROR_NO_MONEY = {ERROR}Necesitas %d$ para cambiar tu personaje.
GAMETEXT_INFO_CHAR_CHANGED = ~g~personaje cambiado
MESSAGE_ERROR_SAME_CLOTHE = {ERROR}Ya estás vistiendo esa ropa.
GAMETEXT_INFO_CLOTHES_CHANGED = ~g~ropa cambiada
GAMETEXT_INFO_CLOTHES_DELETED = ~r~ropa eliminada
DIALOG_CLOTHES_CAPTION = Ropa
DIALOG_CLOTHES_BODY = Vestirse\nTirar
DIALOG_CLOTHES_YES = Continuar
DIALOG_CLOTHES_NO = Cerrar
MESSAGE_ERROR_DEFAULT_CLOTHES = {ERROR}No puedes tirar esta ropa porque es la ropa por defecto de tu personaje.

[jobs]
JOB_TAXI = taxista
JOB_TRUCKER = camionero
JOB_GUNSMITH = ensamblador

TEXTDRAW_JOB_LEVEL_UP = Felicidades, tu nivel de %s ahora es %s.

DIALOG_HEADER = Trabajo\tNivel\tExperiencia\tTrabajos realizados\n
DIALOG_CAPTION = Trabajos

MESSAGE_ERROR_ALREADY_IN_JOB = {ERROR}Primero tienes que dejar tu trabajo actual (%s).
MESSAGE_INFO_JOB_STARTED = {INFO}¡Felicidades! Has firmado un contrato temporal, vuelve aquí para dejar el trabajo.
GAMETEXT_INFO_JOB_STARTED = ~g~Trabajo obtenido
GAMETEXT_INFO_JOB_FINISHED = ~g~Trabajo finalizado
MESSAGE_ERROR_LEVEL = {ERROR}Necesitas ser nivel %d para obtener este trabajo.
MESSAGE_ERROR_JOB_LEVEL = {ERROR}Necesitas ser nivel %d en el trabajo.
MESSAGE_ERROR_DRIVER_LICENSE = {ERROR}Necesitas la licencia de conducir para este trabajo.

[taxi]
TEXTDRAW_TAXIMETER = ~y~Taxímetro:_~w~%d$

GAMETEXT_INFO_TAXI_REQUESTED = ~g~taxi solicitado
GAMETEXT_INFO_TAXI_CANCELLED = ~r~taxi cancelado
MESSAGE_WARNING_TAXI_CUSTOMER = {WARNING}[Central] {FFFFFF}Hay un nuevo cliente solicitando un taxi en %s (%.2f KM). Utiliza {WARNING}/responder %d {FFFFFF}para atenderlo.
MESSAGE_WARNING_TAXI_CUSTOMER_MPH = {WARNING}[Central] {FFFFFF}Hay un nuevo cliente solicitando un taxi en %s (%.2f millas). Utiliza {WARNING}/responder %d {FFFFFF}para atenderlo.
MESSAGE_ERROR_TAXI_REQUEST = {ERROR}No puedes solicitar un taxi en este momento.
MESSAGE_ERROR_NO_MONEY = {ERROR}No tienes dinero para pagar el taxi.

[trucker]
TEXTDRAW_1_CANCEL = Tienes ~y~%d segundos ~w~para recuperar el remolque antes de que se cancele el trabajo.
TEXTDRAW_2_CANCEL = Tienes ~y~%d segundos ~w~para volver al camión antes de que se cancele el trabajo.

TEXTDRAW_1_AUX = Estado: ~y~cargando (%ds)
TEXTDRAW_2_AUX = Estado: ~y~descargando (%ds)
TEXTDRAW_3_AUX = Estado de la carga: ~g~bueno
TEXTDRAW_4_AUX = Estado de la carga: ~y~regular
TEXTDRAW_5_AUX = Estado de la carga: ~r~malo

MESSAGE_WARNING_LOAD_TRUCK = {WARNING}El camión no está cargado, ve hasta el punto de carga.
MESSAGE_INFO_TRUCK_LOADED = {INFO}El camión ha sido cargado, entrega la carga en las mejores condiciones para cobrar lo máximo posible.
MESSAGE_ERROR_TRUCK_CANCELED = {ERROR}El trabajo se ha cancelado porque has abandonado el camión.
MESSAGE_WARNING_TRUCK_COMPLETE = {WARNING}La entrega se ha completado, puedes volver al punto de carga para seguir trabajando.
MESSAGE_WARNING_NEED_TRAILER = {WARNING}Necesitas un remolque para poder cargar el camión.
GAMETEXT_INFO_TRAILER_ATTACHED = ~g~remolcado
MESSAGE_WARNING_TRUCK_POSITION = {WARNING}Coloca el camión correctamente para (des)cargarlo.

[interest_points]
DIALOG_INTEREST_POINT_CAPTION = Lugares de interés
DIALOG_INTEREST_POINT_BODY = Autoescuela\nTienda general\nTienda de electrónica\nCamioneros\nTaxista
DIALOG_INTEREST_POINT_YES = Continuar
DIALOG_INTEREST_POINT_NO = Cerrar
MESSAGE_INFO_INTEREST_POINT = {INFO}Se ha marcado en el mapa la posición de este lugar.

[gunsmith]
TEXTDRAW_KEY = ~w~Pulsa ~y~%s ~w~repetidamente

MESSAGE_ERROR_NO_JOB = {ERROR}No eres ensamblador.
MESSAGE_ERROR_GSPOINT_IN_USE = {ERROR}Esta mesa de trabajo está en uso.
MESSAGE_ERROR_NO_PIECES = {ERROR}No tienes piezas para comenzar a ensamblar.
MESSAGE_ERROR_PIECES = {ERROR}Ya tienes suficientes piezas para ensamblar.
MESSAGE_INFO_PIECES = {INFO}Ahora tienes las piezas necesarias, ve hasta una mesa de trabajo para empezar a ensamblar.
MESSAGE_INFO_PIECE_PLACE = {INFO}Coloca la mercancía en la mesa de detrás.

[gun_license]
TEST_1_QUESTION = ¿Qué tipo de armas me permite llevar la licencia?
TEST_1_VALID_ANSWER = 2
TEST_1_1_ANSWER = Todo tipo de armas
TEST_1_2_ANSWER = Solo las armas reglamentarias vendidas en locales autorizados
TEST_1_3_ANSWER = Lanzacohetes y bombas

TEST_2_QUESTION = ¿Se pueden llevar armas en lugares públicos?
TEST_2_VALID_ANSWER = 1
TEST_2_1_ANSWER = No, está prohibido
TEST_2_2_ANSWER = Naturalmente
TEST_2_3_ANSWER = Sí, cuando sea necesario

TEST_3_QUESTION = ¿En qué caso puedo utilizar el arma?
TEST_3_VALID_ANSWER = 3
TEST_3_1_ANSWER = Cuando quiera
TEST_3_2_ANSWER = Cuando sea necesario
TEST_3_3_ANSWER = Solo para advertir en defensa propia

MESSAGE_ERROR_INV_SLOT = {ERROR}No tienes espacio en tu inventario.
MESSAGE_ERROR_ALREADY_LICENSE = {ERROR}Ya tienes licencia de armas.
MESSAGE_ERROR_NO_MONEY = {ERROR}No tienes suficiente dinero.

DIALOG_LICENSE_INFO_CAPTION = Exámen teórico
DIALOG_LICENSE_INFO_BODY_1 = Realizar el exámen tiene un coste de %d$.\n
DIALOG_LICENSE_INFO_BODY_2 = Si apruebas tendrás que realizar obtendrás la licencia.\n
DIALOG_LICENSE_INFO_BODY_3 = Si suspendes tendrás que volver a repetir el examen y perderás el dinero.
DIALOG_LICENSE_INFO_YES = Empezar
DIALOG_LICENSE_INFO_NO = Salir

MESSAGE_ERROR_LICENSE_TEST = {ERROR}No has superado la prueba.
GAMETEXT_INFO_LICENSE_PASSED = ~g~licencia obtenida

[real_estate]
DIALOG_CAPTION = Inmobiliaria
DIALOG_HEADER = Propiedad\tPrecio de venta\n

TYPE_PROPERTY = Propiedad
TYPE_BUSINESS = Negocio

MESSAGE_ERROR_NO_PROPERTIES = {ERROR}No tienes ninguna propiedad o negocio para vender.
GAMETEXT_INFO_PROPERTY_SOLD = ~g~propiedad vendida
GAMETEXT_INFO_BUSINESS_SOLD = ~g~negocio vendido

[intro]
INTRO_0_AUDIO = 10000 https://www.dropbox.com/s/oknzv9jlx596xds/welcome.mp3?dl=1
INTRO_1_AUDIO = 14000 https://www.dropbox.com/s/0g27owbt1iiq3rn/screen.mp3?dl=1
INTRO_2_AUDIO = 17000 https://www.dropbox.com/s/cmqnpbwrenp6nb6/clothes.mp3?dl=1
INTRO_3_AUDIO = 10000 https://www.dropbox.com/s/9n8iy5mfwggkzes/driving_school.mp3?dl=1
INTRO_4_AUDIO = 17000 https://www.dropbox.com/s/pwhwzeu6o7lisyp/vehicles.mp3?dl=1
INTRO_5_AUDIO = 16000 https://www.dropbox.com/s/jef63btdruaq8cc/properties.mp3?dl=1
INTRO_6_AUDIO = 26000 https://www.dropbox.com/s/l4nuvqbxlclj0qt/business.mp3?dl=1
INTRO_7_AUDIO = 10000 https://www.dropbox.com/s/e40gqq9nccw4ffl/keys.mp3?dl=1
INTRO_8_AUDIO = 15000 https://www.dropbox.com/s/b58izl5s3lhflch/jobs.mp3?dl=1
INTRO_9_AUDIO = 17000 https://www.dropbox.com/s/5m0esz0hfiuf397/end.mp3?dl=1
INTRO_10_AUDIO = 60000 https://www.dropbox.com/s/i0d8hrvntthn61p/vctheme.mp3?dl=1

TEXTDRAW_EXIT = Presiona ~y~%s ~w~para salir
TEXT_CODING = Programación
TEXT_OTHERS = Otros

DIALOG_INTRO_INFO_CAPTION = Introducción
DIALOG_INTRO_INFO_BODY = ¿Quieres ver una pequeña introducción?\nTe servirá para orientarte.
DIALOG_INTRO_INFO_YES = Sí
DIALOG_INTRO_INFO_NO = No

[help]
DIALOG_HELP_CAPTION = Ayuda
DIALOG_HELP_BODY = General\nPersonaje\nPropiedades\nVehículos\nNegocios\nTrabajos
DIALOG_HELP_YES = >>
DIALOG_HELP_NO = X

DIALOG_HELP_GENERAL_CAPTION = Ayuda general
DIALOG_HELP_GENERAL_BODY_1 = El servidor está en fase BETA por lo que puede contener errores.\n
DIALOG_HELP_GENERAL_BODY_2 = Un día en el juego dura tres horas reales.\n
DIALOG_HELP_GENERAL_BODY_3 = Para reportar a un jugador usa /reportar.\n
DIALOG_HELP_GENERAL_BODY_4 = Utiliza el comando /duda para preguntar por el canal de dudas.\n\n
DIALOG_HELP_GENERAL_BODY_5 = Para más información visita %s.
DIALOG_HELP_GENERAL_YES = Cerrar

DIALOG_HELP_CHARACTER_CAPTION = Ayuda personaje
DIALOG_HELP_CHARACTER_BODY_1 = Puedes comprar ropa y accesorios para tu personaje.\n
DIALOG_HELP_CHARACTER_BODY_2 = Los accesorios deben ser ajustados por cada ropa.\n
DIALOG_HELP_CHARACTER_BODY_3 = Puedes cambiar de persona desde el /menu en la parte de ajustes.
DIALOG_HELP_CHARACTER_YES = Cerrar

DIALOG_HELP_PROPERTIES_CAPTION = Ayuda propiedades
DIALOG_HELP_PROPERTIES_BODY_1 = Puedes tener %d propiedades, compradas o alquiladas.\n
DIALOG_HELP_PROPERTIES_BODY_2 = Utiliza el comando /puerta apra abrir o cerrar una puerta.\n
DIALOG_HELP_PROPERTIES_BODY_3 = Para vender tu propiedad ve a una inmobiliaria.\n
DIALOG_HELP_PROPERTIES_BODY_4 = Para dejar de alquilar una propiedad borra la llave de tu inventario.\n
DIALOG_HELP_PROPERTIES_BODY_5 = Cuando vendas una casa se borrarán todas las llaves.
DIALOG_HELP_PROPERTIES_YES = Cerrar

DIALOG_HELP_VEHICLES_CAPTION = Ayuda vehículos
DIALOG_HELP_VEHICLES_BODY_1 = Puedes tener %d vehiculos, comprados o alquilados.\n
DIALOG_HELP_VEHICLES_BODY_2 = Para vender tu vehículo ve a un concesionario.\n
DIALOG_HELP_VEHICLES_BODY_3 = Para dejar de alquilar un vehículo borra la llave de tu inventario.\n
DIALOG_HELP_VEHICLES_BODY_4 = Cuando vendas un vehículo se borrarán todas las llaves.\n
DIALOG_HELP_VEHICLES_BODY_5 = Ve a un taller para reparar o tunear tu vehículo.
DIALOG_HELP_VEHICLES_YES = Cerrar

DIALOG_HELP_BUSINESS_CAPTION = Ayuda negocios
DIALOG_HELP_BUSINESS_BODY_1 = Puedes tener %d negocios.\n
DIALOG_HELP_BUSINESS_BODY_2 = Para vender tu negocio ve a una inmobiliaria.\n
DIALOG_HELP_BUSINESS_BODY_3 = Cuando vendas un negocio se borrarán todas las llaves.\n
DIALOG_HELP_BUSINESS_BODY_4 = Utiliza el comando /negocio dentro de tu negocio para administrarlo.
DIALOG_HELP_BUSINESS_YES = Cerrar

DIALOG_HELP_JOBS_CAPTION = Ayuda trabajos
DIALOG_HELP_JOBS_BODY_1 = Los trabajos son temporales.\n
DIALOG_HELP_JOBS_BODY_2 = La experiencia y nivel de los trabajos se guardan.\n
DIALOG_HELP_JOBS_BODY_3 = Utiliza el comando /trabajos para ver tu experiencia en los trabajos.
DIALOG_HELP_JOBS_YES = Cerrar

[help_channel]
MESSAGE_ERROR_SYNTAX = {ERROR}La sintaxis del comando no es correcta, usa /duda [pregunta].
MESSAGE_ERROR_TIME = {ERROR}Debes esperar %d segundos para volver a enviar una duda.
MESSAGE_HELP_CHANNEL = {INFO}[Dudas] [%s] {FFFFFF}%s (%d): %s

[car_workshop]
DIALOG_PAINT_COLORS_CAPTION = Colores
DIALOG_REMOVE_COMPONENT_CAPTION = Eliminar componente
DIALOG_PAINTJOBS_CAPTION = Paintjobs
DIALOG_DELETE_PAINTJOB = Eliminar paintjob

COMPONENT_0_PART_CL = Alerones
COMPONENT_1_PART_CL = Capós
COMPONENT_2_PART_CL = Techos
COMPONENT_3_PART_CL = Faldones derechos
COMPONENT_4_PART_CL = Faldones izquierdos
COMPONENT_5_PART_CL = Faros
COMPONENT_6_PART_CL = Nitro
COMPONENT_7_PART_CL = Tubos de escape
COMPONENT_8_PART_CL = Ruedas
COMPONENT_9_PART_CL = Estéreos
COMPONENT_10_PART_CL = Hidráulicos
COMPONENT_11_PART_CL = Parachoques delanteros
COMPONENT_12_PART_CL = Parachoques traseros
COMPONENT_13_PART_CL = Barras delanteras
COMPONENT_14_PART_CL = Barras traseras
COMPONENT_15_PART_CL = Ventanas derechas
COMPONENT_16_PART_CL = Ventanas izquierdas
COMPONENT_17_PART_CL = Señales delanteras
COMPONENT_18_PART_CL = Fuegos tubos de escape

COMPONENT_0_PART = Alerón
COMPONENT_1_PART = Capó
COMPONENT_2_PART = Techo
COMPONENT_3_PART = Faldón derecho
COMPONENT_4_PART = Faldón izquierdo
COMPONENT_5_PART = Faro
COMPONENT_6_PART = Nitro
COMPONENT_7_PART = Tubo de escape
COMPONENT_8_PART = Rueda
COMPONENT_9_PART = Estéreo
COMPONENT_10_PART = Hidráulicos
COMPONENT_11_PART = Parachoques delantero
COMPONENT_12_PART = Parachoques trasero
COMPONENT_13_PART = Barra delantera
COMPONENT_14_PART = Barra trasera
COMPONENT_15_PART = Ventana derecha
COMPONENT_16_PART = Ventana izquierda
COMPONENT_17_PART = Señal delantera
COMPONENT_18_PART = Fuego tubo de escape

MESSAGE_ERROR_NO_VEHICLE = {ERROR}No estás conduciendo un vehículo.
MESSAGE_ERROR_VEH_ACCESS = {ERROR}No puedes modificar este vehiculo porque no tienes las llaves.
MESSAGE_ERROR_NO_MONEY = {ERROR}No tienes dinero suficiente.
MESSAGE_ERROR_ENGINE = {ERROR}Debes apagar el motor del vehículo.
MESSAGE_ERROR_TUNING = {ERROR}No puedes tunear este vehículo.
MESSAGE_ERROR_PAINTJOB = {ERROR}Este vehículo no tiene paintjobs.
MESSAGE_ERROR_NO_COMPONENTS = {ERROR}Este vehículo no tiene ninguna modificación.
GAMETEXT_INFO_WORK_DONE = ~g~trabajo realizado

DIALOG_CAR_WORKSHOP_CAPTION = Taller de coches
DIALOG_CAR_WORKSHOP_OWNER_BODY = Reparar\t%d$\nPintar\nTunear\nEliminar componente\t%d$\nPaintjob\t%d$
DIALOG_CAR_WORKSHOP_BODY = Reparar
DIALOG_CAR_WORKSHOP_YES = Continuar
DIALOG_CAR_WORKSHOP_NO = Cerrar

DIALOG_CAR_PAINT_CAPTION = Pintar vehículo
DIALOG_CAR_PAINT_BODY = Color primario\t%d$\nColor secundario\t%d$
DIALOG_CAR_PAINT_YES = Continuar
DIALOG_CAR_PAINT_NO = Cerrar

[admin_player]
DIALOG_INFO_PERM_BANNED_CAPTION = ¡Atención!
DIALOG_INFO_PERM_BANNED_BODY = Su cuenta o tu dirección IP está prohibida permanentemente.\n\nID: %d\nRazón: %s\nFecha: %s
DIALOG_INFO_PERM_BANNED_YES = Cerrar

DIALOG_INFO_TEMP_BANNED_CAPTION = ¡Atención!
DIALOG_INFO_TEMP_BANNED_BODY = Su cuenta o tu dirección IP está prohibida temporalmente.\n\nID: %d\nRazón: %s\nFecha: %s\n\nFecha actual: %s\nFecha readmisión: %s
DIALOG_INFO_TEMP_BANNED_YES = Cerrar
MESSAGE_WARNING_TEMP_BAN = {WARNING}Tu cuenta ha sido prohibida por %d días.

MESSAGE_WARNING_UNBANNED = {WARNING}Tu cuenta ha sido readmitida.
MESSAGE_WARNING_KICKED = {WARNING}Has sido expulsado del servidor, razón: %s.

MESSAGE_ERROR_PDISCONNECTED = {ERROR}El jugador no está conectado.
MESSAGE_ERROR_SYNTAX_REPORT = {ERROR}Sintaxis del comando: /reportar <jugador ID/Nombre> <razón>
MESSAGE_WARNING_REPORT = {WARNING}%s (%d) reportó a %s (%d): %s
MESSAGE_INFO_REPORT_SENT = {INFO}Tu reporte fue enviado a los administradores en línea.

[forum]
MESSAGE_WARNING_REGISTERED = {WARNING}Tu cuenta se ha registrado en el foro: %s.

[admin_messages]
MESSAGE_ADMIN_KICK = {ADMIN}El administrador %s (%d) expulsó a %s (%d): %s
MESSAGE_ADMIN_PERM_BAN = {ADMIN}El administrador %s (%d) expulsó (permanentemente) a %s (%d): %s
MESSAGE_ADMIN_TEMP_BAN = {ADMIN}El administrador %s (%d) expulsó (temporalmente) a %s (%d): %s
MESSAGE_ADMIN_AC_KICK = {ADMIN}El anticheat expulsó a %s (%d): %s

[vinv]
TEXTDRAW_TITLE = MALETERO
TEXTDRAW_ADD_BUTTON = + Añadir
TEXTDRAW_CLOSE_INV = Cerrar inventario
TEXTDRAW_INV_FREE_SLOT = Espacio vacío

VINV_BUTTON_TAKE = Sacar
VINV_BUTTON_MOVE = Mover
VINV_BUTTON_DELETE = Eliminar

MESSAGE_ERROR_NO_ONFOOT = {ERROR}No estás depie.
MESSAGE_ERROR_TRUNK_POSITION = {ERROR}No estás cerca de un maletero.
MESSAGE_ERROR_VINV_IN_USE = {ERROR}Hay otra persona buscando en el maletero.
MESSAGE_ERROR_VEH_GONE = {ERROR}Ya no estás cerca del maletero.
MESSAGE_ERROR_INV = {ERROR}No tienes espacio en tu inventario para este objeto.
MESSAGE_INFO_MOVE = {INFO}Selecciona ahora la posición a donde quieres mover este objeto.

GAMETEXT_INFO_TAKEN = ~g~movido al inventario
GAMETEXT_INFO_DELETED = ~r~eliminado

DIALOG_DELETE_ITEM_CAPTION = Eliminar objeto
DIALOG_DELETE_ITEM_BODY = ¿Estás seguro de que quieres eliminar este objeto del maletero?\nEsta opción es irreversible.
DIALOG_DELETE_ITEM_YES = Eliminar
DIALOG_DELETE_ITEM_NO = Cancelar

DIALOG_DELETE_ITEM_AMOUNT_CAPTION = Eliminar objeto
DIALOG_DELETE_ITEM_AMOUNT_BODY = {FFFFFF}¿Cuántos quieres eliminar?, hay {CCFF00}%d.
DIALOG_DELETE_ITEM_AMOUNT_YES = Eliminar
DIALOG_DELETE_ITEM_AMOUNT_NO = Cancelar

MESSAGE_ERROR_INVALID_AMOUNT = {ERROR}Cantidad no válida.

DIALOG_MOVE_ITEM_TO_INV_CAPTION = Mover al inventario
DIALOG_MOVE_ITEM_TO_INV_BODY = {FFFFFF}¿Cuántos quieres mover?, hay {CCFF00}%d.
DIALOG_MOVE_ITEM_TO_INV_YES = Mover
DIALOG_MOVE_ITEM_TO_INV_NO = Cancelar

[autopilot]
TEXTDRAW_DESTROYED = ~r~El vehículo ha sido destruido porque lo has abandonado.
TEXTDRAW_WARNING = Tienes ~y~%d ~w~segundos para volver al vehículo antes de que se destruya.

MESSAGE_ERROR_NO_VEHICLE = {ERROR}Este vehículo está esperando a otra persona.

DIALOG_AUTOPILOT_PLACES_CAPTION = Lugares de interés
DIALOG_AUTOPILOT_PLACES_BODY = Abrir GPS\nAutoescuela\nTienda general\nTienda de electrónica\nCamioneros\nTaxista
DIALOG_AUTOPILOT_PLACES_YES = Ir
DIALOG_AUTOPILOT_PLACES_NO = Cerrar
MESSAGE_ERROR_NO_GPS = {ERROR}No tienes GPS.

GAMETEXT_INFO_ARRIVED = ~g~destino alcanzado
MESSAGE_ERROR_NO_MONEY = {ERROR}No tienes dinero para seguir pagando.
MESSAGE_ERROR_PATH = {ERROR}Ocurrió un error al intentar calcular la ruta.
MESSAGE_INFO_TAXI = {INFO}Hay un taxi esperandote cerca.

[admin_chat]
MESSAGE_CHAT_DEVELOPER = {99CC33}- Desarrollador(%d) %s(%d): %s
MESSAGE_CHAT_ADMIN = {99CC33}- Administrador(%d) %s(%d): %s
MESSAGE_CHAT_MODERATOR = {99CC33}- Moderador(%d) %s(%d): %s

[achievements]
TD_ACHIEVEMENT_NEW_USER = Bienvenido a %s
TD_ACHIEVEMENT_RENT_CAR = Alquila tu primer vehículo
TD_ACHIEVEMENT_PURCHASE_CAR = Compra tu primer vehículo
TD_ACHIEVEMENT_PURCHASE_USED_CAR = Compra tu primer vehículo usado
TD_ACHIEVEMENT_DRIVER_LICENSE = Obtén la licencia de conducir
TD_ACHIEVEMENT_HOSPITAL_BED = ~y~¡Médico!\n~w~Recuperate en el hospital
TD_ACHIEVEMENT_USE_ATM = ~y~Hombre de negocios\n~w~Usa un cajero por primera vez
TD_ACHIEVEMENT_PURCHASE_PROPERTY = ~y~¡Sueño americano!\n~w~Compra tu primera propiedad en Vice City
TD_ACHIEVEMENT_RENT_PROPERTY = Alquila tu primera propiedad
TD_ACHIEVEMENT_PURCHASE_BUSINESS = ~y~Hombre de negocios\n~w~Compra tu primer negocio
TD_ACHIEVEMENT_GUN_LICENSE = ~y~¡Pistolero!\n~w~Obtén la licencia de armas
TD_ACHIEVEMENT_INTRO = ~y~¡Observador!\n~w~Mira la intro completa

ACHIEVEMENT_NEW_USER = nuevo usuario
ACHIEVEMENT_RENT_CAR = alquilar un vehículo
ACHIEVEMENT_PURCHASE_CAR = comprar tu primer vehículo
ACHIEVEMENT_PURCHASE_USED_CAR = comprar tu primer vehículo usado
ACHIEVEMENT_DRIVER_LICENSE = obtener la licencia de conducir
ACHIEVEMENT_HOSPITAL_BED = recuperarte en el hospital
ACHIEVEMENT_USE_ATM = usar un cajero
ACHIEVEMENT_PURCHASE_PROPERTY = comprar tu primera propiedad
ACHIEVEMENT_RENT_PROPERTY = alquilar una propiedad
ACHIEVEMENT_PURCHASE_BUSINESS = comprar tu primer negocio
ACHIEVEMENT_GUN_LICENSE = obtener la licencia de armas
ACHIEVEMENT_INTRO = ver toda la introducción

[server_properties]
MESSAGE_INFO_PROPERTY_RENT_EXPIRED = {FF4040}La propiedad (%d) que tenías alquilada ha sido liberada porque se ha terminado el contrato.

[player_task]
MESSAGE_LEVEL_UP = Felicidades, has subido al nivel ~y~%d.
MESSAGE_1_PTASK = Tienes hambre y sed, come y bebe algo para recuperarte.
MESSAGE_2_PTASK = Tienes sed, bebe algo para recuperarte.
MESSAGE_3_PTASK = Tienes hambre, come algo para recuperarte.

[properties]
TEXTDRAW_TOUR_MESSAGE = Te quedan ~y~%d segundos ~w~de la visita.
TEXTDRAW_TOUR_ENDED = ~r~La visita ha terminado.

[pstats]
TEXTDRAW_HUNGRY = Hambre
TEXTDRAW_THIRST = Sed
TEXTDRAW_STATS = Nivel_%d\nExperiencia_%.2f/%d

[tutorial]
TUTORIAL_1_OBJECTIVE = ~w~Pulsa ~y~%s ~w~para abrir el inventario
TUTORIAL_2_OBJECTIVE = ~w~Pulsa ~y~ESC ~w~para cerrar el inventario
TUTORIAL_3_OBJECTIVE = ~w~Mantén ~y~%s ~w~para ver tus estadísticas
TUTORIAL_4_OBJECTIVE = ~w~Sube a un ~y~taxi ~w~o ~y~bicicleta
TUTORIAL_5_OBJECTIVE = ~w~Ve a la ~y~tienda de electrónica
TUTORIAL_6_OBJECTIVE = ~w~Compra un ~y~teléfono
TUTORIAL_7_OBJECTIVE = ~w~Compra un ~y~GPS
TUTORIAL_8_OBJECTIVE = ~w~Usa las ~y~flechas ~w~para moverte por el menú
TUTORIAL_9_OBJECTIVE = ~w~Pulsa ~y~%s ~w~para avanzar
TUTORIAL_10_OBJECTIVE = ~w~Pulsa ~y~%s ~w~para retroceder
TUTORIAL_11_OBJECTIVE = ~w~Activa el ~y~minimapa
TUTORIAL_12_OBJECTIVE = ~w~Pulsa ~y~ESC ~w~para cerrar el GPS
TUTORIAL_13_OBJECTIVE = ~w~Utiliza ~y~/motor ~w~para encender o apagar el motor
TUTORIAL_14_OBJECTIVE = ~w~Utiliza ~y~/abrir ~w~o ~y~/cerrar ~w~para las puertas
TUTORIAL_15_OBJECTIVE = ~w~Utiliza ~y~/luces ~w~para encender o apagar las luces
TUTORIAL_16_OBJECTIVE = ~w~Utiliza ~y~/radio ~w~para cambiar de emisora

TUTORIAL_1_MESSAGE = ~w~Sal del aeropuerto y sube a una ~y~bicicleta ~w~o a un ~y~taxi ~w~para continuar
TUTORIAL_2_MESSAGE = Sigue los puntos de control hasta llegar a la ~y~tienda de electrónica
TUTORIAL_3_MESSAGE = El taxi te llevará a la ~y~tienda de electrónica, ~w~no te bajes
TUTORIAL_4_MESSAGE = La ~y~tienda de electrónica ~w~está en la planta de arriba
TUTORIAL_5_MESSAGE = Puedes usar el comando ~y~/gps ~w~ para usar el GPS, te recomendamos que ~g~actives el minimapa
TUTORIAL_6_MESSAGE = Puedes usar el comando ~y~/movil ~w~para usar el teléfono
TUTORIAL_7_MESSAGE = ~g~Felicidades, ~w~has completado el tutorial de introducción, te recomendamos que desde el ~y~GPS ~w~localices la ~y~autoescuela ~w~y obtengás la licencia de conducir
TUTORIAL_8_MESSAGE = En el ~y~GPS ~w~también puedes localizar los trabajos, deberías trabajar para conseguir ~g~dinero
TUTORIAL_9_MESSAGE = Utiliza el comando ~y~/ropa ~w~para cambiarte de ropa
TUTORIAL_10_MESSAGE = Utiliza ~y~/abrir ~w~para abrir las puertas y ~y~/cerrar ~w~para cerrarlas, sin embargo, ~r~este vehículo no tiene puertas

[infomsg_render]
TEXTDRAW_VINV_MSG = Presiona ~y~%s ~w~para abrir el maletero
TEXTDRAW_BOOMBOX_MSG = Presiona ~y~%s ~w~para usar el boombox
TEXTDRAW_ENTRANCE_1_MSG = Presiona ~y~%s ~w~para entrar
TEXTDRAW_ENTRANCE_2_MSG = Horario: %02d:00 - %02d:00\n~w~Presiona ~y~%s ~w~para entrar
TEXTDRAW_INTERIOR_MSG = Presiona ~y~%s ~w~para salir
TEXTDRAW_ATM_MSG = Presiona ~y~%s ~w~para usar el cajero
TEXTDRAW_HOSPITAL_BED_MSG = Esta cama está libre, presiona ~y~%s ~w~para recuperarte
TEXTDRAW_BANK_MSG = Presiona ~y~%s ~w~para realizar una operación
TEXTDRAW_SVEHS_MSG = Presiona ~y~%s ~w~para ver el catálogo de vehículos
TEXTDRAW_GAS_MSG = Presiona ~y~%s ~w~para echar gasolina\n~p~%d$/litro
TEXTDRAW_DRIVING_SCHOOL_MSG = Presiona ~y~%s ~w~para realizar el examen por %d$
TEXTDRAW_PROPERTY_MSG = Presiona ~y~%s ~w~para entrar
TEXTDRAW_BSALE_MSG = Presiona ~y~%s ~w~para comprar
TEXTDRAW_BUSINESS_1_MSG = Presiona ~y~%s ~w~para entrar
TEXTDRAW_BUSINESS_2_MSG = Horario: %02d:00 - %02d:00\n~w~Presiona ~y~%s ~w~para entrar
TEXTDRAW_JOB_1_MSG = Presiona ~y~%s ~w~para dejar de trabajar
TEXTDRAW_JOB_2_MSG = Presiona ~y~%s ~w~para trabajar
TEXTDRAW_INTEREST_MSG = Presiona ~y~%s ~w~para ver los lugares de interés
TEXTDRAW_GUNSMITH_MSG = Presiona ~y~%s ~w~para ensamblar
TEXTDRAW_GUN_LICENSE_MSG = Presiona ~y~%s ~w~para realizar el examen por %d$
TEXTDRAW_ACTION_MSG = Presiona ~y~%s ~w~para interactuar
TEXTDRAW_ENV_AREA_TYPE_DANCE = Presiona ~y~%s ~w~para bailar
TEXTDRAW_ENV_AREA_TYPE_BED = Presiona ~y~%s ~w~para dormir
TEXTDRAW_ENV_AREA_TYPE_SEAT = Presiona ~y~%s ~w~para sentarte
TEXTDRAW_ENV_AREA_TYPE_PROSTITUTE_MONEY = Presiona ~y~%s ~w~para lanzar unos billetes
TEXTDRAW_ENV_DEFAULT = Presiona ~y~%s ~w~para interactuar

[label_render]
ENTRANCE_1_NAME = Hospital West Haven
ENTRANCE_2_NAME = Hospital Ocean View
ENTRANCE_3_NAME = El Banco Corrupto Grande
ENTRANCE_4_NAME = Banco
ENTRANCE_5_NAME = Policía de Washington Beach
ENTRANCE_6_NAME = Policía de Downtown
ENTRANCE_7_NAME = Centro comercial North Point
ENTRANCE_8_NAME = Autoescuela
ENTRANCE_9_NAME = Camioneros
ENTRANCE_10_NAME = Inmobiliaria
ENTRANCE_11_NAME = Camioneros
ENTRANCE_12_NAME = Fábrica

LABEL_BOOMBOX_OFF = {CCCC00}[Boombox %d]\n{CC3300}Apagado
LABEL_BOOMBOX = {CCCC00}[Boombox %d]\n{99CC00}Reproduciendo: %s
LABEL_ENTRANCE = {EEEE88}[Entrada %d]\n{FFFFFF}%s
LABEL_INTERIOR = Salida
LABEL_1_PROPERTY = {39a03b}[Alquiler %d]\n{FFFFFF}Arrendatario: %s\nFin alquiler: %s
LABEL_2_PROPERTY = {39a03b}[Propiedad %d]\n{FFFFFF}Propietario: %s
LABEL_3_PROPERTY = {39a03b}[Alquiler %d]\n{FFFFFF}Nivel: %d\nPrecio: %d$/día\n\nUtiliza {39a03b}/alquilar {FFFFFF}para alquilarla
LABEL_4_PROPERTY = {39a03b}[Propiedad %d]\n{FFFFFF}Nivel: %d\nPrecio: %d$\n\nUtiliza {39a03b}/comprar {FFFFFF}para comprarla
LABEL_INTERIOR_PROPERTY = Salida
LABEL_RENT_VEHICLE = {f4e242}[Vehículo de alquiler %d]\n{FFFFFF}%s\n\nPrecio: %d$\nNivel: %d
LABEL_USED_VEH = [%d] {ed7be3}%s\n\n{ffffff}Precio: %d$\nNivel: %d\nKilometraje: %.0f
LABEL_USED_VEH_MPH = [%d] {ed7be3}%s\n\n{ffffff}Precio: %d$\nNivel: %d\nMillaje: %.0f
LABEL_INTERIOR_BUSINESS = Salida
LABEL_1_BUSINESS = {f963e5}[Negocio %d]\n{FFFFFF}%s\n\nPropietario: %s
LABEL_2_BUSINESS = {f963e5}[Negocio %d]\n{FFFFFF}%s\n\nNivel: %d\nPrecio: %d$\n\nUtiliza {f963e5}/comprar {FFFFFF}para comprarlo
LABEL_1_JOB = {f4c542}[Trabajo %d]\n{FFFFFF}%s\n\nNivel requerido: %d\nNivel del trabajo requerido: %d
LABEL_2_JOB = {f4c542}[Trabajo %d]\n{FFFFFF}%s\n\nNivel requerido: %d
LABEL_3_JOB = {f4c542}[Trabajo %d]\n{FFFFFF}%s (%d)\n\nNivel requerido: %d\nNivel del trabajo requerido: %d
LABEL_4_JOB = {f4c542}[Trabajo %d]\n{FFFFFF}%s (%d)\n\nNivel requerido: %d
LABEL_INTEREST_POINTS = {f4d942}Lugares de interés
LABEL_CARWORKSHOP = {f4d942}Mecánico

[boombox]
MESSAGE_ERROR_INV = {ERROR}No tienes espacio en tu inventario.
MESSAGE_ERROR_POSITION = {ERROR}No se puede colocar un boombox aquí.
MESSAGE_ERROR_POWER = {ERROR}El boombox debe estar apagado para moverlo.
GAMETEXT_INFO_TAKE = ~g~guardado

DIALOG_BOOMBOX_CAPTION = Boombox
DIALOG_BOOMBOX_BODY = Emisora\nMover\nGuardar
DIALOG_BOOMBOX_YES = Continuar
DIALOG_BOOMBOX_NO = Cerrar

[anims_cmd]
MESSAGE_ERROR_SYNTAX_1 = {ERROR}El uso del comando es: /anim <ID> <bucle (0 o 1, este parámetro es opcional)>\n
MESSAGE_ERROR_SYNTAX_2 = {ERROR}IDs válidas: 1-%d, utiliza la ID 0 para parar las animación actual.\n\n
MESSAGE_INVALID_INDEX = {ERROR}ID no válida. IDs válidas: 1-%d, utiliza la ID 0 para parar las animación actual.

[minimap]
TEXTDRAW_NO_SIGNAL = ~r~Sin señal