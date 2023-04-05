/***
 * @author Étienne Germain
 * @file Corps.cpp
 * @date 17 janvier 2023
***/

#include "Corps.h"

Corps::Corps(Dynamixel2Arduino* dxl, int pin_electro, int id_moteur)
{
    moteur = new DXL_Corps(dxl, id_moteur);
    //ElectroCPU electro = ElectroCPU(pin_electro);      
    //electroaimant = &electro;
    electroaimant = new ElectroCPU(pin_electro);
    monte = false;
    baisse = false;
}

Corps::~Corps()
{
    delete moteur;
    delete electroaimant;
}

void Corps::init()
{
    desactiverElectro();
    ((DXL_Corps *)moteur)->positionInitiale();

    monte = true;
    baisse = false;
}

bool Corps::monter()
{
    if(monte)
    {
        return true;
    }

    if(baisse)
    {
        ((DXL_Corps *)moteur)->go_to_position(ANGLE_MONTER);
        baisse = false;

        return false;
    }

    if(estArrete())
    {
        monte = true;
        return true;
    }

    return false;
}

bool Corps::baisser()
{
    if(baisse)
    {
        return true;
    }

    if(monte)
    {
        ((DXL_Corps *)moteur)->go_to_position(ANGLE_BAISSER);
        monte = false;

        return false;
    }

    if(estArrete())
    {
        baisse = true;
        return true;
    }

    return false;
}

void Corps::activerElectro()
{
    electroaimant->activer();
}

void Corps::desactiverElectro()
{
    electroaimant->desactiver();
}

bool Corps::estMonte()
{
    return monte;
}

bool Corps::estBaisse()
{
    return baisse;
}

bool Corps::electroActive()
{
    return electroaimant->getEtat();
}

bool Corps::estArrete()
{
    return ((DXL_Corps *)moteur)->is_movement_finished();
}
