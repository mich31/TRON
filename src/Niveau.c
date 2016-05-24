#include <stdio.h>
#include <stdlib.h>
#include "Niveau.h"

void initNiveau(Niveau * N, const int id)
{
	N->idNiveau = id;
	initTerrain(N->T,120,40,id);
}

void libereNiveau(Niveau * N)
{
	libereTerrain(N->T);
	N->idNiveau = NULL;
}

int getNiveau(Niveau * N)
{
	return N->idNiveau;
}

Terrain getTerrain(const Niveau * N)
{
	return N->T;
}
