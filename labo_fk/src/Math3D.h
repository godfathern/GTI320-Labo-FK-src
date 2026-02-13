#pragma once

/**
 * @file Math3D.h
 *
 * @brief Fonctions pour l'intinialisation et la manipulation de matrices de
 * rotation, des matrices de transformations en coordonn�es homog�nes et les
 * vecteurs 3D.
 *
 * Nom: Phan Tung Bui
 * Code permanent : BUIP26109708
 * Email : phan-tung.bui.1@ens.etsmtl.ca
 *
 */

#include "Matrix.h"
#include "Vector.h"
#include "Operators.h"
#include "SubMatrix.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 
#endif

#include <math.h>

namespace gti320 {

    // Type de vecteur 3D.
    typedef Vector<float, 3> Vector3f;

    // Dans le cadre de ce projet, nous consid�rons seulement deux
    // cas :
    //
    //  - les rotations
    //  - les translations
    //
    // Matrice en coordonn�es homog�es :
    typedef Matrix<float, 4, 4, ColumnStorage> Matrix4f;
    // 
    // Matrice pour les rotations
    typedef Matrix<float, 3, 3, ColumnStorage> Matrix3f;

    /**
     * Initialise et retourne la matrice identit�
     */
    template<>
    inline void Matrix4f::setIdentity()
    {
        // TODO affecter la valeur 0.0 partout, sauf sur la diagonale principale o� c'est 1.0.
        //      Note: ceci est une red�finition d'une fonction membre!
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                (*this)(i, j) = (i == j) ? 1: 0;
            }
        }
    }

    /**
     * Calcul de la matrice inverse, SP�CIALIS� pour le cas d'une matrice de
     * transformation rigide en coordonn�es homog�nes.
     *
     * TODO (vous pouvez supposer qu'il s'agit d'une matrice de transformation
     * en coordonn�es homog�nes)
     */
    template<>
    inline Matrix4f Matrix4f::inverse() const
    {
        // TODO : impl�menter
        // A reviser
        Matrix4f inv;
        inv.setIdentity();

        // Extraire R (3x3) et t (3x1)
        Matrix3f R;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                R(i, j) = (*this)(i, j);
            }
        }

        Vector3f t;
        t(0) = (*this)(0, 3);
        t(1) = (*this)(1, 3);
        t(2) = (*this)(2, 3);

        // R^T
        Matrix3f Rt;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                Rt(i, j) = R(j, i);
            }
        }

        // Placer Rt dans inv
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                inv(i, j) = Rt(i, j);
            }
        }

        // Calculer -Rt * t
        Vector3f negRtt;
        for (int i = 0; i < 3; ++i) {
            float s = 0.0f;
            for (int k = 0; k < 3; ++k) {
                s += Rt(i, k) * t(k);
            }
            negRtt(i) = -s;
        }

        inv(0, 3) = negRtt(0);
        inv(1, 3) = negRtt(1);
        inv(2, 3) = negRtt(2);

        // Dernière ligne (0 0 0 1)
        inv(3, 0) = 0.0f; inv(3, 1) = 0.0f; inv(3, 2) = 0.0f; inv(3, 3) = 1.0f;

        return inv;
    }
    
    /**
     * Calcul de la matrice inverse, SP�CIALIS� pour le cas d'une matrice de rotation.
     *
     * (vous pouvez supposer qu'il s'agit d'une matrice de rotation)
     */
    template<>
    inline Matrix3f Matrix3f::inverse() const
    {
        // TODO : impl�menter
        Matrix3f Rt;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                Rt(i, j) = (*this)(j, i);
            }
        }
        return Rt;
    }


    /**
     * Multiplication d'une matrice 4x4 avec un vecteur 3D o� la matrice
     * repr�sente une transformation rigide en coordonn�es homog�ne.
     */
    template <typename _Scalar>
    Vector<_Scalar, 3> operator*(const Matrix<_Scalar, 4, 4, ColumnStorage>& A, const Vector<_Scalar, 3>& v)
    {
        // TODO : impl�menter
        Vector<_Scalar, 3> result;

        for (int i = 0; i < 3; ++i) {
            _Scalar s = 0;
            for (int j = 0; j < 3; ++j) {
                s += A(i, j) * v(j);
            }
            s += A(i, 3);
            result(i) = s;
        }

        return result;
    }


    /**
     * Initialise et retourne la matrice de rotation d�finie par les angles
     * d'Euler XYZ exprim�s en radians.
     *
     * La matrice doit correspondre au produit : Rz*Ry*Rx.
     */
    template<typename _Scalar>
    static Matrix<_Scalar, 3, 3> makeRotation(_Scalar x, _Scalar y, _Scalar z)
    {
        // TODO : impl�menter
        //Diapo 29
        const _Scalar cos_x = cos(x), sin_x = sin(x);
        const _Scalar cos_y = cos(y), sin_y = sin(y);
        const _Scalar cos_z = cos(z), sin_z = sin(z);

        Matrix<_Scalar, 3, 3> Rx, Ry, Rz;

        // Rx
        Rx(0,0)=1;  Rx(0,1)=0;      Rx(0,2)=0;
        Rx(1,0)=0;  Rx(1,1)=cos_x;  Rx(1,2)=-sin_x;
        Rx(2,0)=0;  Rx(2,1)=sin_x;  Rx(2,2)=cos_x;

        // Ry
        Ry(0,0)=cos_y;  Ry(0,1)=0;  Ry(0,2)=sin_y;
        Ry(1,0)=0;      Ry(1,1)=1;  Ry(1,2)=0;
        Ry(2,0)=-sin_y; Ry(2,1)=0;  Ry(2,2)=cos_y;

        // Rz
        Rz(0,0)=cos_z;  Rz(0,1)=-sin_z; Rz(0,2)=0;
        Rz(1,0)=sin_z;  Rz(1,1)=cos_z;  Rz(1,2)=0;
        Rz(2,0)=0;      Rz(2,1)=0;      Rz(2,2)=1;

        // Produit: Rz * Ry * Rx
        return Rz * (Ry * Rx);
    }

}
