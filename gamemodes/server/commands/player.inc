#include <YSI\y_hooks>

hook OnScriptInit()
{
    //ALIAS
    //ahievements
    Command_AddAlt(YCMD:achievements, "premios");
	Command_AddAlt(YCMD:achievements, "trofeos");
	Command_AddAlt(YCMD:achievements, "logros");

    //actions
    Command_AddAlt(YCMD:me, "yo");
	Command_AddAlt(YCMD:me, "accion");
	Command_AddAlt(YCMD:do, "hacer");

    //business
    Command_AddAlt(YCMD:business, "negocio");

    //clothing
    Command_AddAlt(YCMD:clothes, "ropa");
	Command_AddAlt(YCMD:clothes, "skin");

    //help channel
	Command_AddAlt(YCMD:doubt, "duda");
	Command_AddAlt(YCMD:doubt, "preguntar");

    //help
    Command_AddAlt(YCMD:help, "ayuda");

    //inv
    Command_AddAlt(YCMD:inv, "inventario");

    //jobs
    Command_AddAlt(YCMD:jobs, "trabajos");

    //phone
    Command_AddAlt(YCMD:phone, "movil");
	Command_AddAlt(YCMD:phone, "telefono");
	Command_AddAlt(YCMD:call, "llamar");

    //toys
    Command_AddAlt(YCMD:toys, "accesorios");
	Command_AddAlt(YCMD:time, "hora");
	Command_AddAlt(YCMD:time, "reloj");

    //vehicle inv
    Command_AddAlt(YCMD:trunk, "maletero");
	Command_AddAlt(YCMD:trunk, "baul");

    //weapons
    Command_AddAlt(YCMD:weapons, "armas");

    //anims_cmd
    Command_AddAlt(YCMD:anim, "animacion");
    Command_AddAlt(YCMD:anim, "accion");
    
    //GLOBAL
    GROUP_ADD<Group:global_group>
	{
        //menu
        @YCMD:menu;

        //vehicle funcs
        @YCMD:radio;

        //actions
        @YCMD:me;
		@YCMD:do;
		@YCMD:b;

        //clothing
        @YCMD:skin;

        //gps
        @YCMD:gps;

        //inv
        @YCMD:inv;

        //anims_cmd
        @YCMD:anim;
    }

    //SPANISH
    GROUP_ADD<g_lang_groups[LANGUAGE_SPANISH]>
	{
        //admin player
		@YCMD:reportar;

        //achievements
        @YCMD:premios;
		@YCMD:trofeos;
		@YCMD:logros;

        //actions
        @YCMD:yo;
		@YCMD:accion;
		@YCMD:hacer;
    
        //business
        @YCMD:negocio;

        //clothing
        @YCMD:ropa;

        //help channel
        @YCMD:duda;
		@YCMD:preguntar;

        //help
        @YCMD:ayuda;

        //inv
        @YCMD:inventario;

        //jobs
        @YCMD:trabajos;

        //phone
        @YCMD:movil;
		@YCMD:telefono;
		@YCMD:llamar;

        //shared commands
        @YCMD:puerta;
		@YCMD:comprar;
		@YCMD:alquilar;
		@YCMD:responder;

        //toys
        @YCMD:accesorios;
		@YCMD:hora;
		@YCMD:reloj;

        //vehicle funcs
        @YCMD:abrir;
		@YCMD:cerrar;
		@YCMD:motor;
		@YCMD:luces;
		@YCMD:echar;

        //vehicle inv
        @YCMD:maletero;
		@YCMD:baul;

        //weapons
        @YCMD:armas;

        //anims_cmd
        @YCMD:animacion;
        @YCMD:accion;
	}
	return 1;
}