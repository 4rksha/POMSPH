/*
 * Matrix.h : Definition de la structure matrix (matrice 3x3)
 * Copyright (C) 2016 Florence Zara, LIRIS
 *               florence.zara@liris.univ-lyon1.fr
 *               http://liris.cnrs.fr/florence.zara/
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

/** \file Matrix.h
* \brief Definition de la structure matrix (matrice 3x3)
*/

#ifndef MATRIX_H
#define MATRIX_H

/** Librairie de base **/
#include <stdio.h>
#include <vector>
#include <string.h>


#include "vec.h"



/**
 * \brief Structure de donnees relative a une matrice 3x3.
 */
class Matrix
{
public:
    
    /// Creation matrice nulle
    static Matrix NullMatrix();
    
    /// Creation matrice unitaire
    static Matrix UnitMatrix();
    
    /// Matrice de rotation
    static Matrix AngleVectorToMatrix(Vector axe, float angle_degres);
    
    /// Valeurs de la matrice 3 x 3
    float m_Values[9];
    
public:
    /// Surcharge des operateurs
    Matrix & operator= (const Matrix & matrix);
    Matrix & operator*= (float factor);
    Matrix & operator*= (const Matrix & matrix);
    Matrix & operator+= (const Matrix & matrix);
    Matrix & operator-= (const Matrix & matrix);

    // Acces a une valeur de la matrice : par l indice
    float & operator() (unsigned index);
    
    // Acces a une valeur de la matrice : par indices ligne et colonne
    float & operator() (unsigned row, unsigned column);
    
    float operator() (unsigned index) const;
    float operator() (unsigned row, unsigned column) const;
    
    /// Renvoie le vecteur ligne de la matrice selon l indice de ligne donne
    Vector GetLine (unsigned int index) const;
    
    /// Renvoie le vecteur colonne de la matrice selon l indice de colonne donne
    Vector GetColumn (unsigned int index) const;
    
    /// Renvoie le determinant de la matrice
    float Determinant() const;
    
    /// Calcul de la matrice inverse
    void Inverse();
    
    /// Renvoi la matrice inverse
    Matrix InverseConst() const;
    
    /// Calcul de la matrice transposee
    void Transpose();
    
    /// Renvoi la matrice transposee
    Matrix TransposeConst() const;
    
};

Matrix operator* (const Matrix & matrix, float factor);
Matrix operator* (float factor, const Matrix & matrix);
Matrix operator* (const Matrix & matrixA, const Matrix & matrixB);
Vector operator* (const Matrix & matrix, const Vector & coord);
Matrix operator+ (const Matrix & matrixA, const Matrix & matrixB);
Vector operator* (const Vector & coord, const Matrix & matrix);
Matrix operator- (const Matrix & matrixA, const Matrix & matrixB);
std::ostream& operator<<(std::ostream &flux, Matrix const &m);


Matrix MultiplyTransposedAndOriginal(const Vector & coord);

/// Retourne le matrice (vecteur *).
Matrix StarMatrix(const Vector & vector);


#endif
