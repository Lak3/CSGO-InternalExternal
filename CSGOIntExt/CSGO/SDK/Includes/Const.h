#pragma once

#define	FL_ONGROUND				(1<<0)
#define FL_DUCKING				(1<<1)
#define	FL_WATERJUMP			(1<<2)
#define FL_ONTRAIN				(1<<3)
#define FL_INRAIN				(1<<4)
#define FL_FROZEN				(1<<5)
#define FL_ATCONTROLS			(1<<6)
#define	FL_CLIENT				(1<<7)
#define FL_FAKECLIENT			(1<<8)

#define	LIFE_ALIVE				0
#define	LIFE_DYING				1
#define	LIFE_DEAD				2
#define LIFE_RESPAWNABLE		3
#define LIFE_DISCARDBODY		4

#define MAX_PLAYERS				64