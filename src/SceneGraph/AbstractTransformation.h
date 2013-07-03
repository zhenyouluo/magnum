#ifndef Magnum_SceneGraph_AbstractTransformation_h
#define Magnum_SceneGraph_AbstractTransformation_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013 Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
 * @brief Class Magnum::SceneGraph::AbstractBasicTransformation, enum Magnum::SceneGraph::TransformationType, typedef Magnum::SceneGraph::AbstractTransformation2D, Magnum::SceneGraph::AbstractTransformation3D
 */

#include <vector>

#include "DimensionTraits.h"
#include "SceneGraph.h"

#include "SceneGraph/magnumSceneGraphVisibility.h"

namespace Magnum { namespace SceneGraph {

/**
@brief Base for transformations

Provides transformation implementation for Object instances. See @ref scenegraph
for introduction.

@section AbstractTransformation-subclassing Subclassing

When subclassing, you have to:

- Implement all members listed in **Subclass implementation** group above
- Provide implicit (parameterless) constructor

@see @ref AbstractTransformation2D, @ref AbstractTransformation3D,
    @ref scenegraph
*/
template<UnsignedInt dimensions, class T> class MAGNUM_SCENEGRAPH_EXPORT AbstractBasicTransformation {
    public:
        /** @brief Underlying floating-point type */
        typedef T Type;

        /** @brief Dimension count */
        static const UnsignedInt Dimensions = dimensions;

        explicit AbstractBasicTransformation();
        virtual ~AbstractBasicTransformation() = 0;

        #ifdef DOXYGEN_GENERATING_OUTPUT
        /**
         * @{ @name Subclass implementation
         *
         * These members must be defined by the implementation.
         */

        /**
         * @todo Common way to call setClean() on the object after setting
         *      transformation & disallowing transformation setting on scene,
         *      so the implementer doesn't forget to do it? It could also
         *      allow to hide Object::isScene() from unwanted publicity.
         */

        /**
         * @brief Transformation data type
         *
         * The type must satisfy the following requirements:
         *
         * - Default constructor must create identity transformation
         *
         * Defined in subclasses.
         */
        typedef U DataType;

        /**
         * @brief Convert transformation to matrix
         *
         * Defined in subclasses.
         */
        static typename DimensionTraits<dimensions, T>::MatrixType toMatrix(const DataType& transformation);

        /**
         * @brief Convert transformation from matrix
         *
         * Defined in subclasses.
         */
        static DataType fromMatrix(const typename DimensionTraits<dimensions, T>::MatrixType& matrix);

        /**
         * @brief Compose transformations
         *
         * Defined in subclasses.
         */
        static DataType compose(const DataType& parent, const DataType& child);

        /**
         * @brief Inverted transformation
         *
         * Defined in subclasses.
         */
        static DataType inverted(const DataType& transformation);

        /**
         * @brief %Object transformation
         *
         * Relative to parent. Defined in subclasses.
         */
        DataType transformation() const;

        /**
         * @brief Absolute transformation
         *
         * Relative to root object. Defined in subclasses.
         */
        DataType absoluteTransformation() const;

        /*@}*/
        #endif

        /**
         * @brief Reset object transformation
         * @return Pointer to self (for method chaining)
         */
        AbstractBasicTransformation<dimensions, T>* resetTransformation() {
            doResetTransformation();
            return this;
        }

    #ifdef DOXYGEN_GENERATING_OUTPUT
    protected:
    #else
    private:
    #endif
        /** @brief Polymorphic implementation for resetTransformation() */
        virtual void doResetTransformation() = 0;
};

/** @brief Transformation type */
enum class TransformationType: UnsignedByte {
    /** Global transformation, applied after all other transformations. */
    Global = 0x00,

    /** Local transformation, applied before all other transformations. */
    Local = 0x01
};

/**
@brief Base transformation for two-dimensional float scenes

@see @ref AbstractTransformation3D
*/
typedef AbstractBasicTransformation<2, Float> AbstractTransformation2D;

/**
@brief Base transformation for three-dimensional float scenes

@see @ref AbstractTransformation2D
*/
typedef AbstractBasicTransformation<3, Float> AbstractTransformation3D;

}}

#endif
