/*
 * Copyright (C) 2015 Fondazione Istituto Italiano di Tecnologia
 * Authors: Silvio Traversaro
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef IDYNTREE_SPATIAL_INERTIA_RAW_H
#define IDYNTREE_SPATIAL_INERTIA_RAW_H

#include "RotationalInertiaRaw.h"

namespace iDynTree
{
    class PositionRaw;
    class SpatialForceVector;
    class SpatialMotionVector;

    /**
     * Class providing the raw coordinates for a spatial inertia, i.e.
     * a spatial dyadic mapping the motion space to the force space.
     *
     * \ingroup iDynTreeCore
     *
     * \note in iDynTree, the spatial vector follows this serialization: the first three elements are
     *       the linear part and the second three elements are the angular part.
     */
    class SpatialInertiaRaw
    {
    private:
        double m_mass; /** mass */
        double m_mcom[3]; /** first moment of mass (i.e. mass * center of mass */
        RotationalInertiaRaw m_rotInertia; /** rotational inertia */

    public:
        SpatialInertiaRaw();

        /**
         * @param mass mass of the rigid body
         * @param com center of mass of the rigid body, expressed in the frame
         *            in which the spatial inertia is expressed
         * @param rotInertia rotational inertia expressed with respect to the origin of the frame.
         *
         * \warning the KDL::RigidBodyInertia class has a similar constructor, but in that one
         *          the rotational inerta in input is expressed in the center of mass of the body.
         */
        SpatialInertiaRaw(const double mass, const PositionRaw & com, const RotationalInertiaRaw & rotInertia);
        SpatialInertiaRaw(const SpatialInertiaRaw & other);
        virtual ~SpatialInertiaRaw();

        /** multiplication operator
         *
         * overloading happens on proper classes
         *
         */


        /**
         * Getter functions
         *
         * \note for preserving consistency, no setters are implemented..
         *       if you want to modify a spatial inertia create a new one,
         *       and assign it to the spatial inertia that you want modify.
         *       Given that no memory allocation happens it should be still
         *       efficient.
         */
        double getMass() const;
        PositionRaw getCenterOfMass() const;
        RotationalInertiaRaw getRotationalInertiaWrtFrameOrigin() const;
        RotationalInertiaRaw getRotationalInertiaWrtCenterOfMass() const;

        /**
         * Multiplication function
         *
         */
        SpatialForceVector multiply(const SpatialMotionVector & op) const;

        /** reset to zero (i.e. the inertia of body with zero pass) the SpatialInertia */
        void zero();
    };
}

#endif /* IDYNTREE_SPATIAL_FORCE_RAW_H */