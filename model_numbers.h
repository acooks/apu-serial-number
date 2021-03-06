#ifndef MODEL_NUMBER_H
#define MODEL_NUMBER_H

enum model_enum {
	TEST = 1,
	APU1 = 10,
	APU2 = 20,
};

struct model {
	int id;
	int number;
	const char *name;
};


struct model model_n2n[] = {
	{TEST, 100000000, "test"},
	{APU1, 200000000, "apu1"},
	{APU2, 300000000, "apu2"},

	{0, 0, 0}
};

#endif
