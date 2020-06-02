/*
 * Matrix.cpp : Definition de la structure matrix (matrice 3x3)
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

/** \file Matrix.cpp
* \brief Definition de la structure matrix (matrice 3x3)
*/

/** Librairie de base **/
#include <stdio.h>
#include <vector>
#include <string.h>
#include <math.h>
#include <iostream>

#include "vec.h"
#include "Matrix.h"

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /* pi */
#endif


/*
 * Initialisation d une matrice avec valeurs nulles.
 */
Matrix Matrix::NullMatrix()
{
    Matrix result;
    
    for(unsigned int i = 0 ; i < 9 ; ++i)
    {
        result(i) = 0;
    }
    
    return result;
}


/*
 * Creation d une matrice unitaire (1 sur la diagonale, 0 sinon).
 */
Matrix Matrix::UnitMatrix()
{
    Matrix result;
    
    result(0) = 1; result(1) = 0; result(2) = 0;
    result(3) = 0; result(4) = 1; result(5) = 0;
    result(6) = 0; result(7) = 0; result(8) = 1;
    
    return result;
}


/*
 * Matrice de rotation.
 */
Matrix Matrix::AngleVectorToMatrix(Vector axe, float angle_degres)
{
    float angle_radian = angle_degres * (2.0 * M_PI)/360.0;
    float cosinus_angle = cos(angle_radian);
    float sinus_angle = sin(angle_radian);
    
    Vector direction;
    
    Matrix rotation;
    
    if (length(axe) != 0)
    {
        direction = normalize(axe);
        
        std::cout << direction << std::endl;
        
        // https://fr.wikipedia.org/wiki/Matrice_de_rotation
        // Matrice de rotation à partir d'un axe et d'un angle
        // La premiere formule est bonne, les autres ne donnent pas le bon resultat !!
        
        rotation(0)= direction.x * direction.x * (1 - cosinus_angle) + cosinus_angle;
        rotation(1)= direction.x * direction.y * (1 - cosinus_angle) - direction.z * sinus_angle;
        rotation(2)= direction.x * direction.z * (1 - cosinus_angle) + direction.y * sinus_angle;
        
        rotation(3)= direction.x * direction.y * (1 - cosinus_angle) + direction.z * sinus_angle;
        rotation(4)= direction.y * direction.y * (1 - cosinus_angle) + cosinus_angle;
        rotation(5)= direction.y * direction.z * (1 - cosinus_angle) - direction.x * sinus_angle;
        
        rotation(6)= direction.x * direction.z * (1 - cosinus_angle) - direction.y * sinus_angle;
        rotation(7)= direction.y * direction.z * (1 - cosinus_angle) + direction.x * sinus_angle;
        rotation(8)= direction.z * direction.z * (1 - cosinus_angle) + cosinus_angle;
        
    }
    else
    {
        rotation = Matrix::UnitMatrix();
    }
    
    return(rotation);

}


/*
 * Surcharge de l operateur =.
 */
Matrix & Matrix::operator=(const Matrix & matrix)
{
    for(unsigned int i = 0 ; i < 9 ; ++i)
    {
        m_Values[i] = matrix(i);
    }
    
    return *this;
}


/*
 * Surcharge de l operateur *=.
 */
Matrix & Matrix::operator*= (float factor)
{
    m_Values[0] *= factor; m_Values[1] *= factor; m_Values[2] *= factor;
    m_Values[3] *= factor; m_Values[4] *= factor; m_Values[5] *= factor;
    m_Values[6] *= factor; m_Values[7] *= factor; m_Values[8] *= factor;
    
    return *this;
}


/*
 * Surcharge operateur *=.A*=B -> Renvoie A*B.
 */
Matrix & Matrix::operator*= (const Matrix & matrix)
{
    Matrix result;
    
    result(0) = (m_Values[0] * matrix(0)) + (m_Values[1] * matrix(3)) + (m_Values[2] * matrix(6));
    result(1) = (m_Values[0] * matrix(1)) + (m_Values[1] * matrix(4)) + (m_Values[2] * matrix(7));
    result(2) = (m_Values[0] * matrix(2)) + (m_Values[1] * matrix(5)) + (m_Values[2] * matrix(8));
    
    result(3) = (m_Values[3] * matrix(0)) + (m_Values[4] * matrix(3)) + (m_Values[5] * matrix(6));
    result(4) = (m_Values[3] * matrix(1)) + (m_Values[4] * matrix(4)) + (m_Values[5] * matrix(7));
    result(5) = (m_Values[3] * matrix(2)) + (m_Values[4] * matrix(5)) + (m_Values[5] * matrix(8));
    
    result(6) = (m_Values[6] * matrix(0)) + (m_Values[7] * matrix(3)) + (m_Values[8] * matrix(6));
    result(7) = (m_Values[6] * matrix(1)) + (m_Values[7] * matrix(4)) + (m_Values[8] * matrix(7));
    result(8) = (m_Values[6] * matrix(2)) + (m_Values[7] * matrix(5)) + (m_Values[8] * matrix(8));
    
    *this = result;
    
    return *this;
}

/*
 * Surcharge de l operateur +=. A+=B -> renvoie A+B.
 */
 Matrix & Matrix::operator+= (const Matrix & matrix)
{
    for(unsigned int i = 0 ; i < 9 ; ++i)
    {
        m_Values[i] += matrix(i);
    }
    
    return *this;
}


/*
 * Surcharge de l operateur -=. A-=B -> renvoie A-B.
 */
Matrix & Matrix::operator-= (const Matrix & matrix)
{
    for(unsigned int i = 0 ; i < 9 ; ++i)
    {
        m_Values[i] -= matrix(i);
    }
    return *this;
}


/*
 * Renvoie la valeur d une matrice selon l indice donne.
 */
inline float & Matrix::operator()(unsigned index)
{
    return m_Values[index];
}


/*
 * Renvoie la valeur d une matrice selon l indice de ligne et de colonne donnes.
 */
inline float & Matrix::operator()(unsigned row, unsigned column)
{
    return m_Values[row * 3 + column];
}


/*
 * Renvoie la valeur d une matrice selon l indice donne.
 */
float Matrix::operator()(unsigned index) const
{
    return m_Values[index];
}


/*
 * Renvoie la valeur d une matrice selon l indice de ligne et de colonne donnes.
 */
float Matrix::operator()(unsigned row, unsigned column) const
{
    return m_Values[row * 3 + column];
}


/*
 * Renvoie le vecteur ligne de la matrice selon l indice de ligne donne.
 */
Vector Matrix::GetLine(unsigned int row) const
{
    return Vector(m_Values[row * 3 + 0],
                  m_Values[row * 3 + 1],
                  m_Values[row * 3 + 2]);
}

/*
 * Renvoie le vecteur colonne de la matrice selon l indice de colonne donne.
 */
Vector Matrix::GetColumn(unsigned int col) const
{
    return Vector(m_Values[col + 0],
                  m_Values[col + 3],
                  m_Values[col + 6]);
}



/*
 * Renvoi le determinant de la matrice.
 */
float Matrix::Determinant() const
{
    return m_Values[0] * m_Values[4] * m_Values[8]
    + m_Values[1] * m_Values[5] * m_Values[6]
    + m_Values[2] * m_Values[3] * m_Values[7]
    -  m_Values[2] * m_Values[4] * m_Values[6]
    - m_Values[0] * m_Values[5] * m_Values[7]
    - m_Values[1] * m_Values[3] * m_Values[8];
}


/*
 * Calcul de la matrice inverse.
 */
void Matrix::Inverse()
{
    float determinant = this->Determinant();
    if(determinant != 0)
    {
        determinant = 1.f / determinant;
        
        Matrix result;
        
        result(0) = (m_Values[4] * m_Values[8]) - (m_Values[5] * m_Values[7]);
        result(1) = (m_Values[2] * m_Values[7]) - (m_Values[1] * m_Values[8]);
        result(2) = (m_Values[1] * m_Values[5]) - (m_Values[2] * m_Values[4]);
        
        result(3) = (m_Values[5] * m_Values[6]) - (m_Values[3] * m_Values[8]);
        result(4) = (m_Values[0] * m_Values[8]) - (m_Values[2] * m_Values[6]);
        result(5) = (m_Values[2] * m_Values[3]) - (m_Values[0] * m_Values[5]);
        
        result(6) = (m_Values[3] * m_Values[7]) - (m_Values[4] * m_Values[6]);
        result(7) = (m_Values[1] * m_Values[6]) - (m_Values[0] * m_Values[7]);
        result(8) = (m_Values[0] * m_Values[4]) - (m_Values[1] * m_Values[3]);
        
        *this = result * determinant;
    }
}


/*
 * Renvoi la matrice inverse.
 */
Matrix Matrix::InverseConst() const
{
    Matrix result(*this);
    result.Inverse();
    return result;
}


/*
 * Calcul de la matrice transposee.
 */
void Matrix::Transpose()
{
    Matrix backUp = *this;
    
    m_Values[0] = backUp(0); m_Values[1] = backUp(3); m_Values[2] = backUp(6);
    m_Values[3] = backUp(1); m_Values[4] = backUp(4); m_Values[5] = backUp(7);
    m_Values[6] = backUp(2); m_Values[7] = backUp(5); m_Values[8] = backUp(8);
}


/*
 * Renvoi la matrice transposee.
 */
Matrix Matrix::TransposeConst() const
{
    Matrix result;

    result(0) = m_Values[0]; result(1) = m_Values[3]; result(2) = m_Values[6];
    result(3) = m_Values[1]; result(4) = m_Values[4]; result(5) = m_Values[7];
    result(6) = m_Values[2]; result(7) = m_Values[5]; result(8) = m_Values[8];
    
    return result;
}


/********************************************************/
/* Fonctions effectuant des operations sur des matrices */
/* mais ne faisant pas partie de la class Matrix        */
/********************************************************/


/*
 * Multiplication de la matrice par un scalaire. a*M
 */
Matrix operator* (float factor, const Matrix & matrix)
{
    Matrix result(matrix);
    result *= factor;

    return result;
}

/*
 * Multiplication de la matrice par un scalaire. M*a
 */
Matrix operator* (const Matrix & matrix, float factor)
{
    Matrix result(matrix);
    result *= factor;
    
    return result;
}


/*
 * Renvoi la multiplication de deux matrices. A*B dans ce sens
 */
Matrix operator* (const Matrix & matrixA, const Matrix & matrixB)
{
    Matrix result;

    result(0) = (matrixA(0) * matrixB(0)) + (matrixA(1) * matrixB(3)) + (matrixA(2) * matrixB(6));
    result(1) = (matrixA(0) * matrixB(1)) + (matrixA(1) * matrixB(4)) + (matrixA(2) * matrixB(7));
    result(2) = (matrixA(0) * matrixB(2)) + (matrixA(1) * matrixB(5)) + (matrixA(2) * matrixB(8));

    result(3) = (matrixA(3) * matrixB(0)) + (matrixA(4) * matrixB(3)) + (matrixA(5) * matrixB(6));
    result(4) = (matrixA(3) * matrixB(1)) + (matrixA(4) * matrixB(4)) + (matrixA(5) * matrixB(7));
    result(5) = (matrixA(3) * matrixB(2)) + (matrixA(4) * matrixB(5)) + (matrixA(5) * matrixB(8));

    result(6) = (matrixA(6) * matrixB(0)) + (matrixA(7) * matrixB(3)) + (matrixA(8) * matrixB(6));
    result(7) = (matrixA(6) * matrixB(1)) + (matrixA(7) * matrixB(4)) + (matrixA(8) * matrixB(7));
    result(8) = (matrixA(6) * matrixB(2)) + (matrixA(7) * matrixB(5)) + (matrixA(8) * matrixB(8));

    return result;
}


/*
 * Renvoi la multiplication d une matrice par un vecteur. A*X avec X vertical
 */
Vector operator* (const Matrix & matrix, const Vector & coord)
{
    Vector result;

    result.x = coord.x * matrix(0) + coord.y * matrix(1) + coord.z * matrix(2);
    result.y = coord.x * matrix(3) + coord.y * matrix(4) + coord.z * matrix(5);
    result.z = coord.x * matrix(6) + coord.y * matrix(7) + coord.z * matrix(8);

    return result;
}


/*
 * Calcul de la somme de deux matrices.
 */
Matrix operator+ (const Matrix & matrixA, const Matrix & matrixB)
{
    Matrix result(matrixA);
    result += matrixB;
    
    return result;
}


/*
 * Renvoi la multiplication d un vecteur X (horizontal) par une matrice A
 * resultat : vecteur horizontal.
 */
Vector operator* (const Vector & coord, const Matrix & matrix)
{
    Vector result;

    result.x = coord.x * matrix(0) + coord.x * matrix(3) + coord.x * matrix(6);
    result.y = coord.y * matrix(1) + coord.y * matrix(4) + coord.y * matrix(7);
    result.z = coord.z * matrix(2) + coord.z * matrix(5) + coord.z * matrix(8);

    return result;
}


/*
 * Calcul de la soustraction de deux matrices.
 */
Matrix operator- (const Matrix & matrixA, const Matrix & matrixB)
{
    Matrix result(matrixA);
    result -= matrixB;
    return result;
}


/*
 * Retourne le matrice (vecteur * equivalent a : -w cross).
 */
Matrix StarMatrix(const Vector & vector)
{
    Vector direction = normalize(vector);
    
    Matrix matrix;
    matrix(0) = 0;
    matrix(1) = -direction.z;
    matrix(2) = direction.y;
    
    matrix(3) = direction.z;
    matrix(4) = 0;
    matrix(5) = -direction.x;
    
    matrix(6) = -direction.y;
    matrix(7) = direction.x;
    matrix(8) = 0;
    
    return (matrix);
}

/*
 * Renvoie la matrice transposee. Renvoie X*X^t avec X vertical.
 */
Matrix MultiplyTransposedAndOriginal(const Vector & coord)
{
    Matrix result;
    
    result(0) = coord.x * coord.x;
    result(1) = coord.x * coord.y;
    result(2) = coord.x * coord.z;
    
    result(3) = coord.y * coord.x;
    result(4) = coord.y * coord.y;
    result(5) = coord.y * coord.z;
    
    result(6) = coord.z * coord.x;
    result(7) = coord.z * coord.y;
    result(8) = coord.z * coord.z;
    
    return result;
}

/*
 * Surcharge de l operateur <<.
 */
std::ostream& operator<<(std::ostream &flux, Matrix const &m)
{
    std::cout << "La matrice vaut : " << std::endl;
    
    flux << m.m_Values[0] << " " ;
    flux << m.m_Values[1] << " " ;
    flux << m.m_Values[2] << " " ;
    flux << std::endl;
    
    flux << m.m_Values[3] << " " ;
    flux << m.m_Values[4] << " " ;
    flux << m.m_Values[5] << " " ;
    flux << std::endl;
    
    flux << m.m_Values[6] << " " ;
    flux << m.m_Values[7] << " " ;
    flux << m.m_Values[8] << " " ;
    flux << std::endl;
    
    return flux;
}
