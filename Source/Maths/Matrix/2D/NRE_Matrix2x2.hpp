
    /**
     * @file NRE_Matrix2x2.hpp
     * @brief Declaration of Engine's Maths's Object : Matrix2x2
     * @author Louis ABEL
     * @version 1.0
     */

    #pragma once

    #include "../../../Generic/NRE_Type.hpp"

    /**
     * @namespace NRE
     * @brief The global NearlyRealEngine's namespace
     */
    namespace NRE {
        /**
         * @namespace Maths
         * @brief Engine's Mathematicals Module
         */
        namespace Maths {

            template<class> class Point2D;
            template<class> class Vector2D;

            /**
             * @class Matrix2x2
             * @brief Maths's Objects : 2x2 Generic Matrix
             */
             template <class T>
            class Matrix2x2 {
                private:
                    Vector2D<T> data[2];   /**< Matrix's data */

                public:
                    //## Constructor ##//
                         /**
                          * @brief Constructor
                          * Default constructor, iniatlize a 2x2 identity matrix
                          */
                        Matrix2x2();
                        Matrix2x2(T const& a, T const& b,
                                  T const& c, T const& d);
                        Matrix2x2(T const& value);
                        Matrix2x2(Vector2D<T> const& l1, Vector2D<T> const& l2);
                        Matrix2x2(Point2D<T> const& l1, Point2D<T> const& l2);

                    //## Copy-Constructor ##//
                        Matrix2x2(Matrix2x2 const& m);

                    //## Move-Constructor ##//
                        Matrix2x2(Matrix2x2 && m);

                    //## Convertor ##//
                        /**
                         * @brief Convertor
                         * Convert a 2x2 generic-type matrix into a 2x2 T matrix
                         * @param m : Matrix2x2<K>, the matrix to convert
                         */
                        template <class K>
                        Matrix2x2(Matrix2x2<K> const& m);

                    //## Deconstructor ##//
                        /**
                         * @brief Deconstructor
                         * Deconstruct a 2x2 matrix
                         */
                        ~Matrix2x2();

                    //## Getter ##//
                        /**
                         * @brief First line getter
                         * Return the matrix's first line as a 2D vector
                         * @return Vector2D<T>, the matrix's first line
                         */
                        Vector2D<T> const& getL1() const;
                        /**
                         * @brief Second line getter
                         * Return the matrix's second line as a 2D vector
                         * @return Vector2D<T>, the matrix's second line
                         */
                        Vector2D<T> const& getL2() const;
                        /**
                         * @brief First column getter
                         * Return the matrix's first column as a 2D vector
                         * @return Vector2D<T>, the matrix's first column
                         */
                        Vector2D<T> getC1() const;
                        /**
                         * @brief Second column getter
                         * Return the matrix's second column as a 2D vector
                         * @return Vector2D<T>, the matrix's second column
                         */
                        Vector2D<T> getC2() const;
                        /**
                         * @brief Determinant getter
                         * Compute the matrix's determinant
                         * @return NREfloat, the computed determinant
                         */
                        NREfloat const getDeterminant() const;

                    //## Setter ##//
                        /**
                         * @brief First line setter
                         * Set the matrix's first line with a 2D generic-type vector
                         * @param l1 : Vector2D<K>, the vector use as first line
                         */
                        template <class K>
                        void setL1(Vector2D<K> const& l1);
                        /**
                         * @brief Second line setter
                         * Set the matrix's second line with a 2D generic-type vector
                         * @param l2 : Vector2D<K>, the vector use as second line
                         */
                        template <class K>
                        void setL2(Vector2D<K> const& l2);
                        /**
                         * @brief First column setter
                         * Set the matrix's first column with a 2D generic-type vector
                         * @param c1 : Vector2D<K>, the vector use as first column
                         */
                        template <class K>
                        void setC1(Vector2D<K> const& c1);
                        /**
                         * @brief Second column setter
                         * Set the matrix's second column with a 2D generic-type vector
                         * @param c2 : Vector2D<K>, the vector use as second column
                         */
                        template <class K>
                        void setC2(Vector2D<K> const& c2);
                        /**
                         * @brief Identity setter
                         * Erase the matrix and transform it into the identity matrix
                         */
                        void setIdentity();

                    //## Methods ##//
                        /**
                         * @brief Transpose the matrix
                         * Transpose the current matrix
                         */
                        void transpose();
                        /**
                         * @brief Inverse the matrix
                         * Inverse the current matrix, set it to identity if the determinant is null
                         */
                        void inverse();
                        void translate(T const& u);
                        void scale(T const& u);
                        const T* const value() const;

                    //## Access Operator ##//
                        /**
                         * @brief Write Access Operator []
                         * Return the index's line from the matrix
                         * @param index : unsigned int, tell which line to return
                         * @return T*, the matrix's line
                         */
                        Vector2D<T>& operator[](unsigned int const& index);
                        /**
                         * @brief Read Access Operator []
                         * Return the index's line from the matrix
                         * @param index : unsigned int, tell which line to return
                         * @return T*, the matrix's line
                         */
                        const Vector2D<T>& operator[](unsigned int const& index) const;

                    //## Assignment Operator ##//
                        Matrix2x2<T>& operator=(Matrix2x2<T> const& m);
                        Matrix2x2<T>& operator=(Matrix2x2<T> && m);

                    //## Shortcut Operator ##//
                        Matrix2x2<T>& operator+=(Matrix2x2<T> const& m);
                        Matrix2x2<T>& operator-=(Matrix2x2<T> const& m);
                        Matrix2x2<T>& operator*=(T const& k);
                        Matrix2x2<T>& operator*=(Matrix2x2<T> const& m);
                        Matrix2x2<T>& operator/=(T const& k);
                        Matrix2x2<T>& operator/=(Matrix2x2<T> const& m);

                    //## Arithmetic Operator ##//
                        Matrix2x2<T> operator+(Matrix2x2<T> const& m) const;
                        Matrix2x2<T> operator-(Matrix2x2<T> const& m) const;
                        Matrix2x2<T> operator*(T const& k) const;
                        Matrix2x2<T> operator*(Matrix2x2<T> const& m) const;
                        Vector2D<T> operator*(Vector2D<T> const& u) const;
                        Matrix2x2<T> operator/(T const& k) const;
                        Matrix2x2<T> operator/(Matrix2x2<T> const& m) const;

                    //## Comparison Operator ##//
                        bool operator==(Matrix2x2<T> const& m) const;
                        bool operator!=(Matrix2x2<T> const& m) const;

                    //## BitWise Operator ##//

                    //## Shift Operator ##//

                private:
            };

            /**
             * @brief Shift Operator <<
             * Add m to an out stream with : [a b]\n[c d]
             * @param stream : std::ostream, the out stream to add m
             * @param m : Matrix2x2<T>, the matrix to add
             * @return std::ostream, the modified out stream
             */
             template <class T>
             inline std::ostream& operator<<(std::ostream &stream, Matrix2x2<T> const& m) {
                 stream << "[" << m[0][0] << " " << m[0][1] << "]" << '\n';
                 stream << "[" << m[1][0] << " " << m[1][1] << "]";
                 return stream;
             }

        };
    };

    #include "NRE_Matrix2x2.tpp"