#pragma once

/**
 * @file Math3D.h
 *
 * @brief Fonctions pour l'intinialisation et la manipulation de matrices de
 * rotation, des matrices de transformations en coordonnées homogènes et les
 * vecteurs 3D.
 *
 * Nom: 
 * Code permanent : 
 * Email : 
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

    // Dans le cadre de ce projet, nous considérons seulement deux
    // cas :
    //
    //  - les rotations
    //  - les translations
    //
    // Matrice en coordonnées homogèes :
    typedef Matrix<float, 4, 4, ColumnStorage> Matrix4f;
    // 
    // Matrice pour les rotations
    typedef Matrix<float, 3, 3, ColumnStorage> Matrix3f;

    /**
     * Initialise et retourne la matrice identité
     */
    template<>
    inline void Matrix4f::setIdentity()
    {
        // TODO affecter la valeur 0.0 partout, sauf sur la diagonale principale où c'est 1.0.
        //      Note: ceci est une redéfinition d'une fonction membre!
    }

    /**
     * Calcul de la matrice inverse, SPÉCIALISÉ pour le cas d'une matrice de
     * transformation rigide en coordonnées homogènes.
     *
     * TODO (vous pouvez supposer qu'il s'agit d'une matrice de transformation
     * en coordonnées homogènes)
     */
    template<>
    inline Matrix4f Matrix4f::inverse() const
    {
        // TODO : implémenter
        return Matrix4f(); // Pas bon, à changer
    }
    
    /**
     * Calcul de la matrice inverse, SPÉCIALISÉ pour le cas d'une matrice de rotation.
     *
     * (vous pouvez supposer qu'il s'agit d'une matrice de rotation)
     */
    template<>
    inline Matrix3f Matrix3f::inverse() const
    {
        // TODO : implémenter
        return Matrix3f();
    }


    /**
     * Multiplication d'une matrice 4x4 avec un vecteur 3D où la matrice
     * représente une transformation rigide en coordonnées homogène.
     */
    template <typename _Scalar>
    Vector<_Scalar, 3> operator*(const Matrix<_Scalar, 4, 4, ColumnStorage>& A, const Vector<_Scalar, 3>& v)
    {
        // TODO : implémenter
        return Vector<_Scalar, 3>(); // pas bon, à changer
    }


    /**
     * Initialise et retourne la matrice de rotation définie par les angles
     * d'Euler XYZ exprimés en radians.
     *
     * La matrice doit correspondre au produit : Rz*Ry*Rx.
     */
    template<typename _Scalar>
    static Matrix<_Scalar, 3, 3> makeRotation(_Scalar x, _Scalar y, _Scalar z)
    {
        // TODO : implémenter

        return Matrix<_Scalar, 3, 3>(); //	 pas bon, à changer
    }

}
