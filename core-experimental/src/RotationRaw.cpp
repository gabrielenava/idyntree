/*
 * Copyright (C) 2015 Fondazione Istituto Italiano di Tecnologia
 * Authors: Silvio Traversaro
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include "RotationRaw.h"
#include "PositionRaw.h"
#include "SpatialMotionVector.h"
#include "SpatialForceVector.h"
#include "Utils.h"
#include <sstream>

#include <Eigen/Dense>
#include <Eigen/Geometry>

typedef Eigen::Matrix<double,3,3,Eigen::RowMajor> Matrix3dRowMajor;
typedef Eigen::Matrix<double,6,1> Vector6d;


namespace iDynTree
{
    RotationRaw::RotationRaw()
    {
        Eigen::Map<Matrix3dRowMajor> thisData(this->m_data);

        thisData.setIdentity();
    }

    RotationRaw::RotationRaw(double xx, double xy, double xz,
                             double yx, double yy, double yz,
                             double zx, double zy, double zz)
    {
        this->m_data[0] = xx;
        this->m_data[1] = xy;
        this->m_data[2] = xz;
        this->m_data[3] = yx;
        this->m_data[4] = yy;
        this->m_data[5] = yz;
        this->m_data[6] = zx;
        this->m_data[7] = zy;
        this->m_data[8] = zz;
    }


    RotationRaw::RotationRaw(const RotationRaw& other)
    {
        Eigen::Map<Matrix3dRowMajor> thisData(this->m_data);
        Eigen::Map<const Matrix3dRowMajor> otherData(other.m_data);

        thisData = otherData;
    }

    RotationRaw::~RotationRaw()
    {

    }

    const RotationRaw& RotationRaw::changeOrientFrame(const RotationRaw& newOrientFrame)
    {
        Eigen::Map<Matrix3dRowMajor> thisData(this->m_data);
        Eigen::Map<Matrix3dRowMajor> newOrientFrameData(this->m_data);

        thisData = thisData*newOrientFrameData;

        return *this;
    }

    const RotationRaw& RotationRaw::changeRefOrientFrame(const RotationRaw& newRefOrientFrame)
    {
        Eigen::Map<Matrix3dRowMajor> thisData(this->m_data);
        Eigen::Map<Matrix3dRowMajor> newRefOrientFrameData(this->m_data);

        thisData = newRefOrientFrameData*thisData;

        return *this;
    }

    RotationRaw RotationRaw::compose(const RotationRaw& op1, const RotationRaw& op2)
    {
        RotationRaw result;

        Eigen::Map<const Matrix3dRowMajor> op1Data(op1.m_data);
        Eigen::Map<const Matrix3dRowMajor> op2Data(op2.m_data);
        Eigen::Map<Matrix3dRowMajor> resultData(result.m_data);

        resultData = op1Data*op2Data;

        return result;
    }

    RotationRaw RotationRaw::inverse2(const RotationRaw& orient)
    {
        RotationRaw result;

        Eigen::Map<const Matrix3dRowMajor> orientData(orient.m_data);
        Eigen::Map<Matrix3dRowMajor> resultData(result.m_data);

        resultData = orientData.transpose();

        return result;
    }

    PositionRaw RotationRaw::changeCoordFrameOf(const PositionRaw & other) const
    {
        PositionRaw result;

        Eigen::Map<const Matrix3dRowMajor> newCoordFrame(m_data);
        Eigen::Map<const Eigen::Vector3d> positionCoord(other.data());
        Eigen::Map<Eigen::Vector3d> resultData(result.data());

        resultData = newCoordFrame*positionCoord;

        return result;
    }

    SpatialMotionVector RotationRaw::changeCoordFrameOf(const SpatialMotionVector& other) const
    {
        SpatialMotionVector result;

        Eigen::Map<const Matrix3dRowMajor> op1Rot(this->data());
        Eigen::Map<const Vector6d> op2Twist(other.data());

        Eigen::Map<Vector6d> resTwist(result.data());

        resTwist.segment<3>(3) =  op1Rot*(op2Twist.segment<3>(3));
        resTwist.segment<3>(0) =  op1Rot*(op2Twist.segment<3>(0));

        return result;
    }

    SpatialForceVector RotationRaw::changeCoordFrameOf(const SpatialForceVector& other) const
    {
        SpatialForceVector result;

        Eigen::Map<const Matrix3dRowMajor> op1Rot(this->data());
        Eigen::Map<const Vector6d> op2Wrench(other.data());

        Eigen::Map<Vector6d> resWrench(result.data());

        resWrench.segment<3>(3) =  op1Rot*(op2Wrench.segment<3>(3));
        resWrench.segment<3>(0) =  op1Rot*(op2Wrench.segment<3>(0));

        return result;
    }


    RotationRaw RotationRaw::RotX(const double angle)
    {
        RotationRaw result;
        Eigen::Map<Matrix3dRowMajor> thisData(result.data());
        thisData = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitX()).matrix();

        return result;
    }

    RotationRaw RotationRaw::RotY(const double angle)
    {
        RotationRaw result;
        Eigen::Map<Matrix3dRowMajor> thisData(result.data());
        thisData = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitY()).matrix();

        return result;
    }

    RotationRaw RotationRaw::RotZ(const double angle)
    {
        RotationRaw result;
        Eigen::Map<Matrix3dRowMajor> thisData(result.data());
        thisData = Eigen::AngleAxisd(angle, Eigen::Vector3d::UnitZ()).matrix();

        return result;
    }

    RotationRaw RotationRaw::RPY(const double roll, const double pitch, const double yaw)
    {
        return compose(RotX(roll), compose(RotY(pitch), RotZ(yaw)));
    }

    RotationRaw RotationRaw::Identity()
    {
        return RotationRaw();
    }


    std::string RotationRaw::toString() const
    {
        std::stringstream ss;

        ss << this->m_data[0]
        << " " << this->m_data[1]
        << " " << this->m_data[2] << std::endl;
        ss << this->m_data[3]
        << " " << this->m_data[4]
        << " " << this->m_data[5] << std::endl;
        ss << this->m_data[6]
        << " " << this->m_data[7]
        << " " << this->m_data[8] << std::endl;

        return ss.str();
    }

    std::string RotationRaw::reservedToString() const
    {
        return this->toString();
    }


}