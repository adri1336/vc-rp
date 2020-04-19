#include <YSI\y_hooks>

hook OnScriptInit()
{
    //DEVELOPER
	GROUP_ADD<Admin_Groups[ADMIN_LEVEL_DEVELOPER]>
	{
        //ac editor
		@YCMD:ac;
		@YCMD:acvars;

        //business editor
        @YCMD:ibusiness;
		@YCMD:itbusiness;
		@YCMD:lbusiness;
		@YCMD:abusiness;
		@YCMD:abdoor;
		@YCMD:gbdoor;
		@YCMD:ebusiness;
		@YCMD:dbowner;
		@YCMD:dbdoor;
		@YCMD:dbusiness;

        //entrances editor
        @YCMD:identrances;
		@YCMD:identrance;
		@YCMD:dentrances;
		@YCMD:gdentrance;
		@YCMD:aentrance;
		@YCMD:adentrance;
		@YCMD:ldentrances;
		@YCMD:ddentrance;
		@YCMD:dentrance;

        //gps cat editor
        @YCMD:igpscats;
		@YCMD:gpscats;
		@YCMD:igpssites;
		@YCMD:gpssites;
		@YCMD:ggpssite;
		@YCMD:agpscat;
		@YCMD:dgpscat;
		@YCMD:agpssite;
		@YCMD:dgpssite;

        //interiors editor
        @YCMD:interiors;
		@YCMD:iinteriors;
		@YCMD:iinterior;
		@YCMD:ginterior;
		@YCMD:linteriors;
		@YCMD:ainterior;
		@YCMD:dinterior;

        //admin player
        @YCMD:setthirst;
		@YCMD:sethungry;
		@YCMD:sethealth;
		@YCMD:setarmour;
		@YCMD:setmoney;
		@YCMD:givemoney;
		@YCMD:setlevel;
		@YCMD:settime;
		@YCMD:setweather;
		@YCMD:con;
		@YCMD:setalevel;
		@YCMD:asay;

        //properties editor
        @YCMD:iproperty;
		@YCMD:iproperties;
		@YCMD:aproperty;
		@YCMD:apdoor;
		@YCMD:lproperties;
		@YCMD:gpdoor;
		@YCMD:eproperty;
		@YCMD:dpowner;
		@YCMD:dpdoor;
		@YCMD:dproperty;

        //variables editor
        @YCMD:svariables;

        //vcmap editor
        @YCMD:evco;
		@YCMD:dvco;
		@YCMD:vcosave;
		@YCMD:vcoss;
		@YCMD:vcodisable;
		@YCMD:avco;
		@YCMD:ddvco;
		@YCMD:lvco;
		@YCMD:gvco;
		@YCMD:ivco;
		@YCMD:ivcobjects;

        //vcnodes editor
        @YCMD:inode;
		@YCMD:inodes;
		@YCMD:lnodes;
		@YCMD:anode;
		@YCMD:dnode;
		@YCMD:gode;

        //veh shop editor
        @YCMD:svehs;
		@YCMD:setoldvehprice;
		@YCMD:setoldvehlevel;

        //vehicles editor
        @YCMD:vtypes;
		@YCMD:aveh;
		@YCMD:uvehpos;
		@YCMD:atveh;
		@YCMD:iveh;
		@YCMD:ivehs;
		@YCMD:dtvehs;
		@YCMD:dveh;
		@YCMD:repairveh;
		@YCMD:setvehfuel;
		@YCMD:gveh;
		@YCMD:getveh;
		@YCMD:vparams;
		@YCMD:lvehs;

        #if IMPL_DEV == 1
            //dev commands
            @YCMD:gvc;
            @YCMD:radar;
            @YCMD:gpos;
            @YCMD:gcpos;
            @YCMD:ls;
            @YCMD:setint;
            @YCMD:setvw;
            @YCMD:setpos;
            @YCMD:vcsetpos;
            @YCMD:sound;
            @YCMD:gotoint;
            @YCMD:devanim;
            @YCMD:cobject;
            @YCMD:eobject;
            @YCMD:dtobject;
            @YCMD:dobject;
            @YCMD:hud;
            @YCMD:audio;
            @YCMD:std;
            @YCMD:gotonode;
            @YCMD:fs;
            @YCMD:flymode;
            @YCMD:gotomdlpreview;
		    @YCMD:mdlpreview;
        #endif

        //veh prices
        @YCMD:vehprices;
	}

    //ADMINISTRADOR
	GROUP_ADD<Admin_Groups[ADMIN_LEVEL_ADMINISTRATOR]>
	{
        //admin player
		@YCMD:goto;
		@YCMD:get;
		@YCMD:ban;
		@YCMD:tban;
		@YCMD:unban;
		@YCMD:spec;
		@YCMD:getid;
		@YCMD:getname;
		@YCMD:dban;
		@YCMD:dtban;

		//boombox
		@YCMD:iboombox;
		@YCMD:dboombox;
	}

    //MODERADOR
    GROUP_ADD<Admin_Groups[ADMIN_LEVEL_MODERATOR]>
	{
        //admin player
		@YCMD:kick;
        @YCMD:a;
	}

    //GLOBAL
    GROUP_ADD<Group:global_group>
	{
        //getadmin
		@YCMD:getadmin;
    }
	return 1;
}