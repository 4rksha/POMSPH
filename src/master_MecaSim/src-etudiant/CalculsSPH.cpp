/*
 * CalculsSPH.cpp :
 * Copyright (C) 2017 Florence Zara, LIRIS
 *               florence.zara@liris.univ-lyon1.fr
 *               http://liris.cnrs.fr/florence.zara/
 *
 * Utilisation du code :
 * https://www.cs.cornell.edu/~bindel/class/cs5220-f11/code/sph.pdf
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/** \file CalculsSPH.cpp
Programme calculant pour  un fluide son etat au pas de temps suivant (methode d 'Euler semi-implicite) en utilisant la methode SPH (Smoothed Particles Hydrodynamics):
principales fonctions de calculs.  
\brief Fonctions de calculs pour un fluide avec methode SPH.
*/

#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <omp.h>

#include "vec.h"
#include "ObjetSimule.h"
#include "ObjetSimuleSPH.h"
#include "Viewer.h"

using namespace std;

/**
 * Calcul des densites des particules.
 * Formule :
 *  \rho_i = \frac{4m}{\pi h^8} \sum_{j \in N_i} (h^2 - r^2)^3.
 */
void ObjetSimuleSPH::CalculDensite()
{
    float h2 = h * h;
    float h8 = h * h * h * h * h * h * h * h;
    float c = 4 * M[0] / M_PI / h8;
#pragma omp parallel for
    for (int i = 0; i < _Nb_Sommets; ++i)
    {
        rho[i] += 4 * M[i] / M_PI / (h * h);
        for (int j = i + 1; j < _Nb_Sommets; ++j)
        {
            float dx = P[i].x - P[j].x;
            float dy = P[i].y - P[j].y;
            float dz = P[i].z - P[j].z;
            float r2 = dx * dx + dy * dy + dz * dz;
            float z = h2 - r2;
            if (z > 0)
            {
                float rho_ij = c * z * z * z;
                rho[i] += rho_ij;
                rho[j] += rho_ij;
            }
        }
    }
} //void

/**
 * Calcul des forces d interaction entre particules.
  * Attention - Calcul direct de fij / rho_i
 */
void ObjetSimuleSPH::CalculInteraction(float visco)
{
    float h2 = h * h;
    float c = M[0] / M_PI / (h2 * h2);
    float c_bulk = 15 * bulk;
    float c_mu = -40 * visco;

#pragma omp parallel for
    for (int i = 0; i < _Nb_Sommets; ++i)
    {
        for (int j = i + 1; j < _Nb_Sommets; ++j)
        {
            float dx = P[i].x - P[j].x;
            float dy = P[i].y - P[j].y;
            float dz = P[i].z - P[j].z;
            float r2 = dx * dx + dy * dy + dz * dz;
            if (r2 < h2)
            {
                float q = sqrt(r2) / h;
                float tmp0 = c * (1 - q) / rho[i] / rho[j];
                float press = tmp0 * c_bulk * (rho[i] + rho[j] - 2 * rho0) * (1 - q) / q;
                float visc = tmp0 * c_mu;
                float vdx = V[i].x - V[j].x;
                float vdy = V[i].y - V[j].y;
                float vdz = V[i].z - V[j].z;
                Force[i].x = (Force[i].x + (press * dx + visc * vdx)) / rho[i];
                Force[i].y = (Force[i].y + (press * dy + visc * vdy)) / rho[i];
                Force[i].z = (Force[i].z + (press * dz + visc * vdz)) / rho[i];
                Force[j].x = (Force[j].x - (press * dx + visc * vdx)) / rho[j];
                Force[j].y = (Force[j].y - (press * dy + visc * vdy)) / rho[j];
                Force[j].z = (Force[j].z - (press * dz + visc * vdz)) / rho[j];
            }
        }
    } //void
}
/**
 * Gestion des collisions.
 * Notre condition aux limites correspond à une frontière inélastique
 * avec un coefficient de restitution spécifié < 1. Quand
 * une particule frappe une barrière verticale ([[which = 0]]) ou horizontale
 * barrier ([[which = 1]]), nous le traitons avec [[damp_reflect]].
 * Cela réduit la distance totale parcourue en fonction du temps écoulé depuis
 * la collision reflète, amortit les vitesses, et reflète
 * quels que soient les composants de la solution à refléter.
 */

void ObjetSimuleSPH::damp_reflect(int frontiere, float barrier, int indice_part)
{
    /// frontiere : indique quelle frontiere (x, y, z) du domaine est concernee
    float coef = 0.75;
    if (frontiere == 0 && V[indice_part].x != 0)
    {
        float tbounce = (P[indice_part].x - barrier) / V[indice_part].x;
        P[indice_part] = P[indice_part] - V[indice_part] * (1 - coef) * tbounce;
        P[indice_part].x = 2 * barrier - P[indice_part].x;
        V[indice_part].x = -V[indice_part].x;
        Vprec[indice_part].x = -Vprec[indice_part].x;
        V[indice_part] = V[indice_part] * coef;
        Vprec[indice_part] = Vprec[indice_part] * coef;
    }
    else if (frontiere == 1 && V[indice_part].y != 0)
    {
        float tbounce = (P[indice_part].y - barrier) / V[indice_part].y;
        P[indice_part] = P[indice_part] - V[indice_part] * (1 - coef) * tbounce;
        P[indice_part].y = 2 * barrier - P[indice_part].y;
        V[indice_part].y = -V[indice_part].y;
        Vprec[indice_part].y = -Vprec[indice_part].y;
        V[indice_part] = V[indice_part] * coef;
        Vprec[indice_part] = Vprec[indice_part] * coef;
    }
    else if (frontiere == 2 && V[indice_part].z != 0)
    {
        float tbounce = (P[indice_part].z - barrier) / V[indice_part].z;
        P[indice_part] = P[indice_part] - V[indice_part] * (1 - coef) * tbounce;
        P[indice_part].z = 2 * barrier - P[indice_part].z;
        V[indice_part].z = -V[indice_part].z;
        Vprec[indice_part].z = -Vprec[indice_part].z;
        V[indice_part] = V[indice_part] * coef;
        Vprec[indice_part] = Vprec[indice_part] * coef;
    }
}

/**
 * Gestion des collisions.
 * Pour chacune des particules nous verifions la reflection
 * avec chacun des 4 murs du domaine.
 */
void ObjetSimuleSPH::Collision()
{

    float barriers[3][2] =
        {
            {-1.f, 1.f},
            {0.f, 2.f},
            {-1.f, 1.f},
        };

    for (int i = 0; i < _Nb_Sommets; ++i)
    {
        if (P[i].x < barriers[0][0])
            damp_reflect(0, barriers[0][0], i);
        if (P[i].x > barriers[0][1])
            damp_reflect(0, barriers[0][1], i);
        if (P[i].y < barriers[1][0])
            damp_reflect(1, barriers[1][0], i);
        if (P[i].y > barriers[1][1])
            damp_reflect(1, barriers[1][1], i);
        if (P[i].z < barriers[2][0])
            damp_reflect(2, barriers[2][0], i);
        if (P[i].z > barriers[2][1])
            damp_reflect(2, barriers[2][1], i);
    }
}
