
    /**
     * @file NRE_FixedCamera.hpp
     * @brief Declaration of Engine's Camera's Object : FixedCamera
     * @author Louis ABEL
     * @version 1.0
     */

    #pragma once

    #include "../../Generic/NRE_Type.hpp"
    #include "../../Maths/NRE_Maths.hpp"

    /**
     * @namespace NRE
     * @brief The global NearlyRealEngine's namespace
     */
    namespace NRE {
        /**
         * @namespace Camera
         * @brief Engine's Camera Module
         */
        namespace Camera {

            /**
             * @class FixedCamera
             * @brief Camera's Object : A basic fixed camera
             */
            class FixedCamera {
                private:
                    Maths::Point3D<NREfloat> eye;
                    Maths::Point3D<NREfloat> center;
                    Maths::Vector3D<NREfloat> up;
                    Maths::Vector3D<NREfloat> forward;
                    Maths::Vector3D<NREfloat> left;
                    Maths::Vector2D<NREfloat> angle;

                public:
                    //## Constructor ##//
                    FixedCamera();
                    FixedCamera(Maths::Point3D<NREfloat> const& eye, Maths::Point3D<NREfloat> const& center, Maths::Vector2D<NREfloat> const& angle, bool const& calculate = false);
                    FixedCamera(Maths::Point3D<NREfloat> const& eye, Maths::Point3D<NREfloat> const& center, Maths::Vector2D<NREfloat> const& angle,
                                Maths::Vector3D<NREfloat> const& up, Maths::Vector3D<NREfloat> const& forward, Maths::Vector3D<NREfloat> const& left);

                    //## Copy-Constructor ##//
                    FixedCamera(FixedCamera const& camera);

                    //## Convertor ##//

                    //## Deconstructor ##//
                    virtual ~FixedCamera();

                    //## Getter ##//
                    virtual Maths::Point3D<NREfloat> const& getEye() const;
                    virtual Maths::Point3D<NREfloat> const& getCenter() const;
                    virtual Maths::Vector3D<NREfloat> const& getUp() const;
                    virtual Maths::Vector3D<NREfloat> const& getForward() const;
                    virtual Maths::Vector3D<NREfloat> const& getLeft() const;
                    virtual Maths::Vector2D<NREfloat> const& getAngle() const;

                    //## Setter ##//
                    virtual void setEye(Maths::Point3D<NREfloat> const& p);
                    virtual void setCenter(Maths::Point3D<NREfloat> const& p);
                    virtual void setUp(Maths::Vector3D<NREfloat> const& u);
                    virtual void setForward(Maths::Vector3D<NREfloat> const& u);
                    virtual void setLeft(Maths::Vector3D<NREfloat> const& u);
                    virtual void setAngle(Maths::Vector2D<NREfloat> const& u);

                    //## Methods ##//
                    virtual void setView(Maths::Matrix4x4<NREfloat>& modelview) const;
                    virtual void calculateVector();

                    //## Access Operator ##//

                    //## Assignment Operator ##//

                    //## Shortcut Operator ##//

                    //## Arithmetic Operator ##//

                    //## Comparison Operator ##//

                    //## BitWise Operator ##//

                    //## Shift Operator ##//

                private:
                    static NREfloat MAX_PHI;
                    static NREfloat MIN_PHI;
            };

        };
    };