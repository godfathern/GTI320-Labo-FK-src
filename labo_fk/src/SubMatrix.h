#pragma once

#include "Matrix.h"

namespace gti320
{
    /**
     * Classe pour accéder à une sous-matrice.
     *
     * Un sous-matrice ne copie pas les données. Au lieu de cela, elle conserve une
     * référence à la matrice originale.
     */
    template <typename _Scalar, int _RowsAtCompile, int _ColsAtCompile, int _StorageType>
    class SubMatrix
    {
    private:
        // Référence à la matrice originale
        Matrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType>& m_matrix;

        // Constructeur par défaut (privé)
        SubMatrix() {}

        // (i,j) est le coin supérieur gauche de la sous-matrice
        int m_i;        // Décalage en ligne 
        int m_j;        // Décalage en colonne

        // la sous-matrice est de dimension : m_rows x m_cols
        int m_rows;     // Hauteur de la sous-matrice (nombre de lignes)
        int m_cols;     // Largeur de la sous-matrice (nombre de colonnes)

    public:

        /**
         * Constructeur à partir d'une référence en lecture seule à une matrice.
         */
        SubMatrix(const Matrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType>& _matrix, int _i, int _j, int _rows, int _cols) :
            m_matrix(const_cast<Matrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType>&>(_matrix)),
            m_i(_i), m_j(_j), m_rows(_rows), m_cols(_cols)
        {
        }

        /**
         * Constructeur à partir d'une référence en lecture et écriture à une matrice.
         */
        explicit SubMatrix(Matrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType>& _matrix, int _i, int _j, int _rows, int _cols) :
            m_matrix(_matrix),
            m_i(_i), m_j(_j), m_rows(_rows), m_cols(_cols)
        {

        }

        // Constructeur de copie
        SubMatrix(const SubMatrix& other) :
            m_matrix(other.m_matrix),
            m_i(other.m_i), m_j(other.m_j), m_rows(other.m_rows), m_cols(other.m_cols)
        {
        }

        /**
         * Destructeur
         */
        ~SubMatrix() {}

        /**
         * Opérateur de copie (à partir d'une matrice)
         *
         * Copies toutes les entrées de la matrice dans la sous-matrice.
         *
         * Note : la taille de la matrice doit correspondre à la taille de la
         * sous-matrice.
         */
        template<typename _OtherScalar, int _OtherRows, int _OtherCols, int _OtherStorage>
        SubMatrix& operator= (const Matrix<_OtherScalar, _OtherRows, _OtherCols, _OtherStorage>& matrix)
        {
            // TODO Copie les valeurs de la matrice dans la sous-matrice.
            //      Note les dimensions de la matrice doivent correspondre à celle de
            //      la sous-matrice.
            return *this;
        }

        /**
         * Accesseur aux entrées de la sous-matrice (lecture seule)
         *
         * Note : il faut s'assurer que les indices respectent la taille de la
         * sous-matrice
         */
        _Scalar operator()(int i, int j) const
        {
            // TODO implémenter
            return 0.0;
        }

        /**
         * Accesseur aux entrées de la sous-matrice (lecture et écriture)
         *
         * Note : il faut s'assurer que les indices respectent la taille de la
         * sous-matrice
         */
        _Scalar& operator()(int i, int j)
        {
            // TODO implémenter
            _Scalar x = 0.0;
            return x;
        }

        /**
         * Retourne la transposée de la sous-matrice sous la forme d'une matrice.
         */
        template<typename _OtherScalar, int _OtherRows, int _OtherCols, int _OtherStorage>
        Matrix<_OtherScalar, _OtherRows, _OtherCols, _OtherStorage> transpose() const
        {
            // TODO implémenter
            return Matrix<_OtherScalar, _OtherRows, _OtherCols, _OtherStorage>();
        }

		/**
		 * Operateur += 
		 */
        template <int _OtherRows, int _OtherCols, int _OtherStorageType>
        SubMatrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType>& operator+=(const Matrix<_Scalar, _OtherRows, _OtherCols, _OtherStorageType>& rhs)
        {
        	// TODO mettre à jour les valeurs dans la matrice originale en ajoutant @a rhs.
            return *this;
        }

		/**
		 * Operateur de conversion - matrice. Retourne la sous-matrice sous la forme d'une matrice.
		 */
        template <int _OtherRows, int _OtherCols, int _OtherStorageType>
        operator Matrix< _Scalar, _OtherRows, _OtherCols, _OtherStorageType>()
        {
        	// TODO implémenter
        }

        inline int rows() const { return m_rows; }
        inline int cols() const { return m_cols; }

    };

}
