//#define RADIO_URL "http://158.69.113.197:8000"
#define RADIO_URL "http://radio.vc-rp.es:8080"

enum enum_Radios
{
	radio_NAME[32],
	radio_URL[128]
};
new Radios[][enum_Radios] =
{
	{"Radio OFF", ""},
	{"Emotion 98.3", ""RADIO_URL"/emotion.ogg"},
	{"Radio Espantoso", ""RADIO_URL"/espantoso.ogg"},
	{"Fever 105", ""RADIO_URL"/fever105.ogg"},
	{"Flash FM", ""RADIO_URL"/flashfm.ogg"},
	{"K-Chat", ""RADIO_URL"/kchat.ogg"},
	{"VCPR", ""RADIO_URL"/vcpr.ogg"},
	{"V-Rock", ""RADIO_URL"/vrock.ogg"},
	{"Wave 103", ""RADIO_URL"/wave.ogg"},
	{"Wildstyle", ""RADIO_URL"/wildstyle.ogg"}
};